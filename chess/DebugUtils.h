#pragma once

#include "Board.h"

#include <ostream>

namespace chss {

namespace debug {

char PieceTypeToChar(const PieceType& pieceType);

std::string PositionToString(Position position);

void PrintBoard(const Board& board, std::ostream& os);

}

}
