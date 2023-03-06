cmake_minimum_required(VERSION 3.12)

set(CMAKE_C_COMPILER "/usr/bin/clang-14")

set(CMAKE_C_STANDARD 11)

project(terminalFlappyBird C CXX)

set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_subdirectory(src)

