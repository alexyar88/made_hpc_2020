#!/bin/zsh
# На маке пришлось g++ использовать
g++ -c matrix.cpp
g++ -c vector_col.cpp
g++ -c vector_row.cpp
g++ -c dot_product.cpp
g++ -c dot_product_strassen.cpp
ar rc matrix_lib.a matrix.o vector_col.o vector_row.o dot_product.o dot_product_strassen.o
g++ -std=c++17 main.cpp matrix_lib.a -o matmul.bin