#include "DebugUtils.h"
#include "Fen.h"
#include "Move.h"
#include "Movements.h"
#include "PieceMovements.h"
#include "State.h"

#include "cpp_utils/Overloaded.h"

#include <iostream>
#include <ranges>

namespace chss::MoveGeneration {

std::int64_t Perft(const State& state, int depth) {
	if (depth == 0) {
		return 1;
	}

	std::int64_t nodesVisited = 0;
	for (const auto [move, newState] : LegalMoves(state)) {
		const std::int64_t newNodesVisited = Perft(newState, depth - 1);
		if (depth > 10) {
			std::visit(
				Overloaded{
					[newNodesVisited](const Promotion& promotion) -> void {
						const auto fromStr = debug::PositionToString(promotion.from);
						const auto toStr = debug::PositionToString(promotion.to);
						const auto promotionStr = debug::PieceTypeToChar(promotion.type);
						std::cout << fromStr << toStr << promotionStr << ": " << newNodesVisited << std::endl;
					},
					[newNodesVisited](const auto& move) -> void {
						const auto fromStr = debug::PositionToString(move.from);
						const auto toStr = debug::PositionToString(move.to);
						std::cout << fromStr << toStr << ": " << newNodesVisited << std::endl;
					}},
				move);
		}
		nodesVisited += newNodesVisited;
	}

	return nodesVisited;
}

} // namespace chss::MoveGeneration