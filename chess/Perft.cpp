#include "DebugUtils.h"
#include "Movements.h"
#include "PieceMovements.h"

#include "fen/Fen.h"
#include "representation/Move.h"
#include "representation/State.h"

#include <iostream>
#include <ranges>

namespace {

std::string PromotionToString(const std::optional<chss::PieceType>& promotionType) {
	auto result = std::string();
	if (promotionType.has_value()) {
		result.push_back(chss::debug::PieceTypeToChar(promotionType.value()));
	}
	return result;
}

}

namespace chss::MoveGeneration {

std::int64_t Perft(const State& state, int depth) {
	if (depth == 0) {
		return 1;
	}

	std::int64_t nodesVisited = 0;
	for (const auto [move, newState] : LegalMoves(state)) {
		const std::int64_t newNodesVisited = Perft(newState, depth - 1);
		if (depth > 10) {
			const auto fromStr = debug::PositionToString(move.from);
			const auto toStr = debug::PositionToString(move.to);
			const auto promotionStr = PromotionToString(move.promotionType);
			std::cout << fromStr << toStr << promotionStr << ": " << newNodesVisited << std::endl;
		}
		nodesVisited += newNodesVisited;
	}

	return nodesVisited;
}

} // namespace chss::MoveGeneration