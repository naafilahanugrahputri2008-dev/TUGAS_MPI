#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int data = 0;
    MPI_Request request;
    MPI_Status status;

    if (rank == 0) {
        data = 42;
        printf("Rank 0: Mengirim data %d (non-blocking)...\n", data);
        MPI_Isend(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Rank 0: Pengiriman selesai.\n");
    } else if (rank == 1) {
        printf("Rank 1: Memulai penerimaan data (non-blocking)...\n");
        MPI_Irecv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        MPI_Wait(&request, &status);
        printf("Rank 1: Data berhasil diterima: %d\n", data);
    }

    MPI_Finalize();
    return 0;
}
