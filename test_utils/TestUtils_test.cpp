#include "TestUtils.h"

constexpr bool equal(char const* lhs, char const* rhs) noexcept {
	while (*lhs || *rhs) {
		if (*lhs++ != *rhs++) {
			return false;
		}
	}

	return true;
}

TEST_CASE("name", "TEST_CASE::name") {
	STATIC_REQUIRE(equal(name, "name"));
}

TEST_CASE("group", "TEST_CASE::group") {
	STATIC_REQUIRE(equal(group, "TEST_CASE::group"));
}

TEST_CASE("constexpr tests", "STATIC_REQUIRE") {
	constexpr int i = 1234;
	constexpr int j = 1234;
	constexpr int k = 5678;

	STATIC_REQUIRE(i == j);
	STATIC_REQUIRE(i != k);
}

TEST_CASE("tests", "REQUIRE") {
	const int i = 1234;
	const int j = 1234;
	const int k = 5678;

	REQUIRE(i == j);
	REQUIRE(i != k);
}
