cmake_minimum_required(VERSION 3.17)
project(1_meeting_people_game C)

include_directories(/usr/local/Cellar/open-mpi/4.0.5/include)
link_directories(/usr/local/Cellar/open-mpi/4.0.5/lib)

set(CMAKE_C_STANDARD 99)

add_executable(1_meeting_people_game meeting_game.c)