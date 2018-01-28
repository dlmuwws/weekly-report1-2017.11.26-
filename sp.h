#pragma once
#include<iostream>
using  namespace std;
#include<vector>
#include<queue>
#define vexnum 4
#define INF 99999999
int dijkstra(vector<vector<int>> &graph, int start_vertex, int end_vertex, vector<int> &path) 
{
		
		vector<int> shortpath(vexnum, INF);
		vector<int> visited(vexnum, 0);

		path[start_vertex] = start_vertex;
	
		for (int i = 0; i < vexnum; i++)
		{
			if (graph[start_vertex][i] != INF)
				shortpath[i] = graph[start_vertex][i];
		}
		visited[start_vertex] = 1;

		int min_weight = INF;
		int u = -1;
		int nums = vexnum - 1;
		bool first = true;
		while (nums)
		{
			min_weight = INF;
			u = -1;
			for (int i = 0; i < vexnum; i++)
			{
				if (visited[i] == 0 && shortpath[i] < min_weight)
				{
					u = i;
					min_weight = shortpath[i];
					
				}
				
			}

			if (first)
			{
				path[u] = start_vertex;
				first = false;
				
			}

			visited[u] = 1;

			nums--;
			if (end_vertex == u)
			{
				
				break;
			}
			for (int w = 0; w < vexnum; w++)
			{
				if (visited[w] == 0 && graph[u][w] != INF && min_weight + graph[u][w] < shortpath[w])
				{
					shortpath[w] = min_weight + graph[u][w];
		
					path[w] = u;
				
				}
			}
		}
	/*	int i = 3;
		while (i != -1) {
		cout << i << "<=";
		i = path[i];
		}

		cout << -1;
		cout << endl;*/
		return shortpath[end_vertex];
	


};

