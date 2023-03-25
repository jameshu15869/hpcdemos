#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

/**
 * For this demonstration we assume that all the elements
 * of the array can be easily divided into each process
 * for simplicity.
*/
int ARRAY_SIZE = 12;
int main() {
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int elements_per_process = ARRAY_SIZE / world_size;
    if(world_rank == world_size - 1) {
        elements_per_process += ARRAY_SIZE % world_size;
    }

    int *a = NULL;
    int *b = NULL;
    if(world_rank == 0) {
        a = (int *) malloc(sizeof(int) * ARRAY_SIZE);
        b = (int *) malloc(sizeof(int) * ARRAY_SIZE);
        for(int i = 0; i < ARRAY_SIZE; i++) {
            a[i] = i;
            b[i] = i;
        }
    }

    double execution_time = MPI_Wtime();
    
    int *a_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    int *b_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    int *c_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    MPI_Scatter(a, elements_per_process, MPI_INT, a_sub_array, elements_per_process, 
        MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, elements_per_process, MPI_INT, b_sub_array, elements_per_process, 
        MPI_INT, 0, MPI_COMM_WORLD);
    for(int i = 0; i < elements_per_process; i++) {
        c_sub_array[i] = a_sub_array[i] + b_sub_array[i];
        int world_index = elements_per_process * world_rank + i;
        printf("Process #%d: a[%d]: %d, b[%d]: %d, c[%d]: %d \n", 
            world_rank, world_index, a_sub_array[i], world_index, b_sub_array[i], world_index, c_sub_array[i]);
    }
    printf("\n");

    int *c_result = NULL;
    if(world_rank == 0) {
        c_result = (int *) malloc(sizeof(int) * ARRAY_SIZE);
    }
    MPI_Gather(c_sub_array, elements_per_process, MPI_INT, c_result, elements_per_process, MPI_INT, 0, MPI_COMM_WORLD);

    if(world_rank == 0) {
        execution_time = MPI_Wtime() - execution_time;
        printf("execution time = %f \n", execution_time);

        free(a);
        free(b);
        free(c_result);
    }
    free(a_sub_array);
    free(b_sub_array);
    free(c_sub_array);

    MPI_Finalize();
}