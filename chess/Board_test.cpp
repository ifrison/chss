#include "Board.h"

#include <gtest/gtest.h>

TEST(Board, InverseColor) {
	EXPECT_EQ(InverseColor(chss::Color::White), chss::Color::Black);
	EXPECT_EQ(InverseColor(chss::Color::Black), chss::Color::White);
}

TEST(Board, Piece_Comparison) {
	constexpr auto piece1 = chss::Piece{.type = chss::PieceType::Pawn, .color = chss::Color::White};
	constexpr auto piece2 = chss::Piece{.type = chss::PieceType::Pawn, .color = chss::Color::White};
	constexpr auto piece3 = chss::Piece{.type = chss::PieceType::Pawn, .color = chss::Color::Black};
	constexpr auto piece4 = chss::Piece{.type = chss::PieceType::Knight, .color = chss::Color::White};

	EXPECT_TRUE(piece1 == piece2);
	EXPECT_FALSE(piece1 == piece3);
	EXPECT_FALSE(piece1 == piece4);

	EXPECT_FALSE(piece1 != piece2);
	EXPECT_TRUE(piece1 != piece3);
	EXPECT_TRUE(piece1 != piece4);
}
