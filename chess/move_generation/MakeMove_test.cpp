#include "MakeMove.h"

#include "chess/fen/Fen.h"

#include <test_utils/TestUtils.h>

TEST_CASE("MakeMove", "e2e3") {
	constexpr auto state = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E2, .to = chss::positions::E4, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// TODO: Add more tests
