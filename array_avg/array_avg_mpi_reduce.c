#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * This demo program calculates the sum of numbers in an array
 * using mpi scatter/gather - it scatters 
*/
static long ARRAY_SIZE = 12;

int* generate_array(int size) {
    int* array = (int *) malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        array[i] = i;
    }
    return array;
}

int main() {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int elements_per_process = ARRAY_SIZE / world_size;

    int *a = NULL;
    if(world_rank == 0) {
        a = generate_array(ARRAY_SIZE);
    }

    double execution_time = MPI_Wtime();

    int *sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    MPI_Scatter(a, elements_per_process, MPI_INT, 
        sub_array, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    double sub_sum = 0;
    for(int i = 0; i < elements_per_process; i++) {
        sub_sum += sub_array[i];
        printf("Process #%d: sub_array[%d] = %d, sub_sum = %.2f \n", 
            world_rank, i, sub_array[i], sub_sum);
    }
    printf("Process #%d: subsum: %.2f \n", world_rank, sub_sum);
    printf("\n");

    double global_sum;
    MPI_Reduce(&sub_sum, &global_sum, 1, MPI_DOUBLE,
        MPI_SUM, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    execution_time = MPI_Wtime() - execution_time;
    if(world_rank == 0) {
        double global_average = global_sum / ARRAY_SIZE;
        printf("global sum = %.2f, average = %.2f \n", global_sum, global_average);
        printf("execution time = %f \n", execution_time);
    }
    printf("\n");

    MPI_Finalize();
}