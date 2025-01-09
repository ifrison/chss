#include "KnightMoves.h"

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

TEST_CASE("KnightMoves", "Unobstructed") {
	constexpr auto state = chss::fen::Parse("8/8/8/3N4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::KnightPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 8>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E7, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KnightMoves", "EdgeOfBoard") {
	constexpr auto state = chss::fen::Parse("8/N7/8/8/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::KnightPseudoLegalMoves(state, chss::positions::A7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 3>{
		chss::Move{.from = chss::positions::A7, .to = chss::positions::B5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::A7, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::A7, .to = chss::positions::C8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KnightMoves", "ObstructedByFriendlyPiece") {
	constexpr auto state = chss::fen::Parse("8/2K1Q3/5R2/3N4/5B2/2P1N3/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::KnightPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KnightMoves", "CaptureEnemyPiece") {
	constexpr auto state = chss::fen::Parse("8/2k1q3/5r2/3N4/5b2/2p1n3/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::KnightPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 8>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E7, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}
