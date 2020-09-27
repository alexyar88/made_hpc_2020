#include "cblas_test.h"

double *get_flatten_array_from_matrix(Matrix m) {
    double *arr = new double[m.rows * m.rows];

    for (int i = 0; i < m.rows * m.cols; ++i) {
        arr[i] = m.arr[i];
    }
    return arr;
}

void CblasTest(Matrix m1, Matrix m2, int n) {
    CBLAS_TRANSPOSE transA = CBLAS_TRANSPOSE::CblasNoTrans;
    CBLAS_TRANSPOSE transB = CBLAS_TRANSPOSE::CblasNoTrans;
    CBLAS_ORDER Order = CBLAS_ORDER::CblasRowMajor;

    Matrix Am = Matrix(n, n);
    Matrix Bm = Matrix(n, n);
    Matrix Cm = Matrix(n, n);

    double *A = get_flatten_array_from_matrix(Am);
    double *B = get_flatten_array_from_matrix(Bm);
    double *C = get_flatten_array_from_matrix(Cm);

//    for (int i = 0; i < n * n; ++i) {
//        C[i] = 0;
//        std::cout << C[i] << std::endl;
//    }

    cblas_dgemm(Order, transA, transB, n, n, n, 1, A, n, B, n, 1, C, n);

    delete [] A;
    delete [] B;
    delete [] C;
}
