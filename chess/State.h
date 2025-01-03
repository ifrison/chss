#pragma once

#include "Board.h"

#include <optional>

namespace chss {

struct CastlingAvailability {
	bool isKingSideAvailable;
	bool isQueenSideAvailable;
	[[nodiscard]] constexpr bool operator==(const CastlingAvailability& other) const = default;
};

struct CastlingAvailabilities {
	CastlingAvailability white;
	CastlingAvailability black;
	[[nodiscard]] constexpr bool operator==(const CastlingAvailabilities& other) const = default;
};

struct State {
	Board board;
	Color activeColor;
	CastlingAvailabilities castlingAvailabilities;
	std::optional<Position> enPassantTargetSquare;
	int halfmoveClock;
	int fullmoveNumber;
	[[nodiscard]] constexpr bool operator==(const State& other) const = default;
};
static_assert(sizeof(State) == 220);

}
