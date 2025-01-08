#pragma once

#include <chess/State.h>

#include <array>
#include <string>
#include <string_view>

namespace detail {

constexpr std::array<std::string_view, 6> SplitInput(const std::string_view& input) {
	auto parts = std::array<std::string_view, 6>();
	int partIndex = 0;
	auto partBegin = input.begin() + 0;
	const int inputSize = static_cast<int>(input.size());
	for (int i = 0; i < inputSize; ++i) {
		if (input[i] == ' ') {
			parts[partIndex] = std::string_view(partBegin, input.begin() + i);
			partBegin = input.begin() + i + 1;
			++partIndex;
		}
	}
	parts[partIndex] = std::string_view(partBegin, input.end());
	return parts;
}

constexpr chss::Board ParseBoard(const std::string_view& boardStr) {
	auto board = chss::Board();
	int y = 7;
	int x = 0;
	for (const auto c : boardStr) {
		switch (c) {
		case '/':
			y--;
			x = 0;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			x += c - '0';
			break;
		case 'B':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Bishop, .color = chss::Color::White};
			++x;
			break;
		case 'K':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::King, .color = chss::Color::White};
			++x;
			break;
		case 'N':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Knight, .color = chss::Color::White};
			++x;
			break;
		case 'P':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Pawn, .color = chss::Color::White};
			++x;
			break;
		case 'Q':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Queen, .color = chss::Color::White};
			++x;
			break;
		case 'R':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Rook, .color = chss::Color::White};
			++x;
			break;
		case 'b':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Bishop, .color = chss::Color::Black};
			++x;
			break;
		case 'k':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::King, .color = chss::Color::Black};
			++x;
			break;
		case 'n':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Knight, .color = chss::Color::Black};
			++x;
			break;
		case 'p':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Pawn, .color = chss::Color::Black};
			++x;
			break;
		case 'q':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Queen, .color = chss::Color::Black};
			++x;
			break;
		case 'r':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::PieceType::Rook, .color = chss::Color::Black};
			++x;
			break;
		default:
			assert(false);
		}
	}
	assert(y == 0 && x == 8);
	return board;
}

constexpr chss::Color ParseActiveColor(const std::string_view& activeColorStr) {
	assert(activeColorStr == "w" || activeColorStr == "b");
	return activeColorStr == "w" ? chss::Color::White : chss::Color::Black;
}

constexpr chss::CastlingAvailabilities ParseCastlingAvailabilities(const std::string_view& castlingAvailabilitiesStr) {
	auto castlingAvailabilities = chss::CastlingAvailabilities{
		.white = chss::CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false},
		.black = chss::CastlingAvailability{.isKingSideAvailable = false, .isQueenSideAvailable = false}};
	if (castlingAvailabilitiesStr == "-") {
		return castlingAvailabilities;
	}
	assert(castlingAvailabilitiesStr.size() <= 4);
	for (const auto c : castlingAvailabilitiesStr) {
		switch (c) {
		case 'K':
			castlingAvailabilities.white.isKingSideAvailable = true;
			break;
		case 'Q':
			castlingAvailabilities.white.isQueenSideAvailable = true;
			break;
		case 'k':
			castlingAvailabilities.black.isKingSideAvailable = true;
			break;
		case 'q':
			castlingAvailabilities.black.isQueenSideAvailable = true;
			break;
		default:
			assert(false);
		}
	}
	return castlingAvailabilities;
}

constexpr std::optional<chss::Position> ParseEnPassantTargetSquare(const std::string_view& enPassantTargetSquareStr) {
	if (enPassantTargetSquareStr == "-") {
		return std::nullopt;
	}
	assert(enPassantTargetSquareStr.size() == 2);
	assert('a' <= enPassantTargetSquareStr[0] && enPassantTargetSquareStr[0] <= 'h');
	assert('1' <= enPassantTargetSquareStr[1] && enPassantTargetSquareStr[1] <= '8');
	const int x = enPassantTargetSquareStr[0] - 'a';
	const int y = enPassantTargetSquareStr[1] - '1';
	return chss::Position{.y = y, .x = x};
}

constexpr int ParseInteger(std::string_view integerStr) {
	assert(!integerStr.empty());
	bool isNegative = false;
	std::size_t idx = 0;
	if (integerStr[0] == '+') {
		idx = 1;
	} else if (integerStr[0] == '-') {
		isNegative = true;
		idx = 1;
	}
	int result = 0;
	for (; idx < integerStr.size(); ++idx) {
		const char c = integerStr[idx];
		result = result * 10 + (c - '0');
	}
	return isNegative ? -result : result;
}

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

constexpr char* SerializeInteger(char* out, int integer) {
	if (integer < 0) {
		*out = '-';
		++out;
		integer = -integer;
	}
	if (integer == 0) {
		*out = '0';
		++out;
		return out;
	}
	int closestPow10 = 1;
	while (integer >= closestPow10) {
		closestPow10 *= 10;
	}
	closestPow10 /= 10;
	while (closestPow10 > 0) {
		const int quotient = integer / closestPow10;
		const int remainder = integer % closestPow10;
		*out = static_cast<char>('0' + quotient);
		++out;
		integer = remainder;
		closestPow10 /= 10;
	}
	return out;
}

constexpr char* SerializeBoard(char* out, const chss::Board& board) {
	for (int y = 7; y >= 0; --y) {
		int emptyConsecutive = 0;
		for (int x = 0; x < 8; ++x) {
			const auto piece = board.At(chss::Position{.y = y, .x = x});
			if (!piece.has_value()) {
				++emptyConsecutive;
			} else {
				if (emptyConsecutive > 0) {
					*out = static_cast<char>('0' + emptyConsecutive);
					++out;
					emptyConsecutive = 0;
				}
				*out = PieceToChar(piece.value());
				++out;
			}
		}
		if (emptyConsecutive > 0) {
			*out = static_cast<char>('0' + emptyConsecutive);
			++out;
		}
		if (y > 0) {
			*out = '/';
			++out;
		}
	}
	return out;
}

constexpr char* SerializeActiveColor(char* out, chss::Color activeColor) {
	*out = activeColor == chss::Color::White ? 'w' : 'b';
	++out;
	return out;
}

constexpr char* SerializeCastlingAvailabilities(char* out, const chss::CastlingAvailabilities& castlingAvailabilities) {
	bool anyOutput = false;
	if (castlingAvailabilities.white.isKingSideAvailable) {
		*out = 'K';
		++out;
		anyOutput = true;
	}
	if (castlingAvailabilities.white.isQueenSideAvailable) {
		*out = 'Q';
		++out;
		anyOutput = true;
	}
	if (castlingAvailabilities.black.isKingSideAvailable) {
		*out = 'k';
		++out;
		anyOutput = true;
	}
	if (castlingAvailabilities.black.isQueenSideAvailable) {
		*out = 'q';
		++out;
		anyOutput = true;
	}
	if (!anyOutput) {
		*out = '-';
		++out;
	}
	return out;
}

constexpr char* SerializeEnPassantTargetSquare(char* out, const std::optional<chss::Position>& enPassantTargetSquare) {
	if (!enPassantTargetSquare.has_value()) {
		*out = '-';
		++out;
	} else {
		const auto& position = enPassantTargetSquare.value();
		*out = static_cast<char>('a' + position.x);
		++out;
		*out = static_cast<char>('1' + position.y);
		++out;
	}
	return out;
}

} // namespace detail

// Forsyth–Edwards Notation
namespace chss::fen {

[[nodiscard]] constexpr State Parse(const std::string_view& input) {
	const auto fenParts = detail::SplitInput(input);
	return State{
		.board = detail::ParseBoard(fenParts[0]),
		.activeColor = detail::ParseActiveColor(fenParts[1]),
		.castlingAvailabilities = detail::ParseCastlingAvailabilities(fenParts[2]),
		.enPassantTargetSquare = detail::ParseEnPassantTargetSquare(fenParts[3]),
		.halfmoveClock = detail::ParseInteger(fenParts[4]),
		.fullmoveNumber = detail::ParseInteger(fenParts[5])};
}

[[nodiscard]] constexpr std::string Serialize(const State& state) {
	auto buffer = std::array<char, 90>(); // https://chess.stackexchange.com/questions/30004/longest-possible-fen
	char* out = buffer.begin();
	out = detail::SerializeBoard(out, state.board);
	*out = ' ';
	++out;
	out = detail::SerializeActiveColor(out, state.activeColor);
	*out = ' ';
	++out;
	out = detail::SerializeCastlingAvailabilities(out, state.castlingAvailabilities);
	*out = ' ';
	++out;
	out = detail::SerializeEnPassantTargetSquare(out, state.enPassantTargetSquare);
	*out = ' ';
	++out;
	out = detail::SerializeInteger(out, state.halfmoveClock);
	*out = ' ';
	++out;
	out = detail::SerializeInteger(out, state.fullmoveNumber);
	return std::string(buffer.begin(), out);
}

[[nodiscard]] constexpr Board ParseBoard(const std::string_view& input) {
	return detail::ParseBoard(input);
}

[[nodiscard]] constexpr std::string SerializeBoard(const Board& board) {
	auto buffer = std::array<char, 71>(); // https://chess.stackexchange.com/questions/30004/longest-possible-fen
	char* out = buffer.begin();
	out = detail::SerializeBoard(out, board);
	return std::string(buffer.begin(), out);
}

} // namespace chss::fen
