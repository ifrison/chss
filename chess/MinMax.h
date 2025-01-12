#pragma once

#include "evaluation/Evaluation.h"
#include "move_generation/LegalMoves.h"
#include "representation/Move.h"
#include "representation/State.h"

#include <atomic>

namespace detail {

[[nodiscard]] constexpr int Search0(const chss::State& state, int depth, const std::atomic_flag& stop) {
	if (depth == 0) {
		return chss::evaluation::Evaluate(state.board);
	}
	int result =
		state.activeColor == chss::Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if constexpr (!std::is_constant_evaluated()) {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto score = Search0(newState, depth - 1, stop);
		if (state.activeColor == chss::Color::White) {
			result = std::max(result, score);
		} else {
			result = std::min(result, score);
		}
	}
	return result;
}

[[nodiscard]] constexpr std::tuple<int, chss::Move> Search1(
	const chss::State& state,
	int depth,
	const std::atomic_flag& stop) {
	assert(depth > 0);
	auto resultScore = state.activeColor == chss::Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = chss::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}};
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if constexpr (!std::is_constant_evaluated()) {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto score = Search0(newState, depth - 1, stop);
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
	return std::tuple<int, chss::Move>(resultScore, resultMove);
}

[[nodiscard]] constexpr std::tuple<int, chss::Move, chss::Move> Search2(
	const chss::State& state,
	int depth,
	const std::atomic_flag& stop) {
	assert(depth > 1);
	auto resultScore =
		state.activeColor == chss::Color::White ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
	auto resultMove = chss::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}};
	auto resultPonderMove =
		chss::Move{.from = chss::Position{.y = -1, .x = -1}, .to = chss::Position{.y = -1, .x = -1}};
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if constexpr (!std::is_constant_evaluated()) {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto [score, ponderMove] = Search1(newState, depth - 1, stop);
		if (state.activeColor == chss::Color::White) {
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
	return std::tuple<int, chss::Move, chss::Move>(resultScore, resultMove, resultPonderMove);
}

} // namespace detail

namespace chss::search {

[[nodiscard]] constexpr std::pair<Move, Move> Search(const State& state, int depth, const std::atomic_flag& stop) {
	const auto [score, move, ponderMove] = detail::Search2(state, depth, stop);
	return std::pair<Move, Move>(move, ponderMove);
}

} // namespace chss::search
