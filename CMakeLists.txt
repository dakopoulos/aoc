cmake_minimum_required(VERSION 3.22.2)

set(CMAKE_CXX_COMPILER /usr/bin/g++-11)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

project(aoc CXX)

add_subdirectory(src)
