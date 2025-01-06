#include "MinMax.h"
#include "Fen.h"
#include "Movements.h"

#include <gtest/gtest.h>

TEST(Search, MateInOne) {
	auto stop = std::atomic_flag(false);
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("2k5/7R/2K5/8/8/8/8/8 w - - 0 1"), 2, stop), (std::pair(chss::MoveGeneration::Move{.from = chss::positions::H7, .to = chss::positions::H8}, chss::MoveGeneration::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}})));
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("8/8/8/7q/8/2k5/8/2K5 b - - 0 1"), 2, stop), (std::pair(chss::MoveGeneration::Move{.from = chss::positions::H5, .to = chss::positions::H1}, chss::MoveGeneration::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}})));
}

TEST(Search, MateInTwo) {
	auto stop = std::atomic_flag(false);
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("7K/8/8/8/6R1/7R/1k6/8 w - - 0 1"), 4, stop), (std::pair(chss::MoveGeneration::Move{.from = chss::positions::G4, .to = chss::positions::G2}, chss::MoveGeneration::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}})));
	EXPECT_EQ(chss::search::Search(chss::fen::Parse("4K2b/8/4pk2/8/7N/6Q1/8/8 w - - 0 1"), 4, stop), (std::pair(chss::MoveGeneration::Move{.from = chss::positions::E8, .to = chss::positions::F8}, chss::MoveGeneration::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}})));
}