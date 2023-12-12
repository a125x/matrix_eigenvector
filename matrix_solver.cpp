#include "matrix_solver.h"
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

double norm1(double *vec, int n) 
{
    double res = 0;

    for(int i = 0; i < n; i++) 
        res += f_abs(vec[i]);
    
    return res;
}

double f_abs(double a)
{
    return (a > 0 ? a : -a);
}

void mult(double *A, double *X, int n)
{
    double temp = 0;

    for (int i = 0; i < n; i++)
    {
        temp = 0;

        for (int j = 0; j < n; j++)
            temp += A[i*n+j] * X[j];       
        
        X[i] = temp;
    }
}

int del(double *X, int d, int n)
{
    if (d == 0)
        return 1;

    for (int i = 0; i < n; i++)
        X[i] = X[i] / d;

    return 0;
}

//finding eigenvector X with given precision e
int solve(double *A, double *X, int n, int e)
{
    double error = 0;
    double *prev_X = X;

    do
    {   
        prev_X = X;
        for (int i = 0; i < 10; i++)
        {
            mult(A, X, n);
            if (del(X, norm1(X, n), n))
                return 1;
        }
    
        error = f_abs(norm1(X, n) - norm1(prev_X, n));
    }
    while (error > e);

    return 0;
}
