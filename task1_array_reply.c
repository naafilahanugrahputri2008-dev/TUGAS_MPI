#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        if (rank == 0) {
            fprintf(stderr, "Gunakan tepat 2 proses.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        int send_buf[5] = {1, 2, 3, 4, 5};
        int recv_buf[5] = {0};

        // Kirim array 5 elemen ke Rank 1
        MPI_Send(send_buf, 5, MPI_INT, 1, 10, MPI_COMM_WORLD);
        // Terima hasil kuadrat dari Rank 1
        MPI_Recv(recv_buf, 5, MPI_INT, 1, 20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("Rank 0 menerima hasil kuadrat: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", recv_buf[i]);
        }
        printf("\n");
    } else {
        int local_buf[5] = {0};
        int reply_buf[5] = {0};

        // Terima array dari Rank 0
        MPI_Recv(local_buf, 5, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Hitung kuadrat tiap elemen
        for (int i = 0; i < 5; i++) {
            reply_buf[i] = local_buf[i] * local_buf[i];
        }

        // Kirim balik ke Rank 0
        MPI_Send(reply_buf, 5, MPI_INT, 0, 20, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
