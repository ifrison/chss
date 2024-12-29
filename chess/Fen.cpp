#include "Fen.h"

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

constexpr void SerializeBoard(std::ostream& out, const chss::Board& board) {
	for (int y = 7; y >= 0; --y) {
		int emptyConsecutive = 0;
		for (int x = 0; x < 8; ++x) {
			const auto piece = board.At(chss::Position{.y = y, .x = x});
			if (!piece.has_value()) {
				++emptyConsecutive;
			} else {
				if (emptyConsecutive > 0) {
					out << emptyConsecutive;
					emptyConsecutive = 0;
				}
				out << PieceToChar(piece.value());
			}
		}
		if (emptyConsecutive > 0) {
			out << emptyConsecutive;
		}
		if (y > 0) {
			out << '/';
		}
	}
}

constexpr void SerializeActiveColor(std::ostream& out, chss::Color activeColor) {
	out << (activeColor == chss::Color::White ? 'w' : 'b');
}

constexpr void SerializeCastlingAvailabilities(
	std::ostream& out,
	const chss::CastlingAvailabilities& castlingAvailabilities) {
	bool anyOutput = false;
	if (castlingAvailabilities.white.isKingSideAvailable) {
		out << 'K';
		anyOutput = true;
	}
	if (castlingAvailabilities.white.isQueenSideAvailable) {
		out << 'Q';
		anyOutput = true;
	}
	if (castlingAvailabilities.black.isKingSideAvailable) {
		out << 'k';
		anyOutput = true;
	}
	if (castlingAvailabilities.black.isQueenSideAvailable) {
		out << 'q';
		anyOutput = true;
	}
	if (!anyOutput) {
		out << '-';
	}
}

constexpr void SerializeEnPassantTargetSquare(
	std::ostream& out,
	const std::optional<chss::Position>& enPassantTargetSquare) {
	if (!enPassantTargetSquare.has_value()) {
		out << '-';
	} else {
		const auto& position = enPassantTargetSquare.value();
		out << static_cast<char>('a' + position.x) << static_cast<char>('1' + position.y);
	}
}

} // namespace

namespace chss::fen {

std::string Serialize(const State& state) {
	auto ss = std::stringstream();
	SerializeBoard(ss, state.board);
	ss << ' ';
	SerializeActiveColor(ss, state.activeColor);
	ss << ' ';
	SerializeCastlingAvailabilities(ss, state.castlingAvailabilities);
	ss << ' ';
	SerializeEnPassantTargetSquare(ss, state.enPassantTargetSquare);
	ss << ' ';
	ss << state.halfmoveClock;
	ss << ' ';
	ss << state.fullmoveNumber;
	return std::move(ss).str();
}

} // namespace chss::fen
