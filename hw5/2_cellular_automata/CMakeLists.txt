cmake_minimum_required(VERSION 3.17)
project(2_cellular_automata C)

include_directories(/usr/local/Cellar/open-mpi/4.0.5/include)
link_directories(/usr/local/Cellar/open-mpi/4.0.5/lib)
set(CMAKE_C_STANDARD 99)

add_executable(2_cellular_automata cellular_automata.c)