#include "SlidingPieceMoves.h"

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

TEST_CASE("BishopMoves", "Unobstructed") {
	constexpr auto state = chss::fen::Parse("8/8/8/3B4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::BishopPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 13>{
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
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("BishopMoves", "ObstructedByFriendlyPiece") {
	constexpr auto state = chss::fen::Parse("6B1/1N6/8/3B4/2P5/8/8/7R w - - 0 1");
	constexpr auto generator = chss::move_generation::BishopPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("BishopMoves", "CaptureEnemyPiece") {
	constexpr auto state = chss::fen::Parse("6q1/1r6/8/3B4/2b5/8/8/7k w - - 0 1");
	constexpr auto generator = chss::move_generation::BishopPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 10>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::H1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array != expectedResult);
}

TEST_CASE("RookMoves", "Unobstructed") {
	constexpr auto state = chss::fen::Parse("8/8/8/3R4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::RookPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 14>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::A5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::H5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("RookMoves", "ObstructedByFriendlyPiece") {
	constexpr auto state = chss::fen::Parse("8/3N4/8/2PR2B1/8/8/8/3R4 w - - 0 1");
	constexpr auto generator = chss::move_generation::RookPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("RookMoves", "CaptureEnemyPiece") {
	constexpr auto state = chss::fen::Parse("8/3r4/8/2bR2q1/8/8/8/3k4 w - - 0 1");
	constexpr auto generator = chss::move_generation::RookPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 10>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D7, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("QueenMoves", "Unobstructed") {
	constexpr auto state = chss::fen::Parse("8/8/8/3Q4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::QueenPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 27>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::A2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::H1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::A5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::H5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::A8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("QueenMoves", "ObstructedByFriendlyPiece") {
	constexpr auto state = chss::fen::Parse("6Q1/1B1R4/8/2NQ2K1/2P5/8/8/3N3P w - - 0 1");
	constexpr auto generator = chss::move_generation::QueenPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 12>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("QueenMoves", "CaptureEnemyPiece") {
	constexpr auto state = chss::fen::Parse("6q1/1b1r4/8/2nQ2k1/2p5/8/8/3n3p w - - 0 1");
	constexpr auto generator = chss::move_generation::QueenPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 20>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::H1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G5, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::B7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::G8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}