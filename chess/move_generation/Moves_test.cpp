#include "Moves.h"

#include "chess/DebugUtils.h"
#include "chess/fen/Fen.h"

#include <test_utils/TestUtils.h>

#include <iostream>

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

TEST_CASE("Moves", "AllPieces_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/1PNBRQK1/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PseudoLegalMoves(state);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	 constexpr auto expectedResult = std::array<chss::Move, 54>{
	 	chss::Move{.from = chss::positions::B5, .to = chss::positions::B6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::B3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::D3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::A4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::E4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::A6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::E6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::B7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::C5, .to = chss::positions::D7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::B3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::A2, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::H1, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::B7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::A8, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::D5, .to = chss::positions::G8, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E2, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E1, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::E5, .to = chss::positions::E8, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::E4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::D3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::C2, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::B1, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F2, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F1, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::G4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::H3, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::E6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::D7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::C8, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::F8, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::G6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::F5, .to = chss::positions::H7, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::F4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::G4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::H4, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::H5, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::F6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::G6, .promotionType = std::nullopt},
	 	chss::Move{.from = chss::positions::G5, .to = chss::positions::H6, .promotionType = std::nullopt},
	 };
	STATIC_REQUIRE(array == expectedResult);
}

// TODO: Add tests for Black.