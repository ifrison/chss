#pragma once

#include "Board.h"

#include <generator>

namespace chss {

struct Move;
struct State;

namespace MoveGeneration {

[[nodiscard]] std::generator<std::pair<Move, State>> PseudoLegalMoves(const chss::State& state);

[[nodiscard]] bool IsInCheck(const chss::Board& board, chss::Color color);

[[nodiscard]] std::generator<std::pair<Move, State>> LegalMoves(const chss::State& state);

} // namespace MoveGeneration

} // namespace chss
