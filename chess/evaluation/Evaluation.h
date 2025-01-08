#pragma once

#include <chess/Board.h>

namespace chss::evaluation {

[[nodiscard]] constexpr int Evaluate(const Board& board) {
	// clang-format off
	constexpr auto kCentralityValues = matrix::Matrix2D<int, matrix::Size2D{.sizeX = 8, .sizeY = 8}>(
		std::array<int, 64>{
			1, 1, 1, 1, 1, 1, 1, 1,
			1, 2, 2, 2, 2, 2, 2, 1,
			1, 2, 3, 3, 3, 3, 2, 1,
			1, 2, 3, 4, 4, 3, 2, 1,
			1, 2, 3, 4, 4, 3, 2, 1,
			1, 2, 3, 3, 3, 3, 2, 1,
			1, 2, 2, 2, 2, 2, 2, 1,
			1, 1, 1, 1, 1, 1, 1, 1,
		}
	);
	// clang-format on
	constexpr auto kPieceValues = std::array<int, 6>{100, 300, 300, 500, 900, 20000};
	int result = 0;
	for (const auto position : ForEach(board.GetSize())) {
		const auto pieceOpt = board.At(position);
		if (!pieceOpt.has_value()) {
			continue;
		}
		const auto [type, color] = pieceOpt.value();
		const auto typeIndex = static_cast<std::underlying_type_t<chss::PieceType>>(type);
		const auto pieceValue = kPieceValues[typeIndex];
		const auto centralityValue = kCentralityValues.At(position);
		const auto value = color == Color::White ? +(pieceValue + centralityValue) : -(pieceValue + centralityValue);
		result += value;
	}
	return result;
}

} // namespace chss::evaluation
