#include <stdio.h>
#include <stdlib.h>

/**
 * This demo program calculates the sum of numbers in an array
 * using a single process.
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
        printf("i = %d, sum = %.2f \n", i, sum);
        sum += a[i];
    }
    return sum / n;
}

int main() {
    int* a = generate_array(ARRAY_SIZE);
    double avg = compute_average(a, ARRAY_SIZE);
    printf("average = %f \n", avg);
}