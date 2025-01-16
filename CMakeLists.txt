cmake_minimum_required(VERSION 3.28)

project(chess LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -pedantic -Wextra")

include(FetchContent)

FetchContent_Declare(
        stdgenerator
        GIT_REPOSITORY https://github.com/lewissbaker/generator
        GIT_TAG origin/main)
FetchContent_MakeAvailable(stdgenerator)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.11.3)
FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_subdirectory(test_utils)
add_subdirectory(cpp_utils)
add_subdirectory(matrix)
add_subdirectory(concurrency)

add_subdirectory(chess)
