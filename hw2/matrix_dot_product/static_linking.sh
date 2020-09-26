#!/bin/zsh
# На маке пришлось g++ использовать
g++ -c matrix.cpp
g++ -c vector_col.cpp
g++ -c vector_row.cpp
ar rc matrix_lib.a matrix.o vector_col.o vector_row.o
g++ main.cpp matrix_lib.a -o matmul.bin