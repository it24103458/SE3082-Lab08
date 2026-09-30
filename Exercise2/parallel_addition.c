#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long N = 10000000;

    long long local_sum = 0;
    long long total_sum = 0;

    double start_time = MPI_Wtime();

    /*
     * Divide the numbers among the processes.
     */
    long long chunk = N / size;

    long long start = rank * chunk + 1;
    long long end = (rank + 1) * chunk;

    /*
     * Give the remaining numbers to the last process.
     */
    if (rank == size - 1)
    {
        end = N;
    }

    /*
     * Calculate the local sum.
     */
    for (long long i = start; i <= end; i++)
    {
        local_sum += i;
    }

    /*
     * Add all local sums into process 0.
     */
    MPI_Reduce(
        &local_sum,
        &total_sum,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    double end_time = MPI_Wtime();

    if (rank == 0)
    {
        printf("Number of processes: %d\n", size);
        printf("Total sum: %lld\n", total_sum);
        printf("Execution time: %.6f seconds\n",
               end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
