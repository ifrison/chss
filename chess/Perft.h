#pragma once

#include "move_generation/LegalMoves.h"
#include "representation/Move.h"
#include "representation/State.h"

namespace chss::move_generation {

constexpr std::int64_t Perft(const State& state, int depth) {
	if (depth == 0) {
		return 1;
	}
	std::int64_t nodesVisited = 0;
	for (const auto move : LegalMoves(state)) {
		const auto newState = MakeMove(state, move);
		const std::int64_t newNodesVisited = Perft(newState, depth - 1);
		nodesVisited += newNodesVisited;
	}
	return nodesVisited;
}

} // namespace chss::move_generation
