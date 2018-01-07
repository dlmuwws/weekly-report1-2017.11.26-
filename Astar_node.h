#pragma once
#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;

class Astar_node
{
int max=1000000;
private:
	int g;
	int h;
	int row, col;
	Astar_node*parent;
public:
	Astar_node(int row_, int col_) :g(max),h(max),row(row_),col(col_),parent(nullptr)
	{
	}
	int get_row() { return row; };
	int get_col() { return col; };
	void setG(int g_) { g = g_; };
	int getG() { return g; };
	void setH(int h_) { h = h_; };
	int getH() { return h; };
	int getF(int g,int h) { return g + h; };
	void set_parent(Astar_node*parent_) { parent = parent_; };
	Astar_node*get_parent() { return parent; };
	bool operator == ( Astar_node  node)
	{
		//return (node.get_row()== node.get_row()) && (node.get_col()==col);
		return (this->get_row() == node.get_row() && this->get_col() == node.get_col());
    }
};
