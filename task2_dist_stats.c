#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    enum { N = 12 };
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size > N || N % size != 0) {
        if (rank == 0) {
            fprintf(stderr, "Gunakan 1, 2, 3, 4, 6, atau 12 ranks.\n");
        }
        MPI_Finalize();
        return 1;
    }

    int data[N] = {0};
    if (rank == 0) {
        for (int i = 0; i < N; ++i) {
            data[i] = i + 1;
        }
    }

    int count = N / size;
    int local[N] = {0};

    MPI_Scatter(data, count, MPI_INT, local, count, MPI_INT, 0, MPI_COMM_WORLD);

    int local_sum = 0;
    int local_max = local[0];
    for (int i = 0; i < count; ++i) {
        local_sum += local[i];
        if (local[i] > local_max) {
            local_max = local[i];
        }
    }

    int global_sum = 0;
    int global_max = 0;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global Sum: %d\n", global_sum);
        printf("Global Max: %d\n", global_max);
    }

    MPI_Finalize();
    return 0;
}
