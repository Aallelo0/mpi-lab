#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, data[5] = {1, 2, 3, 4, 5};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        MPI_Send(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(data, 5, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("rank 0 sent [1,2,3,4,5] received [%d,%d,%d,%d,%d]\n", 
               data[0], data[1], data[2], data[3], data[4]);
    } else if (rank == 1) {
        MPI_Recv(data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < 5; i++) data[i] *= data[i];
        MPI_Send(data, 5, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
