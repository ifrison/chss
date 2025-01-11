target_sources(chess_tests PRIVATE
        MakeMove_test.cpp
        IsInCheck_test.cpp
        PseudoLegalMoves_test.cpp)

add_subdirectory(pieces)
