cmake_minimum_required(VERSION 3.16)

project(matmul LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# matrix library
add_library(matrix STATIC src/matrix.cpp)
target_include_directories(matrix PUBLIC include)

# main executable
add_executable(matmul src/main.cpp)
target_link_libraries(matmul PRIVATE matrix)

# google benchmark dependency
include(FetchContent)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.4
)

FetchContent_MakeAvailable(googlebenchmark)

# benchmark executable
add_executable(matmul_bench benchmarks/matmul_bench.cpp)
target_link_libraries(matmul_bench PRIVATE matrix benchmark::benchmark_main)
