#include "DebugUtils.h"

#include <gtest/gtest.h>

namespace {

std::string Serialize(const chss::Board& board) {
	auto ss = std::ostringstream();
	chss::debug::PrintBoard(board, ss);
	return ss.str();
}

}

TEST(Debug, PrintBoard) {
	EXPECT_EQ(Serialize(chss::kInitialBoard),
		"  +---+---+---+---+---+---+---+---+\n"
		"8 | r | n | b | q | k | b | n | r |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"7 | p | p | p | p | p | p | p | p |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"6 |   |   |   |   |   |   |   |   |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"5 |   |   |   |   |   |   |   |   |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"4 |   |   |   |   |   |   |   |   |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"3 |   |   |   |   |   |   |   |   |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"2 | P | P | P | P | P | P | P | P |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"1 | R | N | B | Q | K | B | N | R |\n"
		"  +---+---+---+---+---+---+---+---+\n"
		"    a   b   c   d   e   f   g   h  \n"
	);
}