#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long n = 100000000;
    double h = 1.0 / (double)n;
    double local_sum = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);
    double start_time = MPI_Wtime();

    for (long i = rank; i < n; i += size) {
        double x = h * ((double)i + 0.5);
        local_sum += 4.0 / (1.0 + x * x);
    }

    double local_pi = h * local_sum;
    double pi;

    MPI_Reduce(&local_pi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Proses: %d | Hasil Pi: %.16f | Waktu Eksekusi: %f detik\n", 
               size, pi, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
