#include <stdio.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    double mu = 0.0;

    double x_max = 10;
    double x[100] = {0.0};
    int num_iters = sizeof(x)/sizeof(x[0]);
    double del_x = x_max/(num_iters-1);

    x[0] = 0.5;
    x[1] = 0.7;

    for (int i = 1; i < num_iters-1; i++)
    {
        x[i+1] = ( mu*(1-pow(x[i],2))*((x[i] - x[i-1])/del_x) - x[i] ) * (2*pow(del_x,2)) + 2*x[i] - x[i-1];
    }

    for (int i = 0; i < num_iters; i++)
    {
        printf("%f\n", x[i]);
    }

    return 0;
}
