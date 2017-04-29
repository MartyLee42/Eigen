
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int read(double *, double *, int, int, FILE *);
int readGaussAfter(double *, double *,int ,int,char *);
int readEigen(double **,double **,char, char *);
int readGauss(double **, double **,int *, int*,char *);
int readMatrix(double *,int,FILE *);

int readMatrixAndRightSide(double *, double *, int,FILE *);
int fillMatrix(double *, int);
int fillRightSide(double *,int);
double f(int , int);
int printMatrix(double *,int,int);
int printLine(double *, int,int);
int printLineEigen(double *, int,int,int);

#define EPS2 1E-10
#define MAX_LEN 100
