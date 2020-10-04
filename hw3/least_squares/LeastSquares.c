#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"

const int NUM_THREADS = 8;
const double PI = 3.1415926;

double get_rand(unsigned int *seed) {
    return (double) rand_r(seed) / (double) RAND_MAX;
}

// Генерация нормального шума. Генерируем x, y из равномерного распределения и
// приближаем нормальное рапределение cos(2PIx) * sqrt(-2log(y))
double norm_dist_approximation_sample(double mu, double sigma, unsigned int seed) {
    unsigned int tid, seed_x, seed_y;
    double x, y, normal_0_1;
    tid = omp_get_thread_num();
    seed_x = (unsigned int) ((time(NULL) * seed * 7) & 0xFFFFFFF0) | (tid + 1 + seed);
    seed_y = (unsigned int) ((time(NULL) * seed) & 0xFFF0F0FF) | (tid + 51 + seed);
    x = get_rand(&seed_x);
    y = get_rand(&seed_y);
    normal_0_1 = cos(2 * PI * x) * sqrt(-2. * log(y));
    return normal_0_1 * sigma + mu;
}

void fit(const double *x, const double *y, const int size, const double leaning_rate,
         const int n_iters, double *w_hat, double *b_hat) {

    double w_deriv, b_deriv, resid;
    double w = *w_hat, b = *b_hat;
    int i, j;

#pragma omp parallel for  \
    private(i, j, resid, w_deriv, b_deriv) \
    shared(size, x, y, n_iters, leaning_rate) \
    lastprivate(w, b) \
    default(none) \
    num_threads(NUM_THREADS)
    for (i = 0; i < n_iters; ++i) { // Здесь обычный SGD
        j = i % size;
        resid = y[j] - (w * x[j] + b);
        w_deriv = -2. * x[j] * resid;
        b_deriv = -2. * resid;
        w -= leaning_rate * w_deriv / (double) size;
        b -= leaning_rate * b_deriv / (double) size;
    }

    *w_hat = w;
    *b_hat = b;

}


int main() {
    // Должны обучить эти коэффициенты
    double w_real = 0.8;
    double b_real = 0.3;

    // Размер данных
    int size = 500;

    // Параметры тренировки
    int n_epochs = size * 100000;
    double learning_rate = 0.01;

    double *x = malloc(size * sizeof(double));
    double *y = malloc(size * sizeof(double));
    int i;

#pragma omp parallel for private(i) shared(x, y, size, w_real, b_real) default(none) num_threads(NUM_THREADS)
    for (i = 0; i < size; ++i) {
        x[i] = (double) (i / (double) size);
        y[i] = w_real * x[i] + b_real + norm_dist_approximation_sample(0, 1, i + 1);
    }

    printf("%f %f\n", w_real, b_real);
    double w_hat = 0;
    double b_hat = 0;

    double start = omp_get_wtime();
    fit(x, y, size, learning_rate, n_epochs, &w_hat, &b_hat);
    double end = omp_get_wtime();

    printf("%f %f\n", w_hat, b_hat);
    printf("Time=%f\n", end - start);

    return 0;
}
