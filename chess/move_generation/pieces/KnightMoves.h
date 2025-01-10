#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

constexpr auto kKnightMoveOffsets = std::array<matrix::Direction2D, 8>{
	matrix::Direction2D{.deltaY = -2, .deltaX = -1},
	matrix::Direction2D{.deltaY = -2, .deltaX = +1},
	matrix::Direction2D{.deltaY = -1, .deltaX = -2},
	matrix::Direction2D{.deltaY = -1, .deltaX = +2},
	matrix::Direction2D{.deltaY = +1, .deltaX = -2},
	matrix::Direction2D{.deltaY = +1, .deltaX = +2},
	matrix::Direction2D{.deltaY = +2, .deltaX = -1},
	matrix::Direction2D{.deltaY = +2, .deltaX = +1},
};

constexpr std::size_t FindNextKnightMoveOffsetIndex(
	const chss::State& state,
	const chss::Position& knightPosition,
	const std::size_t startIndex) {
	std::size_t i = startIndex;
	while (i < kKnightMoveOffsets.size()) {
		const auto position = knightPosition + kKnightMoveOffsets[i];
		if (state.board.IsInside(position) &&
			(!state.board.At(position).has_value() || state.board.At(position).value().color != state.activeColor)) {
			return i;
		}
		++i;
	}
	return i;
}

class Generator {
public:
	class Sentinel {};

	class Iterator {
	public:
		constexpr explicit Iterator(const chss::State& state, const chss::Position& knightPosition)
			: mState(state)
			, mKnightPosition(knightPosition)
			, mMoveOffsetIndex(FindNextKnightMoveOffsetIndex(state, knightPosition, 0)) {}

		[[nodiscard]] constexpr chss::Move operator*() const {
			assert(mMoveOffsetIndex < kKnightMoveOffsets.size());
			return chss::Move{
				.from = mKnightPosition,
				.to = mKnightPosition + kKnightMoveOffsets[mMoveOffsetIndex],
				.promotionType = std::nullopt};
		}

		constexpr Iterator& operator++() {
			assert(mMoveOffsetIndex < kKnightMoveOffsets.size());
			mMoveOffsetIndex = FindNextKnightMoveOffsetIndex(mState, mKnightPosition, mMoveOffsetIndex + 1);
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			return mMoveOffsetIndex == kKnightMoveOffsets.size();
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			return mMoveOffsetIndex != kKnightMoveOffsets.size();
		}

	private:
		const chss::State& mState;
		const chss::Position mKnightPosition;
		std::size_t mMoveOffsetIndex;
	};

	constexpr explicit Generator(const chss::State& state, const chss::Position& knightPosition)
		: mState(state)
		, mKnightPosition(knightPosition) {}

	[[nodiscard]] constexpr Iterator begin() const { return Iterator(mState, mKnightPosition); }

	[[nodiscard]] constexpr Sentinel end() const { return Sentinel{}; }

private:
	chss::State mState;
	chss::Position mKnightPosition;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto KnightPseudoLegalMoves(const State& state, const Position& knightPosition) {
	return detail::Generator(state, knightPosition);
}

} // namespace chss::move_generation
