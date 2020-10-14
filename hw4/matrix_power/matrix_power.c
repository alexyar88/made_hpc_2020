#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

void matmul(const double *A, const double *B, double *C, int N) {
    int i, j, k, temp_index;

    for (i = 0; i < N * N; i++) {
        C[i] = 0;
    }
#pragma omp parallel for private(i, j, k, temp_index) shared(A, B, C, N) default(none)
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            temp_index = i * N;
            for (j = 0; j < N; j++) {
                C[temp_index + j] += A[temp_index + k] * B[k * N + j];
            }
        }
    }
//    for (i = 0; i < N; i++) {
//        for (j = 0; j < N; j++) {
//            for (k = 0; k < N; k++) {
//                C[i * N + j] += A[i * N + k] * B[k * N + j];
//            }
//        }
//    }
}

void power(const double *A, double *C, int p, int N) {
    int i, j;
    double *B = malloc(N * N * sizeof(double));
    double *D = malloc(N * N * sizeof(double));
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            B[i * N + j] = A[i * N + j];
            if (i == j) {
                C[i * N + j] = 1;
            } else {
                C[i * N + j] = 0;
            }
        }
    }

    while (p > 0) {
        if (p % 2 > 0) {
            matmul(C, B, D, N);
        }
        for (i = 0; i < N * N; i++) {
            C[i] = D[i];

        }

        p = p / 2;
        matmul(B, B, D, N);
        for (i = 0; i < N * N; i++) {
            B[i] = D[i];
        }
    }
    free(B);
    free(D);
}


int main() {
    int N = 1000;
    double *A = malloc(N * N * sizeof(double));
    double *C = malloc(N * N * sizeof(double));

    for (int i = 0; i < N * N; i++) {
        A[i] = 1 + i;
        C[i] = 0;
    }
    double start = omp_get_wtime();
    power(A, C, 7, N);
    double end = omp_get_wtime();
    printf("Time = %f \n", end - start);

//    for (int i = 0; i < N * N; i++) {
//        printf("%f \t", C[i]);
//    }
    free(A);
    free(C);
    return 0;
}
