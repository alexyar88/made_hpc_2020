#ifndef MATRIX_MATMUL_MATRIX_H
#define MATRIX_MATMUL_MATRIX_H

#include <vector>
#include <iostream>
#include "assert.h"


class Matrix {
public:
    Matrix(size_t rows_num, size_t cols_num);

    double Get(size_t row, size_t col) const;

    void Set(size_t row, size_t col, double val);

    void Print();

    Matrix operator+(const Matrix &m) const;

    Matrix operator-(const Matrix &m) const;

    Matrix operator*(double num) const;

    size_t rows;
    size_t cols;
    std::vector<double> arr;

};


#endif //MATRIX_MATMUL_MATRIX_H
