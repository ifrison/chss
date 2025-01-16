add_executable(chess)
target_sources(chess PRIVATE
        chess.cpp)
target_link_libraries(chess
        cpp_utils
        matrix
        concurrency)

add_executable(chess_tests)
target_sources(chess_tests PRIVATE
        DebugUtils_test.cpp
        Perft_test.cpp
        MinMax_test.cpp)
target_link_libraries(chess_tests
        testutils
        cpp_utils
        matrix
        GTest::gtest_main
        GTest::gmock
        concurrency)
gtest_discover_tests(chess_tests)

add_subdirectory(representation)
add_subdirectory(move_generation)
add_subdirectory(evaluation)
add_subdirectory(fen)
add_subdirectory(uci)
