cmake_minimum_required(VERSION 3.12)

project(terminalFlappyBird C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_subdirectory(src)

