#include "dot_product_strassen.h"

Matrix DotProductStrassen(Matrix &m1, Matrix &m2) {
    assert(m1.cols == m1.rows);
    assert(m2.cols == m2.rows);
    assert(m1.rows == m2.rows);

    size_t n = m1.rows;

    if (n <= 64) {
        return DotProduct(m1, m2);
    }

    size_t k = n / 2;

    Matrix A11 = Matrix(k, k);
    Matrix A12 = Matrix(k, k);
    Matrix A21 = Matrix(k, k);
    Matrix A22 = Matrix(k, k);

    Matrix B11 = Matrix(k, k);
    Matrix B12 = Matrix(k, k);
    Matrix B21 = Matrix(k, k);
    Matrix B22 = Matrix(k, k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < k && j < k) { // 11
                A11.Set(i, j, m1.Get(i, j));
                B11.Set(i, j, m2.Get(i, j));
            } else if (i < k && j >= k) { // 12
                A12.Set(i, j - k, m1.Get(i, j));
                B12.Set(i, j - k, m2.Get(i, j));
            } else if (i >= k && j < k) { // 21
                A21.Set(i - k, j, m1.Get(i, j));
                B21.Set(i - k, j, m2.Get(i, j));
            } else if (i >= k && j >= k) { // 22
                A22.Set(i - k, j - k, m1.Get(i, j));
                B22.Set(i - k, j - k, m2.Get(i, j));
            }
        }
    }
    Matrix P11 = A11 + A22;
    Matrix P12 = B11 + B22;
    Matrix P1 = DotProductStrassen(P11, P12);

    Matrix P21 = A21 + A22;
    Matrix P22 = B11;
    Matrix P2 = DotProductStrassen(P21, P22);

    Matrix P31 = A11;
    Matrix P32 = B12 + B22 * (-1);
    Matrix P3 = DotProductStrassen(P31, P32);

    Matrix P41 = A22;
    Matrix P42 = B21 - B11;
    Matrix P4 = DotProductStrassen(P41, P42);

    Matrix P51 = A11 + A12;
    Matrix P52 = B22;
    Matrix P5 = DotProductStrassen(P51, P52);

    Matrix P61 = A21 - A11;
    Matrix P62 = B11 + B12;
    Matrix P6 = DotProductStrassen(P61, P62);

    Matrix P71 = A12 - A22;
    Matrix P72 = B21 + B22;
    Matrix P7 = DotProductStrassen(P71, P72);

    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;

    Matrix C = Matrix(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < k && j < k) { // 11
                C.Set(i, j, C11.Get(i, j));
            } else if (i < k && j >= k) { // 12
                C.Set(i, j, C12.Get(i, j - k));
            } else if (i >= k && j < k) { // 21
                C.Set(i, j, C21.Get(i - k, j));
            } else if (i >= k && j >= k) { // 22
                C.Set(i, j, C22.Get(i - k, j - k));
            }
        }
    }

    return C;
}