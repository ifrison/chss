#pragma once

#include <matrix/Matrix2D.h>

#include <array>
#include <cstdint>
#include <optional>

namespace chss {

enum class PieceType : std::int8_t { Pawn, Knight, Bishop, Rook, Queen, King };

enum class Color : std::int8_t { White, Black };

[[nodiscard]] constexpr Color InverseColor(Color color) {
	return color == Color::White ? Color::Black : Color::White;
};

struct Piece {
	PieceType type;
	Color color;
	[[nodiscard]] constexpr bool operator==(const Piece& other) const = default;
};

using Position = matrix::Position2D;
namespace positions {
constexpr auto A1 = Position{.y = 0, .x = 0};
constexpr auto B1 = Position{.y = 0, .x = 1};
constexpr auto C1 = Position{.y = 0, .x = 2};
constexpr auto D1 = Position{.y = 0, .x = 3};
constexpr auto E1 = Position{.y = 0, .x = 4};
constexpr auto F1 = Position{.y = 0, .x = 5};
constexpr auto G1 = Position{.y = 0, .x = 6};
constexpr auto H1 = Position{.y = 0, .x = 7};
constexpr auto A2 = Position{.y = 1, .x = 0};
constexpr auto B2 = Position{.y = 1, .x = 1};
constexpr auto C2 = Position{.y = 1, .x = 2};
constexpr auto D2 = Position{.y = 1, .x = 3};
constexpr auto E2 = Position{.y = 1, .x = 4};
constexpr auto F2 = Position{.y = 1, .x = 5};
constexpr auto G2 = Position{.y = 1, .x = 6};
constexpr auto H2 = Position{.y = 1, .x = 7};
constexpr auto A3 = Position{.y = 2, .x = 0};
constexpr auto B3 = Position{.y = 2, .x = 1};
constexpr auto C3 = Position{.y = 2, .x = 2};
constexpr auto D3 = Position{.y = 2, .x = 3};
constexpr auto E3 = Position{.y = 2, .x = 4};
constexpr auto F3 = Position{.y = 2, .x = 5};
constexpr auto G3 = Position{.y = 2, .x = 6};
constexpr auto H3 = Position{.y = 2, .x = 7};
constexpr auto A4 = Position{.y = 3, .x = 0};
constexpr auto B4 = Position{.y = 3, .x = 1};
constexpr auto C4 = Position{.y = 3, .x = 2};
constexpr auto D4 = Position{.y = 3, .x = 3};
constexpr auto E4 = Position{.y = 3, .x = 4};
constexpr auto F4 = Position{.y = 3, .x = 5};
constexpr auto G4 = Position{.y = 3, .x = 6};
constexpr auto H4 = Position{.y = 3, .x = 7};
constexpr auto A5 = Position{.y = 4, .x = 0};
constexpr auto B5 = Position{.y = 4, .x = 1};
constexpr auto C5 = Position{.y = 4, .x = 2};
constexpr auto D5 = Position{.y = 4, .x = 3};
constexpr auto E5 = Position{.y = 4, .x = 4};
constexpr auto F5 = Position{.y = 4, .x = 5};
constexpr auto G5 = Position{.y = 4, .x = 6};
constexpr auto H5 = Position{.y = 4, .x = 7};
constexpr auto A6 = Position{.y = 5, .x = 0};
constexpr auto B6 = Position{.y = 5, .x = 1};
constexpr auto C6 = Position{.y = 5, .x = 2};
constexpr auto D6 = Position{.y = 5, .x = 3};
constexpr auto E6 = Position{.y = 5, .x = 4};
constexpr auto F6 = Position{.y = 5, .x = 5};
constexpr auto G6 = Position{.y = 5, .x = 6};
constexpr auto H6 = Position{.y = 5, .x = 7};
constexpr auto A7 = Position{.y = 6, .x = 0};
constexpr auto B7 = Position{.y = 6, .x = 1};
constexpr auto C7 = Position{.y = 6, .x = 2};
constexpr auto D7 = Position{.y = 6, .x = 3};
constexpr auto E7 = Position{.y = 6, .x = 4};
constexpr auto F7 = Position{.y = 6, .x = 5};
constexpr auto G7 = Position{.y = 6, .x = 6};
constexpr auto H7 = Position{.y = 6, .x = 7};
constexpr auto A8 = Position{.y = 7, .x = 0};
constexpr auto B8 = Position{.y = 7, .x = 1};
constexpr auto C8 = Position{.y = 7, .x = 2};
constexpr auto D8 = Position{.y = 7, .x = 3};
constexpr auto E8 = Position{.y = 7, .x = 4};
constexpr auto F8 = Position{.y = 7, .x = 5};
constexpr auto G8 = Position{.y = 7, .x = 6};
constexpr auto H8 = Position{.y = 7, .x = 7};
} // namespace positions

using Board = matrix::Matrix2D<std::optional<Piece>, matrix::Size2D{.sizeY = 8, .sizeX = 8}>;
static_assert(sizeof(Board) == 64 * 3);

constexpr auto kEmptyBoard = Board(std::optional<Piece>(std::nullopt));
constexpr auto kInitialBoard = Board(
	std::array<std::optional<Piece>, 64>{
		std::optional<Piece>(Piece{PieceType::Rook, Color::White}),
		std::optional<Piece>(Piece{PieceType::Knight, Color::White}),
		std::optional<Piece>(Piece{PieceType::Bishop, Color::White}),
		std::optional<Piece>(Piece{PieceType::Queen, Color::White}),
		std::optional<Piece>(Piece{PieceType::King, Color::White}),
		std::optional<Piece>(Piece{PieceType::Bishop, Color::White}),
		std::optional<Piece>(Piece{PieceType::Knight, Color::White}),
		std::optional<Piece>(Piece{PieceType::Rook, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::White}),
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
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Pawn, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Rook, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Knight, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Bishop, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Queen, Color::Black}),
		std::optional<Piece>(Piece{PieceType::King, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Bishop, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Knight, Color::Black}),
		std::optional<Piece>(Piece{PieceType::Rook, Color::Black})});

} // namespace chss