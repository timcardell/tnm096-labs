cmake_minimum_required(VERSION 3.15)
project(tnm096_labs)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tnm096_labs
        CMakeLists.txt
        main.cpp
        Puzzle.cpp
        Puzzle.h)
