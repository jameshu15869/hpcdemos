#include <mpi.h>
#include <stdio.h>

int main() {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if(world_rank == 0) {
        printf("Total Processes: %d \n", world_size);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Hello world! from Process #%d \n", world_rank);

    MPI_Finalize();

    return 0;
}