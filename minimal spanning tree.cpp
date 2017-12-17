#include<vector>
#include"graph.h"
#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define INF 9999




int main()
{
	int size = 10;
	graph* graph;
	vector<int>nodes;
	int m = 5; int n = 7;   //m—node_num; n—edge_num;
	for (int i = 0; i<m; i++)
	{
		graph->insert_node(i + 1);
	}
	//cout << graph.getnodelist<< endl;
	graph->insert_edge(0, 1, 5);
	graph->insert_edge(0, 3, 2);
	graph->insert_edge(1, 2, 7);
	graph->insert_edge(1, 3, 6);
	graph->insert_edge(2, 3, 8);
	graph->insert_edge(2, 4, 3);
	graph->insert_edge(3, 4, 9);

	//graph->creat_graph(m, graph->getnodelist(), graph->get_edge_set());

	int treecost1= graph->kruskal;
	int treecost2 = graph->prim;
	cout << "the minimum cost by kruskal is" << treecost1 << endl;
	cout << "the minimum cost by prim is" << treecost2 << endl;
	return 0;
}


int graph::prim(graph *&graph)
{
	int treecost = 0;
	int n = graph->getnodelist.size();
	vector<vector<int>>edges = graph->get_edge_set;
	vector<int>edge_que;          //可选择的边
	vector<int>start_que;           //边的起始点
	vector<int>end_que;              //边的终点

	for (int i = 0; i<n; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (i != j&&edges[i][j] != INF)
			{
				edge_que.push_back(edges[i][j]);
				start_que.push_back(i);
				end_que.push_back(j);
			}
		}
	}
	sort(edge_que.begin, edge_que.end, campare);

	vector<int>N;
	vector<int>E;
	N.push_back(0);

	while (N.size<n)         //直到所有顶点都加入N
	{
		for (int i = 0; i<edge_que.size; i++)
		{
			int k = 0;
			for (int j = 0; j<N.size; j++)
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
				E.push_back(edge_que[i]);
				treecost += edge_que[i];
				for (int j = 0; j < N.size; j++)
				{
					if (start_que[i] == N[j])
					{
						N.push_back(end_que[i]);     //把边的另一端点加入集合N
					}
					else if (end_que[i] == N[j])
					{
						N.push_back(start_que[i]);
					}
				}
			}
		}
	}

	return treecost;
}

int graph::kruskal(graph *&graph)
{
	int treecost = 0;
	int n = graph->getnodelist.size;
	vector<vector<int>>edges = graph->get_edge_set;
	vector<int>edge_que;          //可选择的边
	vector<int>start_que;           //边的起始点
	vector<int>end_que;              //边的终点
									 
	for (int i = 0; i<n; i++)
	{
		for (int j = i + 1; j<n; j++)
		{
			if (i != j&&edges[i][j] != INF)
			{
				edge_que.push_back(edges[i][j]);
				start_que.push_back(i);
				end_que.push_back(j);
			}
		}
	}

	sort(edge_que.begin, edge_que.end, campare);          

	vector<int>start;   //存储最小生成树的起点终点和边
	vector<int>end;
	vector<int>weight;

	while (end.size<n - 1)                //n个点，n-1条边
	{
		for (int i = 0; i < edge_que.size(); i++)
		{
			if (end.size> 0)
			{
				int k = 0;
				for (int j = 0; j < end.size; j++)
				{
					if (start_que[i] == start[j])
						k++;
					else if (end_que[i] == end[j])
						k++;
				}

				if (k < 2)                 //起点终点如果都已经出现了，再加入这个边就会形成圈
				{
					start.push_back(start_que[i]);
					end.push_back(end_que[i]);
					weight.push_back(edge_que[i]);
					treecost += edge_que[i];
				}
				else
					continue;
			}
			else
			{
				start.push_back(start_que[i]);
				end.push_back(end_que[i]);
				weight.push_back(edge_que[i]);
				treecost += edge_que[i];
			}
		}
	}
	return treecost;
}


bool graph::campare(int a, int b)
{
	if (a <b)
		return true;
	else
		return false;
}
