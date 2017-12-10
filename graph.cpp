#include"graph.h"

graph::graph(int size)   //初始化
{
	int node_num = 0;

	for (int i=0;i<size;i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i != j)
				edge_set[j][i] = edge_set[i][j]= INF;
			else
				edge_set[i][j] = 0;
		}
	}
}

void graph::insert_edge(int i, int j, int weight)
{
	edge_set[i][j] = weight;
}

vector<int>graph::getrow(int nodenum,int m,vector<vector<int>>&edge_set)
{
		for (int j = 0; j<nodenum; j++)
		{
			row[j] = edge_set[m][j];
		}
	return row;
}

void graph::creat_graph(int node_num, vector<int>&nodes, vector<vector<int>>&edge_sets)
{
	for (int i=0;i<node_num;i++)
	{
		nodelist.push_back(nodes[i]);
	}
	for (int j=0;j<node_num;j++)
	{
		edge_set.push_back(getrow(node_num,j,edge_sets));
	}
}
