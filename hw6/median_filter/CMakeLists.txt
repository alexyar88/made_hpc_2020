cmake_minimum_required(VERSION 3.18)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
project(median_filter CUDA)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CUDA_STANDARD 14)
add_executable(median_filter median_filter.cu)

set_target_properties(
        median_filter
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries( median_filter ${OpenCV_LIBS} )