// https://www.cfd-online.com/Wiki/Tridiagonal_matrix_algorithm_-_TDMA_(Thomas_algorithm)
// Used TDMA algorithm from this website

#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    int mat_size = 5;
    double A[5][5] = {1,0,0,0,0,1,-3,1,0,0,0,1,-3,1,0,0,0,1,-3,1,0,0,0,1,-3};
    double b[5] = {100,-1,-1,-1,25};
    double x[5];

    A[0][1] = A[0][1]/A[0][0];
    b[0] = b[0]/A[0][0];

    for (int i = 1; i < mat_size; i++)
    {
        double m = A[i][i-1]/A[i-1][i-1];
        A[i][i] = A[i][i] - m*A[i-1][i];
        b[i] = b[i] - m*b[i-1];
    }

    x[mat_size-1] = b[mat_size-1]/A[mat_size-1][mat_size-1];
    #pragma omp parallel for firstprivate(A,b,mat_size) shared (x)
    for (int i = mat_size-2; i >= 0; i--)
    {
        x[i] = (b[i] - A[i][i+1]*x[i+1]) / A[i][i];
    }

    for (int i = 0; i < mat_size; i++)
    {
        printf("%f\n", x[i]);
    }

    return 0;
}
