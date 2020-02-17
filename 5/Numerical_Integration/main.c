#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

double func_x(double x)
{
    return x - (pow(x,2)/2.0) + (x*log(x));
}

int main()
{
    double a = 1.0;
    double b = 2.0;

    // Trapezoidal rule
    double h = b-a;
    double integral_trap = (h/2.0)*(func_x(a) + func_x(b));
    printf("Trapezoidal Rule integration is %f\n", integral_trap);

    // Simpson's 1/3rd rule
    h = (b-a)/2.0;
    double integral_simps = (h/3.0)*( func_x(a) + func_x(b) + 4*func_x(a+h) );
    printf("Simpson's 1/3rd Rule integration is %f\n", integral_simps);

    // Multiple interval Trapezoidal rule
    int num_points = 100000000;
    h = (b-a)/(num_points-1);
    double integral_mult = 0;
    int thread_num;

    double par_start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:integral_mult) firstprivate(num_points, h)
    for (int i = 0; i < num_points-1; i++)
    {
        thread_num = omp_get_num_threads();
        integral_mult = integral_mult + ( (h/2.0) * (func_x(a + i*h) + func_x(a+(i+1)*h)) );
    }
    double par_end_time = omp_get_wtime();
    printf("Multiple interval Trapezoidal integration is %f\n", integral_mult);
    printf("Parallel computing with %d threads took %g time \n", thread_num, par_end_time-par_start_time);

    double ser_start_time = omp_get_wtime();


    for (int i = 0; i < num_points-1; i++)
    {
        integral_mult = integral_mult + ( (h/2.0) * (func_x(a + i*h) + func_x(a+(i+1)*h)) );
    }
    double ser_end_time = omp_get_wtime();
    printf("Serial computing took %g time \n", ser_end_time-ser_start_time);

    double speedup = (ser_end_time-ser_start_time)/(par_end_time-par_start_time);
    printf("Speedup for %d nodes computation is: %f\n", num_points, speedup);


    return 0;
}
