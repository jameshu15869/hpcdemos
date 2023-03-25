#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 2

int ARRAY_SIZE = 12;
int main() {
    
    int a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];

    for(int i = 0; i < ARRAY_SIZE; i++){
        a[i] = i;
        b[i] = i;
    }

    double execution_time = omp_get_wtime();

    int i;
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel
{
    int thread_id = omp_get_thread_num();
    #pragma for private(i) // schedule(static) can be used for demonstration purposes
    for(i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
        printf("Thread #%d: a[%d]=%d, b[%d]=%d, c[%d]=%d \n", thread_id, i, a[i], i, b[i], i, c[i]);
    }
}

    execution_time = omp_get_wtime() - execution_time;
    printf("execution time = %f \n", execution_time);

    return 0;
}