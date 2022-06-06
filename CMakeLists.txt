cmake_minimum_required(VERSION 3.22.2)

set(CMAKE_CXX_COMPILER /usr/bin/g++-11)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

project(aoc CXX)

find_package(Boost REQUIRED COMPONENTS program_options)

add_subdirectory(src)
