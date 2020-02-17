#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    int mat_size = 4;
    double A[4][4] = {1.0, 2.0, 2.0, 1.0, 2.0, 2.0, 4.0, 2.0, 1.0, 3.0, 2.0, 5.0, 2.0, 6.0, 5.0, 8.0};
    double b[4] = {1.0, 0.0, 2.0, 4.0};
    double x_old = 0.0;
    double x[4] = {0.0, 0.0, 0.0, 0.0};
    double eps = 10.0;

    int num_threads;

    while (eps > 0.01)
    {
        for (int row = 0; row < mat_size; row++)
        {
            double sum = 0;
            #pragma omp parallel for reduction (+:sum) firstprivate (row, A)
            for (int col = 0; col < row-1; col++)
            {
                num_threads = omp_get_num_threads();
                if (col != row)
                {
                    sum = sum + A[row][col]*x[col];
                }
            }

            x[row] = (1/A[row][row]) * (b[row] - sum);
            eps = x[row] - x_old;
            x_old = x[row];
        }
    }

    printf("Gauss-Siedel Method solution using %d threads\n", num_threads);
    for (int i = 0; i < mat_size; i++)
    {
        printf("%f\n", x[i]);
    }

    return 0;
}
