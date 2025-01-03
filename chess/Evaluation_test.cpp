#include "Evaluation.h"
#include "Fen.h"

#include <gtest/gtest.h>

TEST(Evaluation, EvaluateFullBoard) {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	EXPECT_EQ(chss::evaluation::Evaluate(board), 0);
}

TEST(Evaluation, EvaluateOnlyWhite) {
	constexpr auto board = chss::fen::ParseBoard("8/8/8/8/8/8/PPPPPPPP/RNBQKBNR");
	EXPECT_EQ(chss::evaluation::Evaluate(board), 239);
}

TEST(Evaluation, EvaluateOnlyBlack) {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/8/8");
	EXPECT_EQ(chss::evaluation::Evaluate(board), -239);
}
