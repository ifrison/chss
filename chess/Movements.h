#pragma once

#include <generator>

namespace chss {

struct Move;
struct State;

namespace MoveGeneration {

[[nodiscard]] std::generator<std::pair<Move, State>> LegalMoves(const chss::State& state);

} // namespace MoveGeneration

} // namespace chss
