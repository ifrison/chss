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
	int y = 0;
	int x = 0;
	while (y < state.board.GetSize().sizeY) {
		while (x < state.board.GetSize().sizeX) {
			const auto position = chss::Position{.y = y, .x = x};
			const auto& pieceOpt = state.board.At(position);
			if (pieceOpt.has_value() && pieceOpt.value().color == state.activeColor) {
				switch (pieceOpt.value().type) {
				case chss::PieceType::Pawn: {
					const auto pawnGenerator = chss::move_generation::PawnPseudoLegalMoves(state, position);
					auto it = pawnGenerator.begin();
					auto end = pawnGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = PawnState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				case chss::PieceType::Knight: {
					const auto knightGenerator = chss::move_generation::KnightPseudoLegalMoves(state, position);
					auto it = knightGenerator.begin();
					auto end = knightGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = KnightState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				case chss::PieceType::Bishop: {
					const auto bishopGenerator = chss::move_generation::BishopPseudoLegalMoves(state, position);
					auto it = bishopGenerator.begin();
					auto end = bishopGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = BishopState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				case chss::PieceType::Rook: {
					const auto rookGenerator = chss::move_generation::RookPseudoLegalMoves(state, position);
					auto it = rookGenerator.begin();
					auto end = rookGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = RookState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				case chss::PieceType::Queen: {
					const auto queenGenerator = chss::move_generation::QueenPseudoLegalMoves(state, position);
					auto it = queenGenerator.begin();
					auto end = queenGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = QueenState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				case chss::PieceType::King: {
					const auto kingGenerator = chss::move_generation::KingPseudoLegalMoves(state, position);
					auto it = kingGenerator.begin();
					auto end = kingGenerator.end();
					if (it != end) {
						return MovePositionAndPieceState{
							.position = position,
							.pieceState = KingState{.it = std::move(it), .end = std::move(end)}};
					}
					break;
				}
				}
			}
			++x;
		}
		x = 0;
		++y;
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
			int y = position.y;
			int x = position.x + 1;
			while (y < state.board.GetSize().sizeY) {
				while (x < state.board.GetSize().sizeX) {
					const auto newPosition = chss::Position{.y = y, .x = x};
					const auto& pieceOpt = state.board.At(newPosition);
					if (pieceOpt.has_value() && pieceOpt.value().color == state.activeColor) {
						switch (pieceOpt.value().type) {
						case chss::PieceType::Pawn: {
							const auto pawnGenerator = chss::move_generation::PawnPseudoLegalMoves(state, newPosition);
							auto it = pawnGenerator.begin();
							auto end = pawnGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = PawnState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						case chss::PieceType::Knight: {
							const auto knightGenerator = chss::move_generation::KnightPseudoLegalMoves(state, newPosition);
							auto it = knightGenerator.begin();
							auto end = knightGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = KnightState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						case chss::PieceType::Bishop: {
							const auto bishopGenerator = chss::move_generation::BishopPseudoLegalMoves(state, newPosition);
							auto it = bishopGenerator.begin();
							auto end = bishopGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = BishopState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						case chss::PieceType::Rook: {
							const auto rookGenerator = chss::move_generation::RookPseudoLegalMoves(state, newPosition);
							auto it = rookGenerator.begin();
							auto end = rookGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = RookState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						case chss::PieceType::Queen: {
							const auto queenGenerator = chss::move_generation::QueenPseudoLegalMoves(state, newPosition);
							auto it = queenGenerator.begin();
							auto end = queenGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = QueenState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						case chss::PieceType::King: {
							const auto kingGenerator = chss::move_generation::KingPseudoLegalMoves(state, newPosition);
							auto it = kingGenerator.begin();
							auto end = kingGenerator.end();
							if (it != end) {
								return MovePositionAndPieceState{
									.position = newPosition,
									.pieceState = KingState{.it = std::move(it), .end = std::move(end)}};
							}
							break;
						}
						}
					}
					++x;
				}
				x = 0;
				++y;
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
			assert(
				std::visit(
					[](const auto& pieceState) { return pieceState.it != pieceState.end; },
					mPositionAndPieceState.pieceState));
			return std::visit(
				[](const auto& state) -> chss::Move { return *state.it; },
				mPositionAndPieceState.pieceState);
		}

		constexpr Iterator& operator++() {
			assert(mPositionAndPieceState.position.y < mState.board.GetSize().sizeY);
			assert(
				std::visit(
					[](const auto& pieceState) { return pieceState.it != pieceState.end; },
					mPositionAndPieceState.pieceState));
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
