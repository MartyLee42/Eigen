#define EPS 1E-15
#define EPS3 1E-15
#define COMP_EPS 1E-15
#define MAX 10000

#include <math.h>


double sign(double);

int N(double *a, double l,int n);
void triangle(double *,int);
double norm2(double *,int);
void solve(double *, double *,double, double, int,double);
double trace(double *, int);

double norm(double *, int);
double Trace(double *,int);
void rotate(double *, int, int, int, double,double);
double distToSolution(double *,int);
double square(double );
double Axb(double *, double *, double *,int);
