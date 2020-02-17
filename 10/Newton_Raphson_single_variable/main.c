#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

double func_x(double x)
{
    return 2 - x + log2(x);
}

double diff_x(double x)
{
    double h = 1.0e-2;
    return (func_x(x+h) - func_x(x-h)) / (2.0*h);   // Numerical differentiation
}

int main()
{
    double x_new;
    double x = 1.5;
    int n_iters = 100;   // Number of iterations
    int counter = 0;
    double tol = 0.001; // Tolerance limit

    #pragma omp parallel for reduction(+:counter) lastprivate(x_new) firstprivate(x, n_iters, tol)
    for (int i = 0; i < n_iters; i++)
    {
        x_new = x - (func_x(x) / diff_x(x));

        if (fabs(x_new - x) < tol)
        {
            #pragma omp cancel for  // Stop iteration when tolerance reached - number of iterations grow significantly
        }

        x = x_new;  // Substitute old value with newer one for next iteration
        counter = counter+1;    // Number of iterations counter
    }

    printf("Solution is %f after %d iterations\n", x_new, counter);
    return 0;
}
