add_library(concurrency STATIC)
target_sources(concurrency PRIVATE
        TaskQueue.cpp)
target_include_directories(concurrency
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
        $<INSTALL_INTERFACE:concurrency>)

add_executable(concurrency_tests)
target_sources(concurrency_tests PRIVATE
        TaskQueue.cpp
        TaskQueue_test.cpp
        tests_main.cpp)
target_link_libraries(concurrency_tests
        testutils)
