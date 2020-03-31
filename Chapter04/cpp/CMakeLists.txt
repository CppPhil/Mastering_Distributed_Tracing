cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(HunterGate)

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.249.tar.gz"
    SHA1 "d45d77d8bba9da13e9290a180e0477e90accd89b"
)

project(Chapter04_project VERSION 1.0.0)

string(APPEND CMAKE_CXX_FLAGS " -Werror -Wall -Wcast-align -Wmissing-include-dirs -Wpointer-arith -Wstrict-aliasing=2 -Wunreachable-code -Wlogical-op -Wduplicated-cond -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-sign-compare -Wno-reorder -Wno-missing-field-initializers -Wno-type-limits -Wno-deprecated-copy -Wno-implicit-fallthrough -Wno-variadic-macros -Wno-stringop-truncation")
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -g -O0")
string(APPEND CMAKE_CXX_FLAGS_RELEASE " -O3 -march=native -funroll-loops -flto -fwhole-program -DNDEBUG")

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

find_package(Threads REQUIRED)

set(BUILD_TESTING false)
set(JAEGERTRACING_BUILD_EXAMPLES false)
add_subdirectory(external/jaeger-client-cpp)

add_subdirectory(external/drogon)
add_subdirectory(external/poco)

add_subdirectory(lib)
add_subdirectory(exercise1)

