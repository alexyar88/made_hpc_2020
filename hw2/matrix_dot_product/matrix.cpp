#include "matrix.h"

Matrix::Matrix(size_t rows_num, size_t cols_num) {
    cols = cols_num;
    rows = rows_num;
    arr.resize(rows * cols * 1);
    for (int i = 0; i < rows * cols; ++i) {
        arr[i] = i + 1;
    }
}


int Matrix::Get(size_t row, size_t col) const {
    return arr[row * cols + col];
};

void Matrix::Set(size_t row, size_t col, int val) {
    arr[row * cols + col] = val;
}

void Matrix::Print() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << Get(i, j) << " \n\n"[j == cols - 1];
        }

    }
}

Matrix Matrix::operator+(const Matrix &m) const {
    assert(m.rows == rows);
    assert(m.cols == cols);
    Matrix m_r = Matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            int val = Get(i, j) + m.Get(i, j);
            m_r.Set(i, j, val);
        }
    }

    return m_r;
}

Matrix Matrix::operator-(const Matrix &m) const {
    return *this + m*(-1);
}

Matrix Matrix::operator*(int num) const {
    Matrix m = Matrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int val = Get(i, j) * num;
            m.Set(i, j, val);
        }
    }
    return m;
}


