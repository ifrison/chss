#include "Board.h"
#include "Fen.h"
#include "Movements.h"
#include "State.h"
#include "UCI.h"

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <ranges>
#include <tuple>
#include <vector>

#include <generator>

int main() {
	chss::uci::UCI(std::cin, std::cout);
	return 0;
}
