#pragma once

#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

constexpr auto kPawnMoveOffsets = std::array<std::pair<matrix::Direction2D, std::optional<chss::PieceType>>, 16>{
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		std::nullopt),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		chss::PieceType::Knight),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		chss::PieceType::Bishop),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		chss::PieceType::Rook),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = 0},
		chss::PieceType::Queen),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		std::nullopt),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
		std::nullopt),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		chss::PieceType::Knight),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		chss::PieceType::Bishop),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		chss::PieceType::Rook),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = -1},
		chss::PieceType::Queen),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
		chss::PieceType::Knight),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
		chss::PieceType::Bishop),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
		chss::PieceType::Rook),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +1, .deltaX = +1},
		chss::PieceType::Queen),
	std::pair<matrix::Direction2D, std::optional<chss::PieceType>>(
		matrix::Direction2D{.deltaY = +2, .deltaX = 0},
		std::nullopt),
};

constexpr std::size_t FindNextPawnMoveOffsetIndex(
	const chss::State& state,
	const chss::Position& pawnPosition,
	const std::size_t startIndex) {
	std::size_t i = startIndex;
	while (i < kPawnMoveOffsets.size()) {
		const auto position = state.activeColor == chss::Color::White ? pawnPosition + kPawnMoveOffsets[i].first
																	  : pawnPosition - kPawnMoveOffsets[i].first;
		switch (i) {
		case 0: { // Advance
			if (0 < position.y && position.y < 7 && !state.board.At(position).has_value()) {
				assert(state.board.IsInside(position));
				return i;
			}
			break;
		}
		case 1:
		case 2:
		case 3:
		case 4: { // Advance + Promotion
			 if ((position.y == 0 || position.y == 7) && !state.board.At(position).has_value()) {
				assert(state.board.IsInside(position));
				return i;
			}
			break;
		}
		case 5:
		case 6: { // Capture left and right
			if (state.board.IsInside(position) && (position.y > 0 && position.y < 7) &&
				((state.board.At(position).has_value() &&
				  state.board.At(position).value().color != state.activeColor) ||
				 state.enPassantTargetSquare == position)) {
				return i;
			}
			break;
		}
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14: { // Capture + Promotion
			if (state.board.IsInside(position) && (position.y == 0 || position.y == 7) &&
				((state.board.At(position).has_value() &&
				  state.board.At(position).value().color != state.activeColor) ||
				 state.enPassantTargetSquare == position)) {
				return i;
			}
			break;
		}
		case 15: { // Double Advance
			if ((pawnPosition.y == 1 && state.activeColor == chss::Color::White &&
				 !state.board.At(chss::Position{.y = 2, .x = pawnPosition.x}).has_value() &&
				 !state.board.At(chss::Position{.y = 3, .x = pawnPosition.x}).has_value()) ||
				(pawnPosition.y == 6 && state.activeColor == chss::Color::Black &&
				 !state.board.At(chss::Position{.y = 5, .x = pawnPosition.x}).has_value() &&
				 !state.board.At(chss::Position{.y = 4, .x = pawnPosition.x}).has_value())) {
				return i;
			}
			break;
		}
		}
		++i;
	}
	return i;
}

class PawnMovesGenerator {
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
				.to = mState.activeColor == chss::Color::White
					? mPawnPosition + kPawnMoveOffsets[mMoveOffsetIndex].first
					: mPawnPosition - kPawnMoveOffsets[mMoveOffsetIndex].first,
				.promotionType = kPawnMoveOffsets[mMoveOffsetIndex].second};
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
		chss::State mState;
		chss::Position mPawnPosition;
		std::size_t mMoveOffsetIndex;
	};

	constexpr explicit PawnMovesGenerator(const chss::State& state, const chss::Position& pawnPosition)
		: mState(state)
		, mPawnPosition(pawnPosition) {}

	[[nodiscard]] constexpr Iterator begin() const {
		return Iterator(mState, mPawnPosition);
	}

	[[nodiscard]] constexpr Sentinel end() const {
		return Sentinel{};
	}

private:
	chss::State mState;
	chss::Position mPawnPosition;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto PawnPseudoLegalMoves(const State& state, const Position& pawnPosition) {
	return detail::PawnMovesGenerator(state, pawnPosition);
}

} // namespace chss::move_generation
