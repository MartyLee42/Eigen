#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "RW.h"
#include "solve.h"

#define MAX_LEN 100

#define EPS_SOLVE 1E-10

const int M = 10;

int  main()
{
	int n;
	time_t t;
	double t_solve;
	char file[MAX];
	double *a=NULL,*b=NULL,*x=NULL; 
	/*double tr=0.0,vect=0.0;*/
	int num;

	char c;	
	double ai,bi;

	ai=0.0;
	bi=0.0;

	printf("Interval\n>> ");

	scanf("%lf",&ai);
	scanf("%lf",&bi);

	printf("Formula/File (1/2) \n>> ");
	scanf("%s",&c);
	
	printf("%f %f\n",ai,bi);
	
	

	n=readEigen(&a,&b,c,file);
	
	
	if(n==-1)
	{
		printf("ERROR while reading\n");
		return -1;
	}	
	
	
	/*tr=Trace(a,n);
	vect=norm(a,n*n);*/

	t=clock();
		
	x = (double *)malloc(sizeof(double)*n);
	
	solve(a,x,ai,bi,n,EPS_SOLVE);

	t_solve=(double)((clock()-t))/CLOCKS_PER_SEC;

	num = N(a,bi,n);
	num -= N(a,ai,n);

	printf("Number of eigen values %d\n",num);

	printf("time solving: %f\n",t_solve);

	
	/*printf("trace difference: %e \n",fabs(tr-trace(x,n)));
	printf("norm difference: %e \n",fabs(vect-norm(x,n)));*/
	
	printf("Answer: \n");
	printLineEigen(x,n,10,num);
	
	return 0;	
}
