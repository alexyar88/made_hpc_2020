cmake_minimum_required(VERSION 3.17)
project(least_squares C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_C_STANDARD 99)

add_executable(least_squares LeastSquares.c)