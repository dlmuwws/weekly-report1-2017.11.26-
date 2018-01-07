#pragma once

#include"Astar_node.h"
#include<vector>
#include<deque>
using namespace std;

const int row_num=5, col_num=7;

struct point
{
	int x;
	int y;
	point(int x_, int y_) :x(x_), y(y_)
	{
	}
};
class Astar
{
private:
	const int (&matrix)[row_num][col_num];
	deque<point> AstarPath;
	deque<Astar_node> visitingList;
	deque<Astar_node> visitedList;

public:
	Astar(const int(&matrix_)[row_num][col_num]);
	//~Astar(void);
	bool in_visitedlist(int row_,int col_);
	Astar_node* in_visitinglist(int row_, int col_);
	bool CanReach(int row, int col);
	bool CanReach(Astar_node&current, int row, int col, bool allowcorner);
	vector<Astar_node>get_adj_points(Astar_node current, vector<Astar_node> &adjpoints,bool allowcorner);
	void found(Astar_node&current, Astar_node *newpoint);
	void unfound(Astar_node&current, Astar_node &end, Astar_node&newpoint);
	Astar_node findminimum();
	int caculate_G(Astar_node&current,Astar_node *newpoint);
	int caculate_H(Astar_node &newpoint,Astar_node&end);
	deque<point> Getpath() { return AstarPath; };
	void findpath(int start_X, int start_Y, int endX, int endY, bool bAllowCorner = false);
};
