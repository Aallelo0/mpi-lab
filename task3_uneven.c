#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int N = 17;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        if (rank == 0) {
            printf("Program ini dirancang khusus untuk 4 proses (-np 4).\n");
        }
        MPI_Finalize();
        return 0;
    }

    int base_chunk = N / size;
    int remainder = N % size;

    int start_index, local_n;

    if (rank < remainder) {
        local_n = base_chunk + 1;
        start_index = rank * local_n;
    } else {
        local_n = base_chunk;
        start_index = rank * base_chunk + remainder;
    }

    printf("Rank %d: start_index = %d, iterations = %d\n", rank, start_index, local_n);

    MPI_Finalize();
    return 0;
}
