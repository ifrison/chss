#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace {

constexpr auto kMoveOffsets = std::array<matrix::Direction2D, 8>{
	matrix::Direction2D{.deltaY = -2, .deltaX = -1},
	matrix::Direction2D{.deltaY = -2, .deltaX = +1},
	matrix::Direction2D{.deltaY = -1, .deltaX = -2},
	matrix::Direction2D{.deltaY = -1, .deltaX = +2},
	matrix::Direction2D{.deltaY = +1, .deltaX = -2},
	matrix::Direction2D{.deltaY = +1, .deltaX = +2},
	matrix::Direction2D{.deltaY = +2, .deltaX = -1},
	matrix::Direction2D{.deltaY = +2, .deltaX = +1},
};

constexpr std::size_t FindNextMoveOffsetIndex(const chss::State& state, const chss::Position& knightPosition, std::size_t startIndex) {
	for (std::size_t i = startIndex; i < kMoveOffsets.size(); ++i) {
		const auto position = knightPosition + kMoveOffsets[i];
		if (state.board.IsInside(position)) {
			const auto& pieceOpt = state.board.At(position);
			if (!pieceOpt.has_value() || pieceOpt.value().color == chss::InverseColor(state.activeColor)) {
				return i;
			}
		}
	}
	return kMoveOffsets.size();
}

}

namespace chss::move_generation {

[[nodiscard]] constexpr auto KnightPseudoLegalMoves(const State& state, const Position& knightPosition) {
	class Generator {
	public:
		class Sentinel {};

		class Iterator {
		public:
			constexpr explicit Iterator(const State& state, const Position& knightPosition)
			: mState(state)
			, mKnightPosition(knightPosition)
			, mMoveOffsetIndex(FindNextMoveOffsetIndex(state, knightPosition, 0)) {}

			[[nodiscard]] constexpr Move operator*() const {
				assert(mMoveOffsetIndex < kMoveOffsets.size());
				return Move{.from = mKnightPosition, .to = mKnightPosition + kMoveOffsets[mMoveOffsetIndex], .promotionType = std::nullopt};
			}

			constexpr Iterator& operator++() {
				assert(mMoveOffsetIndex < kMoveOffsets.size());
				mMoveOffsetIndex = FindNextMoveOffsetIndex(mState, mKnightPosition, mMoveOffsetIndex + 1);
				return *this;
			}

			[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
				return mMoveOffsetIndex == kMoveOffsets.size();
			}

			[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
				return mMoveOffsetIndex != kMoveOffsets.size();
			}

		private:
			const State& mState;
			const Position mKnightPosition;
			std::size_t mMoveOffsetIndex;
		};

		constexpr explicit Generator(const State& state, const Position& knightPosition)
			: mState(state)
			, mKnightPosition(knightPosition) {}

		[[nodiscard]] constexpr Iterator begin() const {
			return Iterator(mState, mKnightPosition);
		}

		[[nodiscard]] constexpr Sentinel end() const {
			return Sentinel{};
		}

	private:
		State mState;
		Position mKnightPosition;
	};

	return Generator(state, knightPosition);
}

}
