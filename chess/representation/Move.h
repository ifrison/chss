#pragma once

#include "Board.h"

#include <optional>

namespace chss {

struct Move {
	Position from;
	Position to;
	std::optional<PieceType> promotionType;
	[[nodiscard]] constexpr bool operator==(const Move& other) const = default;
};

} // namespace chss
