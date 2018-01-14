#include"branch and bound.h"
#include<iostream>
#include<algorithm>
using namespace std;

double maxp_knapsack();
double knapsack(double *ww, double *pp, int n_, double c_, int*bestx);
double p_bound(int level);
void addnode(double up, double p,double w, int level_, treenode* parent_,bool leftChild_);
bool cmp(density a, density b);

double c;
int n;
double *w;
double *p;
double cw;
double cp;
int *best_x;
maxheap *maxheap_;


int main()
{
	int n_ = 3; int c_ = 40;
	double*ww = new double[n+1];
	ww[1] = 20; ww[2] = 15; ww[3] = 15;
	double *pp = new double[n + 1];
	pp[1] = 40; pp[2] = 25; pp[3] = 25;
	int*bestx = new int[n+1];
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

bool cmp(density a, density b)
{
	return a.des > b.des;
}

void addnode(double up, double p, double w, int level_, treenode* parent_, bool leftChild_)
{
	treenode*newnode = new treenode(parent_,leftChild_);
	maxheap_->push(maxheap_node(newnode, level_, up, p, w));
}

double maxp_knapsack()
{
	treenode* eNode = new treenode();
	int eNode_Level = 1;
	double lp = 0;      //下界
	double up = p_bound(1);      //上界

	while (eNode_Level != n + 1)
	{
		double wol = cw + w[eNode_Level];
		if (wol <= c)
		{
			if (cp + p[eNode_Level] > lp)                                              //不同问题（树结构），这里的判断条件有所不同
			{
				lp = cp + p[eNode_Level];
				addnode(up, cp+ p[eNode_Level], cw+ w[eNode_Level], eNode_Level + 1, eNode, true);
			}
		}
		up = p_bound(eNode_Level + 1);
		// right child
		if (up >= lp)
		{
			addnode(up, cp, cw, eNode_Level + 1, eNode, false);
		}
		maxheap_node nextHeapNode = maxheap_->pop();
		eNode = nextHeapNode.p_node;
		eNode_Level = nextHeapNode.level;
		cw = nextHeapNode.w;
		cp = nextHeapNode.p;
		up = nextHeapNode.up;
	}
    for (int j = n; j > 0; j--)
	{
		best_x[j] = (eNode->leftchild)?1:0;
		eNode = eNode->parent;
	}
return cp;
}


double knapsack(double *ww,double *pp, int n_,double c_,int*bestx)
{
	n = n_; c = c_;
	double best_v;
	density*q = new density[n];
	double wsum=0;
	double psum=0;
	for (int i=1;i<=n;i++)
	{
		q[i - 1] = density(i, pp[i] / ww[i]);
		wsum += ww[i];
		psum += pp[i];
	}
	best_x = new int[n + 1];
	if (wsum<=c)             //全装得下
	{
		for (int i=0;i<n;i++)
		{
			best_x[i+1] = 1;
		}
		return best_v=psum;
	}

	sort(q,q+n_,cmp);         //按照密度排序

	w = new double[n_+1];
	p = new double[n_+1];
	for (int i=1;i<=n_;i++)
	{
		w[i] = ww[q[i-1].getindex()];
		p[i] = pp[q[i-1].getindex()];
	}
	cw = 0.0;
	cp = 0.0;
	maxheap_ = new maxheap(n);
	best_v = maxp_knapsack();
	for (int j = 1; j <= n; j++)
	{
		bestx[q[n-j].getindex()] = best_x[j];
	}
	return  best_v;
}

double p_bound(int level)            //计算upperprofit，一般是current objvalue + rest possible max objvalve
{
	double rest_c =c-cw;
	double p_bound = cp;
	while (level<=n&&w[level]<rest_c)
	{
		rest_c -= w[level];
		p_bound += p[level];
		level++;
	}
	if (level<=n)
	{
		p_bound += rest_c*(p[level] / w[level]);
	}
	return p_bound;
}
