add_library(matrix INTERFACE)
target_include_directories(matrix
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:matrix>)

add_executable(matrix_tests
        Matrix2D_test.cpp)
target_link_libraries(matrix_tests
        stdgenerator
        GTest::gtest_main)
gtest_discover_tests(matrix_tests)
