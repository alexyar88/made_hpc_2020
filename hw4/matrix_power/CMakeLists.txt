cmake_minimum_required(VERSION 3.17)
project(matrix_power C)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
set(CMAKE_C_STANDARD 99)

add_executable(matrix_power matrix_power.c)