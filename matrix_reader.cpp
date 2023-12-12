#include <stdio.h>
#include "matrix_reader.h"
#include "matrix_solver.h"

//printing any matrix
void print_mat(double *A, int n, int m, int p)
{
    for (int i = 0; i < n && i < p; i++)
    {
        for (int j = 0; j < m && j < p; j++)
            printf("%10.3e ", A[i * m + j]);

        printf("\n");
    }
}

//function to create element of matrix 
double f(int i, int j, int n, int mode)
{
    i++;
    j++;

    switch (mode)
    {
      case 1: 
          return n - (i > j ? i : j) + 1;
      case 2: 
          return i == j ? 2 : f_abs(i - j) == 1 ? -1 : 0;
      case 3: 
          return i == (j < n) ? 1 : j == n ? i : i == n ? j : 0;
      case 4:
          return 1. / (i + j - 1);
      default:
          return 0.;
    }

    return 0.;
}

//initializing matrix A
void inint_A_form(double *A, int n, int k)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            A[i * n + j] = f(i, j, n, k);
}

//reading matrix from a file
int inint_A_file(double *A, int n, char *file)
{
    FILE *in = fopen(file, "r");

    if (!in)
      return 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fscanf(in, "%lf", A + i * n + j) != 1)
            {
                fclose(in);
                return 2;
            }

    fclose (in);
    return 0;
}

