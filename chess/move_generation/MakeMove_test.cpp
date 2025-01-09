#include "MakeMove.h"

#include "chess/fen/Fen.h"

#include <test_utils/TestUtils.h>

// Promotion (1)
TEST_CASE("MakeMove", "Promotion") {
	constexpr auto state = chss::fen::Parse("8/3P4/8/8/8/8/K6k/8 w - - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::D7, .to = chss::positions::D8, .promotionType = chss::PieceType::Queen});
	constexpr auto expectedResult = chss::fen::Parse("3Q4/8/8/8/8/8/K6k/8 b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Move Rooks, Castling no longer available (4)
TEST_CASE("MakeMove", "MoveRook_WiteQueenSide_QueenSideCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K3 w Q - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::A1, .to = chss::positions::A5, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/R7/8/8/8/4K3 b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "MoveRook_WiteKingSide_KingSideCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/4K2R w K - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::H1, .to = chss::positions::H5, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/7R/8/8/8/4K3 b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "MoveRook_BlackQueenSide_QueenSideCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k3/8/8/8/8/8/8/4K3 b q - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::A8, .to = chss::positions::A4, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/r7/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "MoveRook_BlackKingSide_KingSideCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k2r/8/8/8/8/8/8/4K3 b - - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::H8, .to = chss::positions::H4, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/7r/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Move Kings, Castling no longer available (2)
TEST_CASE("MakeMove", "MoveKing_White_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E1, .to = chss::positions::E2, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/8/4K3/R6R b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "MoveKing_Black_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E8, .to = chss::positions::E7, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("r6r/4k3/8/8/8/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Castling (4)
TEST_CASE("MakeMove", "Castling_WhiteQueenSide_RookMovesAndCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E1, .to = chss::positions::C1, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/8/8/2KR3R b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "Castling_WhiteKingSide_RookMovesAndCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2R w KQ - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E1, .to = chss::positions::G1, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/8/8/R4RK1 b - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "Castling_BlackQueenSide_RookMovesAndCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E8, .to = chss::positions::C8, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("2kr3r/8/8/8/8/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "Castling_BlackKingSide_RookMovesAndCastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/8/8/4K3 b kq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::E8, .to = chss::positions::G8, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("r4rk1/8/8/8/8/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Two squares pawn advance, en passant target square (2)
TEST_CASE("MakeMove", "TwoSquaresPawnAdvance_White_EnPassantTargetSquareSet") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/8/8/2P5/4K3 w - - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::C2, .to = chss::positions::C4, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/2P5/8/8/4K3 b - c3 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "TwoSquaresPawnAdvance_Black_EnPassantTargetSquareSet") {
	constexpr auto state = chss::fen::Parse("4k3/2p5/8/8/8/8/8/4K3 b - - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::C7, .to = chss::positions::C5, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/2p5/8/8/8/4K3 w - c6 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Eat Rooks, Castling no longer available (4)
TEST_CASE("MakeMove", "EatRook_BlackEatsQueenSide_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/5b2/8/8/8/8/R3K2R b KQ - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::F6, .to = chss::positions::A1, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/8/8/b3K2R w K - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "EatRook_BlackEatsKingSide_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("4k3/8/2b5/8/8/8/8/R3K2R b KQ - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::C6, .to = chss::positions::H1, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/8/8/R3K2b w Q - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "EatRook_WhiteEatsQueenSide_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/5B2/8/4K3 w kq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::F3, .to = chss::positions::A8, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("B3k2r/8/8/8/8/8/8/4K3 b k - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("MakeMove", "EatRook_WhiteEatsKingSide_CastlingNoLongerAvailable") {
	constexpr auto state = chss::fen::Parse("r3k2r/8/8/8/8/2B5/8/4K3 w kq - 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::C3, .to = chss::positions::H8, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("r3k2B/8/8/8/8/8/8/4K3 b q - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Eat en passant with a pawn (1)
TEST_CASE("MakeMove", "EatEnPassant_EatenPawnDisappears") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/8/1Pp5/8/8/4K3 b - b3 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::C4, .to = chss::positions::B3, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/8/1p6/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Do not eat en passant with a non-pawn piece (1)
TEST_CASE("MakeMove", "MoveToEnPassantTargetSquare_BlackBishop_DoNotEatPawn") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/3b4/1P6/8/8/4K3 b - b3 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::D5, .to = chss::positions::B3, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/1P6/1b6/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}

// Move after two squares pawn advance, en passant opportunity lost (1)
TEST_CASE("MakeMove", "MoveWhilePassantTargetSquare_EnPassantOpportunityLost") {
	constexpr auto state = chss::fen::Parse("4k3/8/8/5p2/1P6/8/8/4K3 b - b3 0 1");
	constexpr auto result = chss::move_generation::MakeMove(state, chss::Move{.from = chss::positions::F5, .to = chss::positions::F4, .promotionType = std::nullopt});
	constexpr auto expectedResult = chss::fen::Parse("4k3/8/8/8/1P3p2/8/8/4K3 w - - 0 2");
	STATIC_REQUIRE(result == expectedResult);
}
