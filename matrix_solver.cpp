#include "matrix_solver.h"
#include <vector>
#include <iostream>
#include "matrix_reader.h"
using namespace std;

double norm1(double *vec, int n) 
{
    double res = 0;

    for(int i = 0; i < n; i++) 
        res += f_abs(vec[i]) * f_abs(vec[i]);
    
    return sqrt(res);
}

double f_abs(double a)
{
    return (a > 0 ? a : -a);
}

void mult(double *A, double *X, int n)
{
    double temp = 0.;
    double *temp_X = new double[n];

    for (int i = 0; i < n; i++)
            temp_X[i] = X[i];

    for (int i = 0; i < n; i++)
    {
        temp = 0.;

        for (int j = 0; j < n; j++)
            temp += A[i*n+j] * temp_X[j];
        
        X[i] = temp;
    }

    delete[] temp_X;
}

int del(double *X, double d, int n)
{
    if (f_abs(d) < EPS)
        return 1;

    for (int i = 0; i < n; i++)
        X[i] = X[i] / d;

    return 0;
}

//finding eigenvector X with given precision e
int findEigenvector(double *A, double *X, int n, double e)
{
    double error = 0;
    double *prev_X = new double[n];
        
    do
    {
        for (int i = 0; i < n; i++)
            prev_X[i] = X[i];

        for (int i = 0; i < 10; i++)
            mult(A, X, n);
        
        if (del(X, norm1(X, n), n))
            return 1;
        
        error = f_abs(findEigenvalue(A, X, n) - findEigenvalue(A, prev_X, n));
    }
    while (error > e);
    
    return 0;
}

double findEigenvalue(double *A, double *X, int n)
{
    double *temp_A = A;
    double *temp_X = new double[n];
    for (int i = 0; i < n; i++)
            temp_X[i] = X[i];

    mult(temp_A, temp_X, n);
    double res = norm1(temp_X, n) / norm1(X, n);
    
    delete[] temp_X;
    delete[] temp_A;

    return res;
}
