
#include"tree.h"
#include"node.h"
tree::tree()
{
	root = new node();
}

bool tree::addnode(int index, int direction, node*node_)
{

	node*temp=search_node(index);
	if (temp=NULL)
	{
		return false;
	}
	node*newnode = new node();
	if (newnode=NULL)
	{
		return false;
	}
	newnode->data= node_->data;
	newnode->index = node_->index;
	newnode->parent = temp;
	if (direction = 0)
	{
		temp->Lchild = newnode;
	}
	if (direction=1)
	{
		temp->Rchild = newnode;
	}
	return true;
}

bool tree::delete_node(int index)
{
	node*temp = search_node(index);
	if (temp = NULL)
	{
		return false;
	}

	temp->delete_node();
	return true;
}

node* tree::search_node(int index)
{
	return root->search_node(index);
}

void tree:: fore_traverse()
{
	root->fore_traverse();
}

void tree::mid_traverse()
{
	root->mid_traverse();
}
void tree::aft_traverse()
{
	root->aft_traverse();
}

tree::~tree()
{
	root->delete_node();
}
