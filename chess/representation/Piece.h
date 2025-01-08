#pragma once

#include <cstdint>

namespace chss {

enum class PieceType : std::int8_t { Pawn, Knight, Bishop, Rook, Queen, King };

enum class Color : std::int8_t { White, Black };

[[nodiscard]] constexpr Color InverseColor(Color color) {
	return color == Color::White ? Color::Black : Color::White;
}

struct Piece {
	PieceType type;
	Color color;
	[[nodiscard]] constexpr bool operator==(const Piece& other) const = default;
};

} // namespace chss
