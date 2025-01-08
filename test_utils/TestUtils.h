#pragma once

#include <cassert>

#define DETAIL_NAME_LINE2(name, line) name##line

#define DETAIL_NAME_LINE(name, line) DETAIL_NAME_LINE2(name, line)

#define DETAIL_NAME(name) DETAIL_NAME_LINE(name, __LINE__)

#define DETAIL_TEST_CASE_WITH_NAMES(NAME, GROUP, TYPE_NAME, INSTANCE_NAME)\
namespace {                                                               \
    struct TYPE_NAME {                                                    \
        [[maybe_unused]] static constexpr const char* name = NAME;        \
        [[maybe_unused]] static constexpr const char* group = GROUP;      \
        explicit TYPE_NAME();                                             \
    };                                                                    \
    TYPE_NAME INSTANCE_NAME;                                              \
}                                                                         \
                                                                          \
TYPE_NAME::TYPE_NAME()

/**
 * Creates a test
 *
 * @param [in] name name of the test
 * @param [in] group name of the group of tests
 */
#define TEST_CASE(name, group) DETAIL_TEST_CASE_WITH_NAMES(name, group, DETAIL_NAME(Test), DETAIL_NAME(instance))

/**
 * Asserts a constexpr condition
 * @param [in] condition condition to check
 */
#define STATIC_REQUIRE(...) static_assert(__VA_ARGS__, "TEST FAILED")

/**
 * Asserts a condition
 * @param [in] condition condition to check
 */
#define REQUIRE(...) assert(__VA_ARGS__)