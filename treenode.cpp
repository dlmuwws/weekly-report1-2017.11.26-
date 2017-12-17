#include"node.h"
#include<stdio.h>
#include<iostream>
using namespace std;
node::node()
{
	index = 0;
	data = 0;
	Lchild = NULL;
	Rchild = NULL;
	parent = NULL;
}

void node::delete_node()
{
	if (this->Lchild!=NULL)
	{
		this->Lchild->delete_node();
	}
	if (this->Rchild != NULL)
	{
		this->Rchild->delete_node();
	}
	if (this->parent != NULL)
	{
		if (this->parent->Lchild=this)
		{
			this->parent->Lchild = NULL;
		}
		if (this->parent->Rchild = this)
		{
			this->parent->Rchild = NULL;
		}
	}
	delete this;
}

node*node::search_node(int nodeindex)
{
	if (this->index = nodeindex)
	{
		return this;
	}
	node*temp = NULL;
	if (this->Lchild != NULL)
	{
		if (this->Lchild->index = nodeindex)
		{
			return this->Lchild;
		}
		else
		{
			temp=this->Lchild->search_node(nodeindex);
			if (temp!=NULL)
			{
				return temp;
			}
		}
	}
	if (this->Rchild != NULL)
	{
		if (this->Lchild->index = nodeindex)
		{
			return this->Lchild;
		}
		else
		{
			temp=this->Lchild->search_node(nodeindex);
			return temp;
		}
	}
	return NULL;
}

void node::fore_traverse()               //前序遍历 根左右    (递归操作)
{
	cout << this->index << "   " << this->data << endl;
	if (this->Lchild!= NULL)
	{
		this->Lchild->fore_traverse();
	}
	if (this->Rchild != NULL)
	{
		this->Rchild->fore_traverse();
	}
}
void node::mid_traverse()                 //中序遍历（左根右）
{
	if (this->Lchild != NULL)
	{
		this->Lchild->fore_traverse();
	}
	cout << this->index << "   " << this->data << endl;
	if (this->Rchild != NULL)
	{
		this->Rchild->fore_traverse();
	}

}

void node::aft_traverse()               //后序遍历（左右根）
{
	if (this->Lchild != NULL)
	{
		this->Lchild->fore_traverse();
	}
	if (this->Rchild != NULL)
	{
		this->Rchild->fore_traverse();
	}
	cout << this->index << "   " << this->data << endl;
}
