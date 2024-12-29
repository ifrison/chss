#pragma once

#include "Board.h"

#include <string>

namespace {

constexpr char PieceToChar(const chss::Piece& piece) {
	switch (piece.color) {
	case chss::Color::White:
		switch (piece.type) {
	case chss::Type::Pawn:
		return 'P';
	case chss::Type::Knight:
		return 'N';
	case chss::Type::Bishop:
		return 'B';
	case chss::Type::Rook:
		return 'R';
	case chss::Type::Queen:
		return 'Q';
	case chss::Type::King:
		return 'K';
	default:
		assert(false);
		}
	case chss::Color::Black:
		switch (piece.type) {
	case chss::Type::Pawn:
		return 'p';
	case chss::Type::Knight:
		return 'n';
	case chss::Type::Bishop:
		return 'b';
	case chss::Type::Rook:
		return 'r';
	case chss::Type::Queen:
		return 'q';
	case chss::Type::King:
		return 'k';
	default:
		assert(false);
		}
	default:
		assert(false);
	}
}

}

namespace chss::debug {

std::string PositionToString(const Position position) {
	auto result = std::string();
	result.reserve(2);
	result.push_back(static_cast<char>('a' + position.x));
	result.push_back(static_cast<char>('1' + position.y));
	return result;
}

void PrintBoard(const chss::Board& board, std::ostream& os) {
	for (int y = 7; y >= 0; --y) {
		os << "  +---+---+---+---+---+---+---+---+\n";
		os << y + 1 << " |";
		for (int x = 0; x < 8; ++x) {
			const auto& pieceOpt = board.At(chss::Position{.y = y, .x = x});
			os << " " << (pieceOpt.has_value() ? PieceToChar(pieceOpt.value()) : ' ') << " |";
		}
		os << "\n";
	}
	os << "  +---+---+---+---+---+---+---+---+\n";
	os << "    a   b   c   d   e   f   g   h  \n";
}

}
