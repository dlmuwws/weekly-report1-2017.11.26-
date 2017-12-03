// graph_practise.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include<vector>
#include<queue>

#define vexnum 8
#define INF 99999999


void creat_graph();
bool BFS(vector<vector<int>> &graph, vector<int> &bfs_path, int start_vertex);
bool DFS(vector<vector<int>> &graph, vector<int> &dfs_path, vector<int> &visited, int &idx, int start_vertex);
int dijkstra(vector<vector<int>> &graph, int start_vertex, int end_vertex, vector<int> &path);
int Prim(vector<vector<int>> &graph);
int main()
{	
	creat_graph();
	system("pause");
    return 0;
}

void creat_graph() {
	vector<int> row(vexnum,INF);
	vector<vector<int>> graph(vexnum,row);
	for (int i = 0; i<vexnum; i++)
		graph[i][i] = 0;  

	graph[3][0] = 1;
	graph[0][5] = 1;
	graph[1][2] = 3, graph[2][1] = 3;
	graph[1][6] = 1, graph[6][1] = 1;
	graph[2][3] = 5;
	graph[2][4] = 1;
	graph[3][5] = 3;
	graph[3][6] = 1;
	graph[4][5] = 1;
	graph[4][3] = 3;
	graph[5][7] = 1;
	graph[6][7] = 3;
	graph[7][3] = 3;

	vector<int> bfs_path(vexnum,-1);
	vector<int> dfs_path(vexnum, -1);
	vector<int> visited(vexnum, 0);
	int s_v = 2, e_v = 7;
	BFS(graph, bfs_path, s_v);
	int idx = 0;
	visited[s_v] = 1;
	DFS(graph, dfs_path, visited, idx, s_v);

	vector<int> path(vexnum, -1);
	int result = dijkstra(graph, 2, 7, path);
	cout << "the cost of dijkstra:"<<result << endl;

	cout << "The cost of min spanning tree: " << Prim(graph) << endl;
}
bool BFS(vector<vector<int>> &graph, vector<int> &bfs_path, int start_vertex)
{
	vector<int> visited(vexnum, 0);
	visited[start_vertex] = 1;
	queue<int> que;
	que.push(start_vertex);  
	int idx = 0;
	bfs_path[idx++] = start_vertex;
	while (!que.empty())
	{
		int cur_vex = que.front();
		que.pop(); 
		for (int i = 0; i < vexnum; i++)
		{
			if (graph[cur_vex][i] < INF && graph[cur_vex][i] !=0 && visited[i] == 0)
			{
				visited[i] = 1;
				bfs_path[idx++] = i;
				que.push(i);
			}
		}
	}
	for (int i = 0; i < bfs_path.size(); i++) {
		cout << bfs_path[i]<<" ";
	}
	cout << endl;
	return true;
}
bool DFS(vector<vector<int>> &graph, vector<int> &dfs_path, vector<int> &visited, int &idx, int start_vex)
{
	dfs_path[idx++] = start_vex;
	for (int i = 0; i < vexnum; i++)
	{
		if (graph[start_vex][i] < INF && graph[start_vex][i] != 0 && visited[i] == 0)
		{
			visited[i] = 1;
			DFS(graph, dfs_path, visited, idx, i);
		}
	}
	for (int i = 0; i < dfs_path.size(); i++) {
		cout << dfs_path[i] << " ";
	}
	cout << endl;
	return true;
}
int dijkstra(vector<vector<int>>  &graph, int start_vertex, int end_vertex, vector<int> &path)
{
	vector<int> shortpath(vexnum, INF);    
	vector<int> visited(vexnum, 0);     

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
			break;     
		for (int w = 0; w < vexnum; w++)
		{
			if (visited[w] == 0 && graph[u][w] != INF && min_weight + graph[u][w] < shortpath[w])
			{
				shortpath[w] = min_weight + graph[u][w];     
				path[w] = u; 
			}
		}
	}
	int i = 7;
	while(i!=2) {
		cout << i << "<-";
		i = path[i];
	}
	cout << 2;
	cout << endl;
	return shortpath[end_vertex];
}
int Prim(vector<vector<int>>   &graph)
{
	int sum = 0;
	int u = 0;
	vector<int> lowcost(vexnum, 0);
	vector<int> closest(vexnum, 0);
	vector<int> visited(vexnum, 0);

	for (int i = 0; i < vexnum; i++)
		lowcost[i] = graph[u][i]; 
	visited[u] = 1;

	for (int i = 1; i < vexnum; i++)
	{
		int min = INF;
		u = -1;
		for (int k = 0; k < vexnum; k++)
		{
			if ((lowcost[k] < min) && visited[k] == 0)
			{
				min = lowcost[k];
				u = k;
			}
		}
		if (u == -1) 
			return -1;
		cout << closest[u] << "->"<<u<<endl;  
		sum += min;
		visited[u] = 1; 
		for (int k = 0; k < vexnum; k++)
		{
			if ((graph[u][k] < lowcost[k]) && visited[k] == 0)
			{
				lowcost[k] = graph[u][k];
				closest[k] = u;
			}
		}

	}
	return sum;
}
