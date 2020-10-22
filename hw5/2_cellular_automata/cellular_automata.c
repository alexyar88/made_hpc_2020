#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"


// Считаем массив из [prev, current, next] с учетом периодичности
void get_neighbours(const int *a, int i, int N, int *n, int has_period) {
    if (has_period) {

        if (i == 0) {
            n[0] = a[N - 1];
        } else {
            n[0] = a[i - 1];
        }

        n[1] = a[i];

        if (i == N - 1) {
            n[2] = a[0];
        } else {
            n[2] = a[i + 1];
        }
    } else {
        if (i == 0) {
            n[0] = 0;
        } else {
            n[0] = a[i - 1];
        }

        n[1] = a[i];

        if (i == N - 1) {
            n[2] = 0;
        } else {
            n[2] = a[i + 1];
        }
    }
}

// Правило. Правила можно менять, достаточно задать новую функцию
int rule101(const int *n) {
    if (n[0] == 0 && n[1] == 0 && n[2] == 0) return 0;
    if (n[0] == 0 && n[1] == 0 && n[2] == 1) return 1;
    if (n[0] == 0 && n[1] == 1 && n[2] == 0) return 0;
    if (n[0] == 0 && n[1] == 1 && n[2] == 1) return 1;
    if (n[0] == 1 && n[1] == 0 && n[2] == 0) return 1;
    if (n[0] == 1 && n[1] == 0 && n[2] == 1) return 0;
    if (n[0] == 1 && n[1] == 1 && n[2] == 0) return 1;
    if (n[0] == 1 && n[1] == 1 && n[2] == 1) return 0;
}


// Чтобы нарисовать картинку, утянул откуда-то из интернета
typedef unsigned char U8;
typedef struct {
    U8 p[4];
} color;

void save_to_image(char *file_name, const int *arr, int width, int height) {

    FILE *f = fopen(file_name, "wb");


    color tablo_color[256];
    for (int i = 0; i < 256; i++) {
        tablo_color[i] = (color) {(U8) i, (U8) i, (U8) i, (U8) 255};
    }


    U8 pp[54] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0,
                 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32};
    *(int *) (pp + 2) = 54 + 4 * width * height;  //file size
    *(int *) (pp + 18) = width;
    *(int *) (pp + 22) = height;
    *(int *) (pp + 42) = height * width * 4;      //bitmap size
    fwrite(pp, 1, 54, f);


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            U8 indis = (U8) arr[i * width + j];
            fwrite(tablo_color + indis, 4, 1, f);
        }
    }

    fclose(f);

}

int main(int argc, char **argv) {

    int *a, *n, *hist, *hist2, *image;
    int N = 512;
    int Ng = N / 2 + 2;
    int n_epochs = 512;
    int i, epoch;
    a = malloc(Ng * sizeof(int));
    hist = malloc((N / 2) * n_epochs * sizeof(int));
    n = malloc(3 * sizeof(int));

    int psize;
    int prank;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);

    // Каждый поток заполняет инициализирует свою часть
    for (i = 0; i < Ng; i++) {
        a[i] = rand() & 1;
    }

    for (epoch = 0; epoch < n_epochs; epoch++) {
        // Получаем и отправляем информацию из клеток-призраков
        if (prank == 0) {
            MPI_Ssend(&a[Ng - 2], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            MPI_Ssend(&a[1], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        } else {
            MPI_Recv(&a[0], 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&a[Ng - 1], 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        }

        if (prank == 0) {
            MPI_Recv(&a[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&a[Ng - 1], 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);

        } else {
            MPI_Ssend(&a[Ng - 2], 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Ssend(&a[1], 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }

        for (i = 1; i < Ng - 1; i++) {
            get_neighbours(a, i, Ng, n, 1);
            a[i] = rule101(n);
        }

        for (i = 1; i < Ng - 1; i++) {
            hist[epoch * (Ng - 2) + (i - 1)] = a[i];
        }
    }

    if (prank == 1) {
        MPI_Ssend(&hist[0], (N / 2) * n_epochs, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    if (prank == 0) {

        // Собираем историю в массив, чтобы потом его нарисовать
        image = malloc(N * n_epochs * sizeof(int));
        for (epoch = 0; epoch < n_epochs; epoch++) {
            for (i = 0; i < N / 2; i++) {
                image[epoch * N + i] = hist[epoch * (N / 2) + i] * 255;
            }
        }

        // Получаем вторую часть истории
        MPI_Recv(&hist[0], (N / 2) * n_epochs, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        for (epoch = 0; epoch < n_epochs; epoch++) {
            for (i = 0; i < N / 2; i++) {
                image[epoch * N + i + (N / 2)] = hist[epoch * (N / 2) + i] * 255;
            }
        }

        save_to_image("../cellular_automata_parallel.bmp", image, n_epochs, N);
    }

    MPI_Finalize();

    return 0;
}
