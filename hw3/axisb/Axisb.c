#include <stdio.h>
#include <stdlib.h>

double *solve_gauss_seidel(const double *A, const double *b, int N, double eps) {
    double *prev = malloc(N * sizeof(double));
    double *x = malloc(N * sizeof(double));
    int i, j;
    double temp, x_i, norm2;

    for (i = 0; i < N; i++) {
        x[i] = 0;
    }

    do {
        for (i = 0; i < N; i++) {
            prev[i] = x[i];
        }

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
        for (i = 0; i < N; i++) {
            norm2 += (prev[i] - x[i]) * (prev[i] - x[i]);
        }

    } while (norm2 > eps * eps);
    return x;
}

int main() {

    double A[9] = {2, 1, 1, 1, -1, 0, 3, -1, 2};
    double b[3] = {2, -2, 2};
//    double A[4] = {5, 2, 2, 1};
//    double b[2] = {7, 9};
    int N = 3;

    double *x = solve_gauss_seidel(A, b, N, 0.00000001);


    for (int i = 0; i < N; i++) {
        printf("x_%d = %f\n",i, x[i]);
    }

    return 0;
}
