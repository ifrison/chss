#pragma once

#include "evaluation/Evaluation.h"
#include "move_generation/LegalMoves.h"
#include "representation/Move.h"
#include "representation/State.h"

#include <atomic>

namespace chss::search {

[[nodiscard]] constexpr int Search(const chss::State& state, int depth, const std::atomic_flag& stop) {
	if (depth == 0) {
		return chss::evaluation::Evaluate(state.board);
	}
	int result =
		state.activeColor == chss::Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if !consteval {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto score = Search(newState, depth - 1, stop);
		if (state.activeColor == chss::Color::White) {
			result = std::max(result, score);
		} else {
			result = std::min(result, score);
		}
	}
	return result;
}

[[nodiscard]] constexpr std::pair<int, chss::Move> SearchMove(
	const chss::State& state,
	int depth,
	const std::atomic_flag& stop) {
	assert(depth > 0);
	auto resultScore =
		state.activeColor == chss::Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = chss::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}};
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if !consteval {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto score = Search(newState, depth - 1, stop);
		if (state.activeColor == chss::Color::White) {
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
	return std::pair<int, chss::Move>(resultScore, resultMove);
}

} // namespace chss::search
