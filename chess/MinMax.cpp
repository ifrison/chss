#include "MinMax.h"
#include "Evaluation.h"
#include "Movements.h"
#include "State.h"

namespace chss::search {

[[nodiscard]] int Search0(const State& state, int depth, const std::atomic_flag& stop) {
	if (depth == 0) {
		return evaluation::Evaluate(state.board);
	}
	int result = state.activeColor == Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	for (const auto [move, newState] : MoveGeneration::LegalMoves(state)) {
		if (stop.test()) {
			break;
		}
		const auto score = Search0(newState, depth - 1, stop);
		if (state.activeColor == Color::White) {
			result = std::max(result, score);
		} else {
			result = std::min(result, score);
		}
	}
	return result;
}

[[nodiscard]] std::tuple<int, MoveGeneration::Move> Search1(const State& state, int depth, const std::atomic_flag& stop) {
	assert(depth > 0);
	auto resultScore = state.activeColor == Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = MoveGeneration::Move{.from = Position{.y = -1, .x = -1}, .to = Position{.y = -1, .x = -1}};
	for (const auto [move, newState] : MoveGeneration::LegalMoves(state)) {
		if (stop.test()) {
			break;
		}
		const auto score = Search0(newState, depth - 1, stop);
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
	return std::tuple<int, MoveGeneration::Move>(resultScore, resultMove);
}

[[nodiscard]] std::tuple<int, MoveGeneration::Move, MoveGeneration::Move> Search2(const State& state, int depth, const std::atomic_flag& stop) {
	assert(depth > 1);
	auto resultScore = state.activeColor == Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = MoveGeneration::Move{.from = Position{.y = -1, .x = -1}, .to = Position{.y = -1, .x = -1}};
	auto resultPonderMove = MoveGeneration::Move{.from = Position{.y = -1, .x = -1}, .to = Position{.y = -1, .x = -1}};
	for (const auto [move, newState] : MoveGeneration::LegalMoves(state)) {
		if (stop.test()) {
			break;
		}
		const auto [score, ponderMove] = Search1(newState, depth - 1, stop);
		if (state.activeColor == Color::White) {
			if (score > resultScore) {
				resultScore = score;
				resultMove = move;
				resultPonderMove = ponderMove;
			}
		} else {
			if (score < resultScore) {
				resultScore = score;
				resultMove = move;
				resultPonderMove = ponderMove;
			}
		}
	}
	return std::tuple<int, MoveGeneration::Move, MoveGeneration::Move>(resultScore, resultMove, resultPonderMove);
}

[[nodiscard]] std::pair<MoveGeneration::Move, MoveGeneration::Move> Search(const State& state, int depth, const std::atomic_flag& stop) {
	const auto [score, move, ponderMove] = Search2(state, depth, stop);
	return std::pair<MoveGeneration::Move, MoveGeneration::Move>(move, ponderMove);
}

} // namespace chss::search
