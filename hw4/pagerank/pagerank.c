#include <stdio.h>
#include <stdlib.h>
#include "openblas/cblas.h"

int SEED = 1234;

// Создаем случайный граф
void random_graph(double *A, int N) {
    srand(SEED);
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i * N + j] = A[i * N + j];
            if (i == j) {
                A[i * N + j] = 0;
            } else {
                A[i * N + j] = rand() & 1;
            }
        }
    }
}

// Делает так, чтобы столбцы суммировались в 1, как вероятности
void add_col_probas(double *A, int N) {
    int i, j;
    double col_sum = 0;
    for (j = 0; j < N; j++) {
        col_sum = 0;
        for (i = 0; i < N; i++) {
            col_sum += A[i * N + j];
        }
        for (i = 0; i < N; i++) {
            if (A[i * N + j] != 0) {
                A[i * N + j] = A[i * N + j] / col_sum;
            }
        }
    }
}

// Собственно, сам алгоритм
void pagerank(double *G, double *r, int N, double d, double eps) {
    double *r_new = malloc(N * sizeof(double));
    double eps2 = eps * eps;
    int i;
    double norm;

    CBLAS_ORDER order = CblasRowMajor;
    CBLAS_TRANSPOSE transpose = CblasNoTrans;

    for (i = 0; i < N; i++) {
        r[i] = 1.0 / N;
        r_new[i] = 0;
    }

    do { // r = Gr - метод фиксированной точки
        cblas_dgemv(order, transpose, N, N, 1, G, N, r, 1, 0, r_new, 1);
        norm = 0;
        for (i = 0; i < N; i++) {
            r_new[i] = d * r_new[i] + (1 - d) / N;
            norm += (r_new[i] - r[i]) * (r_new[i] - r[i]);
            r[i] = r_new[i];
        }
    } while (norm > eps2); // условие сходимости

    free(r_new);
}

// Наивный алгоритм, просто считаем ранг как долю входящих ссылок
void naive_ranking(double *G, double *r, int N) {
    int i, j;
    double all_sum = 0;
    double sum;
    for (i = 0; i < N; i++) {

        sum = 0;
        for (j = 0; j < N; j++) {
            sum += G[i * N + j] > 0;
        }
        all_sum += sum;
        r[i] = sum;
    }
    for (i = 0; i < N; i++) {
        r[i] = r[i] / all_sum;
    }
}



int main() {

    int N = 10;
    int i;
    double dumping_factor = 0.85;
    double eps = 0.001;
    double *G = malloc(N * N * sizeof(double));
    double *rank = malloc(N * sizeof(double));
    double *rank_naive = malloc(N * sizeof(double));

    random_graph(G, N);
    add_col_probas(G, N);

    pagerank(G, rank, N, dumping_factor, eps);
    naive_ranking(G, rank_naive, N);

    printf("\nPageRank:\n");
    for (i = 0; i < N; i++) {
        printf("%.3f ", rank[i]);
    }
    printf("\nNaive ranking:\n");
    for (i = 0; i < N; i++) {
        printf("%.3f ", rank_naive[i]);
    }

    free(rank);
    free(G);

    return 0;
}
