#include <omp.h>
#include <stdio.h>

float dotprod(float *a, float *b, size_t N) {
    int i, tid;
    float sum;

#pragma omp parallel \
    default(none) \
    shared(sum, a, b, N) \
    private(i, tid) \
    num_threads(4)
    {
        tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
        for (i = 0; i < N; ++i) {
            sum += a[i] * b[i];
            printf("tid = %d i = %d\n", tid, i);
        }
    }
    return sum;
}

int main(int argc, char *argv[]) {
    const size_t N = 100;
    int i;
    float sum;
    float a[N], b[N];


    for (i = 0; i < N; ++i) {
        a[i] = b[i] = (float) i;
    }
    double start = omp_get_wtime();
    sum = dotprod(a, b, N);
    double end = omp_get_wtime();

    printf("Sum = %f\n", sum);
    printf("Time = %f\n", end - start);

    return 0;
}