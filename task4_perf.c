#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    double start_time, end_time, local_elapsed, max_elapsed;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();

    long long N = 10000000;
    long long sum = 0;
    for (long long i = 0; i < N; i++) {
        sum += i;
    }

    end_time = MPI_Wtime();
    local_elapsed = end_time - start_time;

    MPI_Reduce(&local_elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Jumlah Proses : %d  Waktu Eksekusi: %f detik\n", size, max_elapsed);
    }

    MPI_Finalize();
    return 0;
}
