#include "UCI.h"
#include "State.h"
#include "Fen.h"
#include "MinMax.h"
#include "Move.h"
#include "TaskQueue.h"
#include "Movements.h"
#include "DebugUtils.h"
#include "file_utils/FileUtils.h"

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

void Log(const std::string& message) {
	auto logFile = std::ofstream("/Users/inaki.frison/Development/chss/cmake-build-debug/chess/logs.txt", std::ios::out | std::ios::app);
	logFile << message << std::endl;
	logFile.flush();
	logFile.close();
}

}

namespace chss::uci {

void UCI(std::istream& in, std::ostream& out) {
	auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	auto taskQueue = TaskQueue(1);
	auto stop = std::atomic_flag(false);
	auto searchResult = std::future<std::pair<Move, Move>>();

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
			Log("uci version: 8");
			out << "id name chss\n" << "id author ifrison\n" << "uciok\n" << std::flush;
		}
		else if (tokens[0] == "position") {
			if (tokens[1] == "startpos") {
				state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
			}
			else if (tokens[1] == "fen") {
				assert(tokens.size() >= 8);
				const auto fenString = tokens[2] + " " + tokens[3] + " " + tokens[4] + " " + tokens[5] + " " + tokens[6] + " " + tokens[7];
				state = fen::Parse(fenString);
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
				searchResult = taskQueue.PushBack(std::function<std::pair<Move, Move>()>([&stop, state]() {
					const auto neverStop = std::atomic_flag(false);
					auto [bestMove, bestPonderMove] = search::Search(state, 2, neverStop);
					for (int depth = 2; depth < 100; ++depth) {
						if (stop.test()) {
							break;
						}
						const auto [move, ponderMove] = search::Search(state, depth, stop);
						if (!stop.test()) {
							bestMove = move;
							bestPonderMove = ponderMove;
						}
					}
					return std::pair<Move, Move>(bestMove, bestPonderMove);
				}));
				searchResult.wait_for(std::chrono::milliseconds(time));
				stop.test_and_set();
				const auto [move, ponderMove] = searchResult.get();
				out << "bestmove " << debug::PositionToString(move.from) << debug::PositionToString(move.to) << std::endl;
				Log("bestmove " + debug::PositionToString(move.from) + debug::PositionToString(move.to));
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
			const auto [move, ponderMove] = searchResult.get();
			out << "bestmove " << debug::PositionToString(move.from) << debug::PositionToString(move.to) << std::endl << std::flush;
			Log("bestmove " + debug::PositionToString(move.from) + debug::PositionToString(move.to));
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
