#pragma once

#include "chess/representation/Board.h"

namespace chss::move_generation {

[[nodiscard]] constexpr chss::Position FindKing(const chss::Board& board, const chss::Color color) {
	for (const auto position : ForEach(board.GetSize())) {
		const auto pieceOpt = board.At(position);
		if (pieceOpt.has_value() && pieceOpt.value() == Piece{.type = PieceType::King, .color = color}) {
			return position;
		}
	}
	assert(false);
	return chss::Position{.y = -1, .x = -1};
}

[[nodiscard]] constexpr auto IsInCheck(const Board& board, const Color color, const Position& kingPosition) {
	const auto enemyColor = InverseColor(color);
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

} // namespace chss::move_generation
