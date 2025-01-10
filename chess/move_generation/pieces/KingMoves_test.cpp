#include "KingMoves.h"

#include "chess/fen/Fen.h"

#include <test_utils/TestUtils.h>

namespace {

template<typename Generator>
constexpr std::size_t GeneratorSize(const Generator& generator) {
	std::size_t size = 0;
	for ([[maybe_unused]] const auto& _ : generator) {
		++size;
	}
	return size;
}

template<typename T, std::size_t S, typename Generator>
constexpr std::array<T, S> GeneratorToArray(const Generator& generator) {
	auto result = std::array<T, S>();
	auto it = generator.begin();
	for (std::size_t i = 0; i < S; ++i) {
		result[i] = *it;
		++it;
	}
	return result;
}

} // namespace

TEST_CASE("PawnMoves", "TODO") {
	constexpr auto state = chss::fen::Parse("8/8/8/3K4/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 8>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}
