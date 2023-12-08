#include "matrix_solver.h"
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

double f_abs(double a)
{
    return (a > 0 ? a : -a);
}

//finding eigenvector X with given precision e
int solve(double *A, double *X, int n, int e)
{
    return 0;
}
