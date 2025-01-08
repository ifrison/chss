#include "DebugUtils.h"

#include <gtest/gtest.h>

TEST(Debug, PieceTypeToChar) {
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::Pawn), 'p');
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::Knight), 'n');
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::Bishop), 'b');
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::Rook), 'r');
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::Queen), 'q');
	EXPECT_EQ(chss::debug::PieceTypeToChar(chss::PieceType::King), 'k');
}

TEST (DEBUG, PositionToString) {
	EXPECT_EQ(chss::debug::PositionToString({0, 0}), "a1");
	EXPECT_EQ(chss::debug::PositionToString({1, 1}), "b2");
	EXPECT_EQ(chss::debug::PositionToString({4, 4}), "e5");
	EXPECT_EQ(chss::debug::PositionToString({7, 7}), "h8");
}
