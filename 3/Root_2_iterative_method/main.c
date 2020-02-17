#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    double num = 2.0;
    double sum = 1.0;
    int num_iters = 100;
    int num_threads;

    // Serial code

    double start_ser_time = omp_get_wtime();
    #pragma omp master
    for (int i = 0; i < num_iters; i++)
    {
        num_threads = omp_get_num_threads();
        sum = 0.5*(sum + (num/sum));
    }
    double end_ser_time = omp_get_wtime();

    printf("Square Root of %f is %f | time taken %f by %d threads\n", num, sum, end_ser_time-start_ser_time,num_threads);

    return 0;
}
