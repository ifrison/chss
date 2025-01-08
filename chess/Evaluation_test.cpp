#include "Evaluation.h"
#include "Fen.h"

#include <test_utils/TestUtils.h>

TEST_CASE("Evaluation", "EvaluateFullBoard") {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	STATIC_REQUIRE(chss::evaluation::Evaluate(board) == 0);
}

TEST_CASE("Evaluation", "EvaluateOnlyWhite") {
	constexpr auto board = chss::fen::ParseBoard("8/8/8/8/8/8/PPPPPPPP/RNBQKBNR");
	STATIC_REQUIRE(chss::evaluation::Evaluate(board) == 23922);
}

TEST_CASE("Evaluation", "EvaluateOnlyBlack") {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/8/8");
	STATIC_REQUIRE(chss::evaluation::Evaluate(board) == -23922);
}
