#pragma once

#include "Board.h"

#include <generator>

namespace chss {

struct State;

namespace MoveGeneration {

struct Move {
	Position from;
	Position to;
	[[nodiscard]] constexpr bool operator==(const Move& other) const = default;
};

[[nodiscard]] std::generator<std::pair<Move, State>> PseudoLegalMoves(const chss::State& state);

[[nodiscard]] bool IsInCheck(const chss::Board& board, chss::Color color);

} // namespace MoveGeneration

} // namespace chss
