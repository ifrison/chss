#pragma once

#include "representation/Board.h"

#include <ostream>

namespace chss::debug {

[[nodiscard]] constexpr char PieceTypeToChar(const chss::PieceType& pieceType) {
	switch (pieceType) {
	case chss::PieceType::Pawn:
		return 'p';
	case chss::PieceType::Knight:
		return 'n';
	case chss::PieceType::Bishop:
		return 'b';
	case chss::PieceType::Rook:
		return 'r';
	case chss::PieceType::Queen:
		return 'q';
	case chss::PieceType::King:
		return 'k';
	default:
		assert(false);
	}
}

[[nodiscard]] constexpr std::string_view PositionToString(const Position position) {
	// clang-format off
	constexpr auto kPositionNames = matrix::Matrix2D<std::string_view, matrix::Size2D{.sizeX = 8, .sizeY = 8}>(
		std::array<std::string_view, 64>{
			"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
			"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
			"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
			"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
			"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
			"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
			"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
			"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
		}
	);
	// clang-format on
	return kPositionNames.At(position);
}

} // namespace chss::debug
