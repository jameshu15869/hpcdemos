#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000;
int main()
{
    double step = 1.0 / (double)num_steps;

    double x;
    double pi = 0.0;

    double execution_time = omp_get_wtime();

    for (int i = 0; i < num_steps; i++)
    {
        x = i * step + 0.5 * step;          // step to middle of the rectangle
        pi += step * (4.0 / (1.0 + x * x)); // calculate the area of a riemann sum
    }

    execution_time = omp_get_wtime() - execution_time;
    printf("serial pi = %f \n", pi);
    printf("execution time = %f \n", execution_time);
    return 0;
}
