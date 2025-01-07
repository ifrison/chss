#include "Board.h"

#include <string>

namespace {

constexpr char PieceToChar(const chss::Piece& piece) {
	switch (piece.color) {
	case chss::Color::White:
		switch (piece.type) {
	case chss::PieceType::Pawn:
		return 'P';
	case chss::PieceType::Knight:
		return 'N';
	case chss::PieceType::Bishop:
		return 'B';
	case chss::PieceType::Rook:
		return 'R';
	case chss::PieceType::Queen:
		return 'Q';
	case chss::PieceType::King:
		return 'K';
	default:
		assert(false);
		}
	case chss::Color::Black:
		switch (piece.type) {
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
