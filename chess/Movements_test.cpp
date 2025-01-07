#include "Movements.h"
#include "State.h"

#include <gtest/gtest.h>

template<typename T>
std::vector<T> ToVector(std::generator<T> generator) {
	auto result = std::vector<T>();
	for (const auto& element : generator) {
		result.push_back(element);
	}
	return result;
}

TEST(Movements, PseudoLegalMoves) {
	const auto state = chss::State{
		.board = chss::kInitialBoard,
		.activeColor = chss::Color::White,
		.castlingAvailabilities =
			chss::CastlingAvailabilities{
				.white = chss::CastlingAvailability{.isKingSideAvailable = true, .isQueenSideAvailable = true},
				.black = chss::CastlingAvailability{.isKingSideAvailable = true, .isQueenSideAvailable = true}},
		.enPassantTargetSquare = std::nullopt,
		.halfmoveClock = 0,
		.fullmoveNumber = 1};
	auto statesGenerator = chss::MoveGeneration::PseudoLegalMoves(state);
	const auto result = ToVector<std::pair<chss::MoveGeneration::Move, chss::State>>(std::move(statesGenerator));
	EXPECT_EQ(result.size(), 20);
}

TEST(Movements, IsCheck_InitialBoard) {
	const auto board = chss::kInitialBoard;
	EXPECT_FALSE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}

TEST(Movements, IsCheck_ByPawn) {
	auto board = chss::kEmptyBoard;
	board.At(chss::Position{.y = 3, .x = 3}) = chss::Piece{chss::PieceType::King, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 2}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	EXPECT_TRUE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}

TEST(Movements, IsCheck_ByKnight) {
	auto board = chss::kEmptyBoard;
	board.At(chss::Position{.y = 3, .x = 3}) = chss::Piece{chss::PieceType::King, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 1}) = chss::Piece{chss::PieceType::Knight, chss::Color::Black};
	EXPECT_TRUE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}

TEST(Movements, IsCheck_ByBishop) {
	auto board = chss::kEmptyBoard;
	board.At(chss::Position{.y = 3, .x = 3}) = chss::Piece{chss::PieceType::King, chss::Color::White};
	board.At(chss::Position{.y = 5, .x = 1}) = chss::Piece{chss::PieceType::Bishop, chss::Color::Black};
	EXPECT_TRUE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}

TEST(Movements, IsCheck_ByRook) {
	auto board = chss::kEmptyBoard;
	board.At(chss::Position{.y = 3, .x = 3}) = chss::Piece{chss::PieceType::King, chss::Color::White};
	board.At(chss::Position{.y = 3, .x = 1}) = chss::Piece{chss::PieceType::Rook, chss::Color::Black};
	EXPECT_TRUE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}

TEST(Movements, IsCheck_ByQueen) {
	auto board = chss::kEmptyBoard;
	board.At(chss::Position{.y = 3, .x = 3}) = chss::Piece{chss::PieceType::King, chss::Color::White};
	board.At(chss::Position{.y = 5, .x = 1}) = chss::Piece{chss::PieceType::Queen, chss::Color::Black};
	EXPECT_TRUE(chss::MoveGeneration::IsInCheck(board, chss::Color::White));
}
