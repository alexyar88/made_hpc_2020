cmake_minimum_required(VERSION 3.17)
project(pagerank C)

set(CMAKE_C_STANDARD 99)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(pagerank pagerank.c)
target_link_libraries(pagerank ${CONAN_LIBS})