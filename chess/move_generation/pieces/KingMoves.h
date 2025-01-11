#pragma once

#include "chess/move_generation/IsInCheck.h"
#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

constexpr auto kKingMoveOffsets = std::array<matrix::Direction2D, 10>{
	matrix::Direction2D{.deltaY = -1, .deltaX = -1},
	matrix::Direction2D{.deltaY = -1, .deltaX = 0},
	matrix::Direction2D{.deltaY = -1, .deltaX = +1},
	matrix::Direction2D{.deltaY = 0, .deltaX = -1},
	matrix::Direction2D{.deltaY = 0, .deltaX = +1},
	matrix::Direction2D{.deltaY = +1, .deltaX = -1},
	matrix::Direction2D{.deltaY = +1, .deltaX = 0},
	matrix::Direction2D{.deltaY = +1, .deltaX = +1},
	matrix::Direction2D{.deltaY = +0, .deltaX = -2},
	matrix::Direction2D{.deltaY = +0, .deltaX = +2},
};

constexpr std::size_t FindNextKingMoveOffsetIndex(
	const chss::State& state,
	const chss::Position& kingPosition,
	const std::size_t startIndex) {
	std::size_t i = startIndex;
	while (i < kKingMoveOffsets.size()) {
		const auto position = kingPosition + kKingMoveOffsets[i];
		switch (i) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7: {
			if (state.board.IsInside(position)) {
				const auto& pieceOpt = state.board.At(position);
				if (!pieceOpt.has_value() || pieceOpt.value().color != state.activeColor) {
					return i;
				}
			}
			break;
		}
		case 8: { // Castling Queen side
			const auto y = state.activeColor == chss::Color::White ? 0 : 7;
			const bool isQueenSideAvailable = state.activeColor == chss::Color::White
				? state.castlingAvailabilities.white.isQueenSideAvailable
				: state.castlingAvailabilities.black.isQueenSideAvailable;
			if (isQueenSideAvailable && kingPosition == chss::Position{.y = y, .x = 4}) {
				bool isInBetweenEmpty = true;
				for (int x = 3; x >= 1; --x) {
					const auto to = chss::Position{.y = y, .x = x};
					isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
				}
				bool isInBetweenSafe = !chss::move_generation::IsInCheck(state.board, state.activeColor, kingPosition);
				for (int x = 3; x >= 2; --x) {
					const auto inBetweenPosition = chss::Position{.y = y, .x = x};
					auto newBoard = state.board;
					newBoard.At(inBetweenPosition) = newBoard.At(kingPosition);
					newBoard.At(kingPosition) = std::nullopt;
					isInBetweenSafe = isInBetweenSafe &&
						!chss::move_generation::IsInCheck(newBoard, state.activeColor, inBetweenPosition);
				}
				if (isInBetweenEmpty && isInBetweenSafe) {
					return i;
				}
			}
			break;
		}
		case 9: { // Castling King side
			const auto y = state.activeColor == chss::Color::White ? 0 : 7;
			const bool isKingSideAvailable = state.activeColor == chss::Color::White
				? state.castlingAvailabilities.white.isKingSideAvailable
				: state.castlingAvailabilities.black.isKingSideAvailable;
			if (isKingSideAvailable && kingPosition == chss::Position{.y = y, .x = 4}) {
				bool isInBetweenEmpty = true;
				for (int x = 5; x <= 6; ++x) {
					const auto to = chss::Position{.y = y, .x = x};
					isInBetweenEmpty = isInBetweenEmpty && !state.board.At(to).has_value();
				}
				bool isInBetweenSafe = !chss::move_generation::IsInCheck(state.board, state.activeColor, kingPosition);
				for (int x = 5; x <= 6; ++x) {
					const auto inBetweenPosition = chss::Position{.y = y, .x = x};
					auto newBoard = state.board;
					newBoard.At(inBetweenPosition) = newBoard.At(kingPosition);
					newBoard.At(kingPosition) = std::nullopt;
					isInBetweenSafe = isInBetweenSafe &&
						!chss::move_generation::IsInCheck(newBoard, state.activeColor, inBetweenPosition);
				}
				if (isInBetweenEmpty && isInBetweenSafe) {
					return i;
				}
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
		constexpr explicit Iterator(const chss::State& state, const chss::Position& kingPosition)
			: mState(state)
			, mKingPosition(kingPosition)
			, mMoveOffsetIndex(FindNextKingMoveOffsetIndex(state, kingPosition, 0)) {}

		[[nodiscard]] constexpr chss::Move operator*() const {
			assert(mMoveOffsetIndex < kKingMoveOffsets.size());
			return chss::Move{
				.from = mKingPosition,
				.to = mKingPosition + kKingMoveOffsets[mMoveOffsetIndex],
				.promotionType = std::nullopt};
		}

		constexpr Iterator& operator++() {
			assert(mMoveOffsetIndex < kKingMoveOffsets.size());
			mMoveOffsetIndex = FindNextKingMoveOffsetIndex(mState, mKingPosition, mMoveOffsetIndex + 1);
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			return mMoveOffsetIndex == kKingMoveOffsets.size();
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			return mMoveOffsetIndex != kKingMoveOffsets.size();
		}

	private:
		const chss::State& mState;
		const chss::Position mKingPosition;
		std::size_t mMoveOffsetIndex;
	};

	constexpr explicit Generator(const chss::State& state, const chss::Position& kingPosition)
		: mState(state)
		, mKingPosition(kingPosition) {}

	[[nodiscard]] constexpr Iterator begin() const {
		return Iterator(mState, mKingPosition);
	}

	[[nodiscard]] constexpr Sentinel end() const {
		return Sentinel{};
	}

private:
	chss::State mState;
	chss::Position mKingPosition;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto KingPseudoLegalMoves(const State& state, const Position& kingPosition) {
	return detail::Generator(state, kingPosition);
}

} // namespace chss::move_generation
