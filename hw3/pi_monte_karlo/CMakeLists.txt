cmake_minimum_required(VERSION 3.17)
project(pi_monte_karlo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")

add_executable(pi_monte_karlo pi_monte_carlo.c)