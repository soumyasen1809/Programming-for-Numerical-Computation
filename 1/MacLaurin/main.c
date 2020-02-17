#include <stdio.h>
#include<omp.h>
#include <stdlib.h>
#include<math.h>

double factorial (int n)
{
    double val = 1;
    for (int i = 0; i < n; i++)
    {
        val = val*(i+1);
    }

    return val;
}

int main()
{
    double a = 0.1;
    int n_iters = 10000;
    double sum = 0;
    int num_threads;

    // Parallel implementation

    double start_parallel_time = omp_get_wtime();
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < n_iters; i++)
    {
        num_threads = omp_get_num_threads();
        sum = sum + pow(a,i)/factorial(i);
    }
    double end_parallel_time = omp_get_wtime();

    printf("e^%f is %f using %d threads in %f time\n", a,sum, num_threads, end_parallel_time-start_parallel_time);

    // Serial implementation for comparison

    double start_serial_time = omp_get_wtime();
    #pragma omp master
    for (int i = 0; i < n_iters; i++)
    {
        num_threads = omp_get_num_threads();
        sum = sum + pow(a,i)/factorial(i);
    }
    double end_serial_time = omp_get_wtime();

    printf("e^%f is %f using %d threads in %f time\n", a,sum, num_threads, end_serial_time-start_serial_time);

    double speedup = (end_serial_time-start_serial_time)/(end_parallel_time-start_parallel_time);
    printf("Speedup is %f\n", speedup);

    return 0;
}
