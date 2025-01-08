#pragma once

#include "Board.h"

#include <ostream>

namespace chss::debug {

char PieceTypeToChar(const PieceType& pieceType);

std::string PositionToString(Position position);

} // namespace chss::debug
