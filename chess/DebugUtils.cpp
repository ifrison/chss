#include "Board.h"
#include "Piece.h"

#include <string>

namespace chss::debug {

char PieceTypeToChar(const chss::PieceType& pieceType) {
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

std::string PositionToString(const Position position) {
	auto result = std::string();
	result.reserve(2);
	result.push_back(static_cast<char>('a' + position.x));
	result.push_back(static_cast<char>('1' + position.y));
	return result;
}

} // namespace chss::debug
