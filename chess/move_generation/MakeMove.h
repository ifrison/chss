#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace chss::move_generation {

[[nodiscard]] constexpr State MakeMove(const State& state, const Move& move) {
	auto newState = state;

	newState.activeColor = InverseColor(state.activeColor);
	newState.board.At(move.to) = newState.board.At(move.from);
	newState.board.At(move.from) = std::nullopt;
	newState.enPassantTargetSquare = std::nullopt;
	newState.fullmoveNumber = state.fullmoveNumber + 1;

	if (move.promotionType.has_value()) {
		newState.board.At(move.to) = Piece{.type = move.promotionType.value(), .color = state.activeColor};
	} else if (move.from == Position{.y = 0, .x = 0}) {
		newState.castlingAvailabilities.white.isQueenSideAvailable = false;
	} else if (move.from == Position{.y = 0, .x = 7}) {
		newState.castlingAvailabilities.white.isKingSideAvailable = false;
	} else if (move.from == Position{.y = 7, .x = 0}) {
		newState.castlingAvailabilities.black.isQueenSideAvailable = false;
	} else if (move.from == Position{.y = 7, .x = 7}) {
		newState.castlingAvailabilities.black.isKingSideAvailable = false;
	} else if (move.from == Position{.y = 0, .x = 4} && state.board.At(move.from).value().type == PieceType::King) {
		newState.castlingAvailabilities.white = CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
		if (move.to == Position{.y = 0, .x = 2}) {
			newState.board.At(Position{.y = 0, .x = 3}) = newState.board.At(Position{.y = 0, .x = 0});
			newState.board.At(Position{.y = 0, .x = 0}) = std::nullopt;
		} else if (move.to == Position{.y = 0, .x = 6}) {
			newState.board.At(Position{.y = 0, .x = 5}) = newState.board.At(Position{.y = 0, .x = 7});
			newState.board.At(Position{.y = 0, .x = 7}) = std::nullopt;
		}
	} else if (move.from == Position{.y = 7, .x = 4} && state.board.At(move.from).value().type == PieceType::King) {
		newState.castlingAvailabilities.black = CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
		if (move.to == Position{.y = 7, .x = 2}) {
			newState.board.At(Position{.y = 7, .x = 3}) = newState.board.At(Position{.y = 7, .x = 0});
			newState.board.At(Position{.y = 7, .x = 0}) = std::nullopt;
		} else if (move.to == Position{.y = 7, .x = 6}) {
			newState.board.At(Position{.y = 7, .x = 5}) = newState.board.At(Position{.y = 7, .x = 7});
			newState.board.At(Position{.y = 7, .x = 7}) = std::nullopt;
		}
	} else if (move.from.y == 1 && move.to.y == 3 && state.board.At(move.from).value().type == PieceType::Pawn) {
		newState.enPassantTargetSquare = Position{.y = 2, .x = move.from.x};
	} else if (move.from.y == 6 && move.to.y == 4 && state.board.At(move.from).value().type == PieceType::Pawn) {
		newState.enPassantTargetSquare = Position{.y = 5, .x = move.from.x};
	}

	if (move.to == Position{.y = 0, .x = 0}) {
		newState.castlingAvailabilities.white.isQueenSideAvailable = false;
	} else if (move.to == Position{.y = 0, .x = 7}) {
		newState.castlingAvailabilities.white.isKingSideAvailable = false;
	} else if (move.to == Position{.y = 7, .x = 0}) {
		newState.castlingAvailabilities.black.isQueenSideAvailable = false;
	} else if (move.to == Position{.y = 7, .x = 7}) {
		newState.castlingAvailabilities.black.isKingSideAvailable = false;
	} else if (move.to == state.enPassantTargetSquare && state.board.At(move.from).value().type == PieceType::Pawn) {
		newState.board.At(Position{.y = move.from.y, .x = move.to.x}) = std::nullopt;
	}

	return newState;
}

} // namespace chss::move_generation
