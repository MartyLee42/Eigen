#include "RW.h"

int min(int a, int b)
{
	if(a<b) return a;
	return b;
}

int readGaussAfter(double *a, double *b,int n,int c,char *f)
{
	FILE *file=NULL;

	if(c==2)
	{
		file = fopen(f,"r");
		fscanf(file,"%d",&n);

		if(file==NULL) return -1;	

		read(a,b,n,0,file);		
		fclose(file);
	}

	if(c==1)
	{

		read(a,b,n,3,NULL);
	}
	
	return n;
}
/*
int read(double *a,double *b, int n, int c, char *file)
{
	if(c==2)
	{	
		int nn;
		FILE *f;
		f=fopen(file,"r");
		if(f==NULL) return -1;

		if(fscanf(f,"%d",&nn)!=1) return -1;	
		
		if(read(a,b,n,0,f)!=0) return -1;
		fclose(f);
	}
	if(c==1)
	{
		if(read(a,b,n,3,NULL)!=0) return -1;
	}
	return 0;
}

int read(double *&a,double *&b)
{
	char c;
	char file[MAX_LEN];

	cout<<"Formula/File (1/2) \n>> ";
	cin>>c;

	if(c=='2')
	{
		
		cin>>file;
	}

	return readGauss(a,b,c,file);
	
}

int read(double *a, double *b, int n,const char * file,char fl)
{
	if(fl=='2')
	{	
		int nn;
		FILE *f;
		f=fopen(file,"r");
		if(f==NULL) return -1;

		if(fscanf(f,"%d",&nn)!=1) return -1;	
		
		if(read(a,b,n,0,f)!=0) return -1;
		fclose(f);
	}
	if(fl=='1')
	{
		if(read(a,b,n,3,NULL)!=0) return -1;
	}
	return 0;
}
*/
int readEigen(double **a,double **b,char c, char *file)
{
	int n;
	FILE *f;
	if(c=='1')
	{
		printf("Matrix size: \n>> ");
		scanf("%d",&n);

		if(n<=0) return -1;

		*a = (double *)malloc(sizeof(double)*n*n);
		*b = (double *)malloc(sizeof(double)*n);
		if(read(*a,*b,n,4,NULL)!=0) return -1;

	}
	if(c=='2')
	{
		printf("File name\n>> ");
		scanf("%s",file);
		
		f=fopen(file,"r");
		if(f==NULL) return -1;

		if(fscanf(f,"%d",&n)!=1) return -1;
	
		if(n<=0) return -1;	
		
		*a = (double *)malloc(sizeof(double)*n*n);
		*b = (double *)malloc(sizeof(double)*n);
		
		if(read(*a,*b,n,1,f)!=0) return -1;
		fclose(f);
	}
	return n;

}

int readGauss(double **a, double **b, int *n, int *c, char *file )
{
	FILE *f;
	if(*c==1)
	{
		printf("Matrix size: \n>> ");
		scanf("%d",n);

		if(*n<=0) return -1;

		*a = (double *)malloc(sizeof(double)*(*n)*(*n));
		*b = (double *)malloc(sizeof(double)*(*n));
		
		if(read(*a,*b,*n,3,NULL)!=0) return -1;

	}
	if(*c==2)
	{
		printf("file name: \n>> ");
		scanf("%s",file);
		f=fopen(file,"r");
		if(f==NULL) return -1;

		if(fscanf(f,"%d",n)!=1) return -1;	

		if(*n<=0) return -1;
		
		*a = (double *)malloc(sizeof(double)*(*n)*(*n));
		*b = (double *)malloc(sizeof(double)*(*n));
		
		if(read(*a,*b,*n,0,f)!=0) return -1;
		fclose(f);
	}
	return *n;
}

int read(double *a, double *b, int n, int f,FILE *file)
{
	
	if(f==0) return readMatrixAndRightSide(a,b,n,file);
	if(f==1) return readMatrix(a,n,file);
	if(f==3) return min(fillMatrix(a,n),fillRightSide(b,n));
	if(f==4) return fillMatrix(a,n);
	
	return -1;
}


int readMatrix(double *a,int n,FILE *f)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(fscanf(f,"%lf",(a + i*n+j))!=1)
			{
				return -1;
			}
		}
	}

	return 0;
}

int readMatrixAndRightSide(double *a, double *b, int n,FILE *f)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(fscanf(f,"%lf",(a+i*n+j))!=1) return -1;
		}
		if(fscanf(f,"%lf",b+i)!=1) return -1;
	}

	return 0;
}


int fillMatrix(double *a, int n)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{	
			*(a+i*n+j)=f(i,j);
		}	
	}
	return 0;
}

int fillRightSide(double *b, int n)
{
	int i,j;
	for(i=0; i<n; i++)
	{
		*(b+i)=0.0;
		for(j=0 ; j<n; j++)
		{
			if(j%2==0)
			*(b+i)+=f(i,j);
		}
	}	
	return 0;
}

double f(int i, int j)
{
	return 1/((double)(i)+(double)(j)+1.0);
}	

int printMatrix(double *a,int n,int m /*=-1*/)
{
	int i,j;

	if(m==-1) m=n;
	for(i=0; i<min(n,m); i++)
	{
		for(j=0; j<min(n,m); j++)
		{
			if(fabs(a[i*n+j])<EPS2) printf("0 ");
			else
			printf("%f ",*(a+i*n+j));
		}
		printf("\n");
	}
	return 0;
}

int printLine(double *a , int n,int m /*=-1*/)
{
	int i;
	if(m==-1) m=n;
	for(i=0; i<min(n,m); i++)
	{
		if(fabs(a[i])<EPS2) printf("0 ");
			else
		printf("%.10f ",*(a+i));
	}
	printf("\n");
	return 0;
}

int printLineEigen(double *a , int n,int m,int num)
{
	int i;
	if(m==-1) m=n;
	for(i=n-num; i<min(n,num+m); i++)
	{
		printf("%.10f ",*(a+i));
	}
	if(num==0) printf("No eigen Values");
	printf("\n");
	return 0;
}
