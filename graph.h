#include <vector>
using namespace std;

class graph
{

private:
	vector<int>nodelist;
	vector<int>row;
	vector<vector<int>>edge_set;
	int INF = 99999;
	int node_num;
	int edge_num;
	int size;

public:
	graph(int size);
	void insert_node(int node) { nodelist.push_back(node);};
	vector<int>getnodelist() { return nodelist; };
	void insert_edge(int i, int j, int weight);
	vector<vector<int>>get_edge_set() { return edge_set; };
	vector<int>getrow(int nodenum, int m,vector<vector<int>>&edge_set);
	void creat_graph(int node_num, vector<int>&nodes, vector<vector<int>>&edge_sets);
};

