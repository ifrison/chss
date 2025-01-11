#include "IsInCheck.h"

#include "chess/fen/Fen.h"

#include <test_utils/TestUtils.h>

TEST_CASE("IsInCheck", "FindKing") {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	STATIC_REQUIRE(chss::move_generation::FindKing(board, chss::Color::White) == chss::positions::E1);
	STATIC_REQUIRE(chss::move_generation::FindKing(board, chss::Color::Black) == chss::positions::E8);
}

TEST_CASE("IsInCheck", "NotInCheck") {
	constexpr auto board = chss::fen::ParseBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	STATIC_REQUIRE(!chss::move_generation::IsInCheck(board, chss::Color::White, chss::positions::E1));
	STATIC_REQUIRE(!chss::move_generation::IsInCheck(board, chss::Color::Black, chss::positions::E8));
}

TEST_CASE("IsInCheck", "IsInCheck_ByPawn") {
	constexpr auto board = chss::fen::ParseBoard("8/8/2p5/3K4/8/8/8/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::White, chss::positions::D5));
}

TEST_CASE("IsInCheck", "IsInCheck_ByKnight") {
	constexpr auto board = chss::fen::ParseBoard("8/8/8/3k4/8/2N5/8/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::Black, chss::positions::D5));
}

TEST_CASE("IsInCheck", "IsInCheck_ByBishop") {
	constexpr auto board = chss::fen::ParseBoard("8/8/8/3K4/8/8/6b1/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::White, chss::positions::D5));
}

TEST_CASE("IsInCheck", "IsInCheck_ByRook") {
	constexpr auto board = chss::fen::ParseBoard("8/8/8/3k3R/8/8/8/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::Black, chss::positions::D5));
}

TEST_CASE("IsInCheck", "IsInCheck_ByQueen") {
	constexpr auto board = chss::fen::ParseBoard("8/1q6/8/3K4/8/8/8/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::White, chss::positions::D5));
}

TEST_CASE("IsInCheck", "IsInCheck_ByKing") {
	constexpr auto board = chss::fen::ParseBoard("8/8/4K3/3k4/8/8/8/8");
	STATIC_REQUIRE(chss::move_generation::IsInCheck(board, chss::Color::Black, chss::positions::D5));
}
