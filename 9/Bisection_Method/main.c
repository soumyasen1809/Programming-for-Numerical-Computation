#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

double func_x(double x)
{
    return 2 - x + log(x);
}

int main()
{
    double a = 2.0; // Initial solution guess lower limit
    double b = 8.0; // Initial solution guess upper limit
    double c;
    int n_iters = 1000;
    int count = 0;
    double tol = 0.01;  // Tolerance limit of the approximate solution to the exact solution

    #pragma omp parallel for reduction(+:count) lastprivate(c) firstprivate (a,b, n_iters, tol)
    for (int i = 0; i < n_iters; i++)
    {
        if (func_x(a) * func_x(b) < 0)  // Condition for a and b to be on the opposite side of the root
        {
            c = (a+b)/2.0;  // Midpoint
            if (func_x(c) * func_x(a) < 0)
            {
                b = c;  // b and c are on the same side of the root
                count = count+1;   // increment counter
            }
            else
            {
                a = c;  // a and c are on the same side of the root
                count = count + 1;   // increment counter
            }
        }

        if (func_x(c) == 0 || (b-a)/2.0 < tol)  // Conditions for accepting the solution
        {
            #pragma omp cancel for  // acts like a break command, but increases number of iterations significantly
        }
    }

    printf("Solution is %f after %d counts\n", c, count);

    return 0;
}
