#include "Matrix2D.h"

#include <gtest/gtest.h>

TEST(Matrix2D, Position2D_Comparison) {
	constexpr auto pos1 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos2 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos3 = matrix::Position2D{.y = 1, .x = 3};
	constexpr auto pos4 = matrix::Position2D{.y = 2, .x = 2};

	EXPECT_TRUE(pos1 == pos2);
	EXPECT_FALSE(pos1 == pos3);
	EXPECT_FALSE(pos1 == pos4);

	EXPECT_FALSE(pos1 != pos2);
	EXPECT_TRUE(pos1 != pos3);
	EXPECT_TRUE(pos1 != pos4);
}

TEST(Matrix2D, Direction2D_Comparison) {
	constexpr auto dir1 = matrix::Direction2D{.deltaY = 1, .deltaX = 2};
	constexpr auto dir2 = matrix::Direction2D{.deltaY = 1, .deltaX = 2};
	constexpr auto dir3 = matrix::Direction2D{.deltaY = 1, .deltaX = 3};
	constexpr auto dir4 = matrix::Direction2D{.deltaY = 2, .deltaX = 2};

	EXPECT_TRUE(dir1 == dir2);
	EXPECT_FALSE(dir1 == dir3);
	EXPECT_FALSE(dir1 == dir4);

	EXPECT_FALSE(dir1 != dir2);
	EXPECT_TRUE(dir1 != dir3);
	EXPECT_TRUE(dir1 != dir4);
}

TEST(Matrix2D, Size2D_Comparison) {
	constexpr auto size1 = matrix::Size2D{.sizeY = 1, .sizeX = 2};
	constexpr auto size2 = matrix::Size2D{.sizeY = 1, .sizeX = 2};
	constexpr auto size3 = matrix::Size2D{.sizeY = 1, .sizeX = 3};
	constexpr auto size4 = matrix::Size2D{.sizeY = 2, .sizeX = 2};

	EXPECT_TRUE(size1 == size2);
	EXPECT_FALSE(size1 == size3);
	EXPECT_FALSE(size1 == size4);

	EXPECT_FALSE(size1 != size2);
	EXPECT_TRUE(size1 != size3);
	EXPECT_TRUE(size1 != size4);
}

TEST(Matrix2D, Position2D_PlusEquals_Direction2D) {
	auto result = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	result += dir;
	constexpr auto expectedResult = matrix::Position2D{.y = 4, .x = 6};
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Position2D_Plus_Direction2D) {
	constexpr auto pos = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	constexpr auto result = pos + dir;
	constexpr auto expectedResult = matrix::Position2D{.y = 4, .x = 6};
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Position2D_MinusEquals_Direction2D) {
	auto result = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	result -= dir;
	constexpr auto expectedResult = matrix::Position2D{.y = -2, .x = -2};
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Position2D_Minus_Direction2D) {
	constexpr auto pos = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto dir = matrix::Direction2D{.deltaY = 3, .deltaX = 4};
	constexpr auto result = pos - dir;
	constexpr auto expectedResult = matrix::Position2D{.y = -2, .x = -2};
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Position2D_Minus_Position2D) {
	constexpr auto pos1 = matrix::Position2D{.y = 1, .x = 2};
	constexpr auto pos2 = matrix::Position2D{.y = 3, .x = 4};
	constexpr auto result = pos2 - pos1;
	constexpr auto expectedResult = matrix::Direction2D{.deltaY = 2, .deltaX = 2};
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, IsInside) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	EXPECT_TRUE(IsInside(size, matrix::Position2D{.y = 0, .x = 0}));
	EXPECT_TRUE(IsInside(size, matrix::Position2D{.y = 1, .x = 2}));
	EXPECT_FALSE(IsInside(size, matrix::Position2D{.y = -1, .x = 0}));
	EXPECT_FALSE(IsInside(size, matrix::Position2D{.y = 0, .x = -1}));
	EXPECT_FALSE(IsInside(size, matrix::Position2D{.y = 2, .x = 0}));
	EXPECT_FALSE(IsInside(size, matrix::Position2D{.y = 0, .x = 3}));
}

TEST(Matrix2D, ForEach) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto positions = std::array<matrix::Position2D, 6>{
		matrix::Position2D{.y = 0, .x = 0},
		matrix::Position2D{.y = 0, .x = 1},
		matrix::Position2D{.y = 0, .x = 2},
		matrix::Position2D{.y = 1, .x = 0},
		matrix::Position2D{.y = 1, .x = 1},
		matrix::Position2D{.y = 1, .x = 2},
	};
	std::size_t i = 0;
	for (const auto pos : ForEach(size)) {
		EXPECT_LT(i, positions.size());
		EXPECT_EQ(pos, positions[i]);
		++i;
	}
}

TEST(Matrix2D, ForEach_Empty) {
	constexpr auto size = matrix::Size2D{.sizeY = 0, .sizeX = 0};
	for ([[maybe_unused]] const auto _ : ForEach(size)) {
		FAIL();
	}
}

TEST(Matrix2D, Matrix2D_ArrayConstructor) {
	constexpr auto array = std::array<int, 6>{1, 2, 3, 4, 5, 6};
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(array);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 0}), 1);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 1}), 2);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 2}), 3);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 0}), 4);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 1}), 5);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 2}), 6);
}

TEST(Matrix2D, Matrix2D_ValueConstructor) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 0}), 1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 1}), 1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 2}), 1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 0}), 1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 1}), 1234);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 2}), 1234);
}

TEST(Matrix2D, Matrix2D_DefaultConstructor) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 0}), 0);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 1}), 0);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 0, .x = 2}), 0);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 0}), 0);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 1}), 0);
	EXPECT_EQ(matrix.At(matrix::Position2D{.y = 1, .x = 2}), 0);
}

TEST(Matrix2D, Matrix2D_At) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto pos = matrix::Position2D{.y = 0, .x = 0};
	auto matrix = matrix::Matrix2D<int, size>();
	EXPECT_TRUE((std::is_same_v<decltype(matrix.At(pos)), int&>));
	EXPECT_TRUE((std::is_same_v<decltype(std::as_const(matrix).At(pos)), const int&>));
}

TEST(Matrix2D, Matrix2D_GetSize) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	EXPECT_EQ(matrix.GetSize(), size);
}

TEST(Matrix2D, Matrix2D_IsInside) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>();
	EXPECT_TRUE(matrix.IsInside(matrix::Position2D{.y = 0, .x = 0}));
	EXPECT_TRUE(matrix.IsInside(matrix::Position2D{.y = 1, .x = 2}));
	EXPECT_FALSE(matrix.IsInside(matrix::Position2D{.y = -1, .x = 0}));
	EXPECT_FALSE(matrix.IsInside(matrix::Position2D{.y = 0, .x = -1}));
	EXPECT_FALSE(matrix.IsInside(matrix::Position2D{.y = 2, .x = 0}));
	EXPECT_FALSE(matrix.IsInside(matrix::Position2D{.y = 0, .x = 3}));
}

TEST(Matrix2D, Matrix2D_Comparison) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix1 = matrix::Matrix2D<int, size>(123);
	constexpr auto matrix2 = matrix::Matrix2D<int, size>(123);
	constexpr auto matrix3 = matrix::Matrix2D<int, size>(456);

	EXPECT_TRUE(matrix1 == matrix2);
	EXPECT_FALSE(matrix1 == matrix3);

	EXPECT_FALSE(matrix1 != matrix2);
	EXPECT_TRUE(matrix1 != matrix3);
}

TEST(Matrix2D, Transform) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::Transform(matrix, [](int value) { return value * 2; });
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{2, 4, 6, 8, 10, 12});
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Rotate90DegreesClockwise) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::RotateClockwise(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, matrix::Size2D{.sizeY = 3, .sizeX = 2}>(std::array<int, 6>{4, 1, 5, 2, 6, 3});
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, FlipHorizontal) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::FlipHorizontal(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{3, 2, 1, 6, 5, 4});
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, FlipVertical) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::FlipVertical(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, size>(std::array<int, 6>{4, 5, 6, 1, 2, 3});
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, Transpose) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	constexpr auto result = matrix::Transpose(matrix);
	constexpr auto expectedResult = matrix::Matrix2D<int, matrix::Size2D{.sizeY = 3, .sizeX = 2}>(std::array<int, 6>{1, 4, 2, 5, 3, 6});
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, ToString_int) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<int, size>(std::array<int, 6>{1, 2, 3, 4, 5, 6});
	const auto result = matrix::ToString(matrix, "\n", " ");
	constexpr auto expectedResult = "1 2 3\n4 5 6";
	EXPECT_EQ(result, expectedResult);
}

TEST(Matrix2D, ToString_char) {
	constexpr auto size = matrix::Size2D{.sizeY = 2, .sizeX = 3};
	constexpr auto matrix = matrix::Matrix2D<char, size>(std::array<char, 6>{'a', 'b', 'c', 'd', 'e', 'f'});
	const auto result = matrix::ToString(matrix, ";", "");
	constexpr auto expectedResult = "abc;def";
	EXPECT_EQ(result, expectedResult);
}
