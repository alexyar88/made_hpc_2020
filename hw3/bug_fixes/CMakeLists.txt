cmake_minimum_required(VERSION 3.17)
project(bug_fixes C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(bug_fixes omp_bugparfoc.c)