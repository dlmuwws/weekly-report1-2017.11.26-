#include<vector>
//#include"graph.h"
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define INF 9999


bool campare(int a, int b)
{
	if (a <b)
		return true;
	else
		return false;
}


int prim(vector<vector<int>>&graph)
{
	int treecost = 0;
	int n = graph.size();
	//vector<vector<int>>edges = graph->get_edge_set();
	vector<int>edge_que;          //可选择的边
	vector<int>start_que;           //边的起始点
	vector<int>end_que;              //边的终点

	for (int i = 0; i<n; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (i != j&&graph[i][j] != INF)
			{
				edge_que.push_back(graph[i][j]);
				start_que.push_back(i);
				end_que.push_back(j);
			}
		}
	}
	int size1 = edge_que.size();
	for (int i=0;i<size1-1;i++)              //排序
	{
		for (int j=i+1;j<size1;j++)
		{
			if (edge_que[i]>edge_que[j])
			{
				int a = edge_que[i]; int b = start_que[i]; int c = end_que[i];
				edge_que[i] = edge_que[j]; start_que[i] = start_que[j]; end_que[i] = end_que[j];
				edge_que[j] = a; start_que[j] = b; end_que[j] = c;
			}
		}
	}
	for (int i=0;i<size1;i++)
	{
		cout << start_que[i] << "   " << end_que[i] << "   " << edge_que[i] << endl;
	}

	//sort(edge_que.begin(), edge_que.end(), campare);
	cout << "start!!!" << endl;

	vector<int>N;
	vector<int>E;
	N.push_back(0);

	int size2 = N.size();
	//cout << size2 << endl;
	while (size2<n)         //直到所有顶点都加入N
	{
		for (int i = 0; i<size1; i++)
		{
			int k = 0;
			for (int j = 0; j<size2; j++)
			{
				if (start_que[i] == N[j])
				{
					k++;
				}
				if (end_que[i] == N[j])
				{
					k++;
				}
			}
			if (k == 1)              //该边只有一个顶点在顶点集合N里
			{
				cout <<"add an edge  "<< edge_que[i]<<"  ";
				E.push_back(edge_que[i]);
				treecost += edge_que[i];
				vector<int>::iterator it;
				it = find(edge_que.begin(), edge_que.end(), edge_que[i]);
				edge_que.erase(it);
				size1--;
				for (int j = 0; j <size2; j++)
				{
					if (start_que[i] == N[j])
					{
						N.push_back(end_que[i]);     //把边的另一端点加入集合N
						cout << "add its end_node  " << end_que[i] << "  ";
						break;
					}
					else if (end_que[i] == N[j])
					{
						N.push_back(start_que[i]);
						cout << "add its start_node  " << start_que[i] << "   ";
						break;
					}
				}
				it = find(start_que.begin(), start_que.end(), start_que[i]);
				start_que.erase(it);
				it = find(end_que.begin(), end_que.end(), end_que[i]);
				end_que.erase(it);
				cout << "now,the treecost is " << treecost << endl;
				size2++;
				break;
			}
		}
		cout << endl;
		cout << endl;
		for (int i = 0; i<size1; i++)
		{
			cout << start_que[i] << "   " << end_que[i] << "   " << edge_que[i] << endl;
		}
	}
	cout << "find" << endl;
	return treecost;
}



int main()
{
	int m = 5; int n = 7;   //m—node_num; n—edge_num;
	vector<int>row(m, INF);
	vector<vector<int>>graph(m, row);

	for (int i = 0; i<m; i++)
	{
		graph[i][i] = 0;
	}

	graph[0][1] = graph[1][0]= 5;
	graph[0][3] = graph[3][0]= 2;
	graph[1][2] = graph[2][1]= 7;
	graph[1][3] = graph[3][1]=6;
	graph[2][3] = graph[3][2]=8;
	graph[2][4] = graph[4][2]= 3;
	graph[3][4] = graph[4][3]=9;

	cout << "having got a graph" << endl;

	int treecost = prim(graph);
	cout << "the minimum cost by prim is" << treecost<< endl;
	cout << "okk" << endl;
	getchar();
	return 0;
}
