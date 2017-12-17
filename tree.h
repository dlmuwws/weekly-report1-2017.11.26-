#pragma once
#include"node.h"
#include<stdio.h>


class  tree
{
public:
	tree();
	~tree();
	bool addnode(int index,int direction,node*node_);
	bool delete_node(int index);
	node* search_node(int index);
	void fore_traverse();
	void mid_traverse();
	void aft_traverse();

private:
	node*root;

};
