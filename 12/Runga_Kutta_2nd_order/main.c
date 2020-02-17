#include <stdio.h>
#include<math.h>
#include <stdlib.h>

double func_y(double t, double y)
{
    return -2 * t * y;
}

void Heuns()
{
    double t = 0.0;
    double t_new;

    double y[100] = {0.0};
    y[0] = 1.0;

    int num_iters = sizeof(y) / sizeof(y[0]);   // C language - find length of a vector
    double h = 0.01;
    double k1, k2;  // Heuns method w1 and w2 weights are 0.5

    for (int i = 0; i < num_iters-1; i++)
    {
        k1 = func_y(t,y[i]);
        k2 = func_y(t+h, y[i] + h*k1);
        y[i+1] = y[i] + h*(k1+k2)/2.0;  // Heuns method | k1 = f(t,y) and k2 = f(t+h, y+h*k1)
        t_new = t + h;
        t = t_new;
    }

    printf("Heuns method solution vector is\n");
    for (int i = 0; i < num_iters; i++)
    {
        printf("%f\n", y[i]);
    }

}

void Midpoint()
{
    double t = 0.0;
    double t_new;

    double y[100] = {0.0};
    y[0] = 1.0;

    int num_iters = sizeof(y) / sizeof(y[0]);   // C language - find length of a vector
    double h = 0.01;
    double k1, k2;  // Midpoint method w1 and w2 weights are 0 and 1 resp.

    for (int i = 0; i < num_iters-1; i++)
    {
        k1 = func_y(t,y[i]);
        k2 = func_y(t+(h/2.0), y[i] + (h*k1)/2.0);
        y[i+1] = y[i] + h*k2;  // Midpoint method | k1 = f(t,y) and k2 = f(t+h/2, y+(h*k1)/2)
        t_new = t + h;
        t = t_new;
    }

    printf("Midpoint method solution vector is\n");
    for (int i = 0; i < num_iters; i++)
    {
        printf("%f\n", y[i]);
    }

}



int main()
{
    Heuns();
    Midpoint();

    return 0;
}
