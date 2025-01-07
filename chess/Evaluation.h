#pragma once

#include "Board.h"

namespace chss::evaluation {

[[nodiscard]] constexpr int Evaluate(const Board& board) {
	constexpr auto kPieceValues = std::array<int, 6>{1, 3, 3, 5, 9, 200};
	int result = 0;
	for (const auto position : ForEach(board.GetSize())) {
		const auto pieceOpt = board.At(position);
		if (!pieceOpt.has_value()) {
			continue;
		}
		const auto [type, color] = pieceOpt.value();
		const auto typeIndex = static_cast<std::underlying_type_t<chss::PieceType>>(type);
		const auto colorFactor = color == Color::White ? +1 : -1;
		const auto pieceValue = kPieceValues[typeIndex];
		result += colorFactor * pieceValue;
	}
	return result;
}

} // namespace chss::evaluation
