#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

double *solve_gauss_seidel(const double *A, const double *b, int N, double eps) {
    double *prev = malloc(N * sizeof(double));
    double *x = malloc(N * sizeof(double));
    int i, j;
    int iters = 0;
    double temp, x_i, norm2;
    double eps2 = eps * eps;

    for (i = 0; i < N; i++) {
        x[i] = 0;
    }

    do {
        for (i = 0; i < N; i++) {
            prev[i] = x[i];
        }
#pragma omp parallel for private(i, j, x_i, temp) shared(A, b, N, x, prev) default(none)
        for (i = 0; i < N; i++) {
            temp = 0;

            for (j = 0; j < N; j++) {
                if (i == j) {
                    continue;
                } else if (j < i) {
                    x_i = x[j];
                } else {
                    x_i = prev[j];
                }
                temp += (A[i * N + j] * x_i);
            }
            x[i] = (b[i] - temp) / A[i * N + i];
        }
        norm2 = 0;
#pragma omp parallel for private(i) shared(prev, x, N) default(none) reduction(+:norm2)
        for (i = 0; i < N; i++) {
            norm2 += (prev[i] - x[i]) * (prev[i] - x[i]);
        }
        iters += 1;

    } while (norm2 > eps2);
    printf("n_iters = %d\n", iters);
    return x;
}

int main() {
    int N = 3;
    double A[9] = {2, 1, 1, 1, -1, 0, 3, -1, 2};
    double b[3] = {2, -2, 2}; // x = [-1, 1, 3]

//    int N = 2;
//    double A[4] = {5, 2, 2, 1};
//    double b[2] = {7, 9}; // x = [-11, 31]

//    int N = 1000;
//
//    double *A = malloc(N * N * sizeof(double));
//    double *b = malloc(N * sizeof(double));

//    for (int i = 0; i < N; i++) { // здесь нет верных ответов, это просто чтобы измерять время
//        b[i] = i + 1.01;
//        for (int j = 0; j < N; j++) {
//            A[i * N + j] = i + j + 1;
//        }
//    }

    double start = omp_get_wtime();
    double *x = solve_gauss_seidel(A, b, N, 0.00000001);
    double end = omp_get_wtime();

    printf("Time = %f\n", end - start);
    for (int i = 0; i < N; i++) {
        printf("x_%d = %f\n",i, x[i]);
    }

    return 0;
}
