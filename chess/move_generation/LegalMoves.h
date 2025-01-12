#pragma once

#include "chess/move_generation/IsInCheck.h"
#include "chess/move_generation/MakeMove.h"
#include "chess/move_generation/PseudoLegalMoves.h"

namespace detail {

constexpr void FindNextLegalMove(const chss::State& state, auto& it, const auto& end) {
	while (it != end) {
		auto move = *it;
		const auto newState = chss::move_generation::MakeMove(state, move);
		const auto kingPosition = chss::move_generation::FindKing(newState.board, state.activeColor);
		if (!chss::move_generation::IsInCheck(newState.board, state.activeColor, kingPosition)) {
			return;
		}
		++it;
	}
}

class LegalMovesGenerator {
public:
	class Sentinel {};

	class Iterator {
	public:
		constexpr explicit Iterator(const chss::State& state)
			: mState(state)
			, mPseudoLegalMovesIt(chss::move_generation::PseudoLegalMoves(state).begin())
			, mPseudoLegalMovesEnd(chss::move_generation::PseudoLegalMoves(state).end()) {
			FindNextLegalMove(state, mPseudoLegalMovesIt, mPseudoLegalMovesEnd);
		}

		[[nodiscard]] constexpr chss::Move operator*() const {
			assert(mPseudoLegalMovesIt != mPseudoLegalMovesEnd);
			return *mPseudoLegalMovesIt;
		}

		constexpr Iterator& operator++() {
			assert(mPseudoLegalMovesIt != mPseudoLegalMovesEnd);
			++mPseudoLegalMovesIt;
			FindNextLegalMove(mState, mPseudoLegalMovesIt, mPseudoLegalMovesEnd);
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			return mPseudoLegalMovesIt == mPseudoLegalMovesEnd;
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			return mPseudoLegalMovesIt != mPseudoLegalMovesEnd;
		}

	private:
		chss::State mState;
		decltype(chss::move_generation::PseudoLegalMoves(std::declval<chss::State>()).begin()) mPseudoLegalMovesIt;
		decltype(chss::move_generation::PseudoLegalMoves(std::declval<chss::State>()).end()) mPseudoLegalMovesEnd;
	};

	constexpr explicit LegalMovesGenerator(const chss::State& state)
		: mState(state) {}

	[[nodiscard]] constexpr Iterator begin() const {
		return Iterator(mState);
	}

	[[nodiscard]] constexpr Sentinel end() const {
		return Sentinel{};
	}

private:
	chss::State mState;
};

} // namespace detail

namespace chss::move_generation {

[[nodiscard]] constexpr auto LegalMoves(const State& state) {
	return detail::LegalMovesGenerator(state);
}

} // namespace chss::move_generation
