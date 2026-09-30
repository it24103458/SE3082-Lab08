#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define TOTAL_POINTS 10000000

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int points_per_process = TOTAL_POINTS / size;
    int local_inside = 0;

    unsigned int seed = (unsigned int)time(NULL) + rank;

    for (int i = 0; i < points_per_process; i++)
    {
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;

        if (x * x + y * y <= 1.0)
            local_inside++;
    }

    if (rank == 0)
    {
        long long total_inside = local_inside;

        MPI_Status status;

        for (int i = 1; i < size; i++)
        {
            int received_inside;

            MPI_Recv(
                &received_inside,
                1,
                MPI_INT,
                MPI_ANY_SOURCE,
                0,
                MPI_COMM_WORLD,
                &status
            );

            total_inside += received_inside;

            printf(
                "Received %d points from rank %d\n",
                received_inside,
                status.MPI_SOURCE
            );
        }

        double pi = 4.0 * (double)total_inside / (double)(points_per_process * size);

        printf("Total points inside circle: %lld\n", total_inside);
        printf("Estimated Pi: %.10f\n", pi);
    }
    else
    {
        MPI_Send(
            &local_inside,
            1,
            MPI_INT,
            0,
            0,
            MPI_COMM_WORLD
        );
    }

    MPI_Finalize();

    return 0;
}
