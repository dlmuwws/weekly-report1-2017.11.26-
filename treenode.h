#pragma once

class node
{
public:
	int index;
	int data;
	node*Lchild;
	node*Rchild;
	node*parent;
	node();
	void delete_node();
	node*search_node(int nodeindex);
	void fore_traverse();
	void mid_traverse();
	void aft_traverse();
};
