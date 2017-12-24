#include"Sort.h"
#include<math.h>
#include<iostream>
using namespace std;

#define N 5

void GreedyKnapsack(int *pw[s_size][3],int*x,float m,int n) {

	for (int i = 0; i < s_size; ++i) {
		(*pw)[i][2] = (*pw)[i][0] / (*pw)[i][1];
	}

	for (int i = 1; i < s_size; ++i) {
		int j = i - 1;
		while (j >= 0 && pw[j][2] > pw[i][2]) {
			(*pw)[j + 1] = (*pw)[j];
			j--;
		}
		(*pw)[j+ 1] = (*pw)[i];
	}

	for (int i = 0; i < n; ++i)
		x[i] = 0;
	float u = m;	
	for (int i = s_size; i >=0; ++i) {
		if ((*pw)[i][1] > u)
			continue;
		x[i] = u/(*pw)[i][1];
		u -= (*pw)[i][1]*x[i];
	}	
}

int Binsearch(int *a, int i, int l, int x) {
	Insertionsort(a,s_size);
	if (l == i) {
		if(x==a[i])
			return i;
	    else
			return 0;	
	}
	else {
		int mid = i / 2;
		if (x == a[mid])
			return mid;
		else if (x < a[mid])
			return Binsearch(a, i, mid - 1, x);
		else
			return Binsearch(a, mid+1,l, x);
	}	
}

template<typename Type>
Type *mul(Type A[N][N], Type B[N][N]) {
	Type *C[N][N];
	memset(C, 0, N*N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < N; ++k)
				C[i][j] += A[i][k] * B[k][j];
		}
	}

	for (int j = 0; j < N; ++j) {
		for (int k = 0; k < N; ++k)
			if (abs(C[j][k]) < pow(10, -2))
				C[i][j] = 0;
	}
	return C;
}

void inverse_matrix(double A[], int n, double C[])
{
	int i, j, k, m = 2 * n;//m用来放增广矩阵
	double mik, temp;
	double **a = new double*[n];
	double **B = new double*[n];

	for (i = 0; i<n; i++)
	{
		a[i] = new double[2 * n];
		B[i] = new double[n];
	}

	for (i = 0; i<n; i++)//新建一个单位矩阵B
	{
		for (j = 0; j<n; j++)
		{
			if (i == j)
				B[i][j] = 1.0;
			else
				B[i][j] = 0.0;
		}
	}       

	int iii = 0;
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			a[i][j] = A[iii]; 
			iii++;
		}
	}

	for (i = 0; i<n; i++)
		for (j = n; j<m; j++)
			a[i][j] = B[i][j - n];  //得出增广矩阵  

	for (k = 1; k <= n - 1; k++)
	{
		for (i = k + 1; i <= n; i++)
		{
			mik = a[i - 1][k - 1] / a[k - 1][k - 1];
			for (j = k + 1; j <= m; j++)
			{
				a[i - 1][j - 1] -= mik*a[k - 1][j - 1];
			}
		}
	}        

	for (i = 1; i <= n; i++)
	{
		temp = a[i - 1][i - 1];
		for (j = 1; j <= m; j++)
		{
			a[i - 1][j - 1] /= temp;
		}
	}        

	for (k = n - 1; k >= 1; k--)
	{
		for (i = k; i >= 1; i--)
		{
			mik = a[i - 1][k];
			for (j = k + 1; j <= m; j++)
			{
				a[i - 1][j - 1] -= mik*a[k][j - 1];
			}
		}
	}         

	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			B[i][j] = a[i][j + n];  

	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			if (fabs(B[i][j])<0.0001)//同上一个函数矩阵乘法
				B[i][j] = 0.0;

	int jjj = 0;
	for (i = 0; i<n; i++) {
		for (j = 0; j<n; j++) {
			C[jjj] = B[i][j];
			jjj++;
		}
	}

}

