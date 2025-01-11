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

TEST_CASE("KingMoves", "Unobstructed") {
	constexpr auto state = chss::fen::Parse("8/8/8/3K4/8/8/8/8 w - - 0 1");
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

TEST_CASE("KingMoves", "ObstructedByFriendlyPiece") {
	constexpr auto state = chss::fen::Parse("8/8/4B3/2RKQ3/2PN4/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 3>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "CaptureEnemyPiece") {
	constexpr auto state = chss::fen::Parse("8/8/2kpn3/2rKq3/2pnb3/8/8/8 w - - 0 1");
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

// Castling
TEST_CASE("KingMoves", "Castling_QueenSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/R3K3 w Q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::C1, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "Castling_QueenSide_Black") {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/8/8/8 b q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::C8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "Castling_KingSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/4K2R w K - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::G1, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "Castling_KingSide_Black") {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/8/8/8/8/8 b k - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::G8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// No castling without castling availability
TEST_CASE("KingMoves", "NoCastlingAvailability_QueenSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/R3K3 w - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingAvailability_QueenSide_Black") {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingAvailability_KingSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/4K2R w - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingAvailability_KingSide_Black") {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/8/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// No castling with pieces in between
TEST_CASE("KingMoves", "NoCastlingInBetween_QueenSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/R1B1K3 w Q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingInBetween_QueenSide_Black") {
	constexpr auto state = chss::fen::Parse("r1b1k3/8/8/8/8/8/8/8 b q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingInBetween_KingSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/4K1NR w K - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingInBetween_KingSide_Black") {
	constexpr auto state = chss::fen::Parse("4k1nr/8/8/8/8/8/8/8 b k - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// No castling with unsafe squares in between
TEST_CASE("KingMoves", "NoCastlingUnsafe_QueenSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/6b1/8/8/8/R3K3 w Q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingUnsafe_QueenSide_Black") {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/2R5/8/8 b q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingUnsafe_KingSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/7n/8/4K2R w K - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "NoCastlingUnsafe_KingSide_Black") {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/5Q2/8/8/8/8 b k - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 5>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// Castling Queen Side with B1 or B8 threatened
TEST_CASE("KingMoves", "CastlingWithB1Threatened_QueenSide_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/4b3/8/8/R3K3 w Q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F1, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::D2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::F2, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E1, .to = chss::positions::C1, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("KingMoves", "CastlingWithB8Threatened_QueenSide_Black") {
	constexpr auto state = chss::fen::Parse("r3k3/P7/8/8/8/8/8/8 b q - 0 1");
	constexpr auto generator = chss::move_generation::KingPseudoLegalMoves(state, chss::positions::E8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 6>{
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F7, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::D8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::F8, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::E8, .to = chss::positions::C8, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}
