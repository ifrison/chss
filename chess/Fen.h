#pragma once

#include <string_view>

namespace chss {

struct State;

// Forsyth–Edwards Notation
namespace fen {

[[nodiscard]] State Parse(const std::string_view& input);
[[nodiscard]] std::string Serialize(const State& state);

}

}
