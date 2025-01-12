#pragma once

#include <array>
#include <cassert>

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

[[nodiscard]] constexpr Direction2D operator*(const Direction2D& lhs, const int rhs) {
	return Direction2D{.deltaY = lhs.deltaY * rhs, .deltaX = lhs.deltaX * rhs};
}

constexpr Direction2D& operator*=(Direction2D& lhs, const int rhs) {
	lhs.deltaY *= rhs;
	lhs.deltaX *= rhs;
	return lhs;
}

struct Size2D {
	int sizeY; // height, numRows
	int sizeX; // width, numCols
	[[nodiscard]] constexpr bool operator==(const Size2D&) const = default;
};

[[nodiscard]] constexpr bool IsInside(const Size2D& size, const Position2D& pos) {
	return 0 <= pos.y && pos.y < size.sizeY && 0 <= pos.x && pos.x < size.sizeX;
}

[[nodiscard]] constexpr auto ForEach(Size2D size) {
	class Generator {
	public:
		class Sentinel {};

		class Iterator {
		public:
			constexpr explicit Iterator(Size2D size)
				: mSize(size)
				, mY(0)
				, mX(0) {}

			[[nodiscard]] constexpr Position2D operator*() const {
				assert(0 <= mY && mY < mSize.sizeY);
				assert(0 <= mX && mX < mSize.sizeX);
				return Position2D{.y = mY, .x = mX};
			}

			constexpr Iterator& operator++() {
				assert(0 <= mY && mY < mSize.sizeY);
				assert(0 <= mX && mX < mSize.sizeX);
				++mX;
				if (mX == mSize.sizeX) {
					mX = 0;
					++mY;
				}
				return *this;
			}

			[[nodiscard]] constexpr bool operator==(const Sentinel&) const {
				assert((0 <= mY && mY < mSize.sizeY && 0 <= mX && mX < mSize.sizeX) || (mY == mSize.sizeY && mX == 0));
				return mY == mSize.sizeY;
			}

			[[nodiscard]] constexpr bool operator!=(const Sentinel&) const {
				assert((0 <= mY && mY < mSize.sizeY && 0 <= mX && mX < mSize.sizeX) || (mY == mSize.sizeY && mX == 0));
				return mY != mSize.sizeY;
			}

		private:
			Size2D mSize;
			int mY;
			int mX;
		};

		constexpr explicit Generator(Size2D size)
			: mSize(size) {}

		[[nodiscard]] constexpr Iterator begin() const {
			return Iterator(mSize);
		}

		[[nodiscard]] constexpr Sentinel end() const {
			return Sentinel{};
		}

	private:
		Size2D mSize;
	};

	return Generator(size);
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

	[[nodiscard]] constexpr const std::array<T, S.sizeY * S.sizeX>& GetData() const {
		return mData;
	}

	[[nodiscard]] constexpr std::array<T, S.sizeY * S.sizeX>& GetData() {
		return mData;
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
