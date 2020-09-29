#include "dot_product.h"

Matrix DotProduct(Matrix &m1, Matrix &m2) {
    assert(m1.cols == m2.rows); /* NxM dot MxK */
    Matrix m = Matrix(m1.rows, m2.cols);
    for (int i = 0; i < m1.rows; ++i) {
        for (int j = 0; j < m2.cols; ++j) {
            double sum = 0;
            for (int n = 0; n < m1.cols; ++n) {
                sum += m1.Get(i, n) * m2.Get(n, j);
            }
            m.Set(i, j, sum);
        }
    }
    return m;
}