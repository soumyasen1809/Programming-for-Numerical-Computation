#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double y[5] = {3.0, 9.0, 16.0, 25.0, 40.0};
    int len_arr = sizeof(x)/sizeof(x[0]);
    double x_sum = 0;
    double y_sum = 0;
    double a, b;

    #pragma omp parallel for reduction(+:x_sum, y_sum) firstprivate(x,y)
    for (int i = 0; i < len_arr; i++)
    {
        x_sum = x_sum + x[i];
        y_sum = y_sum + y[i];
    }
    double x_avg = x_sum/len_arr;
    double y_avg = y_sum/len_arr;

    double temp1 = 0;
    double temp2 = 0;
    #pragma omp parallel for reduction(+:temp1, temp2) firstprivate(x_avg, y_avg, x, y)
    for (int i = 0; i < len_arr; i++)
    {
        temp1 = temp1 + (x[i] - x_avg)*(y[i] - y_avg);
        temp2 = temp2 + (x[i] - x_avg)*(x[i] - x_avg);
    }
    a = temp1/temp2;
    b = y_avg - a*x_avg;

    printf("The equation of the regression line is y = %f x + %f\n", a,b);

    return 0;
}
