#include<vector>
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;


struct edge
{
	int start_node;
	int end_node;
	int weight;
};

//vector<edge>edges;

bool cmp(edge a, edge  b)
{
	return a.weight < b.weight;
}

vector<int>father;
void init_father(int &node_num)
{
	for (int i = 0; i<node_num; i++)
	{
		father.push_back(i);
	}
}
int find_father(int &node)
{
	if (father[node] == node)
	{
		return node;
	}
	else
		return father[node]=find_father(father[node]);
}
void unit_father(int &node1, int &node2)
{
	int a = find_father(node1);
	int b = find_father(node2);
	if (a != b)
		father[node2] = a;
}

int main()
{
	int node_num = 5;
	int edge_num = 7;
	vector<edge> edges;
	edges.push_back({ 0,1,5 });
	edges.push_back({ 0,3,2 });
	edges.push_back({ 1,2,7 });
	edges.push_back({ 1,3,6 });
	edges.push_back({ 2,3,8 });
	edges.push_back({ 2,4,3 });
	edges.push_back({ 3,4,9 });
	int treecost = 0;
	cout << "start!!!!!" << endl;
	//vector<edge>::iterator it;
	//it = edges.begin();
	sort(edges.begin(), edges.end(), cmp);
	for (int i = 0; i<edge_num; i++)
	{
		cout << edges[i].start_node << "  " << edges[i].end_node << "  " << edges[i].weight;
		cout << endl;
	}

	init_father(node_num);
	int n = 0;
	for (int i = 0; i <edge_num; i++)
	{
		if (find_father(edges[i].start_node) != find_father(edges[i].end_node))
		{
			n++;
			treecost += edges[i].weight;
			unit_father(edges[i].start_node, edges[i].end_node);
		}
		if (n == node_num - 1)
		{
			break;
		}
	}
	cout << "find!!!" << endl;
	cout << "the minimum cost of tree=" << treecost;
	system("pause");
	return 0;
}
