#include"branch and bound.h"
#include<iostream>
#include<algorithm>
using namespace std;


bool soln(int*s, int i, int d, bool dead);   //判断是否停止搜索最优解
bool constraint(int m, int i, double lp, double*w, double*p, double c_w, double c_p, double c_);       //分支规则
double p_bound(int level);       //计算目标函数上界
bool cmp(density a, density b);       //比较密度（价值/重量）
double knapsack(double *ww, double *pp, int n_, double c_, int*bestx);    //回溯法解背包问题

//全局变量
double c;    //背包容量
int n;       //商品个数
double *w;  //重量
double *p;  //价值
int *best_x;   //解向量

int main()
{
	int n_ = 3; int c_ = 40;
	double*ww = new double[n_+1];
	ww[1] = 20; ww[2] = 15; ww[3] = 10;
	double *pp = new double[n_ + 1];
	pp[1] = 30; pp[2] = 35; pp[3] = 25;
	int*bestx = new int[n_+1];
	double OptSoln = knapsack(ww, pp, n_, c_, bestx);
	cout << "result:" << endl;
	for (int i=1;i<=n;i++)
	{
		cout << "第"<<i<<"件物品放" << best_x[i] << "个" << endl;
	}
	cout << "opt profit:" << OptSoln << endl;
	cout << "finish!!!" << endl;
	system("pause");
	return 0;
}



//public variables 的初始化
bool dead = false;
double lp = 0; //下界
double cw = 0.0;  
double cp = 0.0;
static int m[3]{ 0,0,0 };       //每一层节点的取值位置，在本例中区分左右孩子节点
int a[3][2] = { { 1,0 },{ 1,0 },{ 1,0 } };  //x每一步的取值集合, 在这里x每次的取值集合是1，0          //不同问题不一样，TSP问题的取值集合是 1,2,3,4...  
int k[3]{ 2,2,2 };     //在这里每个节点有两个分支(兄弟节点)   .TSP问题每一层的K不全是2，如第0层是3，第1层是2.。。。
int d[3]{ 0,0,0 };      //记录每一层搜索过的节点数
int s[2]{ 0,0 };     //根节点的分支，访问过后设为1



bool cmp(density a, density b)
{
	return a.des > b.des;
}

double knapsack(double *ww,double *pp, int n_,double c_,int*bestx)             //回溯法求解背包
{
	n = n_; c = c_;
	double best_v=0;
	density*q = new density[n];
	double wsum=0; 
	double psum=0;
	for (int i=1;i<=n;i++)
	{
		q[i - 1] = density(i, pp[i] / ww[i]);
		wsum += ww[i];
		psum += pp[i];
	}
	best_x = new int[n_ + 1];

	if (wsum<=c)             //全装得下
	{
		for (int i=0;i<n;i++)
		{
			best_x[i+1] = 1;
		}
		return best_v=psum;
	}

	sort(q,q+n_,cmp);         //按照密度排序

	for (int i=0;i<n;i++)
	{
		cout << q[i].index;
	}
	cout << endl;


	w = new double[n_+1];
	p = new double[n_+1];
	for (int i=1;i<=n_;i++)
	{
		w[i] = ww[q[i-1].getindex()];    //排序后的w,p
		p[i] = pp[q[i-1].getindex()];
	}

	//print p  and   w
	cout << "w ," << "p" << endl;
	for (int i=1;i<=n;i++)
	{
		cout << w[i] << "," << p[i] << endl;
	}
	cout << endl;



	//开始
	bool find = false;  //是否找到最优解
	int i = 0;
	while (i>=0)
	{
		if (i==0)
		{
			cw = cp = 0;
		}                  
		for (int g=0;g<n;g++)
		{
			if (i==g)
			{
				d[g]++; //每搜索一次i层的点，d[i]+1
			}
		}
		while (m[i]<k[i])
		{
			if (i == 0&&m[i]==k[0]-1)
			{
				  s[m[i]] = 1;       //根节点的该子节点已访问过
			}
			/*
			cout <<"m[i] :"<<m[i] << endl;
			cout <<"i :"<< i << endl;
			cout << "cw :"<<cw << endl;
			cout << "cp :"<<cp << endl;
			*/
			if (constraint(m[i],i,lp,w,p,cw,cp,c_))         // 如果满足约束条件
			{
				cout << "add an item!" << endl;           
				bestx[i+1] = a[i][m[i]];
				cout <<"x"<<i+1<<"="<< bestx[i + 1] << endl;               

				if (soln(s,i,d[i],dead))               
				{
					find = true;
					cout << "find!!!" << endl;
					break;
				}
				else        //继续深度搜索
				{
					cout << "continue" << endl;
					if (i < n - 1)           //没有到达最底层
					{
						i++;
						m[i] = 0;               //重置m[i];
						continue;
					}
					else                            //已经达到最底层
						if (m[i] + 1 < k[i])     //如果是左节点则接下来回溯到它的父亲节点看右节点， 否则跳出循环，回溯到上一层的父亲节点
						{
							m[i]++; 
							cw -= w[i + 1]; cp -= p[i + 1];       //回溯到父亲节点，比较同一层的其他兄弟节点    //但cp,cw应该减去刚刚加入的这一层的孩子节点的w,p
					        continue;                                    //一旦回溯就要注意调整cp cw
						}                  
					    break;
				}
			}
			else        //不满足约束，回溯到父亲节点看兄弟节点
			{
				if (soln(s, i, d[i],dead))
				{
					find = true;
					cout << "find!!!" << endl;
					break;
				}
				m[i]++;                   //如果兄弟节点都访问完了，跳出循环，回溯到上层
			}
		}
		if (find)
			break;
		i--;               //回溯到上层
		if (i < 0)
		{
			cout << "no branch, stop search" << endl;
			break;
		}
		cout << "回溯到:" << i << endl;
		cw -= w[i + 1];  cp -= p[i + 1];
		m[i]++;        //如果上一层无可分支的子节点，m[i]++超出范围，则继续i--
	}
	for (int j = 1; j <= n; j++)
	{
		 best_x[j]=bestx[q[n - j].getindex()];    
	}
	return  lp;
}

double p_bound(int level)            //计算upperprofit，一般是current objvalue + rest possible max objvalve
{
	double rest_c =c-cw;
	double p_bound = cp;
	while (level+1<=n&&w[level+1]<rest_c)
	{
		rest_c -= w[level+1];
		p_bound += p[level+1];
		level++;
	}
	if (level+1<=n)
	{
		p_bound += rest_c*(p[level+1] / w[level+1]);
	}
	return p_bound;
}

bool soln(int*s,int i,int d,bool dead)   //判断是否停止搜索最优解
{
	if (s[1]!=1)         //s[k[0]-1]!=1  如果根节点的子节点每访问完
	{
		return false;
	}
	if (d==(2^(i+1))&&dead)   //右节点且无法继续分支,全部搜索完
	{
		return true;
	}
	if (i==n-1&&d == (2^(i+1))&&!dead)    
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool constraint(int m, int i,double lp_,double*w,double*p,double c_w,double c_p,double c_)  
{
	if (m==0)  //左孩子
	{
		//cout << "up_bound:"<<p_bound(i) << endl;
		if (c_w+w[i+1] < c_&&p_bound(i) >= lp_)
		{
			//cout << "left child is feasible" << endl;
			cw += w[i+1];
			//cout << "cw" << cw << endl;        
			cp += p[i + 1];
			lp = c_p+ p[i+1];
			//cout << "lp" << lp << endl;           
			dead = false;
			return true;
		}
		else
			dead = true;     //unfeasible, set as dead node
			return false;
	}
	else      //右孩子
	{
		if (p_bound(i + 1) >= lp_)
		{
			lp = p_bound(i + 1);
			/*
			cout << "p_bound:" << p_bound(i + 1) << endl;
			cout << "new lp" << lp << endl;
			cout << "right child is feasible" << endl;
			*/
			dead = false;
			return true;
		}
		else
		{
			dead = true;     //unfeasible, set as dead node
			return false;
		}
	}
}
