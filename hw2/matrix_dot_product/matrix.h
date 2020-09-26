#ifndef MATRIX_MATMUL_MATRIX_H
#define MATRIX_MATMUL_MATRIX_H

#include <vector>
#include <iostream>


class Matrix {
public:
    Matrix(size_t rows_num, size_t cols_num);

    int Get(size_t row, size_t col) const;

    void Set(size_t row, size_t col, int val);

    void Print();

    Matrix operator+(const Matrix &m) const;

    Matrix operator-(const Matrix &m) const;

    Matrix operator*(int num) const;

    size_t rows;
    size_t cols;

private:
    int default_val = 1;
    std::vector<int> arr;
};


#endif //MATRIX_MATMUL_MATRIX_H
