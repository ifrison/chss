#pragma once

#include "representation/Board.h"

namespace chss {

struct State;

namespace MoveGeneration {

[[nodiscard]] std::int64_t Perft(const State& state, int depth);

} // namespace MoveGeneration

} // namespace chss
