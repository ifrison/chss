#include "Piece.h"

#include <test_utils/TestUtils.h>

TEST_CASE("Board", "InverseColor") {
	STATIC_REQUIRE(InverseColor(chss::Color::White) == chss::Color::Black);
	STATIC_REQUIRE(InverseColor(chss::Color::Black) == chss::Color::White);
}
