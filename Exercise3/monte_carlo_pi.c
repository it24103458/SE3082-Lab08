#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const long long total_points = 10000000;

    long long points_per_process = total_points / size;

    long long inside_circle = 0;
    long long total_inside_circle = 0;

    double start_time = MPI_Wtime();

    /*
     * Give each MPI process a different random seed.
     */
    unsigned int seed = (unsigned int)(time(NULL) + rank);

    /*
     * Generate random points.
     */
    for (long long i = 0; i < points_per_process; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        /*
         * Check whether the point is inside
         * the quarter circle.
         */
        if ((x * x + y * y) <= 1.0)
        {
            inside_circle++;
        }
    }

    /*
     * Add the results from all processes.
     */
    MPI_Reduce(
        &inside_circle,
        &total_inside_circle,
        1,
        MPI_LONG_LONG,
        MPI_SUM,
        0,
        MPI_COMM_WORLD
    );

    double end_time = MPI_Wtime();

    if (rank == 0)
    {
        double pi = 4.0 *
                    ((double)total_inside_circle / total_points);

        printf("Number of processes: %d\n", size);
        printf("Total points: %lld\n", total_points);
        printf("Points inside circle: %lld\n",
               total_inside_circle);
        printf("Calculated Pi: %.10f\n", pi);
        printf("Execution time: %.6f seconds\n",
               end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
