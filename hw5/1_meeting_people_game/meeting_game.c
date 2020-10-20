#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

char names[4][8] = {
        "Alex",
        "Sergey",
        "Gleb",
        "Vlad",
};

int in_array(int *arr, int val, int N) {
    for (int i = 0; i < N; i++) {
        if (arr[i] == val) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {

    int psize;
    int prank;
    MPI_Status status;
    int N = 4;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &psize);
    MPI_Comm_rank(MPI_COMM_WORLD, &prank);


    int to, count, str_len;
    int *previous_senders, *new_senders;
    char *previous_names, *new_names;
    srand(prank);

    if (prank == 0) {
        to = rand() % (N - 1) + 1;
        count = 1;

        previous_senders = malloc(count * sizeof(int));
        previous_senders[0] = 0;

        str_len = (int) strlen(names[0]);

        MPI_Ssend(&count, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
        MPI_Ssend(previous_senders, 1, MPI_INT, to, 1, MPI_COMM_WORLD);
        MPI_Ssend(&str_len, 1, MPI_INT, to, 2, MPI_COMM_WORLD);
        MPI_Ssend(names[0], str_len, MPI_CHAR, to, 3, MPI_COMM_WORLD);


    } else {
        MPI_Recv(&count, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        previous_senders = malloc(count * sizeof(int));
        MPI_Recv(previous_senders, count, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&str_len, count, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
        previous_names = malloc(str_len * sizeof(char));
        MPI_Recv(&previous_names[0], str_len, MPI_CHAR, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);


        new_senders = malloc((count + 1) * sizeof(int));
        new_senders[count] = prank;
        for (int i = 0; i < count; i++) {
            new_senders[i] = previous_senders[i];
        }

        str_len = str_len + 1 + (int) strlen(names[prank]);
        new_names = malloc((str_len) * sizeof(char));
        strcpy(new_names, previous_names);
        strcat(new_names, "|");
        strcat(new_names, names[prank]);

        printf("current name: %s \n", names[prank]);
        printf("Received elements count = %d \n", count);
        printf("Received names: %s \n", previous_names);
        printf("Received rangs:");
        for (int i = 0; i < count; i++) {
            printf("%d ", previous_senders[i]);
        }
        printf("\n");

        count += 1;
        if (count < N) {
            do {
                to = rand() % (N - 1) + 1;
            } while (in_array(previous_senders, to, count - 1));

            MPI_Ssend(&count, 1, MPI_INT, to, 0, MPI_COMM_WORLD);
            MPI_Ssend(new_senders, count, MPI_INT, to, 1, MPI_COMM_WORLD);
            MPI_Ssend(&str_len, 1, MPI_INT, to, 2, MPI_COMM_WORLD);
            MPI_Ssend(&new_names[0], str_len, MPI_CHAR, to, 3, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();

    return 0;
}
