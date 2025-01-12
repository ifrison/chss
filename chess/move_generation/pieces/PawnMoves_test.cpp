#include "PawnMoves.h"

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

// Advance
TEST_CASE("PawnMoves", "Advance_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/3P4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 1>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/3p4/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 1>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_BlockedByOtherPiece_White") {
	constexpr auto state = chss::fen::Parse("8/8/3n4/3P4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_BlockedByOtherPiece_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/3p4/3N4/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_BlockedByEndOfBoard_White") {
	constexpr auto state = chss::fen::Parse("3P4/8/8/8/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D8);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_BlockedByEndOfBoard_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/8/3p4 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D1);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_Promotion_White") {
	constexpr auto state = chss::fen::Parse("8/3P4/8/8/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 4>{
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Queen},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Advance_Promotion_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/3p4/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 4>{
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Queen},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// DoubleAdvance
TEST_CASE("PawnMoves", "DoubleAdvance_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/3P4/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DoubleAdvance_Black") {
	constexpr auto state = chss::fen::Parse("8/3p4/8/8/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D5, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DoubleAdvance_BlockedShortByOtherPiece_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/3B4/3P4/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DoubleAdvance_BlockedShortByOtherPiece_Black") {
	constexpr auto state = chss::fen::Parse("8/3p4/3b4/8/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 0>{};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DoubleAdvance_BlockedLongByOtherPiece_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/3k4/8/3P4/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 1>{
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D3, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DoubleAdvance_BlockedLongByOtherPiece_Black") {
	constexpr auto state = chss::fen::Parse("8/3p4/8/3K4/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 1>{
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

// Capture
TEST_CASE("PawnMoves", "Capture_White") {
	constexpr auto state = chss::fen::Parse("8/8/2r1q3/3P4/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 3>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Capture_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/3p4/2R1Q3/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 3>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::E4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "CaptureAndPromotion_White") {
	constexpr auto state = chss::fen::Parse("2n1b3/3P4/8/8/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 12>{
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Queen},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::C8, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::C8, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::C8, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::C8, .promotionType = chss::PieceType::Queen},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::E8, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::E8, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::E8, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::E8, .promotionType = chss::PieceType::Queen},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "CaptureAndPromotion_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/8/8/3p4/2N1B3 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 12>{
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D1, .promotionType = chss::PieceType::Queen},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::E1, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::E1, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::E1, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::E1, .promotionType = chss::PieceType::Queen},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::C1, .promotionType = chss::PieceType::Knight},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::C1, .promotionType = chss::PieceType::Bishop},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::C1, .promotionType = chss::PieceType::Rook},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::C1, .promotionType = chss::PieceType::Queen},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Capture_WhileOnLeftEdge_White") {
	constexpr auto state = chss::fen::Parse("8/8/1q6/P7/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::A5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::A5, .to = chss::positions::A6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::A5, .to = chss::positions::B6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Capture_WhileOnLeftEdge_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/p7/1Q6/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::A5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::A5, .to = chss::positions::A4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::A5, .to = chss::positions::B4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Capture_WhileOnRightEdge_White") {
	constexpr auto state = chss::fen::Parse("8/8/6q1/7P/8/8/8/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::H5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::H5, .to = chss::positions::H6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::H5, .to = chss::positions::G6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "Capture_WhileOnRightEdge_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/7p/6Q1/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::H5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::H5, .to = chss::positions::H4, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::H5, .to = chss::positions::G4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DontCaptureAtDistanceTwo_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/2r5/8/3P4/8 w - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D2);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D2, .to = chss::positions::D4, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "DontCaptureAtDistanceTwo_Black") {
	constexpr auto state = chss::fen::Parse("8/3p4/8/2R5/8/8/8/8 b - - 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D7);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D7, .to = chss::positions::D5, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "CaptureEnPassant_White") {
	constexpr auto state = chss::fen::Parse("8/8/8/2pP4/8/8/8/8 w - c6 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D5);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D5, .to = chss::positions::D6, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D5, .to = chss::positions::C6, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}

TEST_CASE("PawnMoves", "CaptureEnPassant_Black") {
	constexpr auto state = chss::fen::Parse("8/8/8/8/2Pp4/8/8/8 b - c3 0 1");
	constexpr auto generator = chss::move_generation::PawnPseudoLegalMoves(state, chss::positions::D4);
	constexpr auto size = GeneratorSize(generator);
	constexpr auto array = GeneratorToArray<chss::Move, size>(generator);
	constexpr auto expectedResult = std::array<chss::Move, 2>{
		chss::Move{.from = chss::positions::D4, .to = chss::positions::D3, .promotionType = std::nullopt},
		chss::Move{.from = chss::positions::D4, .to = chss::positions::C3, .promotionType = std::nullopt},
	};
	STATIC_REQUIRE(array == expectedResult);
}
