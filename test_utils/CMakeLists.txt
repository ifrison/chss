add_library(testutils INTERFACE)
target_include_directories(testutils
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:testutils>)

add_executable(testutils_tests
        TestUtils_test.cpp
        tests_main.cpp)