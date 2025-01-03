#include "MinMax.h"
#include "Fen.h"
#include "Movements.h"

#include <gtest/gtest.h>

constexpr int kWiteWins = std::numeric_limits<int>::max();
constexpr int kBlackWins = std::numeric_limits<int>::min();

TEST(MinMax, MateInOne) {
	EXPECT_EQ(chss::search::MinMax(chss::fen::Parse("2k5/7R/2K5/8/8/8/8/8 w - - 0 1"), 2), kWiteWins);
	EXPECT_EQ(chss::search::MinMax(chss::fen::Parse("8/8/8/7q/8/2k5/8/2K5 b - - 0 1"), 2), kBlackWins);
}

TEST(MinMax, MateInTwo) {
	EXPECT_EQ(chss::search::MinMax(chss::fen::Parse("7K/8/8/8/6R1/7R/1k6/8 w - - 0 1"), 4), kWiteWins);
	EXPECT_EQ(chss::search::MinMax(chss::fen::Parse("4K2b/8/4pk2/8/7N/6Q1/8/8 w - - 0 1"), 4), kWiteWins);
}

TEST(Search, MateInOne) {
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("2k5/7R/2K5/8/8/8/8/8 w - - 0 1"), 2), (chss::MoveGeneration::Move{.from = chss::positions::H7, .to = chss::positions::H8}));
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("8/8/8/7q/8/2k5/8/2K5 b - - 0 1"), 2), (chss::MoveGeneration::Move{.from = chss::positions::H5, .to = chss::positions::H1}));
}

TEST(Search, MateInTwo) {
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("7K/8/8/8/6R1/7R/1k6/8 w - - 0 1"), 4), (chss::MoveGeneration::Move{.from = chss::positions::G4, .to = chss::positions::G2}));
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("4K2b/8/4pk2/8/7N/6Q1/8/8 w - - 0 1"), 4), (chss::MoveGeneration::Move{.from = chss::positions::E8, .to = chss::positions::F8}));
}
