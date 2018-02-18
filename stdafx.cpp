// 三次样条曲线拟合.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<iostream.h>
#include<iomanip.h>
#define N 50
int main(int argc, char* argv[])
{
	int i,j,k,n;
	double X[N],Y[N],h[N],u[N],d[N],m[N],a[N],b[N],A[N][N],S[N][4];
	void line_equations(double A[][50],double X[],int n=1);
	                

	
	for(i=0;i<=n-1;i++){
		cout<<"X["<<i<<"]=";
			cin>>X[i];
		cout<<"Y["<<i<<"]=";
			cin>>Y[i];
	};

	for(i=0;i<=n-1;i++){
		cout<<"+m["<<i<<"]*";
		cin>>a[i];
	};
	cout<<"=";
	cin>>u[0];
	for(i=0;i<=n-1;i++){
		cout<<"+m["<<i<<"]*";
		cin>>b[i];
	};
	cout<<"=";
	cin>>u[n-1];

	for(k=0;k<=n-2;k++){
		h[k]=X[k+1]-X[k];
		d[k]=(Y[k+1]-Y[k])/(X[k+1]-X[k]);
	};
	if(n>=3){
		for(k=1;k<=n-2;k++){
		    u[k]=6*(d[k]-d[k-1]);
		};
		for(i=1;i<=n-2;i++){
	    	for(j=0;j<=n;j++){
			A[i][j]=0;
			}
		}
	}
//增广矩阵
    for(i=0;i<=n-1;i++){
	    	A[0][i]=a[i];
		    A[n-1][i]=b[i];
		    A[i][n]=u[i];
	}
	if(n>=3){
		for(i=1;i<=n-2;i++){
			A[i][i-1]=h[i-1];
			A[i][i]=2*(h[i-1]+h[i]);
			A[i][i+1]=h[i];
		}
	};
	
	line_equations(A,m,n);

	for(k=0;k<=n-2;k++){
		S[k][0]=m[k]*X[k+1]*X[k+1]*X[k+1]/(6*h[k])+(Y[k]/h[k]-m[k]*h[k]/6)*X[k+1];
		S[k][0]-=m[k+1]/(6*h[k])*X[k]*X[k]*X[k]+(Y[k+1]/h[k]-m[k+1]*h[k]/6)*X[k];
		S[k][1]=m[k+1]*X[k]*X[k]/(2*h[k])+(Y[k+1]/h[k]-m[k+1]*h[k]/6);
		S[k][1]-=m[k]*X[k+1]*X[k+1]/(2*h[k])+(Y[k]/h[k]-m[k]*h[k]/6);
		S[k][2]=m[k]*X[k+1]/(2*h[k])-m[k+1]*X[k]/(2*h[k]);
		S[k][3]=(m[k+1]-m[k])/(6*h[k]);
	}

	
	return 0;
};

void line_equations(double A[][50],double X[],int n=1){
	int i,j,k,s=0;
	double temp;
	if(n==1 && A[0][0]!=0){
		X[0]=A[0][1]/A[0][0];
		return ;
	}

}