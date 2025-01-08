add_executable(chess)
target_sources(chess PRIVATE
        DebugUtils.cpp
        PieceMovements.cpp
        Movements.cpp
        Perft.cpp
        MinMax.cpp
        chess.cpp
        UCI.cpp)
target_link_libraries(chess
        matrix
        stdgenerator
        concurrency)

add_executable(chess_tests)
target_sources(chess_tests PRIVATE
        Piece_test.cpp
        DebugUtils.cpp
        DebugUtils_test.cpp
        PieceMovements.cpp
        PieceMovements_test.cpp
        Movements.cpp
        Movements_test.cpp
        Perft.cpp
        Perft_test.cpp
        MinMax.cpp
        MinMax_test.cpp
        UCI.cpp)
target_link_libraries(chess_tests
        testutils
        matrix
        stdgenerator
        GTest::gtest_main
        GTest::gmock
        concurrency)
gtest_discover_tests(chess_tests)

add_subdirectory(evaluation)
add_subdirectory(fen)
