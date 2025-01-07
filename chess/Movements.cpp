#include "Movements.h"

#include "Move.h"
#include "PieceMovements.h"
#include "State.h"

#include <cpp_utils/Overloaded.h>

#include <iostream>
#include <ranges>

namespace chss::MoveGeneration {

State MakeMove(const chss::State& state, const chss::Move& move) {
	return std::visit(
		Overloaded{
			[&state](const NormalMove& normalMove) -> State {
				auto newState = state;
				newState.activeColor = InverseColor(state.activeColor);
				newState.board.At(normalMove.to) = newState.board.At(normalMove.from);
				newState.board.At(normalMove.from) = std::nullopt;
				newState.enPassantTargetSquare = std::nullopt;
				newState.fullmoveNumber = state.fullmoveNumber + 1;
				if (state.enPassantTargetSquare == normalMove.to &&
					state.board.At(normalMove.from).value().type == PieceType::Pawn) {
					newState.board.At(Position{.y = normalMove.from.y, .x = normalMove.to.x}) = std::nullopt;
				} else if (normalMove.to == Position{.y = 0, .x = 0}) {
					newState.castlingAvailabilities.white.isQueenSideAvailable = false;
				} else if (normalMove.to == Position{.y = 0, .x = 7}) {
					newState.castlingAvailabilities.white.isKingSideAvailable = false;
				} else if (normalMove.to == Position{.y = 7, .x = 0}) {
					newState.castlingAvailabilities.black.isQueenSideAvailable = false;
				} else if (normalMove.to == Position{.y = 7, .x = 7}) {
					newState.castlingAvailabilities.black.isKingSideAvailable = false;
				}
				if (normalMove.from == Position{.y = 0, .x = 0}) {
					newState.castlingAvailabilities.white.isQueenSideAvailable = false;
				} else if (normalMove.from == Position{.y = 0, .x = 7}) {
					newState.castlingAvailabilities.white.isKingSideAvailable = false;
				} else if (normalMove.from == Position{.y = 7, .x = 0}) {
					newState.castlingAvailabilities.black.isQueenSideAvailable = false;
				} else if (normalMove.from == Position{.y = 7, .x = 7}) {
					newState.castlingAvailabilities.black.isKingSideAvailable = false;
				} else if (normalMove.from == Position{.y = 0, .x = 4}) {
					newState.castlingAvailabilities.white =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				} else if (normalMove.from == Position{.y = 7, .x = 4}) {
					newState.castlingAvailabilities.black =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				}
				return newState;
			},
			[&state](const TwoSquaresAdvance& twoSquaresAdvance) -> State {
				auto newState = state;
				newState.activeColor = InverseColor(state.activeColor);
				newState.board.At(twoSquaresAdvance.to) = newState.board.At(twoSquaresAdvance.from);
				newState.board.At(twoSquaresAdvance.from) = std::nullopt;
				newState.enPassantTargetSquare = Position{
					.y = (twoSquaresAdvance.from.y + twoSquaresAdvance.to.y) / 2,
					.x = twoSquaresAdvance.from.x};
				newState.fullmoveNumber = state.fullmoveNumber + 1;
				return newState;
			},
			[&state](const Promotion& promotion) -> State {
				auto newState = state;
				newState.activeColor = InverseColor(state.activeColor);
				newState.board.At(promotion.to) = Piece{.type = promotion.type, .color = state.activeColor};
				newState.board.At(promotion.from) = std::nullopt;
				newState.enPassantTargetSquare = std::nullopt;
				newState.fullmoveNumber = state.fullmoveNumber + 1;
				if (promotion.to == Position{.y = 0, .x = 0}) {
					newState.castlingAvailabilities.white.isQueenSideAvailable = false;
				} else if (promotion.to == Position{.y = 0, .x = 7}) {
					newState.castlingAvailabilities.white.isKingSideAvailable = false;
				} else if (promotion.to == Position{.y = 7, .x = 0}) {
					newState.castlingAvailabilities.black.isQueenSideAvailable = false;
				} else if (promotion.to == Position{.y = 7, .x = 7}) {
					newState.castlingAvailabilities.black.isKingSideAvailable = false;
				}
				return newState;
			},
			[&state](const Castling& castling) -> State {
				auto newState = state;
				newState.activeColor = InverseColor(state.activeColor);
				newState.board.At(castling.to) = newState.board.At(castling.from);
				newState.board.At(castling.from) = std::nullopt;
				newState.enPassantTargetSquare = std::nullopt;
				newState.fullmoveNumber = state.fullmoveNumber + 1;
				if (castling.to == Position{.y = 0, .x = 2}) {
					newState.board.At(Position{.y = 0, .x = 3}) = newState.board.At(Position{.y = 0, .x = 0});
					newState.board.At(Position{.y = 0, .x = 0}) = std::nullopt;
					newState.castlingAvailabilities.white =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				} else if (castling.to == Position{.y = 0, .x = 6}) {
					newState.board.At(Position{.y = 0, .x = 5}) = newState.board.At(Position{.y = 0, .x = 7});
					newState.board.At(Position{.y = 0, .x = 7}) = std::nullopt;
					newState.castlingAvailabilities.white =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				} else if (castling.to == Position{.y = 7, .x = 2}) {
					newState.board.At(Position{.y = 7, .x = 3}) = newState.board.At(Position{.y = 7, .x = 0});
					newState.board.At(Position{.y = 7, .x = 0}) = std::nullopt;
					newState.castlingAvailabilities.black =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				} else if (castling.to == Position{.y = 7, .x = 6}) {
					newState.board.At(Position{.y = 7, .x = 5}) = newState.board.At(Position{.y = 7, .x = 7});
					newState.board.At(Position{.y = 7, .x = 7}) = std::nullopt;
					newState.castlingAvailabilities.black =
						CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false};
				} else {
					assert(false);
				}
				return newState;
			}},
		move);
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
						co_yield Promotion{.from = from, .to = to, .type = promotionType};
					}
				} else if ((from.y == 1 && to.y == 3) || (from.y == 6 && to.y == 4)) { // two squares advance
					co_yield TwoSquaresAdvance{.from = from, .to = to};
				} else {
					co_yield NormalMove{.from = from, .to = to};
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
					co_yield NormalMove{.from = from, .to = enPassantTargetSquare};
				}
			}
			break;
		}
		case PieceType::Knight: {
			for (const auto to : PseudoLegalMovesKnight(state.board, from)) {
				co_yield NormalMove{.from = from, .to = to};
			}
			break;
		}
		case PieceType::Bishop: {
			for (const auto to : PseudoLegalMovesBishop(state.board, from)) {
				co_yield NormalMove{.from = from, .to = to};
			}
			break;
		}
		case PieceType::Rook: {
			for (const auto to : PseudoLegalMovesRook(state.board, from)) {
				co_yield NormalMove{.from = from, .to = to};
			}
			break;
		}
		case PieceType::Queen: {
			for (const auto to : PseudoLegalMovesQueen(state.board, from)) {
				co_yield NormalMove{.from = from, .to = to};
			}
			break;
		}
		case PieceType::King: {
			for (const auto to : PseudoLegalMovesKing(state.board, from)) {
				co_yield NormalMove{.from = from, .to = to};
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
						co_yield Castling{.from = from, .to = Position{.y = 0, .x = 6}};
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
						co_yield Castling{.from = from, .to = Position{.y = 0, .x = 2}};
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
						co_yield Castling{.from = from, .to = Position{.y = 7, .x = 6}};
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
						co_yield Castling{.from = from, .to = Position{.y = 7, .x = 2}};
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