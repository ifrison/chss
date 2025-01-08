#include "Matrix2D.h"

#include <test_utils/TestUtils.h>

TEST_CASE("Matrix2D", "Position2D_Comparison") {
	constexpr auto pos1 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos2 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos3 = matrix::Position2D{.y = 1, .x = 3};
	constexpr auto pos4 = matrix::Position2D{.y = 2, .x = 2};

	STATIC_REQUIRE(pos1 == pos2);
	STATIC_REQUIRE(!(pos1 == pos3));
	STATIC_REQUIRE(!(pos1 == pos4));

	STATIC_REQUIRE(!(pos1 != pos2));
	STATIC_REQUIRE(pos1 != pos3);
	STATIC_REQUIRE(pos1 != pos4);
}

TEST_CASE("Matrix2D", "Direction2D_Comparison") {
	constexpr auto dir1 = matrix::Direction2D{.deltaY = 1, .deltaX = 2};
	constexpr auto dir2 = matrix::Direction2D{.deltaY = 1, .deltaX = 2};
	constexpr auto dir3 = matrix::Direction2D{.deltaY = 1, .deltaX = 3};
	constexpr auto dir4 = matrix::Direction2D{.deltaY = 2, .deltaX = 2};

	STATIC_REQUIRE(dir1 == dir2);
	STATIC_REQUIRE(!(dir1 == dir3));
	STATIC_REQUIRE(!(dir1 == dir4));

	STATIC_REQUIRE(!(dir1 != dir2));
	STATIC_REQUIRE(dir1 != dir3);
	STATIC_REQUIRE(dir1 != dir4);
}

TEST_CASE("Matrix2D", "Size2D_Comparison") {
	constexpr auto size1 = matrix::Size2D{.sizeY = 1, .sizeX = 2};
	constexpr auto size2 = matrix::Size2D{.sizeY = 1, .sizeX = 2};
	constexpr auto size3 = matrix::Size2D{.sizeY = 1, .sizeX = 3};
	constexpr auto size4 = matrix::Size2D{.sizeY = 2, .sizeX = 2};

	STATIC_REQUIRE(size1 == size2);
	STATIC_REQUIRE(!(size1 == size3));
	STATIC_REQUIRE(!(size1 == size4));

	STATIC_REQUIRE(!(size1 != size2));
	STATIC_REQUIRE(size1 != size3);
	STATIC_REQUIRE(size1 != size4);
}

TEST_CASE("Matrix2D", "Position2D_PlusEquals_Direction2D") {
	constexpr auto result = []() -> matrix::Position2D {
		constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
		auto pos = matrix::Position2D{.y = 1, .x = 2};
		pos += dir;
		return pos;
	}();
	constexpr auto expectedResult = matrix::Position2D{.y = 4, .x = 6};
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Position2D_Plus_Direction2D") {
	constexpr auto pos = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	constexpr auto result = pos + dir;
	constexpr auto expectedResult = matrix::Position2D{.y = 4, .x = 6};
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Position2D_MinusEquals_Direction2D") {
	constexpr auto result = []() -> matrix::Position2D {
		constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
		auto pos = matrix::Position2D{.y = 1, .x = 2};
		pos -= dir;
		return pos;
	}();
	constexpr auto expectedResult = matrix::Position2D{.y = -2, .x = -2};
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Position2D_Minus_Direction2D") {
	constexpr auto pos = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	constexpr auto result = pos - dir;
	constexpr auto expectedResult = matrix::Position2D{.y = -2, .x = -2};
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Position2D_Minus_Position2D") {
	constexpr auto pos1 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos2 = matrix::Position2D{.y = 3, .x = 4};
	constexpr auto result = pos2 - pos1;
	constexpr auto expectedResult = matrix::Direction2D{.deltaY = 2, .deltaX = 2};
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "IsInside") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	STATIC_REQUIRE(IsInside(size, matrix::Position2D{.y = 0, .x = 0}));
	STATIC_REQUIRE(IsInside(size, matrix::Position2D{.y = 1, .x = 2}));
	STATIC_REQUIRE(!IsInside(size, matrix::Position2D{.y = -1, .x = 0}));
	STATIC_REQUIRE(!IsInside(size, matrix::Position2D{.y = 0, .x = -1}));
	STATIC_REQUIRE(!IsInside(size, matrix::Position2D{.y = 2, .x = 0}));
	STATIC_REQUIRE(!IsInside(size, matrix::Position2D{.y = 0, .x = 3}));
}

TEST_CASE("Matrix2D", "ForEach") {
	constexpr bool OK = []() -> bool {
		constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
		constexpr auto positions = std::array<matrix::Position2D, 6>{
			matrix::Position2D{.y = 0, .x = 0},
			matrix::Position2D{.y = 0, .x = 1},
			matrix::Position2D{.y = 0, .x = 2},
			matrix::Position2D{.y = 1, .x = 0},
			matrix::Position2D{.y = 1, .x = 1},
			matrix::Position2D{.y = 1, .x = 2},
		};
		bool ok = true;
		std::size_t i = 0;
		for (const auto pos : ForEach(size)) {
			ok = ok && i < positions.size() && pos == positions[i];
			++i;
		}
		return ok;
	}();
	STATIC_REQUIRE(OK);
}

TEST_CASE("Matrix2D", "ForEach_Empty") {
	constexpr auto count = []() -> std::size_t {
		constexpr auto size = matrix::Size2D{.sizeY = 0, .sizeX = 0};
		std::size_t i = 0;
		for ([[maybe_unused]] const auto _ : ForEach(size)) {
			++i;
		}
		return i;
	}();
	STATIC_REQUIRE(count == 0);
}

TEST_CASE("Matrix2D", "Matrix2D_ArrayConstructor") {
	constexpr auto array = std::array<int, 6>{1, 2, 3, 4, 5, 6};
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(array);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 0}) == 1);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 1}) == 2);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 2}) == 3);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 0}) == 4);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 1}) == 5);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 2}) == 6);
}

TEST_CASE("Matrix2D", "Matrix2D_ValueConstructor") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 0}) == 1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 1}) == 1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 2}) == 1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 0}) == 1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 1}) == 1234);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 2}) == 1234);
}

TEST_CASE("Matrix2D", "Matrix2D_DefaultConstructor") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 0}) == 0);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 1}) == 0);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 0, .x = 2}) == 0);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 0}) == 0);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 1}) == 0);
	STATIC_REQUIRE(matrix.At(matrix::Position2D{.y = 1, .x = 2}) == 0);
}

TEST_CASE("Matrix2D", "Matrix2D_At") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto pos = matrix::Position2D{.y = 0, .x = 0};
	auto matrix = matrix::Matrix2D<int, size>();
	STATIC_REQUIRE(std::is_same_v<decltype(matrix.At(pos)), int&>);
	STATIC_REQUIRE(std::is_same_v<decltype(std::as_const(matrix).At(pos)), const int&>);
}

TEST_CASE("Matrix2D", "Matrix2D_GetSize") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	STATIC_REQUIRE(matrix.GetSize() == size);
}

TEST_CASE("Matrix2D", "Matrix2D_IsInside") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	STATIC_REQUIRE(matrix.IsInside(matrix::Position2D{.y = 0, .x = 0}));
	STATIC_REQUIRE(matrix.IsInside(matrix::Position2D{.y = 1, .x = 2}));
	STATIC_REQUIRE(!matrix.IsInside(matrix::Position2D{.y = -1, .x = 0}));
	STATIC_REQUIRE(!matrix.IsInside(matrix::Position2D{.y = 0, .x = -1}));
	STATIC_REQUIRE(!matrix.IsInside(matrix::Position2D{.y = 2, .x = 0}));
	STATIC_REQUIRE(!matrix.IsInside(matrix::Position2D{.y = 0, .x = 3}));
}

TEST_CASE("Matrix2D", "Matrix2D_Comparison") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix1 = matrix::Matrix2D<int, size>(123);
	constexpr auto matrix2 = matrix::Matrix2D<int, size>(123);
	constexpr auto matrix3 = matrix::Matrix2D<int, size>(456);

	STATIC_REQUIRE(matrix1 == matrix2);
	STATIC_REQUIRE(!(matrix1 == matrix3));

	STATIC_REQUIRE(!(matrix1 != matrix2));
	STATIC_REQUIRE(matrix1 != matrix3);
}

TEST_CASE("Matrix2D", "Transform") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::Transform(matrix, [](int value) { return value * 2; });
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{2, 4, 6, 8, 10, 12});
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Rotate90DegreesClockwise") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::RotateClockwise(matrix);
	constexpr auto expectedResult =
		matrix::Matrix2D<int, matrix::Size2D{.sizeY = 3, .sizeX = 2}>(std::array<int, 6>{4, 1, 5, 2, 6, 3});
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "FlipHorizontal") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::FlipHorizontal(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{3, 2, 1, 6, 5, 4});
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "FlipVertical") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::FlipVertical(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{4, 5, 6, 1, 2, 3});
	STATIC_REQUIRE(result == expectedResult);
}

TEST_CASE("Matrix2D", "Transpose") {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::Transpose(matrix);
	constexpr auto expectedResult =
		matrix::Matrix2D<int, matrix::Size2D{.sizeY = 3, .sizeX = 2}>(std::array<int, 6>{1, 4, 2, 5, 3, 6});
	STATIC_REQUIRE(result == expectedResult);
}
