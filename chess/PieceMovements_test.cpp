#include "PieceMovements.h"
#include "State.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

template<typename T>
std::vector<T> to_vector(std::generator<T> generator) {
	auto result = std::vector<T>();
	for (const auto& element : generator) {
		result.push_back(element);
	}
	return result;
}

TEST(PieceMovements, PawnWhite_Forward) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 4, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_Forward_BlockedByEndOfBoard) {
	constexpr auto pawn_position = chss::Position{.y = 7, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 5}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array<chss::Position, 0>{};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_Forward_BlockedByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
		board.At(chss::Position{.y = 4, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array<chss::Position, 0>{};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnBlack_Forward) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_Forward_BlockedByEndOfBoard) {
	constexpr auto pawn_position = chss::Position{.y = 0, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 2, .x = 5}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array<chss::Position, 0>{};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_Forward_BlockedByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
		board.At(chss::Position{.y = 2, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array<chss::Position, 0>{};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnWhite_DoubleForward) {
	constexpr auto pawn_position = chss::Position{.y = 1, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 5}, chss::Position{.y = 3, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_DoubleForward_BlockedShortByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 1, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
		board.At(chss::Position{.y = 2, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array<chss::Position, 0>{};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnWhite_DoubleForward_BlockedLongByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 1, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
		board.At(chss::Position{.y = 3, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 5}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnBlack_DoubleForward) {
	constexpr auto pawn_position = chss::Position{.y = 6, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 5, .x = 5}, chss::Position{.y = 4, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_DoubleForward_BlockedShortByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 6, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
		board.At(chss::Position{.y = 5, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array<chss::Position, 0>{};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnBlack_DoubleForward_BlockedLongByOtherPiece) {
	for (const auto otherPieceColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto pawn_position = chss::Position{.y = 6, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
		board.At(chss::Position{.y = 4, .x = 5}) = chss::Piece{chss::PieceType::Pawn, otherPieceColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
		constexpr auto expectedResult = std::array{chss::Position{.y = 5, .x = 5}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, PawnWhite_Capture) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 4}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult =
		std::array{chss::Position{.y = 4, .x = 4}, chss::Position{.y = 4, .x = 5}, chss::Position{.y = 4, .x = 6}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_Capture_OnLeftEdge) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 0};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 1}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 4, .x = 0}, chss::Position{.y = 4, .x = 1}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_Capture_OnRightEdge) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 7};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 4, .x = 6}, chss::Position{.y = 4, .x = 7}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_Capture) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 2, .x = 4}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 2, .x = 6}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult =
		std::array{chss::Position{.y = 2, .x = 4}, chss::Position{.y = 2, .x = 5}, chss::Position{.y = 2, .x = 6}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_Capture_OnLeftEdge) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 0};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 2, .x = 1}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 0}, chss::Position{.y = 2, .x = 1}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_Capture_OnRightEdge) {
	constexpr auto pawn_position = chss::Position{.y = 3, .x = 7};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 2, .x = 6}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 6}, chss::Position{.y = 2, .x = 7}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnWhite_DontCaptureWhenDoubleForward) {
	constexpr auto pawn_position = chss::Position{.y = 1, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	board.At(chss::Position{.y = 3, .x = 4}) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 2, .x = 5}, chss::Position{.y = 3, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, PawnBlack_DontCaptureWhenDoubleForward) {
	constexpr auto pawn_position = chss::Position{.y = 6, .x = 5};
auto board = chss::kEmptyBoard;
	board.At(pawn_position) = chss::Piece{chss::PieceType::Pawn, chss::Color::Black};
	board.At(chss::Position{.y = 4, .x = 4}) = chss::Piece{chss::PieceType::Pawn, chss::Color::White};
	const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesPawn(board, pawn_position));
	constexpr auto expectedResult = std::array{chss::Position{.y = 5, .x = 5}, chss::Position{.y = 4, .x = 5}};
	EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
}

TEST(PieceMovements, Knight_Move) {
	for (const auto knight_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto knight_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(knight_position) = chss::Piece{chss::PieceType::Knight, knight_color};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKnight(board, knight_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 1, .x = 4},
			chss::Position{.y = 1, .x = 6},
			chss::Position{.y = 2, .x = 3},
			chss::Position{.y = 2, .x = 7},
			chss::Position{.y = 4, .x = 3},
			chss::Position{.y = 4, .x = 7},
			chss::Position{.y = 5, .x = 4},
			chss::Position{.y = 5, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Knight_Move_BlockedByEndOfBoard) {
	for (const auto knight_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto knight_position = chss::Position{.y = 1, .x = 7};
	auto board = chss::kEmptyBoard;
		board.At(knight_position) = chss::Piece{chss::PieceType::Knight, knight_color};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKnight(board, knight_position));
		constexpr auto expectedResult =
			std::array{chss::Position{.y = 0, .x = 5}, chss::Position{.y = 2, .x = 5}, chss::Position{.y = 3, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Knight_Move_BlockedByPiceOfSameColor) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto knight_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(knight_position) = chss::Piece{chss::PieceType::Knight, playerColor};
		board.At(chss::Position{.y = 1, .x = 4}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		board.At(chss::Position{.y = 2, .x = 7}) = chss::Piece{chss::PieceType::Knight, playerColor};
		board.At(chss::Position{.y = 4, .x = 3}) = chss::Piece{chss::PieceType::Queen, playerColor};
		board.At(chss::Position{.y = 5, .x = 4}) = chss::Piece{chss::PieceType::King, playerColor};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKnight(board, knight_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 1, .x = 6},
			chss::Position{.y = 2, .x = 3},
			chss::Position{.y = 4, .x = 7},
			chss::Position{.y = 5, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Knight_Capture) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		const auto enemyColor = InverseColor(playerColor);
		constexpr auto knight_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(knight_position) = chss::Piece{chss::PieceType::Knight, playerColor};
		board.At(chss::Position{.y = 1, .x = 4}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		board.At(chss::Position{.y = 2, .x = 7}) = chss::Piece{chss::PieceType::Knight, enemyColor};
		board.At(chss::Position{.y = 4, .x = 3}) = chss::Piece{chss::PieceType::Queen, enemyColor};
		board.At(chss::Position{.y = 5, .x = 4}) = chss::Piece{chss::PieceType::King, enemyColor};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKnight(board, knight_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 1, .x = 4},
			chss::Position{.y = 1, .x = 6},
			chss::Position{.y = 2, .x = 3},
			chss::Position{.y = 2, .x = 7},
			chss::Position{.y = 4, .x = 3},
			chss::Position{.y = 4, .x = 7},
			chss::Position{.y = 5, .x = 4},
			chss::Position{.y = 5, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Bishop_Move) {
	for (const auto bishop_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto bishop_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(bishop_position) = chss::Piece{chss::PieceType::Bishop, bishop_color};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesBishop(board, bishop_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 1, .x = 3},
			chss::Position{.y = 0, .x = 2},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 1, .x = 7},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 5, .x = 3},
			chss::Position{.y = 6, .x = 2},
			chss::Position{.y = 7, .x = 1},
			chss::Position{.y = 4, .x = 6},
			chss::Position{.y = 5, .x = 7}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Bishop_Move_BlockedByPieceOfSameColor) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto bishop_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(bishop_position) = chss::Piece{chss::PieceType::Bishop, playerColor};
		board.At(chss::Position{.y = 1, .x = 3}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		board.At(chss::Position{.y = 6, .x = 2}) = chss::Piece{chss::PieceType::Bishop, playerColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::King, playerColor};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesBishop(board, bishop_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 1, .x = 7},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 5, .x = 3}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Bishop_Capture) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		const auto enemyColor = InverseColor(playerColor);
		constexpr auto bishop_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(bishop_position) = chss::Piece{chss::PieceType::Bishop, playerColor};
		board.At(chss::Position{.y = 1, .x = 3}) = chss::Piece{chss::PieceType::Knight, enemyColor};
		board.At(chss::Position{.y = 6, .x = 2}) = chss::Piece{chss::PieceType::Bishop, enemyColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		const auto result =
			to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesBishop(board, bishop_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 1, .x = 3},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 1, .x = 7},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 5, .x = 3},
			chss::Position{.y = 6, .x = 2},
			chss::Position{.y = 4, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Rook_Move) {
	for (const auto rook_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto rook_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(rook_position) = chss::Piece{chss::PieceType::Rook, rook_color};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesRook(board, rook_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 1, .x = 5},
			chss::Position{.y = 0, .x = 5},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 5, .x = 5},
			chss::Position{.y = 6, .x = 5},
			chss::Position{.y = 7, .x = 5},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 3},
			chss::Position{.y = 3, .x = 2},
			chss::Position{.y = 3, .x = 1},
			chss::Position{.y = 3, .x = 0},
			chss::Position{.y = 3, .x = 6},
			chss::Position{.y = 3, .x = 7}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Rook_Move_BlockedByPieceOfSameColor) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto rook_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(rook_position) = chss::Piece{chss::PieceType::Rook, playerColor};
		board.At(chss::Position{.y = 1, .x = 5}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		board.At(chss::Position{.y = 6, .x = 5}) = chss::Piece{chss::PieceType::Knight, playerColor};
		board.At(chss::Position{.y = 3, .x = 1}) = chss::Piece{chss::PieceType::Rook, playerColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::King, playerColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesRook(board, rook_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 5, .x = 5},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 3},
			chss::Position{.y = 3, .x = 2}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Rook_Capture) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		const auto enemyColor = InverseColor(playerColor);
		constexpr auto rook_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(rook_position) = chss::Piece{chss::PieceType::Rook, playerColor};
		board.At(chss::Position{.y = 1, .x = 5}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		board.At(chss::Position{.y = 6, .x = 5}) = chss::Piece{chss::PieceType::Knight, enemyColor};
		board.At(chss::Position{.y = 3, .x = 1}) = chss::Piece{chss::PieceType::Rook, enemyColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::King, enemyColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesRook(board, rook_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 1, .x = 5},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 5, .x = 5},
			chss::Position{.y = 6, .x = 5},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 3},
			chss::Position{.y = 3, .x = 2},
			chss::Position{.y = 3, .x = 1},
			chss::Position{.y = 3, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Queen_Move) {
	for (const auto queen_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto queen_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(queen_position) = chss::Piece{chss::PieceType::Queen, queen_color};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesQueen(board, queen_position));
		constexpr auto expectedResult =
			std::array{chss::Position{.y = 2, .x = 4}, chss::Position{.y = 1, .x = 3}, chss::Position{.y = 0, .x = 2},
					   chss::Position{.y = 2, .x = 6}, chss::Position{.y = 1, .x = 7}, chss::Position{.y = 4, .x = 4},
					   chss::Position{.y = 5, .x = 3}, chss::Position{.y = 6, .x = 2}, chss::Position{.y = 7, .x = 1},
					   chss::Position{.y = 4, .x = 6}, chss::Position{.y = 5, .x = 7}, chss::Position{.y = 2, .x = 5},
					   chss::Position{.y = 1, .x = 5}, chss::Position{.y = 0, .x = 5}, chss::Position{.y = 4, .x = 5},
					   chss::Position{.y = 5, .x = 5}, chss::Position{.y = 6, .x = 5}, chss::Position{.y = 7, .x = 5},
					   chss::Position{.y = 3, .x = 4}, chss::Position{.y = 3, .x = 3}, chss::Position{.y = 3, .x = 2},
					   chss::Position{.y = 3, .x = 1}, chss::Position{.y = 3, .x = 0}, chss::Position{.y = 3, .x = 6},
					   chss::Position{.y = 3, .x = 7}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Quen_Move_BlockedByPieceOfSameColor) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto queen_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(queen_position) = chss::Piece{chss::PieceType::Queen, playerColor};
		board.At(chss::Position{.y = 1, .x = 3}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		board.At(chss::Position{.y = 6, .x = 2}) = chss::Piece{chss::PieceType::Knight, playerColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Bishop, playerColor};
		board.At(chss::Position{.y = 1, .x = 5}) = chss::Piece{chss::PieceType::Rook, playerColor};
		board.At(chss::Position{.y = 6, .x = 5}) = chss::Piece{chss::PieceType::Queen, playerColor};
		board.At(chss::Position{.y = 3, .x = 1}) = chss::Piece{chss::PieceType::King, playerColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesQueen(board, queen_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 1, .x = 7},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 5, .x = 3},
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 5, .x = 5},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 3},
			chss::Position{.y = 3, .x = 2}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, Queen_Capture) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		const auto enemyColor = InverseColor(playerColor);
		constexpr auto queen_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(queen_position) = chss::Piece{chss::PieceType::Queen, playerColor};
		board.At(chss::Position{.y = 1, .x = 3}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		board.At(chss::Position{.y = 6, .x = 2}) = chss::Piece{chss::PieceType::Knight, enemyColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Bishop, enemyColor};
		board.At(chss::Position{.y = 1, .x = 5}) = chss::Piece{chss::PieceType::Rook, enemyColor};
		board.At(chss::Position{.y = 6, .x = 5}) = chss::Piece{chss::PieceType::Queen, enemyColor};
		board.At(chss::Position{.y = 3, .x = 1}) = chss::Piece{chss::PieceType::King, enemyColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesQueen(board, queen_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 1, .x = 3},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 1, .x = 7},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 5, .x = 3},
			chss::Position{.y = 6, .x = 2},
			chss::Position{.y = 4, .x = 6},
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 1, .x = 5},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 5, .x = 5},
			chss::Position{.y = 6, .x = 5},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 3},
			chss::Position{.y = 3, .x = 2},
			chss::Position{.y = 3, .x = 1},
			chss::Position{.y = 3, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, King_Move) {
	for (const auto king_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto king_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(king_position) = chss::Piece{chss::PieceType::King, king_color};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKing(board, king_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 6},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 4, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, King_Move_BlockedByEndOfBoard) {
	for (const auto king_color : {chss::Color::White, chss::Color::Black}) {
		constexpr auto king_position = chss::Position{.y = 0, .x = 0};
	auto board = chss::kEmptyBoard;
		board.At(king_position) = chss::Piece{chss::PieceType::King, king_color};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKing(board, king_position));
		constexpr auto expectedResult =
			std::array{chss::Position{.y = 0, .x = 1}, chss::Position{.y = 1, .x = 0}, chss::Position{.y = 1, .x = 1}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, King_Move_BlockedByPieceOfSameColor) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		constexpr auto king_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(king_position) = chss::Piece{chss::PieceType::King, playerColor};
		board.At(chss::Position{.y = 2, .x = 5}) = chss::Piece{chss::PieceType::Pawn, playerColor};
		board.At(chss::Position{.y = 3, .x = 4}) = chss::Piece{chss::PieceType::Bishop, playerColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::Rook, playerColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Queen, playerColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKing(board, king_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 4, .x = 5}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}

TEST(PieceMovements, King_Capture) {
	for (const auto playerColor : {chss::Color::White, chss::Color::Black}) {
		const auto enemyColor = InverseColor(playerColor);
		constexpr auto king_position = chss::Position{.y = 3, .x = 5};
	auto board = chss::kEmptyBoard;
		board.At(king_position) = chss::Piece{chss::PieceType::King, playerColor};
		board.At(chss::Position{.y = 2, .x = 5}) = chss::Piece{chss::PieceType::Pawn, enemyColor};
		board.At(chss::Position{.y = 3, .x = 4}) = chss::Piece{chss::PieceType::Bishop, enemyColor};
		board.At(chss::Position{.y = 3, .x = 6}) = chss::Piece{chss::PieceType::Rook, enemyColor};
		board.At(chss::Position{.y = 4, .x = 6}) = chss::Piece{chss::PieceType::Queen, enemyColor};
		const auto result = to_vector<chss::Position>(chss::MoveGeneration::PseudoLegalMovesKing(board, king_position));
		constexpr auto expectedResult = std::array{
			chss::Position{.y = 2, .x = 4},
			chss::Position{.y = 2, .x = 5},
			chss::Position{.y = 2, .x = 6},
			chss::Position{.y = 3, .x = 4},
			chss::Position{.y = 3, .x = 6},
			chss::Position{.y = 4, .x = 4},
			chss::Position{.y = 4, .x = 5},
			chss::Position{.y = 4, .x = 6}};
		EXPECT_THAT(result, testing::UnorderedElementsAreArray(expectedResult));
	}
}
