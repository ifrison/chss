#include "UCI.h"
#include "State.h"
#include "Fen.h"
#include "MinMax.h"
#include "Move.h"
#include <concurrency/TaskQueue.h>
#include "Movements.h"
#include "DebugUtils.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

void Log(const std::string& message) {
	const auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	auto logFile = std::ofstream("/Users/inaki.frison/Development/chss/cmake-build-debug/chess/logs.txt", std::ios::out | std::ios::app);
	logFile << std::put_time(std::localtime(&now), "%Y-%m-%d %X") << " " << message << std::endl;
	logFile.flush();
	logFile.close();
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

}

namespace chss::uci {

void UCI(std::istream& in, std::ostream& out) {
	auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	auto taskQueue = concurrency::TaskQueue(1);
	auto stop = std::atomic_flag(false);
	auto searchResult = std::future<std::tuple<Move, Move, int>>();

	auto command = std::string();
	while (getline(in, command)) {
		if (command.empty()) {
			continue;
		}
		Log(command);
		const auto tokens = SplitInTokens(command);
		if (tokens.empty()) {
			continue;
		}
		assert(!tokens.empty());
		if (tokens[0] == "uci") {
			Log("uci version: 9");
			out << "id name chss\n" << "id author ifrison\n" << "uciok\n" << std::flush;
		}
		else if (tokens[0] == "position") {
			if (tokens[1] == "startpos") {
				state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
				if (tokens.size() > 2) {
					assert(tokens[2] == "moves");
					for (size_t i = 3; i < tokens.size(); ++i) {
						const auto move = ParseMove(tokens[i]);
						state = chss::MoveGeneration::MakeMove(state, move);
					}
				}
			}
			else if (tokens[1] == "fen") {
				assert(tokens.size() >= 8);
				const auto fenString = tokens[2] + " " + tokens[3] + " " + tokens[4] + " " + tokens[5] + " " + tokens[6] + " " + tokens[7];
				state = fen::Parse(fenString);
				if (tokens.size() > 8) {
					assert(tokens[8] == "moves");
					for (size_t i = 9; i < tokens.size(); ++i) {
						const auto move = ParseMove(tokens[i]);
						state = chss::MoveGeneration::MakeMove(state, move);
					}
				}
			}
			else {
				Log("Unknown \"position " + tokens[1] + "\" command!");
				//assert(false);
			}
		}
		else if (tokens[0] == "isready") {
			out << "readyok\n" << std::flush;
			Log("readyok");

		}
		else if (tokens[0] == "go") {
			if (tokens[1] == "infinite") {
				Log("\"go infinite\" not supported!");
				//assert(false);
			}
			else if (tokens[1] == "movetime") {
				const auto time = std::stoi(tokens[2]) - 1000;
				stop.clear();
				searchResult = taskQueue.PushBack(std::function<std::tuple<Move, Move, int>()>([&stop, state]() {
					const auto neverStop = std::atomic_flag(false);
					auto [bestMove, bestPonderMove] = search::Search(state, 2, neverStop);
					auto bestDepth = 2;
					for (int depth = 3; depth < 100; ++depth) {
						if (stop.test()) {
							break;
						}
						const auto [move, ponderMove] = search::Search(state, depth, stop);
						if (!stop.test()) {
							bestMove = move;
							bestPonderMove = ponderMove;
							bestDepth = depth;
						}
					}
					return std::tuple<Move, Move, int>(bestMove, bestPonderMove, bestDepth);
				}));
				searchResult.wait_for(std::chrono::milliseconds(time));
				stop.test_and_set();
				const auto [move, ponderMove, depth] = searchResult.get();
				const auto fromStr = debug::PositionToString(move.from);
				const auto toStr = debug::PositionToString(move.to);
				const auto promotionStr = PromotionToString(move.promotionType);
				out << "bestmove " << fromStr << toStr << promotionStr << std::endl;
				Log("bestmove " + fromStr + toStr + promotionStr + " - depth " + std::to_string(depth));
			}
			else if (tokens[1] == "depth") {
				Log("\"depth\" not supported!");
				//assert(false);
			}
			else {
				Log("Unknown \"go " + tokens[1] + "\" command!");
				//assert(false);
			}
		}
		else if (tokens[0] == "stop") {
			stop.test_and_set();
			searchResult.wait();
			const auto [move, ponderMove, depth] = searchResult.get();
			const auto fromStr = debug::PositionToString(move.from);
			const auto toStr = debug::PositionToString(move.to);
			const auto promotionStr = PromotionToString(move.promotionType);
			out << "bestmove " << fromStr << toStr << promotionStr << std::endl;
			Log("bestmove " + fromStr + toStr + promotionStr + " - depth " + std::to_string(depth));
		}
		else if (tokens[0] == "quit") {
			Log("QUIT!");
			return;
		}
		else {
			Log("Unknown \""+ tokens[0] + "\" command!");
			//assert(false);
		}
	}
}

} // namespace chss::uci
