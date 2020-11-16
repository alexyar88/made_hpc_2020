cmake_minimum_required(VERSION 3.18)
set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc)
project(blur CUDA)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
set(CMAKE_CUDA_STANDARD 14)
add_executable(blur blur_kernel.cu)

set_target_properties(
        blur
        PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries( blur ${OpenCV_LIBS} )