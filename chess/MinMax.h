#pragma once

#include <atomic>

namespace chss {

struct State;

namespace MoveGeneration {
struct Move;
} // namespace MoveGeneration

namespace search {

[[nodiscard]] std::pair<MoveGeneration::Move, MoveGeneration::Move> Search(const State& state, int depth, const std::atomic_flag& stop);

} // namespace search

} // namespace chss
