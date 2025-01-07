#include "Piece.h"

#include <gtest/gtest.h>

TEST(Board, InverseColor) {
	EXPECT_EQ(InverseColor(chss::Color::White), chss::Color::Black);
	EXPECT_EQ(InverseColor(chss::Color::Black), chss::Color::White);
}
