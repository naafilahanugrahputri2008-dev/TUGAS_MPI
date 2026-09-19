#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int send_data = world_rank * 10;
    int recv_data;

    int next_rank = (world_rank + 1) % world_size;
    int prev_rank = (world_rank - 1 + world_size) % world_size;

    MPI_Sendrecv(&send_data, 1, MPI_INT, next_rank, 0,
                 &recv_data, 1, MPI_INT, prev_rank, 0,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Rank %d mengirim %d ke Rank %d dan menerima %d dari Rank %d\n",
           world_rank, send_data, next_rank, recv_data, prev_rank);

    MPI_Finalize();
    return 0;
}
