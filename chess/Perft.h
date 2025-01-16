#pragma once

#include "move_generation/LegalMoves.h"
#include "representation/Move.h"
#include "representation/State.h"

#include <concurrency/TaskQueue.h>

namespace chss::move_generation {

[[nodiscard]] constexpr std::int64_t Perft(const State& state, int depth, std::atomic_flag& stop);

}

namespace detail {

inline void CreatePerfTasks(
	const chss::State& state,
	int depth,
	std::atomic_flag& stop,
	concurrency::TaskQueue& taskQueue,
	std::vector<std::future<std::int64_t>>& futures) {
	if (depth <= 4) {
		auto future = taskQueue.PushBack(std::function<std::int64_t()>([state, depth, &stop]() {
			return chss::move_generation::Perft(state, depth, stop);
		}));
		futures.push_back(std::move(future));
		return;
	}
	for (const auto move : chss::move_generation::LegalMoves(state)) {
		if (stop.test()) {
			break;
		}
		const auto newState = chss::move_generation::MakeMove(state, move);
		CreatePerfTasks(newState, depth - 1, stop, taskQueue, futures);
	}
}

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr std::int64_t Perft(const State& state, int depth, std::atomic_flag& stop) {
	if (depth == 0) {
		return 1;
	}
	std::int64_t nodesVisited = 0;
	for (const auto move : LegalMoves(state)) {
		if !consteval {
			if (stop.test()) {
				break;
			}
		}
		const auto newState = MakeMove(state, move);
		const std::int64_t newNodesVisited = Perft(newState, depth - 1, stop);
		nodesVisited += newNodesVisited;
	}
	return nodesVisited;
}

[[nodiscard]] inline std::int64_t ParallelPerft(const State& state, int depth, std::atomic_flag& stop) {
	auto taskQueue = concurrency::TaskQueue(static_cast<int>(std::thread::hardware_concurrency()));
	auto futures = std::vector<std::future<std::int64_t>>();
	detail::CreatePerfTasks(state, depth, stop, taskQueue, futures);
	std::int64_t nodesVisited = 0;
	for (auto& future : futures) {
		nodesVisited += future.get();
	}
	return nodesVisited;
}

} // namespace chss::move_generation
