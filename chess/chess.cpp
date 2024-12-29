#include "Board.h"
#include "State.h"
#include "Movements.h"
#include "Fen.h"

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <ranges>
#include <tuple>
#include <vector>

#include <generator>

int main() {
	constexpr auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	const auto str = chss::fen::Serialize(state);
	std::cout << str << std::endl;
	return 0;
}
