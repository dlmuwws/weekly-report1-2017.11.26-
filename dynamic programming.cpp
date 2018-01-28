//0-1背包问题动态规划法

#include<iostream>
using namespace std;

double knapsack_dynamic(int n,int*ww,double*pp,int c,int*best_x);

int main()
{
	int n = 4; int c= 45;
	int*ww = new int[n + 1];
	ww[1] = 20; ww[2] = 15; ww[3] = 10; ww[4] = 10;
	double *pp = new double[n + 1];
	pp[1] = 30; pp[2] = 35; pp[3] = 25; pp[4] = 20;
	int*best_x = new int[n + 1];
	double OptSoln = knapsack_dynamic(n,ww,pp,c,best_x);
	cout << "opt profit:" << OptSoln << endl;
	cout << "finish!!!" << endl;
	system("pause");
	return 0;
}

double knapsack_dynamic(int n, int*ww, double*pp, int c, int*best_x)
{
	double **opt;
	opt = new double*[n + 1];
	for (int i=0;i<=n;i++)
	{
		opt[i] = new double[c + 1];
	}
	for (int i=0;i<=n;i++)
	{
		opt[i][0] = 0;
	}
	for (int i=0;i<=n;i++)
	{
		best_x[i] = 0;
	}
	for (int i=0;i<=c;i++)
	{
		opt[0][i] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j= 1; j<= c; j++)
		{
			opt[i][j] = opt[i - 1][j];
			if (j>=ww[i]&&((opt[i-1][j-ww[i]])+pp[i])>opt[i - 1][j])
			{
				opt[i][j] = opt[i - 1][j - ww[i]] + pp[i];
			}
		}
	 }

	int j = c;
	for (int i=n;i>0;i--)
	{
		if (opt[i][j]>opt[i-1][j])
		{
			best_x[i] = 1;
			j -= ww[i];
		}
	}
	double opt_profits = opt [n][c];
	
	cout << "result:" << endl;
	cout << "opt table:" << endl;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= c; j++)
		{
			cout << opt[i][j] << "  ";
		}
		cout << endl;
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "第" << i << "件物品放" << best_x[i] << "个" << endl;
	}
	return opt_profits;
}









// 动态规划求解资源分配问题
#include<iostream>
using namespace std;

double resource_assign(int m, int p, double**G);
template<class type>
int main()
{
	type r; //资源总数
	int m=3;  //工程总数
	int p=8;  //将资源等分成f份，分给m个工程
	double**G = new double[m + 1][p + 1];   //G[i][j]表示分给工程i的资源份额为j份时的利润
	G[1][0] = 0; G[1][1] = 4; G[1][2] = 26; G[1][3] = 40; G[1][4] = 45; G[1][5] =50; G[1][6] = 51; G[1][7] = 52; G[1][8] = 53;
	G[2][0] = 0; G[2][1] = 5; G[2][2] = 15; G[2][3] = 40; G[2][4] = 60; G[2][5] = 70; G[2][6] = 73; G[2][7] = 74; G[2][8] = 75;
	G[3][0] = 0; G[3][1] = 5; G[3][2] = 15; G[3][3] = 40; G[3][4] = 80; G[3][5] = 90; G[3][6] = 95; G[1][7] = 98; G[1][8] = 100;
	double total_p = resource_assign(m,p,G);
	system("pause");
	return 0;
}

double resource_assign(int m,int p,double**G)
{
	double*g = new double[m]; //前i项工程的最优分配方案下的利润
	int*q = new int[m];  //前i项工程的最优分配方案下对应的分配份额数
	double opt_g;
	int opt_x;
	int k;
	int*opt_q = new int[m];  //回溯得到的各工程分配的资源份额
	int**d; double**f;
	d = new int*[m + 1]; //第i项工程的资源分配份额数
	f = new double*[m + 1];//给前i项工程分配一定资源时对应的最大利润
	for (int i=0;i<=m;i++)
	{
		d[i] = new int[p + 1];
		f[i] = new double[p + 1];
	}

	//第一个工程的资源分配表
	for (int i=0;i<=p;i++)
	{
		f[1][i] = G[1][i];  d[1][i] = i;
	}

	//第i个工程的资源分配表(i>=2)

	for (int i=2;i<=m;i++)
	{
		f[i][0] = 0; d[i][0] = 0;
		for (int j=0;j<=p;j++)
		{
			f[i][j] = f[i][0]; d[i][j] = d[i][0];
			for (int z=0;z<=j;z++)
			{
				if (f[i][j]<G[i][z]+f[i-1][j-z])
				{
					f[i][j] = G[i][z] + f[i - 1][j - z];
					d[i][j] = z;
				}
			}
		}
	}
	// 求前i个工程的各自的最大分配利润g[i]和以及对应的分配份额q[i]
	for (int i=0;i<m;i++)
	{
		g[i] = f[i+1][0];
		for (int j=1;j<=p;j++)
		{
			if (g[i]<f[i][j])
			{
				g[i] = f[i][j];
				q[i] = j;
			}
		}
	}
	//求全局最优分配利润及分配份额opt_g 和opt_x
	opt_g = g[0]; opt_x = q[0];  k = 0;
	for (int i=1;i<m;i++)
	{
		if (opt_g<g[i])
		{
			opt_g = g[i]; opt_x = q[i]; k = i;
		}
	}

	//回溯求各个工程的最优分配份额opt_q[i]
	if (k<m)   //k之后的工程没有分配资源
	{
		for (int i=k+1;i<=m;i++)
		{
			opt_q[i] = 0;
		}
	}
	else
	{
		for (int i=k;i>=0;i--)
		{
			opt_q[i] = d[i][opt_x];
			opt_x -= opt_q[i];
		}
	}
	cout << "get_opt_soln:" << endl;
	for (int i=0;i<=k;i++)
	{
		cout << "第" << i + 1 << "项工程分配的资源份额为:" << opt_q[i] << endl;
	}
	cout << "opt_profits: " << opt_g << endl;
	return opt_g;
}
