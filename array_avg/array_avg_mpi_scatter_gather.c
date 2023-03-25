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

double compute_average(int a[], int n, int process_id) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        printf("Process #%d: a[%d] = %d, sum = %.2f \n", process_id, i, a[i], sum);
    }
    return sum / n;
}

double compute_final_average(double a[], int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
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

    double sub_average = compute_average(sub_array, elements_per_process, world_rank);

    double *sub_results = (double *) malloc(sizeof(double) * world_size);

    MPI_Gather(&sub_average, 1, MPI_DOUBLE, 
        sub_results, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    execution_time = MPI_Wtime() - execution_time;
    if(world_rank == 0) {
        for(int i = 0; i < world_size; i++){
            printf("Process #%d average = %f \n", i, sub_results[i]);
        }
        double total_average = compute_final_average(sub_results, world_size);
        printf("average = %f \n", total_average);
        printf("execution time = %f \n", execution_time);
    }

    free(sub_array);
    free(sub_results);

    MPI_Finalize();
}