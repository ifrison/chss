#pragma once

#include <istream>
#include <ostream>

namespace chss {

struct State;

namespace uci {

void UCI(std::istream& in, std::ostream& out);

} // namespace uci

} // namespace chss
