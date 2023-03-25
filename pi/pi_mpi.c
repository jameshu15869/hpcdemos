#include <stdio.h>
#include <mpi.h>

long num_steps = 1000000;

int main() {
    MPI_Init(NULL, NULL);
    MPI_Barrier(MPI_COMM_WORLD);
    double time_data = MPI_Wtime();

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    double step = 1.0 / (double) num_steps;

    double x;
    double local_sum = 0.0;
    for(int i = world_rank; i < num_steps; i += world_size) {
        x = i * step + 0.5 * step;
        local_sum += (4.0 / (1.0 + x * x));
        // printf("hi from %d, %d \n", world_rank, i);
    }

    local_sum *= step;

    double pi;
    MPI_Reduce(&local_sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    time_data = MPI_Wtime() - time_data;
    if(world_rank == 0) {
        printf("pi = %f \n", pi);
        printf("final time: %f \n", time_data);
    }
    MPI_Finalize();
    return 0;
}