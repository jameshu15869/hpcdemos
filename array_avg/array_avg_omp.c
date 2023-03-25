#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 2

/**
 * This demo program calculates the sum of numbers in an array
 * using omp
*/
static long ARRAY_SIZE = 12;

int* generate_array(int size) {
    int* array = (int *) malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        array[i] = i;
    }
    return array;
}

double compute_average(int a[], int n) {
    double sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum / n;
}

int main() {
    int* a = generate_array(ARRAY_SIZE);

    double sum = 0;
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        #pragma omp for reduction (+:sum)
        for(int i = 0; i < ARRAY_SIZE; i++) {
            sum += a[i];
            printf("Thread #%d: i=%d, sum = %.2f \n", thread_id, i, sum);
        }
    }

    double avg = sum / ARRAY_SIZE;
    printf("average = %f \n", avg);
}