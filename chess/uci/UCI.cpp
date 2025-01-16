#include "UCI.h"

#include "chess/DebugUtils.h"
#include "chess/fen/Fen.h"
#include "chess/MinMax.h"
#include "chess/move_generation/MakeMove.h"
#include "chess/Perft.h"
#include "chess/representation/Move.h"
#include "chess/representation/State.h"

#include <concurrency/TaskQueue.h>
#include <concurrency/ThreadSafeQueue.h>
#include <cpp_utils/Overloaded.h>

#include <atomic>
#include <iostream>
#include <string>
#include <vector>

namespace {

std::vector<std::string> SplitInTokens(const std::string& input) {
	auto tokens = std::vector<std::string>();
	auto ss = std::stringstream(input);
	auto token = std::string();
	while (ss >> std::skipws >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

std::string PromotionToString(const std::optional<chss::PieceType>& promotionType) {
	auto result = std::string();
	if (promotionType.has_value()) {
		result.push_back(chss::debug::PieceTypeToChar(promotionType.value()));
	}
	return result;
}

chss::Position ParsePosition(const std::string_view& input) {
	const auto x = input[0] - 'a';
	const auto y = input[1] - '1';
	return chss::Position{.x = x, .y = y};
}

std::optional<chss::PieceType> ParsePromotion(const std::string_view& input) {
	if (input.empty()) {
		return std::nullopt;
	}
	switch (input[0]) {
	case 'q':
		return chss::PieceType::Queen;
	case 'r':
		return chss::PieceType::Rook;
	case 'b':
		return chss::PieceType::Bishop;
	case 'n':
		return chss::PieceType::Knight;
	default:
		assert(false);
	}
}

chss::Move ParseMove(const std::string_view& input) {
	const auto fromStr = std::string_view(input.substr(0, 2));
	const auto from = ParsePosition(fromStr);
	const auto toStr = std::string_view(input.substr(2, 2));
	const auto to = ParsePosition(toStr);
	const auto promotionTypeStr = std::string_view(input.substr(4));
	const auto promotionType = ParsePromotion(promotionTypeStr);
	return chss::Move{.from = from, .to = to, .promotionType = promotionType};
}

struct Ready {
	chss::State state;
};

struct BestMoveCalculation {
	chss::State state;
	std::atomic_flag stopFlag;
	std::future<std::pair<int, chss::Move>> bestMove;
};

struct PerftCalculation {
	chss::State state;
	std::atomic_flag stopFlag;
	std::future<std::int64_t> nodesVisited;
};

using UciState = std::variant<Ready, BestMoveCalculation, PerftCalculation>;

void UciCommand(const std::vector<std::string>& tokens, std::ostream& out, UciState& uciState) {
	std::visit(
		Overloaded(
			[&out, &uciState](Ready& ready) {
				out << "id name chss\nid author ifrison\nuciok\n" << std::flush;
			},
			[&out, &uciState](BestMoveCalculation& bestMoveCalculation) {
				out << "\"uci\" command is not supported while calculating BestMove.\n" << std::flush;
			},
			[&out, &uciState](PerftCalculation& perftCalculation) {
				out << "\"uci\" command is not supported while calculating Perft.\n" << std::flush;
			}),
		uciState);
}

void PositionCommand(const std::vector<std::string>& tokens, std::ostream& out, UciState& uciState) {
	std::visit(
		Overloaded(
			[&tokens, &out, &uciState](Ready& ready) {
				if (tokens[1] == "startpos") {
					auto newState = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
					if (tokens.size() > 2) {
						assert(tokens[2] == "moves");
						for (size_t i = 3; i < tokens.size(); ++i) {
							const auto move = ParseMove(tokens[i]);
							newState = chss::move_generation::MakeMove(newState, move);
						}
					}
					ready.state = newState;
				} else if (tokens[1] == "fen") {
					assert(tokens.size() >= 8);
					const auto fenString = tokens[2] + " " + tokens[3] + " " + tokens[4] + " " + tokens[5] + " " + tokens[6] + " " + tokens[7];
					auto newState = chss::fen::Parse(fenString);
					if (tokens.size() > 8) {
						assert(tokens[8] == "moves");
						for (size_t i = 9; i < tokens.size(); ++i) {
							const auto move = ParseMove(tokens[i]);
							newState = chss::move_generation::MakeMove(newState, move);
						}
					}
					ready.state = newState;
				} else {
					out << "\"position " << tokens[1] << "\" command is not known.\n" << std::flush;
				}
			},
			[&out, &uciState](BestMoveCalculation& bestMoveCalculation) {
				out << "\"position\" command is not supported while calculating BestMove.\n" << std::flush;
			},
			[&out, &uciState](PerftCalculation& perftCalculation) {
				out << "\"position\" command is not supported while calculating Perft.\n" << std::flush;
			}),
		uciState);
}

void IsReadyCommand(const std::vector<std::string>& tokens, std::ostream& out, UciState& uciState) {
	std::visit(
		Overloaded(
			[&out, &uciState](Ready& ready) {
				out << "readyok\n" << std::flush;
			},
			[&out, &uciState](BestMoveCalculation& bestMoveCalculation) {
				out << "\"isready\" command is not supported while calculating BestMove.\n" << std::flush;
			},
			[&out, &uciState](PerftCalculation & perftCalculation) {
				out << "\"isready\" command is not supported while calculating Perft.\n" << std::flush;
			}),
		uciState);
}

void GoCommand(const std::vector<std::string>& tokens, std::ostream& out, UciState& uciState) {
	return std::visit(
		Overloaded(
			[&tokens, &out, &uciState](Ready& ready) {
				if (tokens[1] == "depth") {
					const auto depth = std::stoi(tokens[2]);
					auto stateTmp = std::move(ready).state;
					auto& bestMoveCalculation = uciState.emplace<BestMoveCalculation>();
					bestMoveCalculation.state = std::move(stateTmp);
					bestMoveCalculation.stopFlag.clear();
					bestMoveCalculation.bestMove =
						std::async([state = bestMoveCalculation.state, &stopFlag = bestMoveCalculation.stopFlag, depth]() {
							return chss::search::ParallelSearchMove(state, depth, stopFlag);
						});
				} else if (tokens[1] == "perft") {
					const auto depth = std::stoi(tokens[2]);
					auto stateTmp = std::move(ready).state;
					auto& perftCalculation = uciState.emplace<PerftCalculation>();
					perftCalculation.state = std::move(stateTmp);
					perftCalculation.stopFlag.clear();
					perftCalculation.nodesVisited =
						std::async([state = perftCalculation.state, &stopFlag = perftCalculation.stopFlag, depth]() {
							return chss::move_generation::ParallelPerft(state, depth, stopFlag);
						});
				} else {
					out << "\"go " << tokens[1] << "\" command is not known.\n" << std::flush;
				}
			},
			[&out, &uciState](BestMoveCalculation& bestMoveCalculation) {
				out << "\"go\" command is not supported while calculating BestMove.\n" << std::flush;
			},
			[&out, &uciState](PerftCalculation & perftCalculation) {
				out << "\"go\" command is not supported while calculating Perft.\n" << std::flush;
			}),
		uciState);
}

void StopCommand(const std::vector<std::string>& tokens, std::ostream& out, UciState& uciState) {
	std::visit(
		Overloaded(
			[&tokens, &out, &uciState](Ready& ready) {
				out << "\"stop\" command is not supported while Ready.\n" << std::flush;
			},
			[&out, &uciState](BestMoveCalculation& bestMoveCalculation) {
				bestMoveCalculation.stopFlag.test_and_set();
				const auto [score, move] = bestMoveCalculation.bestMove.get();
				const auto fromStr = std::string(chss::debug::PositionToString(move.from));
				const auto toStr = std::string(chss::debug::PositionToString(move.to));
				const auto promotionStr = PromotionToString(move.promotionType);
				out << "bestmove " << fromStr << toStr << promotionStr << std::endl;
				auto stateTmp = std::move(bestMoveCalculation).state;
				uciState = Ready{.state = std::move(stateTmp)};
			},
			[&out, &uciState](PerftCalculation& perftCalculation) {
				perftCalculation.stopFlag.test_and_set();
				const auto nodesVisited = perftCalculation.nodesVisited.get();
				out << "nodesVisited " << nodesVisited << " (incomplete)" << std::endl;
				auto stateTmp = std::move(perftCalculation).state;
				uciState = Ready{.state = std::move(stateTmp)};
			}),
		uciState);
}

} // namespace

namespace chss::uci {

void UCI(std::istream& in, std::ostream& out) {
	auto inputQueue = concurrency::ThreadSafeQueue<std::string>();
	auto inputThread = std::thread([&in, &inputQueue]() {
		auto line = std::string();
		while (std::getline(in, line)) {
			if (!line.empty()) {
				inputQueue.Push(std::move(line));
			}
		}
	});

	auto uciState =
		UciState(Ready{.state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")});

	while (true) {
		if (const auto inputOpt = inputQueue.TryPop(); inputOpt.has_value()) {
			const auto& input = inputOpt.value();
			const auto tokens = SplitInTokens(input);
			if (tokens[0] == "uci") {
				UciCommand(tokens, out, uciState);
			} else if (tokens[0] == "isready") {
				IsReadyCommand(tokens, out, uciState);
			} else if (tokens[0] == "position") {
				PositionCommand(tokens, out, uciState);
			} else if (tokens[0] == "go") {
				GoCommand(tokens, out, uciState);
			} else if (tokens[0] == "stop") {
				StopCommand(tokens, out, uciState);
			} else if (tokens[0] == "quit") {
				return;
			}
		}
		std::visit(
			Overloaded(
				[](Ready& ready){
					// Do nothing.
				},
				[&out, &uciState](BestMoveCalculation& bestMoveCalculation){
					if (bestMoveCalculation.bestMove.wait_for(std::chrono::milliseconds(0)) != std::future_status::timeout) {
						const auto [score, move] = bestMoveCalculation.bestMove.get();
						const auto fromStr = std::string(debug::PositionToString(move.from));
						const auto toStr = std::string(debug::PositionToString(move.to));
						const auto promotionStr = PromotionToString(move.promotionType);
						out << "bestmove " << fromStr << toStr << promotionStr << std::endl;
						auto stateTmp = std::move(bestMoveCalculation).state;
						uciState = Ready{.state = std::move(stateTmp)};
					}
				},
				[&out, &uciState](PerftCalculation& perftCalculation) {
					if (perftCalculation.nodesVisited.wait_for(std::chrono::milliseconds(0)) != std::future_status::timeout) {
						const auto nodesVisited = perftCalculation.nodesVisited.get();
						out << "nodesVisited " << nodesVisited << std::endl;
						auto stateTmp = std::move(perftCalculation).state;
						uciState = Ready{.state = std::move(stateTmp)};
					}
				}
			),
		uciState);
	}
}

} // namespace chss::uci
