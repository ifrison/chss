#pragma once

#include "Board.h"

namespace chss {

struct State;

namespace MoveGeneration {

struct Move {
	Position from;
	Position to;
};

[[nodiscard]] std::generator<std::pair<Move, State>> PseudoLegalMoves(const chss::State& state);

[[nodiscard]] bool IsInCheck(const chss::Board& board, chss::Color color);

} // namespace MoveGeneration

} // namespace chss
