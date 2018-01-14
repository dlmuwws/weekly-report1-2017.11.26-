#include"tsp.h"
#include<iostream>
#include<iterator>
#include<algorithm>

using namespace std;
#define N 5


int n = N - 1;
int cost[N][N];
int bestTour[N];

int TSP(int *bestpath)
{
	minheap*minheap_=new minheap(n);

	int *Mcost = new int[n + 1];
	int SMcost= 0;
	for (int i = 1; i <= n; ++i)
	{
		int mcost = -1;
		for (int j = 1; j <= n; ++j)
		{
			if (cost[i][j] != -1 && (mcost == -1 || mcost > cost[i][j]))
			{
				mcost = cost[i][j];
				if (mcost == -1)
				{
                  return -1;
				}
				Mcost[i] = mcost;
				SMcost += mcost;
			}
		}
	}

	//初始化根节点
	heapnode eNode;
	eNode.c_cost= 0;
	eNode.r_cost = SMcost;
	eNode.lc = SMcost;
	eNode.s = 0;
	eNode.path = new int[n];

	for (int i = 0; i < n; ++i)
	{
		eNode.path[i]= i + 1;
	}

	int uc = -1;  //上界
	int *ppath = eNode.path;


	while (eNode.s < n - 1)
	{
		ppath = eNode.path;
		if (eNode.s == n - 2)         //只剩最后一个点需要确定，能否找到最优路径
		{
			if (cost[ppath[n - 2]][ppath[n - 1]] != -1 &&cost[ppath[n - 1]][1] != -1 &&
				(uc == -1 || eNode.c_cost +cost[ppath[n - 2]][ppath[n - 1]] +cost[ppath[n - 1]][1] < uc))
			{
				uc= eNode.c_cost +cost[ppath[n - 2]][ppath[n - 1]] +cost[ppath[n - 1]][1];
				eNode.c_cost= uc;
				eNode.lc = uc;
				eNode.s++;
				minheap_->push(eNode);

			}
			else          //不可行
			{
				delete[] eNode.path;
				eNode.path = nullptr;
			}
		}
		else
		{  //继续分支
			for (int i = eNode.s + 1; i < n; ++i)
				if (cost[ppath[eNode.s]][ppath[i]] != -1)
				{
					int new_lc = eNode.c_cost +cost[ppath[eNode.s]][ppath[i]]+ eNode.r_cost -Mcost[ppath[eNode.s]];
					if (uc == -1 ||new_lc< uc)
					{
						heapnode newnode;
						newnode.lc = new_lc;
						newnode.c_cost = eNode.c_cost + cost[ppath[eNode.s]][ppath[i]];
						newnode.r_cost= eNode.r_cost - Mcost[ppath[eNode.s]];
						newnode.s = eNode.s + 1;
						newnode.path= new int[n];
						copy(ppath, ppath + n, newnode.path);
						swap(newnode.path[newnode.s], newnode.path[i]);
						minheap_->push(newnode);
					}
				}

			delete[] eNode.path;
			eNode.path= nullptr;
		}

		if (minheap_->size==0)  //跳出循环
			break;
		eNode = minheap_->pop();
	}

	if (uc == -1)
		return -1;
	//复制到bestTour
	copy(eNode.path, eNode.path + n, bestpath + 1);
	while (true)            //再次删除堆的内存空间
	{
		delete[] eNode.path;
		if (minheap_->size==0)
			break;
		eNode = minheap_->pop();
	}
	return uc;
}

int main()
{
	cost[1][1] = -1;
	cost[1][2] = 30;
	cost[1][3] = 6;
	cost[1][4] = 4;

	cost[2][1] = 30;
	cost[2][2] = -1;
	cost[2][3] = 5;
	cost[2][4] = 10;

	cost[3][1] = 6;
	cost[3][2] = 5;
	cost[3][3] = -1;
	cost[3][4] = 20;

	cost[4][1] = 4;
	cost[4][2] = 10;
	cost[4][3] = 20;
	cost[4][4] = -1;

	int bestcost = TSP(bestTour);
	cout << "opt cost:" << bestcost << endl;
	cout << "opt path: " << endl;
	//for (int i=1;i<=n;i++)
	//{
	//	cout << bestTour[i] <<"  ";
	//}
	//cout<<endl;
	copy(bestTour + 1, bestTour + n + 1, ostream_iterator<int>(cout, "->"));// 模板类 ostream_iterator 描述一个输出迭代器对象，将使用提取的输出流的连续元素写入运算符
	cout << bestTour[1] << endl;
	system("pause");
	return 0;
}
