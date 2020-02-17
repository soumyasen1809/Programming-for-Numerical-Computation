#include <stdio.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    double m = 1.0;
    double c = 10.0;
    double k = 10.0;

    double x_max = 10.0;
    double x[100] = {0.0};
    int num_iters = sizeof(x)/sizeof(x[0]);
    double del_x = x_max/(num_iters-1);

    x[0] = 10;
    x[1] = 9;
    x[num_iters - 1] = 0;

    for (int i = 1; i < num_iters-1; i++)
    {
        x[i+1] = -1.0*(2*del_x*del_x/m)*(c*((x[i] - x[i-1])/del_x) + k*x[i]) + 2*x[i] - x[i-1];
    }


    for (int i = 0; i < num_iters; i++)
    {
        printf("%f\n", x[i]);
    }

    return 0;
}
