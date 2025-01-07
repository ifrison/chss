#pragma once

#include "Board.h"

namespace chss {

struct NormalMove {
	Position from;
	Position to;
	[[nodiscard]] constexpr bool operator==(const NormalMove& other) const = default;
};

struct TwoSquaresAdvance {
	Position from;
	Position to;
	[[nodiscard]] constexpr bool operator==(const TwoSquaresAdvance& other) const = default;
};

struct Promotion {
	Position from;
	Position to;
	PieceType type;
	[[nodiscard]] constexpr bool operator==(const Promotion& other) const = default;
};

struct Castling {
	Position from;
	Position to;
	[[nodiscard]] constexpr bool operator==(const Castling& other) const = default;
};

using Move = std::variant<NormalMove, TwoSquaresAdvance, Promotion, Castling>;

} // namespace chss
