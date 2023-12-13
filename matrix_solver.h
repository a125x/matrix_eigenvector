#ifndef MATRIX_SOLVER_H_
#define MATRIX_SOLVER_H_

//#define EPS 1e-14
#define EPS 1e-14

double f_abs(double a);

//solving matrix a with values b and writing results to x
int findEigenvector(double *A, double *X, int n, double e);

double findEigenvalue(double *A, double *X, int n);

#endif
