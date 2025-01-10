#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

constexpr auto kPawnMoveOffsets = std::array<matrix::Direction2D, 4>{
	matrix::Direction2D{.deltaY = +1, .deltaX = 0},
	matrix::Direction2D{.deltaY = +1, .deltaX = -1},
	matrix::Direction2D{.deltaY = +1, .deltaX = +1},
	matrix::Direction2D{.deltaY = +2, .deltaX = 0},
};

constexpr std::size_t FindNextPawnMoveOffsetIndex(
	const chss::State& state,
	const chss::Position& pawnPosition,
	const std::size_t startIndex) {
	std::size_t i = startIndex;
	while (i < kPawnMoveOffsets.size()) {
		const auto position = state.activeColor == chss::Color::White ? pawnPosition + kPawnMoveOffsets[i] : pawnPosition - kPawnMoveOffsets[i];
		switch (i) {
		case 0: { // Advance
			if (state.board.IsInside(position) && !state.board.At(position).has_value()) {
				return i;
			}
			break;
		}
		case 1:
		case 2: { // Capture
			if (state.board.IsInside(position) &&
				state.board.At(position).has_value() && state.board.At(position).value().color != state.activeColor) {
				return i;
			}
			break;
		}
		case 3: { // Double Advance
			if ((pawnPosition.y == 1 && state.activeColor == chss::Color::White && !state.board.At(chss::Position{.y = 2, .x = pawnPosition.x}).has_value() && !state.board.At(chss::Position{.y = 3, .x = pawnPosition.x}).has_value()) ||
				(pawnPosition.y == 6 && state.activeColor == chss::Color::White && !state.board.At(chss::Position{.y = 5, .x = pawnPosition.x}).has_value() && !state.board.At(chss::Position{.y = 4, .x = pawnPosition.x}).has_value())) {
				return i;
			}
			break;
		}
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
		constexpr explicit Iterator(const chss::State& state, const chss::Position& pawnPosition)
			: mState(state)
			, mPawnPosition(pawnPosition)
			, mMoveOffsetIndex(FindNextPawnMoveOffsetIndex(state, pawnPosition, 0)) {}

		[[nodiscard]] constexpr chss::Move operator*() const {
			assert(mMoveOffsetIndex < kPawnMoveOffsets.size());
			return chss::Move{
				.from = mPawnPosition,
				.to = mState.activeColor == chss::Color::White ? mPawnPosition + kPawnMoveOffsets[mMoveOffsetIndex] : mPawnPosition - kPawnMoveOffsets[mMoveOffsetIndex],
				.promotionType = std::nullopt};
		}

		constexpr Iterator& operator++() {
			assert(mMoveOffsetIndex < kPawnMoveOffsets.size());
			mMoveOffsetIndex = FindNextPawnMoveOffsetIndex(mState, mPawnPosition, mMoveOffsetIndex + 1);
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			return mMoveOffsetIndex == kPawnMoveOffsets.size();
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			return mMoveOffsetIndex != kPawnMoveOffsets.size();
		}

	private:
		const chss::State& mState;
		const chss::Position mPawnPosition;
		std::size_t mMoveOffsetIndex;
	};

	constexpr explicit Generator(const chss::State& state, const chss::Position& pawnPosition)
		: mState(state)
		, mPawnPosition(pawnPosition) {}

	[[nodiscard]] constexpr Iterator begin() const { return Iterator(mState, mPawnPosition); }

	[[nodiscard]] constexpr Sentinel end() const { return Sentinel{}; }

private:
	chss::State mState;
	chss::Position mPawnPosition;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto PawnPseudoLegalMoves(const State& state, const Position& pawnPosition) {
	return detail::Generator(state, pawnPosition);
}

} // namespace chss::move_generation
