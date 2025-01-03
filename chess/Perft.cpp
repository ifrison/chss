#include "DebugUtils.h"
#include "Fen.h"
#include "Movements.h"
#include "PieceMovements.h"
#include "State.h"

#include <iostream>
#include <ranges>

namespace chss::MoveGeneration {

std::int64_t Perft(const State& state, int depth) {
	if (depth == 0) {
		return 1;
	}

	std::int64_t nodesVisited = 0;
	for (const auto [move, newState] : LegalMoves(state)) {
		const auto newNodesVisited = Perft(newState, depth - 1);
		if (depth > 10) {
			std::cout << debug::PositionToString(move.from) << debug::PositionToString(move.to) << ": " << newNodesVisited /*<< chss::fen::Serialize(newState)*/ << std::endl;
		}
		nodesVisited += newNodesVisited;
	}

	return nodesVisited;
}

} // namespace chss::MoveGeneration