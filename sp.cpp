#include<iostream>
using namespace std;
#include<vector>
#include"graph.h"
#define INF 9999


vector<int> Dijkstra(graph &graph,int &source)        //求某点到其余各点的最短路
{
	vector<int>nodelist=graph.getnodelist();
	vector<vector<int>>edges = graph.get_edge_set();
	int size = nodelist.size();
	vector<int>s(size, 0);      //记录有没有被访问过
	vector<int>path(size, 0);  //记录上个点
	vector<int>dis(size, 0);     //记录最短路径

	for (int i = 0; i<size; i++)      //初始化
	{
		if (i != source)
		{
			s[i] = 0;
			if (edges[source][i] = INF)
			{
				dis[i] = INF;
				path[i] = -1;
			}
			else
			{
				dis[i] = edges[source][i];
				path[i] = source;
			}
		}
		s[source] = 1;
		path[source] = -1;
		dis[source] = 0;
	}

	int unfind=size-1;           //没有找到距source的最短路的点的个数
	while (unfind!=0)
	{
		int sp = 0;int  mindis=0;
		for (int i = 0; i < size; i++)
		{
			if (s[i] = 0)
			{
				mindis = dis[i];
				sp = i;
				break;
			}
		}
		for (int i = sp + 1; i < size; i++)
		{
			if (s[i]=0&&dis[i] < mindis)
			{
				mindis = dis[i];
				sp = i;
			}
		}

		int cur_node = sp;
		dis[cur_node] = mindis;

		for (int i = 0; i < size; i++)
		{
			if (edges[cur_node][i] != INF)
			{
				if (s[i] = 0)
				{
					dis[i] = dis[cur_node] + edges[cur_node][i];
				}
				else
				{
					if (dis[i] > dis[cur_node] + edges[cur_node][i])
						dis[i] = dis[cur_node] + edges[cur_node][i];
				}
			}
		}
		s[cur_node] = 1;
		unfind--;
	}
	cout << "find the sp from source to other nodes:" << endl;

	for (int i=1;i<size;i++)
	{
		cout << "source to" << i << ":" << dis[i] << endl;
	}

	return dis;
}


vector<vector<int>> floyd(graph graph)       //得到图中每对点之间的sp
{
	vector<int>nodelist = graph.getnodelist();
	vector<vector<int>>edges = graph.get_edge_set();
	int size = nodelist.size();

	vector<vector<int>>dis;
	vector<vector<int>>path;

	for (int i = 0; i < size; i++)         //初始化
	{
		for (int j = 0; j < size; j++)
		{
			dis[i][j] = edges[i][j];
			if (i != j&&edges[i][j] != INF)
			{
				path[i][j] = i;
			}
			else
				path[i][j] = -1;
		}
	}

	for (int i = 0; i < size; i++)            //每个点到其他各点
	{
		for (int j = 0; j < size; j++)        //到第j点前插入其余各点
		{
			for (int k = 0; k < size; k++)        //插入k点
			{
				if (dis[i][j] > dis[i][k] + dis[k][j])     //是否插入k点
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
	cout << "sp of every two nodes:" << endl;
	for (int i = 0; i < size; i++)         //初始化
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j&&edges[i][j] != INF)
			{
				int q = path[i][j];
				int temp = 0;
				vector<int>rea_path;
				while (q != i&&q != j)
				{
					rea_path[temp++] = q;
					q = path[i][q];
				}
				cout << i << ",";
				while (temp > 0)
				{
					cout << rea_path[temp--];
				}
				cout << j << "长度为" << dis[i][j] << endl;
			}
		}
	}
}




int main()
{
	int size = 10;
	graph graph = graph::graph(size);
	//graph*graph=new graph(size);
	vector<int>nodes;
	int m = 5; int n = 7;   //m—node_num; n—edge_num;
	for (int i = 0; i<m; i++)
	{
		graph.insert_node(i + 1);
	}
	//cout << graph.getnodelist<< endl;
	graph.insert_edge(0, 1, 5);
	graph.insert_edge(0, 3, 2);
	graph.insert_edge(1, 2, 7);
	graph.insert_edge(1, 3, 6);
	graph.insert_edge(2, 3, 8);
	graph.insert_edge(2, 4, 3);
	graph.insert_edge(3, 4, 9);

	//vector<vector<int>>edge_set = graph.get_edge_set();
	graph.creat_graph(m, graph.getnodelist(), graph.get_edge_set());

	vector<vector<int>>ssp1_;  //多对多
	vector<vector<int>>ssp2_;   //多对多
	vector<int>sp_;                 //一对多
	for (int i = 0; i<size; i++)
	{
		sp_ = Dijkstra(graph, i);
		ssp1_.push_back(sp_);
	}
	//test:
	cout << "the sp of node 1 to  node3:" << ssp1_[1][3] << endl;

	ssp2_ = floyd(graph);
	cout << "the sp of node 1 to  node3:" << ssp1_[1][3] << endl;
	return 0;
}

