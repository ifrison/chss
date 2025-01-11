#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

constexpr auto kBishopMoveOffsets = std::array<matrix::Direction2D, 4>{
	matrix::Direction2D{.deltaY = -1, .deltaX = -1},
	matrix::Direction2D{.deltaY = -1, .deltaX = +1},
	matrix::Direction2D{.deltaY = +1, .deltaX = -1},
	matrix::Direction2D{.deltaY = +1, .deltaX = +1},
};

constexpr auto kRookMoveOffsets = std::array<matrix::Direction2D, 4>{
	matrix::Direction2D{.deltaY = -1, .deltaX = 0},
	matrix::Direction2D{.deltaY = 0, .deltaX = -1},
	matrix::Direction2D{.deltaY = 0, .deltaX = +1},
	matrix::Direction2D{.deltaY = +1, .deltaX = 0},
};

constexpr auto kQueenMoveOffsets = std::array<matrix::Direction2D, 8>{
	matrix::Direction2D{.deltaY = -1, .deltaX = -1},
	matrix::Direction2D{.deltaY = -1, .deltaX = 0},
	matrix::Direction2D{.deltaY = -1, .deltaX = +1},
	matrix::Direction2D{.deltaY = 0, .deltaX = -1},
	matrix::Direction2D{.deltaY = 0, .deltaX = +1},
	matrix::Direction2D{.deltaY = +1, .deltaX = -1},
	matrix::Direction2D{.deltaY = +1, .deltaX = 0},
	matrix::Direction2D{.deltaY = +1, .deltaX = +1},
};

struct MoveOffsetIndexAndFactor {
	std::size_t index;
	int factor;
};

template<std::size_t S, std::array<matrix::Direction2D, S> kMoveOffsets>
constexpr MoveOffsetIndexAndFactor FindNextMoveOffsetIndexAndFactor(
	const chss::State& state,
	const chss::Position& piecePosition,
	const MoveOffsetIndexAndFactor startIndexAndFactor) {
	std::size_t i = startIndexAndFactor.index;
	int f = startIndexAndFactor.factor;
	if (f == 8) {
		f = 1;
		++i;
	}
	while (i < kMoveOffsets.size()) {
		const auto position = piecePosition + kMoveOffsets[i] * f;
		if (state.board.IsInside(position) &&
			(!state.board.At(position) || state.board.At(position).value().color != state.activeColor)) {
			return MoveOffsetIndexAndFactor{.index = i, .factor = f};
		}
		f = 1;
		++i;
	}
	return MoveOffsetIndexAndFactor{.index = i, .factor = f};
}

template<std::size_t S, std::array<matrix::Direction2D, S> kMoveOffsets>
class SlidingPieceMovesGenerator {
public:
	class Sentinel {};

	class Iterator {
	public:
		constexpr explicit Iterator(const chss::State& state, const chss::Position& piecePosition)
			: mState(state)
			, mPiecePosition(piecePosition)
			, mMoveOffsetIndexAndFactor(
				  FindNextMoveOffsetIndexAndFactor<S, kMoveOffsets>(
					  state,
					  piecePosition,
					  MoveOffsetIndexAndFactor{.index = 0, .factor = 1})) {}

		[[nodiscard]] constexpr chss::Move operator*() const {
			const auto [moveOffsetIndex, moveOffsetFactor] = mMoveOffsetIndexAndFactor;
			assert(moveOffsetIndex < kMoveOffsets.size());
			return chss::Move{
				.from = mPiecePosition,
				.to = mPiecePosition + kMoveOffsets[moveOffsetIndex] * moveOffsetFactor,
				.promotionType = std::nullopt};
		}

		constexpr Iterator& operator++() {
			const auto [moveOffsetIndex, moveOffsetFactor] = mMoveOffsetIndexAndFactor;
			assert(moveOffsetIndex < kMoveOffsets.size());
			const auto position = mPiecePosition + kMoveOffsets[moveOffsetIndex] * moveOffsetFactor;
			const auto& pieceOpt = mState.board.At(position);
			if (pieceOpt.has_value()) {
				assert(pieceOpt.value().color != mState.activeColor);
				mMoveOffsetIndexAndFactor = FindNextMoveOffsetIndexAndFactor<S, kMoveOffsets>(
					mState,
					mPiecePosition,
					MoveOffsetIndexAndFactor{.index = moveOffsetIndex + 1, .factor = 1});
			} else {
				mMoveOffsetIndexAndFactor = FindNextMoveOffsetIndexAndFactor<S, kMoveOffsets>(
					mState,
					mPiecePosition,
					MoveOffsetIndexAndFactor{.index = moveOffsetIndex, .factor = moveOffsetFactor + 1});
			}
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			const auto [moveOffsetIndex, moveOffsetFactor] = mMoveOffsetIndexAndFactor;
			return moveOffsetIndex == kMoveOffsets.size();
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			const auto [moveOffsetIndex, moveOffsetFactor] = mMoveOffsetIndexAndFactor;
			return moveOffsetIndex != kMoveOffsets.size();
		}

	private:
		chss::State mState;
		chss::Position mPiecePosition;
		MoveOffsetIndexAndFactor mMoveOffsetIndexAndFactor;
	};

	constexpr explicit SlidingPieceMovesGenerator(const chss::State& state, const chss::Position& knightPosition)
		: mState(state)
		, mPiecePosition(knightPosition) {}

	[[nodiscard]] constexpr Iterator begin() const {
		return Iterator(mState, mPiecePosition);
	}

	[[nodiscard]] constexpr Sentinel end() const {
		return Sentinel{};
	}

private:
	chss::State mState;
	chss::Position mPiecePosition;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto BishopPseudoLegalMoves(const State& state, const Position& knightPosition) {
	return detail::SlidingPieceMovesGenerator<4, detail::kBishopMoveOffsets>(state, knightPosition);
}

[[nodiscard]] constexpr auto RookPseudoLegalMoves(const State& state, const Position& knightPosition) {
	return detail::SlidingPieceMovesGenerator<4, detail::kRookMoveOffsets>(state, knightPosition);
}

[[nodiscard]] constexpr auto QueenPseudoLegalMoves(const State& state, const Position& knightPosition) {
	return detail::SlidingPieceMovesGenerator<8, detail::kQueenMoveOffsets>(state, knightPosition);
}

} // namespace chss::move_generation
