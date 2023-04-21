#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <string.h>

int ARRAY_SIZE = 21;
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

        // send to all nodes except root
        for(int child_proc = 1; child_proc < world_size - 1; child_proc++) {
            MPI_Send(a + child_proc * elements_per_process, elements_per_process, MPI_INT, child_proc, 0, MPI_COMM_WORLD);
            MPI_Send(b + child_proc * elements_per_process, elements_per_process, MPI_INT, child_proc, 0, MPI_COMM_WORLD);
        }

        // send the last one
        MPI_Send(a + (world_size - 1) * elements_per_process, elements_per_process + ARRAY_SIZE % world_size, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD);
        MPI_Send(b + (world_size - 1) * elements_per_process, elements_per_process + ARRAY_SIZE % world_size, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD);
    }

    double execution_time = MPI_Wtime();
    
    int *a_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    int *b_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    int *c_sub_array = (int *) malloc(sizeof(int) * elements_per_process);
    MPI_Status status;
    int received_count;

    if(world_rank == 0) {
        memcpy(a_sub_array, a, sizeof(int) * elements_per_process);
        memcpy(b_sub_array, b, sizeof(int) * elements_per_process);
    } else {
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &received_count);

        printf("Process #%d: Received %d numbers from process 0 \n", world_rank, received_count);

        MPI_Recv(a_sub_array, received_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b_sub_array, received_count, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for(int i = 0; i < elements_per_process; i++) {
        c_sub_array[i] = a_sub_array[i] + b_sub_array[i];
        int world_index = elements_per_process * world_rank + i;
        printf("Process #%d: a[%d]: %d, b[%d]: %d, c[%d]: %d \n", 
            world_rank, world_index, a_sub_array[i], world_index, b_sub_array[i], world_index, c_sub_array[i]);
    }
    printf("\n");
    if(world_rank != 0) {
        MPI_Send(c_sub_array, elements_per_process, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    int *c_result = NULL;
    if(world_rank == 0) {
        c_result = (int *) malloc(sizeof(int) * ARRAY_SIZE);
        memcpy(c_result, c_sub_array, sizeof(int) * elements_per_process);

        for(int i = 1; i < world_size - 1; i++) {
            MPI_Recv(c_result + i * elements_per_process, elements_per_process, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        MPI_Recv(c_result + (world_size - 1) * elements_per_process,
            elements_per_process + ARRAY_SIZE % world_size, 
            MPI_INT,
            world_size - 1,
            0,
            MPI_COMM_WORLD,
            MPI_STATUS_IGNORE);

        for(int i = 0; i < ARRAY_SIZE; i++) {
            printf("Master Thread: c[%d]: %d \n", i, c_result[i]);
        }

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