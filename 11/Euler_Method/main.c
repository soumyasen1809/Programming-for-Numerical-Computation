#include <stdio.h>
#include<math.h>
#include <stdlib.h>

double func_y(double t, double y)
{
    return -2 * t * y;
}

int main()
{
    double t = 0.0;
    double t_new;

    double y[100] = {0.0};
    y[0] = 1.0;

    int num_iters = sizeof(y) / sizeof(y[0]);   // C language - find length of a vector
    double h = 0.01;

    for (int i = 0; i < num_iters-1; i++)
    {
        y[i+1] = y[i] + h*func_y(t , y[i]);
        t_new = t + h;
        t = t_new;
    }

    printf("Solution vector is\n");
    for (int i = 0; i < num_iters; i++)
    {
        printf("%f\n", y[i]);
    }

    return 0;
}
