#pragma once

#include "chess/move_generation/pieces/KingMoves.h"
#include "chess/move_generation/pieces/KnightMoves.h"
#include "chess/move_generation/pieces/PawnMoves.h"
#include "chess/move_generation/pieces/SlidingPieceMoves.h"
#include "chess/representation/Move.h"
#include "chess/representation/State.h"

namespace detail {

struct PawnState {
	using Iterator = decltype(chss::move_generation::PawnPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::PawnPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

struct KnightState {
	using Iterator = decltype(chss::move_generation::KnightPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::KnightPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

struct BishopState {
	using Iterator = decltype(chss::move_generation::BishopPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::BishopPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

struct RookState {
	using Iterator = decltype(chss::move_generation::RookPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::RookPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

struct QueenState {
	using Iterator = decltype(chss::move_generation::QueenPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::QueenPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

struct KingState {
	using Iterator = decltype(chss::move_generation::KingPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .begin());
	using Sentinel = decltype(chss::move_generation::KingPseudoLegalMoves(
								  std::declval<chss::State>(),
								  std::declval<chss::Position>())
								  .end());
	Iterator it;
	Sentinel end;
};

using PieceState = std::variant<PawnState, KnightState, BishopState, RookState, QueenState, KingState>;

struct MovePositionAndPieceState {
	chss::Position position;
	PieceState pieceState;
};

[[nodiscard]] constexpr MovePositionAndPieceState FindFirstMove(const chss::State& state) {
	for (chss::Position position : matrix::ForEach(state.board.GetSize())) {
		const auto& pieceOpt = state.board.At(position);
		if (pieceOpt.has_value() && pieceOpt.value().color == state.activeColor) {
			switch (pieceOpt.value().type) {
			case chss::PieceType::Pawn:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = PawnState{
						.it = chss::move_generation::PawnPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::PawnPseudoLegalMoves(state, position).end()}};
			case chss::PieceType::Knight:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = KnightState{
						.it = chss::move_generation::KnightPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::KnightPseudoLegalMoves(state, position).end()}};
			case chss::PieceType::Bishop:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = BishopState{
						.it = chss::move_generation::BishopPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::BishopPseudoLegalMoves(state, position).end()}};
			case chss::PieceType::Rook:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = RookState{
						.it = chss::move_generation::RookPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::RookPseudoLegalMoves(state, position).end()}};
			case chss::PieceType::Queen:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = QueenState{
						.it = chss::move_generation::QueenPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::QueenPseudoLegalMoves(state, position).end()}};
			case chss::PieceType::King:
				return MovePositionAndPieceState{
					.position = position,
					.pieceState = KingState{
						.it = chss::move_generation::KingPseudoLegalMoves(state, position).begin(),
						.end = chss::move_generation::KingPseudoLegalMoves(state, position).end()}};
			}
		}
	}
	assert(false);
	return MovePositionAndPieceState{
		.position = chss::Position{.y = state.board.GetSize().sizeY, .x = state.board.GetSize().sizeX},
		.pieceState = PawnState{
			.it = chss::move_generation::PawnPseudoLegalMoves(state, chss::Position{.y = 7, .x = 7}).begin(),
			.end = PawnState::Sentinel{}}};
}

[[nodiscard]] constexpr MovePositionAndPieceState FindNextMove(
	const chss::State& state,
	const MovePositionAndPieceState& startMove) {
	return std::visit(
		[position = startMove.position, &state](auto pieceState) -> MovePositionAndPieceState {
			++pieceState.it;
			if (pieceState.it != pieceState.end) {
				return MovePositionAndPieceState{.position = position, .pieceState = pieceState};
			}
			for (int y = position.y; y < state.board.GetSize().sizeY; ++y) {
				for (int x = position.x + 1; x < state.board.GetSize().sizeX; ++x) {
					const auto newPosition = chss::Position{.y = y, .x = x};
					const auto& pieceOpt = state.board.At(newPosition);
					if (pieceOpt.has_value() && pieceOpt.value().color == state.activeColor) {
						switch (pieceOpt.value().type) {
						case chss::PieceType::Pawn:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = PawnState{
									.it = chss::move_generation::PawnPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::PawnPseudoLegalMoves(state, newPosition).end()}};
						case chss::PieceType::Knight:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = KnightState{
									.it = chss::move_generation::KnightPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::KnightPseudoLegalMoves(state, newPosition).end()}};
						case chss::PieceType::Bishop:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = BishopState{
									.it = chss::move_generation::BishopPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::BishopPseudoLegalMoves(state, newPosition).end()}};
						case chss::PieceType::Rook:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = RookState{
									.it = chss::move_generation::RookPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::RookPseudoLegalMoves(state, newPosition).end()}};
						case chss::PieceType::Queen:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = QueenState{
									.it = chss::move_generation::QueenPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::QueenPseudoLegalMoves(state, newPosition).end()}};
						case chss::PieceType::King:
							return MovePositionAndPieceState{
								.position = newPosition,
								.pieceState = KingState{
									.it = chss::move_generation::KingPseudoLegalMoves(state, newPosition).begin(),
									.end = chss::move_generation::KingPseudoLegalMoves(state, newPosition).end()}};
						}
					}
				}
			}
			return MovePositionAndPieceState{
				.position = chss::Position{.y = state.board.GetSize().sizeY, .x = state.board.GetSize().sizeX},
				.pieceState = PawnState{
					.it = chss::move_generation::PawnPseudoLegalMoves(state, chss::Position{.y = 7, .x = 7}).begin(),
					.end = PawnState::Sentinel{}}};
		},
		startMove.pieceState);
}

class PseudoLegalMovesGenerator {
public:
	class Sentinel {};

	class Iterator {
	public:
		constexpr explicit Iterator(const chss::State& state)
			: mState(state)
			, mPositionAndPieceState(FindFirstMove(state)) {}

		[[nodiscard]] constexpr chss::Move operator*() const {
			assert(mPositionAndPieceState.position.y < mState.board.GetSize().sizeY);
			return std::visit(
				[](const auto& state) -> chss::Move { return *state.it; },
				mPositionAndPieceState.pieceState);
		}

		constexpr Iterator& operator++() {
			assert(mPositionAndPieceState.position.y < mState.board.GetSize().sizeY);
			mPositionAndPieceState = FindNextMove(mState, mPositionAndPieceState);
			return *this;
		}

		[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
			return mPositionAndPieceState.position.y == mState.board.GetSize().sizeY;
		}

		[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
			return mPositionAndPieceState.position.y != mState.board.GetSize().sizeY;
		}

	private:
		chss::State mState;
		MovePositionAndPieceState mPositionAndPieceState;
	};

	constexpr explicit PseudoLegalMovesGenerator(const chss::State& state)
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

[[nodiscard]] constexpr auto PseudoLegalMoves(const State& state) {
	return detail::PseudoLegalMovesGenerator(state);
}

} // namespace chss::move_generation
