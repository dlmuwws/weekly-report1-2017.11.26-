#include<iostream>
#include<vector>
using namespace std;
#define INF 999999


struct node
{
	int index;             //当前点的索引
	int pre_index;     //上一个点的索引
	int adjusted_volumn;          //可调节的流量
	int state;    //访问状态
};

struct edge
{
	node start;        //边的起点
	node end;      //终点
	int v;         //流量
	int c;        //容量
};

void adjust(node sink, vector<edge>edges)
{
	int edge_num = edges.size();
	for (int i = 0; i < edge_num; i++)
	{
		if (edges[i].start.index == sink.pre_index)
		{
			edges[i].v += sink.adjusted_volumn;
			sink = edges[i].start;
			adjust(sink, edges);
		}
		else if (edges[i].start.index == -sink.pre_index)
		{
			edges[i].v -= sink.adjusted_volumn;
			sink = edges[i].start;
			adjust(sink, edges);
		}
	}
}

bool BFS(vector<node>nodelist,vector<edge>edges,node source,node sink)             //找增广链，同时调整增广链上的流量
{
	cout << "BFS  start!!!!" << endl;
	vector<node>ingvisit;
	ingvisit.clear();
	int node_num = nodelist.size();

	for (int i = 0; i < node_num; i++)
	{
		nodelist[i].state = 0;
		nodelist[i].pre_index = 0;
		nodelist[i].adjusted_volumn = 0;
		cout << nodelist[i].index << " " << nodelist[i].pre_index << " " << nodelist[i].state << endl;
	}
	ingvisit.push_back(source);
	source.pre_index = -INF;
	source.adjusted_volumn = INF;
	source.state = 1;
	//int k = 0;
	bool find = false;
	while (!ingvisit.empty())
	{
		node cur_node = ingvisit[0];
		cout << "cur_node:" << cur_node.index << endl;
		int n = edges.size();
		for (int i = 0; i < n; i++)
		{
			if (edges[i].start.index == cur_node.index&&edges[i].end.state == 0 && edges[i].v < edges[i].c)           //从cur_node出发的正向弧
			{
				cout << "find a 正向 arc" << endl;
				ingvisit.push_back(edges[i].end);
				edges[i].end.pre_index = cur_node.index;
				if (edges[i].c - edges[i].v <= cur_node.adjusted_volumn)
				{
					edges[i].end.adjusted_volumn = edges[i].c - edges[i].v;
				}
				else
				{
					edges[i].end.adjusted_volumn = cur_node.adjusted_volumn;
				}
				//edges[i].v += edges[i].end.adjusted_volumn;
				edges[i].end.state = 1;
				//k++;
			}
			else if (edges[i].end.index == cur_node.index&&edges[i].start.state == 0 && edges[i].v > 0)             //反向弧
			{
				cout << "find a 反向 arc" << endl;
				ingvisit.push_back(edges[i].start);
				edges[i].start.pre_index = -cur_node.index;
				edges[i].end.adjusted_volumn = edges[i].v;
				//edges[i].v -= edges[i].end.adjusted_volumn;
				edges[i].start.state = 1;
				//k++;
			}
		}
		cout << "ok " << endl;
		ingvisit.erase(ingvisit.begin());

		if (sink.state == 1)
		{
			cout << "找到一条增广链" << endl;
			//调整弧流量
			adjust(sink, edges);
			find = true;
			break;
		}
	}
	return find;
}


int maxflow(node source, node sink, vector<node>nodelist, vector<edge>edges)
{

	int maxflow = 0;
	int node_num = nodelist.size();
	int edge_num = edges.size();

	bool b = true;
	while(b)
	{
		int c= BFS(nodelist, edges, source, sink);
		if (!c)
		{
			cout << "找不到增广链" << endl;
			cout << "find the max flow!!!!!!!" << endl;
			for (int i = 0; i < edge_num; i++)
			{
				if (edges[i].start.index == source.index)             //从source出发的边的流量之和即为整个网络的流量
				{
					maxflow += edges[i].v;
				}
			}
			break;
		}
	}
	cout << "find!!!!" << endl;
	return maxflow;
}

int main()
{
	int node_num=6;
	vector<node>nodelist;
	for (int i=0;i<node_num;i++)
	{
		nodelist.push_back({ i + 1,0,0,0});
	}
	vector<edge>edges;
	edges.push_back({ nodelist[0],nodelist[1],8,13 });
	edges.push_back({ nodelist[0],nodelist[2],11,16 });
	edges.push_back({ nodelist[1],nodelist[2],1,4 });
	edges.push_back({ nodelist[2],nodelist[1],0,10 });
	edges.push_back({ nodelist[2],nodelist[3], 12,12});
	edges.push_back({ nodelist[1],nodelist[4],11,14 });
	edges.push_back({ nodelist[3],nodelist[1],4,9 });
	edges.push_back({ nodelist[4],nodelist[3],7,7 });
	edges.push_back({ nodelist[3],nodelist[5],15,20});
	edges.push_back({ nodelist[4],nodelist[5],4,4 });

	int cost= maxflow(nodelist[0],nodelist[5],nodelist,edges);
	cout << "get the maxflow!!!" << endl;
	cout << cost << endl;
	system("pause");
	return 0;
}
