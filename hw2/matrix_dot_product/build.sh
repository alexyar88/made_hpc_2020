#!/bin/zsh
# На маке пришлось использовать zsh и g++
g++ -c matrix.cpp
g++ -c vector_col.cpp
g++ -c vector_row.cpp
g++ -c dot_product.cpp
g++ -c dot_product_strassen.cpp
ar rc matrix_lib.a matrix.o vector_col.o vector_row.o dot_product.o dot_product_strassen.o
g++ -std=c++17 main.cpp matrix_lib.a -o matmul

# Скопируем в папку для того, чтобы измерять скорость.
mkdir -p ../speed_measurement
cp matmul ../speed_measurement/matmul