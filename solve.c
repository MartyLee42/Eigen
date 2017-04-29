#include "solve.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSMASH 1E-15

double max(double a, double b)
{
	if(a>b) return a;
	return b;
}

void solve(double *mat, double *x,double ai,double bi,int n,double eps)
{
	
	double * rec1,* rec2;
	int iter;
	int num=0;
	int i;
	int aa,bb;
	double a,b;

	triangle(mat,n);

	rec1=(double *)malloc(4*sizeof(double)*n);
	rec2=(double *)malloc(4*sizeof(double)*n);
	
	iter=0;
	rec1[0]=ai;
	rec2[0]=bi;
	num=1;

	while(num!=0)
	{
		a=rec1[iter];
		b=rec2[iter];
		
		
		aa=N(mat,a,n);
		bb=N(mat,b,n);
		
		
		
		if(bb-aa==1)
		{
			x[aa]=a;
		}

		if(b-a>eps && bb-aa>0)
		{
			
			rec1[(iter+num)%(4*n)]=a;
			rec2[(iter+num)%(4*n)]=(a+b)/2;
			rec1[(iter+num+1)%(4*n)]=(a+b)/2;
			rec2[(iter+num+1)%(4*n)]=b;
			num+=2;
		}
		else
		{
			if(bb-aa>0)
			{
				
				for(i=aa; i<bb; i++)
				{
					x[i]=rec1[iter];
				}
			}
			else
			{
				
			}
		}
		iter++;
		iter%=(4*n);
		num--;

	}	
}


int N(double *mat, double l,int n)
{
	int i;

	double *b,*a;
	double m;
	double x,y;
	double aa,bb;
	double gamma,u,v;
	
	b = (double *)(malloc(sizeof(double)*n));
	a = (double *)(malloc(sizeof(double)*n));

	
	m=-1.0;

	for(i=0; i<n-1; i++)
	{
		b[i]=mat[(i+1)*n+i];
		if(fabs(b[i])>=m)
		{
			m=fabs(b[i]);
		}
	}
	for(i=0; i<n; i++)
	{
		a[i]=mat[i*(n+1)]-l;
		if(fabs(a[i])>=m)
		{
			m=fabs(a[i]);
		}
	}

	for(i=0; i<n-1; i++)
	{
		b[i]/=4*m;
		if(fabs(b[i])<EPSMASH)
		{
			b[i]=0;
		}
	}
	for(i=0; i<n; i++)
	{
		a[i]/=4*m;
	}


	m=0;
	
	x=a[0];
	y=1.0;

	if(sign(x*y)<=0) m=1;


	for(i=1; i<n; i++)
	{
		aa=a[i];
		bb=b[i-1];
		gamma=(1.0/EPSMASH)/(max(fabs(x),fabs(bb*bb*y)));
		u=gamma*(aa*x-bb*bb*y);
		v=gamma*x;

		
		if(sign(u*x)<0) m++;
		x=u;
		y=v;
	}	

	return m;
	
}

double norm2(double *a, int n)
{
	int i,j;
	double ans=0.0;
	double m=0.0;	

	for(i=0; i<n; i++)
	{
		m=0.0;
		for(j=0; j<n; j++)
		{
			m+=fabs(a[i*n+j]);
		}
		ans=max(m,ans);
	}

	return ans;
}

void triangle(double *a,int n)
{
	double *cos,*sin;
	double sum=0.0;
	double x,y;
	int i,j,k;

	cos=(double *)malloc(sizeof(double)*n);
	sin=(double *)malloc(sizeof(double)*n);

	for(i=0; i<n-1; i++)
	{
		sum=a[(i+1)*n+i];
		for(j=i+2; j<n; j++)
		{
			x=sum;
			y=a[j*n+i];
			if(x*x+y*y<EPSMASH)
			{
				cos[j]=1.0;
				sin[j]=0.0;
			}
			else
			{
				cos[j]=x/sqrt(x*x+y*y);
				sin[j]=-y/sqrt(x*x+y*y);
			}
			sum=sqrt(x*x+y*y);
		}

		for(j=i+2; j<n; j++)
		{
			for(k=0; k<n; k++)
			{
				x=a[(i+1)*n+k];
				y=a[j*n+k];
				a[(i+1)*n+k]=cos[j]*x-sin[j]*y;
				a[j*n+k]=sin[j]*x+cos[j]*y;	
			}

			for(k=0; k<n; k++)
			{
				x=a[(i+1)+k*n];
				y=a[j+k*n];
				a[(i+1)+k*n]=cos[j]*x-sin[j]*y;
				a[j+k*n]=sin[j]*x+cos[j]*y;	
			}	
		}
		
	}
}


double norm(double *a, int n)
{
	int i;
	double ans = 0.0;
	for( i=0; i<n; i++)
	{
		ans+=square(a[i]);
	}
	ans=sqrt(ans);
	return ans;
}




double distToSolution(double *x, int n)
{
	int i;
	double ans=0.0;
	for(i=0; i<n; i++)
	{
		if(i%2==0)
		{
			ans+=square(x[i]-1.0);
		}
		else
		{
			ans+=square(x[i]);
		}
	}
	ans=sqrt(ans);
	return ans;
}

double Axb(double *a, double *x, double *b, int n)
{
	int i,j;
	double ans=0.0;
	for(i=0; i<n; i++)
	{
		double xi=0.0;
		for(j=0; j<n; j++)
		{
			xi+=x[j]*a[i*n+j];
		}
		ans+=square(xi-b[i]);
	}
	return sqrt(ans);
}

double Trace(double *a, int n)
{
	double ans=0.0;
	int i;	

	for(i=0; i<n; i++)
	{
		ans+=a[i*(n+1)];
	}	
	
	return ans;
}

double square(double x)
{
	return x*x;
}


double sign(double a)
{
	if(a>0) return 1;
	if(a<0) return -1;
	return 0.0;
}

void printM(double *a, int n)
{
	int i,j;

	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			printf("%f ",*(a+i*n+j));
		}
		printf("\n");
	}
	

}

double trace(double * x, int n)
{
	int i;
	double ans;
	ans=0.0;
	for(i=0; i<n; i++)
	{
		ans+=x[i];
	}
	return ans;
}
