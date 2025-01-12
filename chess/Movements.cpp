#include "Movements.h"

#include "move_generation/IsInCheck.h"
#include "move_generation/MakeMove.h"
#include "move_generation/PseudoLegalMoves.h"
#include "representation/Move.h"
#include "representation/State.h"

namespace chss::MoveGeneration {

[[nodiscard]] std::generator<std::pair<Move, State>> LegalMoves(const chss::State& state) {
	for (const auto move : move_generation::PseudoLegalMoves(state)) {
		const auto newState = move_generation::MakeMove(state, move);
		const auto kingPosition = move_generation::FindKing(newState.board, state.activeColor);
		if (!move_generation::IsInCheck(newState.board, state.activeColor, kingPosition)) {
			co_yield std::pair<Move, State>(move, newState);
		}
	}
}

} // namespace chss::MoveGeneration