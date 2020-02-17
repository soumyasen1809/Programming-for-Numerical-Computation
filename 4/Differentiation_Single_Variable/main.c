#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

double func_x(double x)
{
    return 2 - x + log2(x);
}

int main()
{
    double h = 0.01;
    int num_points = 10;
    double fwd_x[num_points];
    double bwd_x[num_points];
    double cd_x[num_points];

    int num_threads;

    // Forward difference, Backward difference and Central difference
    double par_start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(h) shared(fwd_x, bwd_x, cd_x)
    for (int i = 0; i < num_points; i++)
    {
        num_threads = omp_get_num_threads();

        double a = i + 2;
        fwd_x[i] = (func_x(a+h) - func_x(a))/h;
        bwd_x[i] = (func_x(a) - func_x(a-h))/h;
        cd_x[i] = (func_x(a+h) - func_x(a-h))/(2*h);
    }
    double par_end_time = omp_get_wtime();

    printf("x =");
    printf("\t \t \t");
    printf("Forward difference");
    printf("\t");
    printf("Backward difference");
    printf("\t");
    printf("Central difference");
    printf("\n");
    for (int i = 0; i < num_points; i++)
    {
        double a = i+2;
        printf("%f", a);
        printf("\t \t ");
        printf("%f", fwd_x[i]);
        printf("\t \t ");
        printf("%f", bwd_x[i]);
        printf("\t \t ");
        printf("%f", cd_x[i]);
        printf("\n");
    }

    printf("\n");
    printf("Time taken by %d threads = %g \n \n", num_threads, par_end_time - par_start_time);


    // Serial code for comparison of time taken
    double ser_start_time = omp_get_wtime();
    #pragma omp master
    for (int i = 0; i < num_points; i++)
    {
        num_threads = omp_get_num_threads();

        double a = i + 2;
        fwd_x[i] = (func_x(a+h) - func_x(a))/h;
        bwd_x[i] = (func_x(a) - func_x(a-h))/h;
        cd_x[i] = (func_x(a+h) - func_x(a-h))/(2*h);
    }
    double ser_end_time = omp_get_wtime();

    printf("\n");
    printf("Time taken by %d threads = %g \n \n", num_threads, ser_end_time - ser_start_time);

    double speedup = (ser_end_time - ser_start_time)/(par_end_time - par_start_time);
    printf("Speedup is %f\n", speedup);

    return 0;
}
