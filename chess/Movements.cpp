#include "Movements.h"

#include "PieceMovements.h"

#include "representation/Move.h"
#include "representation/State.h"

#include <iostream>
#include <ranges>

namespace chss::MoveGeneration {

State MakeMove(const chss::State& state, const chss::Move& move) {
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

[[nodiscard]] std::generator<Move> PseudoLegalMoves(const chss::State& state) {
	for (const auto from : ForEach(state.board.GetSize())) {
		const auto& pieceOpt = state.board.At(from);
		if (!pieceOpt.has_value()) {
			continue;
		}
		const auto [type, pieceColor] = pieceOpt.value();
		if (pieceColor != state.activeColor) {
			continue;
		}
		switch (type) {
		case PieceType::Pawn: {
			for (const auto to : PseudoLegalMovesPawn(state.board, from)) {
				if (to.y == 0 || to.y == 7) { // promotions
					for (const auto promotionType :
						 {PieceType::Knight, PieceType::Bishop, PieceType::Rook, PieceType::Queen}) {
						co_yield Move{.from = from, .to = to, .promotionType = promotionType};
					}
				} else {
					co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
				}
			}
			if (state.enPassantTargetSquare.has_value()) { // en passant capture
				const auto yForwardOffset = state.activeColor == chss::Color::White ? +1 : -1;
				const auto enPassantTargetSquare = state.enPassantTargetSquare.value();
				const auto enPassantPawnSquare =
					Position{.y = enPassantTargetSquare.y - yForwardOffset, .x = enPassantTargetSquare.x};
				assert(
					(state.board.At(enPassantPawnSquare) ==
					 Piece{.type = PieceType::Pawn, .color = InverseColor(state.activeColor)}));
				if (enPassantTargetSquare == Position{.y = from.y + yForwardOffset, .x = from.x - 1} ||
					enPassantTargetSquare == Position{.y = from.y + yForwardOffset, .x = from.x + 1}) {
					co_yield Move{.from = from, .to = enPassantTargetSquare, .promotionType = std::nullopt};
				}
			}
			break;
		}
		case PieceType::Knight: {
			for (const auto to : PseudoLegalMovesKnight(state.board, from)) {
				co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
			}
			break;
		}
		case PieceType::Bishop: {
			for (const auto to : PseudoLegalMovesBishop(state.board, from)) {
				co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
			}
			break;
		}
		case PieceType::Rook: {
			for (const auto to : PseudoLegalMovesRook(state.board, from)) {
				co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
			}
			break;
		}
		case PieceType::Queen: {
			for (const auto to : PseudoLegalMovesQueen(state.board, from)) {
				co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
			}
			break;
		}
		case PieceType::King: {
			for (const auto to : PseudoLegalMovesKing(state.board, from)) {
				co_yield Move{.from = from, .to = to, .promotionType = std::nullopt};
			}
			// castling
			switch (state.activeColor) {
			case Color::White: {
				const auto& castlingAvailabilities = state.castlingAvailabilities.white;
				if (castlingAvailabilities.isKingSideAvailable) {
					assert((from == Position{.y = 0, .x = 4}));
					assert(state.board.At(Position{.y = 0, .x = 7}).has_value());
					assert(
						(state.board.At(Position{.y = 0, .x = 7}).value() ==
						 Piece{.type = PieceType::Rook, .color = Color::White}));
					bool isInBetweenEmpty = true;
					for (int x = 5; x <= 6; ++x) {
						const auto to = Position{.y = 0, .x = x};
						isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
					}
					bool isInBetweenSafe = !IsInCheck(state.board, state.activeColor);
					for (int x = 5; x <= 6; ++x) {
						const auto to = Position{.y = 0, .x = x};
						auto newBoard = state.board;
						newBoard.At(to) = newBoard.At(from);
						newBoard.At(from) = std::nullopt;
						isInBetweenSafe = isInBetweenSafe && !IsInCheck(newBoard, state.activeColor);
					}
					if (isInBetweenEmpty && isInBetweenSafe) {
						co_yield Move{.from = from, .to = Position{.y = 0, .x = 6}, .promotionType = std::nullopt};
					}
				}
				if (castlingAvailabilities.isQueenSideAvailable) {
					assert((from == Position{.y = 0, .x = 4}));
					assert(
						(state.board.At(Position{.y = 0, .x = 0}).has_value() &&
						 state.board.At(Position{.y = 0, .x = 0}).value() ==
							 Piece{.type = PieceType::Rook, .color = Color::White}));
					bool isInBetweenEmpty = true;
					for (int x = 3; x >= 1; --x) {
						const auto to = Position{.y = 0, .x = x};
						isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
					}
					bool isInBetweenSafe = !IsInCheck(state.board, state.activeColor);
					for (int x = 3; x >= 2; --x) {
						const auto to = Position{.y = 0, .x = x};
						auto newBoard = state.board;
						newBoard.At(to) = newBoard.At(from);
						newBoard.At(from) = std::nullopt;
						isInBetweenSafe = isInBetweenSafe && !IsInCheck(newBoard, state.activeColor);
					}
					if (isInBetweenEmpty && isInBetweenSafe) {
						co_yield Move{.from = from, .to = Position{.y = 0, .x = 2}, .promotionType = std::nullopt};
					}
				}
				break;
			}
			case Color::Black: {
				const auto& castlingAvailabilities = state.castlingAvailabilities.black;
				if (castlingAvailabilities.isKingSideAvailable) {
					assert((from == Position{.y = 7, .x = 4}));
					assert(
						(state.board.At(Position{.y = 7, .x = 7}).has_value() &&
						 state.board.At(Position{.y = 7, .x = 7}).value() ==
							 Piece{.type = PieceType::Rook, .color = Color::Black}));
					bool isInBetweenEmpty = true;
					for (int x = 5; x <= 6; ++x) {
						const auto to = Position{.y = 7, .x = x};
						isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
					}
					bool isInBetweenSafe = !IsInCheck(state.board, state.activeColor);
					for (int x = 5; x <= 6; ++x) {
						const auto to = Position{.y = 7, .x = x};
						auto newBoard = state.board;
						newBoard.At(to) = newBoard.At(from);
						newBoard.At(from) = std::nullopt;
						isInBetweenSafe = isInBetweenSafe && !IsInCheck(newBoard, state.activeColor);
					}
					if (isInBetweenEmpty && isInBetweenSafe) {
						co_yield Move{.from = from, .to = Position{.y = 7, .x = 6}, .promotionType = std::nullopt};
					}
				}
				if (castlingAvailabilities.isQueenSideAvailable) {
					assert((from == Position{.y = 7, .x = 4}));
					assert(
						(state.board.At(Position{.y = 7, .x = 0}).has_value() &&
						 state.board.At(Position{.y = 7, .x = 0}).value() ==
							 Piece{.type = PieceType::Rook, .color = Color::Black}));
					bool isInBetweenEmpty = true;
					for (int x = 3; x >= 1; --x) {
						const auto to = Position{.y = 7, .x = x};
						isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
					}
					bool isInBetweenSafe = !IsInCheck(state.board, state.activeColor);
					for (int x = 3; x >= 2; --x) {
						const auto to = Position{.y = 7, .x = x};
						auto newBoard = state.board;
						newBoard.At(to) = newBoard.At(from);
						newBoard.At(from) = std::nullopt;
						isInBetweenSafe = isInBetweenSafe && !IsInCheck(newBoard, state.activeColor);
					}
					if (isInBetweenEmpty && isInBetweenSafe) {
						co_yield Move{.from = from, .to = Position{.y = 7, .x = 2}, .promotionType = std::nullopt};
					}
				}
				break;
			}
			}
		}
		}
	}
}

[[nodiscard]] bool IsInCheck(const Board& board, const Color color) {
	const auto enemyColor = InverseColor(color);
	const auto kingPosition = [&] {
		for (const auto position : ForEach(board.GetSize())) {
			const auto pieceOpt = board.At(position);
			if (pieceOpt.has_value() && pieceOpt.value() == Piece{.type = PieceType::King, .color = color}) {
				return position;
			}
		}
		assert(false);
	}();
	constexpr auto kBishopOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -1, .deltaX = -1},
		matrix::Direction2D{.deltaY = -1, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		matrix::Direction2D{.deltaY = +1, .deltaX = +1}};
	for (const auto offset : kBishopOffsets) {
		auto to = kingPosition + offset;
		while (board.IsInside(to)) {
			const auto pieceOpt = board.At(to);
			if (pieceOpt.has_value()) {
				if (pieceOpt.value().color == enemyColor &&
					(pieceOpt.value().type == PieceType::Bishop || pieceOpt.value().type == PieceType::Queen)) {
					return true;
				}
				break;
			}
			to += offset;
		}
	}
	constexpr auto kRookOffsets = std::array<matrix::Direction2D, 4>{
		matrix::Direction2D{.deltaY = -1, .deltaX = 0},
		matrix::Direction2D{.deltaY = 0, .deltaX = -1},
		matrix::Direction2D{.deltaY = 0, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = 0}};
	for (const auto offset : kRookOffsets) {
		auto to = kingPosition + offset;
		while (board.IsInside(to)) {
			const auto pieceOpt = board.At(to);
			if (pieceOpt.has_value()) {
				if (pieceOpt.value().color == enemyColor &&
					(pieceOpt.value().type == PieceType::Rook || pieceOpt.value().type == PieceType::Queen)) {
					return true;
				}
				break;
			}
			to += offset;
		}
	}
	constexpr auto kKnightOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -2, .deltaX = -1},
		matrix::Direction2D{.deltaY = -2, .deltaX = +1},
		matrix::Direction2D{.deltaY = -1, .deltaX = -2},
		matrix::Direction2D{.deltaY = -1, .deltaX = +2},
		matrix::Direction2D{.deltaY = +1, .deltaX = -2},
		matrix::Direction2D{.deltaY = +1, .deltaX = +2},
		matrix::Direction2D{.deltaY = +2, .deltaX = -1},
		matrix::Direction2D{.deltaY = +2, .deltaX = +1}};
	for (const auto offset : kKnightOffsets) {
		const auto to = kingPosition + offset;
		if (board.IsInside(to) && board.At(to) == Piece{.type = PieceType::Knight, .color = enemyColor}) {
			return true;
		}
	}
	const auto kPawnOffsets = [&]() {
		const auto yForwardOffset = color == Color::White ? +1 : -1;
		return std::array<matrix::Direction2D, 2>{
			matrix::Direction2D{.deltaY = yForwardOffset, .deltaX = -1},
			matrix::Direction2D{.deltaY = yForwardOffset, .deltaX = +1}};
	}();
	for (const auto offset : kPawnOffsets) {
		const auto to = kingPosition + offset;
		if (board.IsInside(to) && board.At(to) == Piece{.type = PieceType::Pawn, .color = enemyColor}) {
			return true;
		}
	}
	constexpr auto kKingOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -1, .deltaX = -1},
		matrix::Direction2D{.deltaY = -1, .deltaX = 0},
		matrix::Direction2D{.deltaY = -1, .deltaX = +1},
		matrix::Direction2D{.deltaY = 0, .deltaX = -1},
		matrix::Direction2D{.deltaY = 0, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		matrix::Direction2D{.deltaY = +1, .deltaX = +1}};
	for (const auto offset : kKingOffsets) {
		const auto to = kingPosition + offset;
		if (board.IsInside(to) && board.At(to) == Piece{.type = PieceType::King, .color = enemyColor}) {
			return true;
		}
	}
	return false;
}

[[nodiscard]] std::generator<std::pair<Move, State>> LegalMoves(const chss::State& state) {
	for (const auto move : PseudoLegalMoves(state)) {
		const auto newState = MakeMove(state, move);
		if (!IsInCheck(newState.board, state.activeColor)) {
			co_yield std::pair<Move, State>(move, newState);
		}
	}
}

} // namespace chss::MoveGeneration