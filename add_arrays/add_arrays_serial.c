#include <stdio.h>
#include <omp.h>

int ARRAY_SIZE = 12;
int main() {
    int a[ARRAY_SIZE], b[ARRAY_SIZE], c[ARRAY_SIZE];

    for(int i = 0; i < ARRAY_SIZE; i++){
        a[i] = i;
        b[i] = i;
    }

    double execution_time = omp_get_wtime();

    for(int i = 0; i < ARRAY_SIZE; i++) {
        c[i] = a[i] + b[i];
        printf("a[%d]=%d, b[%d]=%d, c[%d]=%d \n", i, a[i], i, b[i], i, c[i]);
    }

    execution_time = omp_get_wtime() - execution_time;
    printf("execution time = %f \n", execution_time);

    return 0;
}