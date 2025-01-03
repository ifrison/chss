#pragma once

#include <array>
#include <cassert>
#include <sstream>
#include <string_view>

#include <generator>

namespace detail {

template<typename T, std::size_t Size>
[[nodiscard]] constexpr std::array<T, Size> CreateFilledArray(const T& value) {
	std::array<T, Size> values{};
	for (std::size_t x = 0; x < Size; ++x) {
		values[x] = value;
	}
	return values;
}

} // namespace detail

namespace matrix {

struct Position2D {
	int y;
	int x;
	[[nodiscard]] constexpr bool operator==(const Position2D&) const = default;
};

struct Direction2D {
	int deltaY;
	int deltaX;
	[[nodiscard]] constexpr bool operator==(const Direction2D&) const = default;
};

constexpr Position2D& operator+=(Position2D& lhs, const Direction2D& rhs) {
	lhs.y += rhs.deltaY;
	lhs.x += rhs.deltaX;
	return lhs;
}

[[nodiscard]] constexpr Position2D operator+(const Position2D& lhs, const Direction2D& rhs) {
	return Position2D{.y = lhs.y + rhs.deltaY, .x = lhs.x + rhs.deltaX};
}

constexpr Position2D& operator-=(Position2D& lhs, const Direction2D& rhs) {
	lhs.y -= rhs.deltaY;
	lhs.x -= rhs.deltaX;
	return lhs;
}

[[nodiscard]] constexpr Position2D operator-(const Position2D& lhs, const Direction2D& rhs) {
	return Position2D{.y = lhs.y - rhs.deltaY, .x = lhs.x - rhs.deltaX};
}

[[nodiscard]] constexpr Direction2D operator-(const Position2D& lhs, const Position2D& rhs) {
	return Direction2D{.deltaY = lhs.y - rhs.y, .deltaX = lhs.x - rhs.x};
}

struct Size2D {
	int sizeY; // height, numRows
	int sizeX; // width, numCols
	[[nodiscard]] constexpr bool operator==(const Size2D&) const = default;
};

[[nodiscard]] constexpr bool IsInside(const Size2D& size, const Position2D& pos) {
	return 0 <= pos.y && pos.y < size.sizeY && 0 <= pos.x && pos.x < size.sizeX;
}

[[nodiscard]] inline std::generator<Position2D> ForEach(Size2D size) {
	for (int y = 0; y < size.sizeY; ++y) {
		for (int x = 0; x < size.sizeX; ++x) {
			co_yield Position2D{.y = y, .x = x};
		}
	}
}

template<typename T, Size2D S>
class Matrix2D {
public:
	constexpr explicit Matrix2D(std::array<T, S.sizeY * S.sizeX> data)
		: mData(std::move(data)) {}

	constexpr explicit Matrix2D(const T& value)
		: mData(detail::CreateFilledArray<T, S.sizeY * S.sizeX>(value)) {}

	constexpr explicit Matrix2D()
		: mData(detail::CreateFilledArray<T, S.sizeY * S.sizeX>(T())) {}

	[[nodiscard]] constexpr T& At(const Position2D& pos) {
		assert(0 <= pos.y && pos.y < S.sizeY);
		assert(0 <= pos.x && pos.x < S.sizeX);
		return mData[pos.y * S.sizeX + pos.x];
	}

	[[nodiscard]] constexpr const T& At(const Position2D& pos) const {
		assert(0 <= pos.y && pos.y < S.sizeY);
		assert(0 <= pos.x && pos.x < S.sizeX);
		return mData[pos.y * S.sizeX + pos.x];
	}

	[[nodiscard]] constexpr Size2D GetSize() const {
		return S;
	}

	[[nodiscard]] constexpr bool IsInside(const Position2D& position) const {
		return matrix::IsInside(S, position);
	}

	[[nodiscard]] constexpr bool operator==(const Matrix2D& other) const = default;

private:
	std::array<T, S.sizeY * S.sizeX> mData;
};

template<typename T, Size2D S, typename F>
[[nodiscard]] constexpr auto Transform(const Matrix2D<T, S>& matrix, F&& transformFunc) {
	using R = std::invoke_result_t<F, T>;
	auto result = Matrix2D<R, S>();
	for (int y = 0; y < S.sizeY; ++y) {
		for (int x = 0; x < S.sizeX; ++x) {
			const auto pos = Position2D{.y = y, .x = x};
			result.At(pos) = std::forward<F>(transformFunc)(matrix.At(pos));
		}
	}
	return result;
}

template<typename T, Size2D S>
[[nodiscard]] constexpr Matrix2D<T, Size2D{.sizeY = S.sizeX, .sizeX = S.sizeY}> RotateClockwise(
	const Matrix2D<T, S>& matrix) {
	constexpr auto ST = Size2D{.sizeY = S.sizeX, .sizeX = S.sizeY};
	auto result = Matrix2D<T, ST>();
	for (int y = 0; y < S.sizeY; ++y) {
		for (int x = 0; x < S.sizeX; ++x) {
			const auto pos = Position2D{.y = y, .x = x};
			const auto resultPos = Position2D{.y = x, .x = S.sizeY - 1 - y};
			result.At(resultPos) = matrix.At(pos);
		}
	}
	return result;
}

template<typename T, Size2D S>
[[nodiscard]] constexpr Matrix2D<T, S> FlipHorizontal(const Matrix2D<T, S>& matrix) {
	auto result = Matrix2D<T, S>();
	for (int y = 0; y < S.sizeY; ++y) {
		for (int x = 0; x < S.sizeX; ++x) {
			const auto pos = Position2D{.y = y, .x = x};
			const auto resultPos = Position2D{.y = y, .x = S.sizeX - 1 - x};
			result.At(resultPos) = matrix.At(pos);
		}
	}
	return result;
}

template<typename T, Size2D S>
[[nodiscard]] constexpr Matrix2D<T, S> FlipVertical(const Matrix2D<T, S>& matrix) {
	auto result = Matrix2D<T, S>();
	for (int y = 0; y < S.sizeY; ++y) {
		for (int x = 0; x < S.sizeX; ++x) {
			const auto pos = Position2D{.y = y, .x = x};
			const auto resultPos = Position2D{.y = S.sizeY - 1 - y, .x = x};
			result.At(resultPos) = matrix.At(pos);
		}
	}
	return result;
}

template<typename T, Size2D S>
[[nodiscard]] constexpr Matrix2D<T, Size2D{.sizeY = S.sizeX, .sizeX = S.sizeY}> Transpose(const Matrix2D<T, S>& m) {
	constexpr auto ST = Size2D{.sizeY = S.sizeX, .sizeX = S.sizeY};
	auto result = Matrix2D<T, ST>();
	for (int y = 0; y < S.sizeY; ++y) {
		for (int x = 0; x < S.sizeX; ++x) {
			const auto pos = Position2D{.y = y, .x = x};
			const auto resultPos = Position2D{.y = x, .x = y};
			result.At(resultPos) = m.At(pos);
		}
	}
	return result;
}

} // namespace matrix
