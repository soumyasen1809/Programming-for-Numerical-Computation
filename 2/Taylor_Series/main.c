#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

double factorial(int n)
{
    double val = 1.0;
    if (n == 0 || n == 1)
        val = 1.0;
    else
        val = val*n;

    return val;
}


int main()
{
    double h = 0.0001;
    double a = 0.1;
    double sum;
    int thread_count;

    // Parallel implementation

    double start_parallel_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 3; i++)
    {
        thread_count = omp_get_num_threads();
        sum = sum + ((pow(h,i))/factorial(i))*exp(a);
    }
    double end_parallel_time = omp_get_wtime();

    printf("Taylor series of e^x at x = %f till 2 terms is:  %f | takes %f time for %d number of threads\n", a, sum, end_parallel_time - start_parallel_time, thread_count);

    // Serial implementation

    sum = 0.0;

    double start_serial_time = omp_get_wtime();
    #pragma omp master
    for (int i = 0; i < 3; i++)
    {
        thread_count = omp_get_num_threads();
        sum = sum + ((pow(h,i))/factorial(i))*exp(a);
    }
    double end_serial_time = omp_get_wtime();

    printf("Taylor series of e^x at x = %f till 2 terms is:  %f | takes %f time for %d number of threads\n", a, sum, end_serial_time - start_serial_time, thread_count);

    double speedup = (end_serial_time - start_serial_time)/(end_parallel_time - start_parallel_time);
    printf("Speedup is %f\n",  speedup);

    return 0;
}
