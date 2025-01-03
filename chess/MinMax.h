#pragma once

namespace chss {

struct State;

namespace MoveGeneration {
struct Move;
} // namespace MoveGeneration

namespace search {

[[nodiscard]] int MinMax(const State& state, int depth);

[[nodiscard]] MoveGeneration::Move Search(const State& state, int depth);

} // namespace search

} // namespace chss
