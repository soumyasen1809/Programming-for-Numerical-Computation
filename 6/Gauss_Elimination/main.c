#include <stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

int main()
{
    int mat_size = 3;
    double A[3][3] = {1.0, 1.0, 1.0, 2.0, 1.0, 3.0, 3.0, 4.0, -2.0};
    double b[3] = {4.0, 7.0, 9.0};
    double A_aug[3][4] = {0,0,0,0,0,0,0,0,0,0,0,0};
    double x[3];

    // Define Augmented matrix
    #pragma omp parallel for shared (A, b, mat_size, A_aug)
    for (int i = 0; i <mat_size;i++)
    {
        for(int j = 0; j <mat_size;j++)
        {
            A_aug[i][j] = A[i][j];
        }
        A_aug[i][mat_size] = b[i];
    }

    // Developing the augmented matrix
    for (int col = 0; col < mat_size; col++)
    {
        #pragma omp parallel for shared (A_aug, mat_size)
        for (int row = col+1; row < mat_size; row++)
        {
            double alp = A_aug[row][col] / A_aug[col][col];

            for (int k = 0; k < mat_size+1; k++)
            {
                A_aug[row][k] = A_aug[row][k] - alp*A_aug[col][k];
            }

        }
    }

    // Printing the augmented matrix
    printf("The augmented matrix is:\n");
    for (int i = 0; i <mat_size;i++)
    {
        for(int j = 0; j <mat_size+1;j++)
        {
            printf("%f\t", A_aug[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Back Substitution
    // Solving for the last element of the solution vector
    x[mat_size-1] = A_aug[mat_size-1][mat_size]/A_aug[mat_size-1][mat_size-1];

    // Solving for the rest of the elements of the solution vector
    for (int row = mat_size-2; row>= 0; row--)
    {
        double sum = 0;
        #pragma omp parallel for shared(A_aug, x, mat_size) reduction(+:sum)
        for (int col = row; col < mat_size; col++)
        {
            sum = sum + A_aug[row][col]*x[col];
        }
        x[row] = (A_aug[row][mat_size] - sum)/A_aug[row][row];
    }

    // Printing the solution vector
    printf("The solution vector is:\n");
    for (int i = 0; i < mat_size; i++)
    {
        printf("%f\n", x[i]);
    }


    return 0;
}
