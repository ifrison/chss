#include "MinMax.h"
#include "Evaluation.h"
#include "Movements.h"
#include "State.h"

namespace chss::search {

[[nodiscard]] int MinMax(const State& state, int depth) {
	if (depth == 0) {
		return evaluation::Evaluate(state.board);
	}
	int result = state.activeColor == Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	for (const auto [move, newState] : MoveGeneration::LegalMoves(state)) {
		const auto score = MinMax(newState, depth - 1);
		if (state.activeColor == Color::White) {
			result = std::max(result, score);
		} else {
			result = std::min(result, score);
		}
	}
	return result;
}

[[nodiscard]] MoveGeneration::Move Search(const State& state, int depth) {
	assert(depth > 0);
	auto resultScore = state.activeColor == Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = MoveGeneration::Move{.from = Position{.y = -1, .x = -1}, .to = Position{.y = -1, .x = -1}};
	for (const auto [move, newState] : MoveGeneration::LegalMoves(state)) {
		const auto score = MinMax(newState, depth - 1);
		if (state.activeColor == Color::White) {
			if (score > resultScore) {
				resultScore = score;
				resultMove = move;
			}
		} else {
			if (score < resultScore) {
				resultScore = score;
				resultMove = move;
			}
		}
	}
	return resultMove;
}

} // namespace chss::search
