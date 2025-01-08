#pragma once

#include "representation/Board.h"

#include <generator>

namespace chss {

struct State;

namespace MoveGeneration {

[[nodiscard]] std::generator<Position> PseudoLegalMovesPawn(const Board& board, const Position& pawnPosition);
[[nodiscard]] std::generator<Position> PseudoLegalMovesKnight(const Board& board, const Position& knightPosition);
[[nodiscard]] std::generator<Position> PseudoLegalMovesBishop(const Board& board, const Position& bishopPosition);
[[nodiscard]] std::generator<Position> PseudoLegalMovesRook(const Board& board, const Position& rookPosition);
[[nodiscard]] std::generator<Position> PseudoLegalMovesQueen(const Board& board, const Position& queenPosition);
[[nodiscard]] std::generator<Position> PseudoLegalMovesKing(const Board& board, const Position& kingPosition);

} // namespace MoveGeneration

} // namespace chss
