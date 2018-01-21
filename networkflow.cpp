// networkflow.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int MAXN = 1e3 + 50;
const int MAXM = 4e5 + 50;
const int INF = 0x3f3f3f3f;

struct Edge
{
	int from, to, cap, flow, cost;
	Edge() {}
	Edge(int u, int v, int c, int f, int w) :from(u), to(v), cap(c), flow(f), cost(w) {}
};

struct MCMF
{
	int n, m;
	vector<Edge> edges;
	vector<int> G[MAXN];
	int inq[MAXN];
	int d[MAXN];
	int p[MAXN];
	int a[MAXN];

	void init(int n)
	{
		this->n = n;
		for (int i = 0; i<n; i++) G[i].clear();
		edges.clear();
	}

	void addEdge(int from, int to, int cap, int cost)
	{
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool Bellman_Frod(int s, int t, int& flow, LL& cost)
	{
		for (int i = 0; i<n; i++) d[i] = INF;
		memset(inq, 0, sizeof(inq));
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

		queue<int> Q;
		Q.push(s);
		while (!Q.empty())
		{
			int u = Q.front(); Q.pop();
			inq[u] = 0;
			for (int i = 0; i<G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				if (e.cap>e.flow&&d[e.to]>d[u] + e.cost)
				{
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap - e.flow);
					if (!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
				}
			}
		}

		if (d[t] == INF) return false;
		flow += a[t];
		cost += (LL)d[t] * (LL)a[t];
		for (int u = t; u != s; u = edges[p[u]].from)
		{
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
		}
		return true;
	}


	int MincostMaxflow(int s, int t, LL& cost)
	{
		int flow = 0;
		cost = 0;
		while (Bellman_Frod(s, t, flow, cost));
		return flow;
	}
};

MCMF cf;

int main()
{

		int n, m;
		while (scanf("%d%d", &n, &m) != EOF)
		{
			cf.init(n + 2);
			int u, v, w;
			for (int i = 1; i <= m; i++)
			{
				scanf("%d%d%d", &u, &v, &w);
				cf.addEdge(u, v, 1, w);
				cf.addEdge(v, u, 1, w);
			}
			cf.addEdge(0, 1, 2, 0);
			cf.addEdge(n, n + 1, 2, 0);
			LL cost;
			cf.MincostMaxflow(0, n + 1, cost);
			printf("%lld\n", cost);
		}
		system("pause");
	return 0;
}


