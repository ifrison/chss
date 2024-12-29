#pragma once

#include <matrix/Matrix2D.h>

#include <array>
#include <cstdint>
#include <optional>

namespace chss {

enum class Type : std::int8_t { Pawn, Knight, Bishop, Rook, Queen, King };

enum class Color : std::int8_t { White, Black };

[[nodiscard]] constexpr Color InverseColor(Color color) {
	return color == Color::White ? Color::Black : Color::White;
};

struct Piece {
	Type type;
	Color color;
	[[nodiscard]] bool operator==(const Piece& other) const = default;
};

using Position = matrix::Position2D;
using Board = matrix::Matrix2D<std::optional<Piece>, matrix::Size2D{.sizeY = 8, .sizeX = 8}>;
static_assert(sizeof(Board) == 64 * 3);

constexpr auto kEmptyBoard = Board(std::optional<Piece>(std::nullopt));
constexpr auto kInitialBoard = Board(
	std::array<std::optional<Piece>, 64>{
		std::optional<Piece>(Piece{Type::Rook, Color::White}),
		std::optional<Piece>(Piece{Type::Knight, Color::White}),
		std::optional<Piece>(Piece{Type::Bishop, Color::White}),
		std::optional<Piece>(Piece{Type::Queen, Color::White}),
		std::optional<Piece>(Piece{Type::King, Color::White}),
		std::optional<Piece>(Piece{Type::Bishop, Color::White}),
		std::optional<Piece>(Piece{Type::Knight, Color::White}),
		std::optional<Piece>(Piece{Type::Rook, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(Piece{Type::Pawn, Color::White}),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(std::nullopt),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Pawn, Color::Black}),
		std::optional<Piece>(Piece{Type::Rook, Color::Black}),
		std::optional<Piece>(Piece{Type::Knight, Color::Black}),
		std::optional<Piece>(Piece{Type::Bishop, Color::Black}),
		std::optional<Piece>(Piece{Type::Queen, Color::Black}),
		std::optional<Piece>(Piece{Type::King, Color::Black}),
		std::optional<Piece>(Piece{Type::Bishop, Color::Black}),
		std::optional<Piece>(Piece{Type::Knight, Color::Black}),
		std::optional<Piece>(Piece{Type::Rook, Color::Black})});

} // namespace chss