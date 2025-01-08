#include "DebugUtils.h"

#include <test_utils/TestUtils.h>

TEST_CASE("Debug", "PieceTypeToChar") {
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::Pawn) == 'p');
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::Knight) == 'n');
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::Bishop) == 'b');
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::Rook) == 'r');
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::Queen) == 'q');
	STATIC_REQUIRE(chss::debug::PieceTypeToChar(chss::PieceType::King) == 'k');
}

TEST_CASE("Debug", "PositionToString") {
	STATIC_REQUIRE(chss::debug::PositionToString({0, 0}) == "a1");
	STATIC_REQUIRE(chss::debug::PositionToString({1, 1}) == "b2");
	STATIC_REQUIRE(chss::debug::PositionToString({4, 4}) == "e5");
	STATIC_REQUIRE(chss::debug::PositionToString({7, 7}) == "h8");
}
