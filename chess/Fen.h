#pragma once

#include "State.h"

#include <array>
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
				chss::Piece{.type = chss::Type::Bishop, .color = chss::Color::White};
			++x;
			break;
		case 'K':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::King, .color = chss::Color::White};
			++x;
			break;
		case 'N':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Knight, .color = chss::Color::White};
			++x;
			break;
		case 'P':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Pawn, .color = chss::Color::White};
			++x;
			break;
		case 'Q':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Queen, .color = chss::Color::White};
			++x;
			break;
		case 'R':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Rook, .color = chss::Color::White};
			++x;
			break;
		case 'b':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Bishop, .color = chss::Color::Black};
			++x;
			break;
		case 'k':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::King, .color = chss::Color::Black};
			++x;
			break;
		case 'n':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Knight, .color = chss::Color::Black};
			++x;
			break;
		case 'p':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Pawn, .color = chss::Color::Black};
			++x;
			break;
		case 'q':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Queen, .color = chss::Color::Black};
			++x;
			break;
		case 'r':
			board.At(chss::Position{.y = y, .x = x}) =
				chss::Piece{.type = chss::Type::Rook, .color = chss::Color::Black};
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

[[nodiscard]] std::string Serialize(const State& state);

} // namespace chss::fen
