cmake_minimum_required(VERSION 3.16)
project(matrix_dot_product)

set(CMAKE_CXX_STANDARD 20)

set(CONAN_CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(matrix_dot_product main.cpp matrix.cpp matrix.h vector_row.cpp vector_row.h vector_col.cpp vector_col.h dot_product.cpp dot_product.h dot_product_strassen.cpp dot_product_strassen.h cblas_test.cpp cblas_test.h)
target_link_libraries(matrix_dot_product ${CONAN_LIBS})