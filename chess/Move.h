#pragma once

#include "Board.h"

namespace chss {

struct Move {
	Position from;
	Position to;
	[[nodiscard]] constexpr bool operator==(const Move& other) const = default;
};

} // namespace chss
