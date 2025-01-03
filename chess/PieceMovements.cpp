#pragma once

#include "State.h"

#include <generator>

namespace chss::MoveGeneration {

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesPawn(const chss::Board& board,const chss::Position& pawnPosition) {
	const auto pawnPieceOpt = board.At(pawnPosition);
	assert(pawnPieceOpt.has_value());
	const auto [type, color] = pawnPieceOpt.value();
	assert(type == chss::Type::Pawn);
	const auto enemyColor = InverseColor(color);
	const auto yPawnsRow = color == chss::Color::White ? 1 : 6;
	const auto yForwardOffset = color == chss::Color::White ? +1 : -1;
	const auto yDoubleForwardOffset = color == chss::Color::White ? +2 : -2;
	const auto forwardPosition = chss::Position{.y = pawnPosition.y + yForwardOffset, .x = pawnPosition.x};
	if (board.IsInside(forwardPosition) && !board.At(forwardPosition).has_value()) {
		co_yield forwardPosition;
		if (pawnPosition.y == yPawnsRow) {
			const auto doubleForwardPosition =
				chss::Position{.y = pawnPosition.y + yDoubleForwardOffset, .x = pawnPosition.x};
			assert(board.IsInside(doubleForwardPosition));
			if (!board.At(doubleForwardPosition).has_value()) {
				co_yield doubleForwardPosition;
			}
		}
	}
	const auto forwardLeftPosition = chss::Position{.y = pawnPosition.y + yForwardOffset, .x = pawnPosition.x - 1};
	if (board.IsInside(forwardLeftPosition) && board.At(forwardLeftPosition).has_value() &&
		board.At(forwardLeftPosition).value().color == enemyColor) {
		co_yield forwardLeftPosition;
	}
	const auto forwardRightPosition = chss::Position{.y = pawnPosition.y + yForwardOffset, .x = pawnPosition.x + 1};
	if (board.IsInside(forwardRightPosition) && board.At(forwardRightPosition).has_value() &&
		board.At(forwardRightPosition).value().color == enemyColor) {
		co_yield forwardRightPosition;
	}
}

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesKnight(const chss::Board& board,const chss::Position& knightPosition) {
	constexpr auto kOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -2, .deltaX = -1},
		matrix::Direction2D{.deltaY = -2, .deltaX = +1},
		matrix::Direction2D{.deltaY = -1, .deltaX = -2},
		matrix::Direction2D{.deltaY = -1, .deltaX = +2},
		matrix::Direction2D{.deltaY = +1, .deltaX = -2},
		matrix::Direction2D{.deltaY = +1, .deltaX = +2},
		matrix::Direction2D{.deltaY = +2, .deltaX = -1},
		matrix::Direction2D{.deltaY = +2, .deltaX = +1},
	};
	const auto& knightPieceOpt = board.At(knightPosition);
	assert(knightPieceOpt.has_value());
	const auto [type, color] = knightPieceOpt.value();
	assert(type == chss::Type::Knight);
	const auto enemyColor = InverseColor(color);
	for (const auto offset : kOffsets) {
		const auto position = knightPosition + offset;
		if (board.IsInside(position)) {
			const auto& pieceOpt = board.At(position);
			if (!pieceOpt.has_value() || pieceOpt.value().color == enemyColor) {
				co_yield position;
			}
		}
	}
}

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesBishop(const chss::Board& board,const chss::Position& bishopPosition) {
	constexpr auto kOffsets = std::array<matrix::Direction2D, 4>{
		matrix::Direction2D{.deltaY = -1, .deltaX = -1},
		matrix::Direction2D{.deltaY = -1, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
	};
	const auto& bishopPieceOpt = board.At(bishopPosition);
	assert(bishopPieceOpt.has_value());
	const auto [type, color] = bishopPieceOpt.value();
	assert(type == chss::Type::Bishop);
	const auto enemyColor = InverseColor(color);
	for (const auto offset : kOffsets) {
		auto position = bishopPosition + offset;
		while (board.IsInside(position)) {
			const auto& pieceOpt = board.At(position);
			if (!pieceOpt.has_value()) {
				co_yield position;
			} else if (pieceOpt.value().color == enemyColor) {
				co_yield position;
				break;
			} else {
				break;
			}
			position += offset;
		}
	}
}

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesRook(const chss::Board& board,const chss::Position& rookPosition) {
	constexpr auto kOffsets = std::array<matrix::Direction2D, 4>{
		matrix::Direction2D{.deltaY = -1, .deltaX = 0},
		matrix::Direction2D{.deltaY = 0, .deltaX = -1},
		matrix::Direction2D{.deltaY = 0, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
	};
	const auto& rookPieceOpt = board.At(rookPosition);
	assert(rookPieceOpt.has_value());
	const auto [type, color] = rookPieceOpt.value();
	assert(type == chss::Type::Rook);
	const auto enemyColor = InverseColor(color);
	for (const auto offset : kOffsets) {
		auto position = rookPosition + offset;
		while (board.IsInside(position)) {
			const auto& pieceOpt = board.At(position);
			if (!pieceOpt.has_value()) {
				co_yield position;
			} else if (pieceOpt.value().color == enemyColor) {
				co_yield position;
				break;
			} else {
				break;
			}
			position += offset;
		}
	}
}

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesQueen(const chss::Board& board,const chss::Position& queenPosition) {
	constexpr auto kOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -1, .deltaX = -1},
		matrix::Direction2D{.deltaY = -1, .deltaX = 0},
		matrix::Direction2D{.deltaY = -1, .deltaX = +1},
		matrix::Direction2D{.deltaY = 0, .deltaX = -1},
		matrix::Direction2D{.deltaY = 0, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
	};
	const auto& queenPieceOpt = board.At(queenPosition);
	assert(queenPieceOpt.has_value());
	const auto [type, color] = queenPieceOpt.value();
	assert(type == chss::Type::Queen);
	const auto enemyColor = InverseColor(color);
	for (const auto& offset : kOffsets) {
		auto position = queenPosition + offset;
		while (board.IsInside(position)) {
			const auto& pieceOpt = board.At(position);
			if (!pieceOpt.has_value()) {
				co_yield position;
			} else if (pieceOpt.value().color == enemyColor) {
				co_yield position;
				break;
			} else {
				break;
			}
			position += offset;
		}
	}
}

[[nodiscard]] std::generator<chss::Position> PseudoLegalMovesKing(const chss::Board& board,const chss::Position& kingPosition) {
	constexpr auto kOffsets = std::array<matrix::Direction2D, 8>{
		matrix::Direction2D{.deltaY = -1, .deltaX = -1},
		matrix::Direction2D{.deltaY = -1, .deltaX = 0},
		matrix::Direction2D{.deltaY = -1, .deltaX = +1},
		matrix::Direction2D{.deltaY = 0, .deltaX = -1},
		matrix::Direction2D{.deltaY = 0, .deltaX = +1},
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
	};
	const auto& kingPieceOpt = board.At(kingPosition);
	assert(kingPieceOpt.has_value());
	const auto [type, color] = kingPieceOpt.value();
	assert(type == chss::Type::King);
	const auto enemyColor = InverseColor(color);
	for (const auto offset : kOffsets) {
		const auto position = kingPosition + offset;
		if (board.IsInside(position)) {
			const auto& pieceOpt = board.At(position);
			if (!pieceOpt.has_value() || pieceOpt.value().color == enemyColor) {
				co_yield position;
			}
		}
	}
}

}
