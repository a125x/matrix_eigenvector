#include <stdio.h>
#include <time.h>
#include <math.h>
#include <chrono>
#include "matrix_solver.h"
#include "matrix_reader.h"

//sum of the main diagonal - sum of the eigenvector
double res_ctr1(double *A, double *X, int n)
{
    double trace_sum = 0;
    double eigen_sum = 0;

    for (int i = 0; i < n; i++)
    {
        trace_sum += A[i*n+i];
        eigen_sum += X[i];
    }

    return f_abs(trace_sum - eigen_sum);
}

double res_ctr2(double *A, double *X, int n)
{
    double eigen_sum = 0;

    for (int i = 0; i < n; i++)
    {
        eigen_sum += X[i]*X[i];
    }

    return f_abs(n*n - eigen_sum); 
}

int main(int argc, char *argv[])
{
    //A is a matrix, X is an eigenvector 
    double *A = nullptr, *X = nullptr;

    //n is matrix dimentions, m is amount of outputs of matrix,
    //e is accuracy of the solution and k is an input formula number
    int n = 0, k = 0, m = 0;
    float e = 0.0;

    //checking if input data are correct
    if (!((argc == 5 || argc == 6) 
        && (sscanf(argv[1], "%d", &n) == 1) && (n > 0)
        && (sscanf(argv[2], "%d", &m) == 1)
        && (sscanf(argv[3], "%e", &e) == 1)
        && (sscanf(argv[4], "%d", &k) == 1)
        && ((k == 0 && argc == 6) || (k > 0 && k <= 4 && argc == 5))))
    {
        printf ("Usage: %s n m e k [file]\n", argv[0]);
        return 0;
    }

    //creating matrix a and eigenvector x
    A = new double[n * n];
    X = new double[n];
    for (int i = 0; i < n; ++i)
        X[i] = 1;

    //memory allocation error
    if (!A || !X)
    {
        if (A) delete [] A;
        if (X) delete [] X;
        printf("ERROR: Memory\n");
      
        return 0;
    }
    
    int res = 0;
    char *file = nullptr;
    
    //obtaining matrix from a file
    if (k)
        inint_A_form(A, n, k);
    else
    {
        file = argv[4];
        res = inint_A_file(A, n, file);
        if (res)
        {
            delete [] A;
            delete [] X;
            printf("ERROR: Wrong file\n");
            return 0;
        }
    }

    //printing matrix a
    for (int i = 0; i < m; i++)
        printf("-----------");

    printf("\nA = \n");
    print_mat(A, n, n, m);
    
    //solving matrix
    auto start = std::chrono::high_resolution_clock::now();
    res = findEigenvector(A, X, n, e);
    auto end = std::chrono::high_resolution_clock::now();
    auto t1 = std::chrono::duration<double, std::milli>(end - start).count();
    
    double eigenvalue = findEigenvalue(A, X, n);

    //printing error if we can't find the solution
    if (res)
    {
        delete [] A;
        delete [] X;
        printf ("Impossible to find an eigenvector\n");

        return 0;
    }

    //printing eigenvector x
    for (int i = 0; i < m; i++)
        printf("-----------");

    printf("\nX = \n");
    print_mat(X, 1, n, m);
  
    //initializing matrix again to find the error
    if (k)
        inint_A_form (A, n, k);
    else
    {
        file = argv[4];
        res = inint_A_file(A, n, file);
        if (res)
        {
            delete [] A;
            delete [] X;
            printf("ERROR: Wrong file\n");
            return 0;
        }
    }    
   
    //printing all the necessary stuff
    for (int i = 0; i < m; i++)
        printf("-----------");
    printf ("\neigenvalue = %e, \ntime = %.5f; \nn = %d, m = %d, e = %e, k = %d.\n", eigenvalue, t1, n, m, e, k);

    //cleaning up the memory
    delete [] A;
    delete [] X;

    return 0;
}
