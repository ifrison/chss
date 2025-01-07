#pragma once

#include "Move.h"

#include <atomic>

namespace chss {

struct State;

namespace search {

[[nodiscard]] std::pair<Move, Move> Search(const State& state, int depth, const std::atomic_flag& stop);

} // namespace search

} // namespace chss
