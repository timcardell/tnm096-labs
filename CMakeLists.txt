cmake_minimum_required(VERSION 3.15)

project(Lab)

set(CMAKE_CXX_STANDARD 14)


include_directories(
	.
	./
)


add_executable(Lab main.cpp Puzzle.cpp Puzzle.h)

