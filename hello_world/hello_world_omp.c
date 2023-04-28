#include <stdio.h>
#include <omp.h>

// #define NUM_THREADS 2
int main(){
    // omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int total_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        if(thread_id == 0) {
            printf("Total Threads: %d \n", total_threads);
        }

        #pragma omp barrier

        printf("Hello world! from Thread #%d \n", thread_id);
    }
    return 0;
}
