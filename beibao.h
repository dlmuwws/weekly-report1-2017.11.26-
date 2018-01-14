#pragma once
#include<queue>
#include<math.h>
using namespace std;


class treenode
{
public:
	treenode*parent;
	bool leftchild;
	treenode() {};
	treenode(treenode*parent_, bool leftchild_)
	{
		parent = parent_;
		leftchild = leftchild_;
	}
};

class maxheap_node
{
public:
	treenode*p_node;     //对应的解空间树上的点
	int level;            //在解空间树上的层数
	double up;  //上界
	double p;
	double w;
	maxheap_node() {};
	maxheap_node(treenode*node_, int level_, double up_, double p_, double w_)
	{
		p_node = node_; level = level_; up = up_; p = p_; w = w_;
	}

	bool operator<(const maxheap_node right)
	{
		return this->up < right.up;
	}

};

class density
{
public:
	int index;
	double des;
	density() {};
	density(int i, double j)
	{
		index = i;
		des = j;
	}
	int getindex()
	{
		return index;
	}
};

class maxheap
{
public:
	int capacity;
	int size;
	maxheap_node*heap;
	maxheap() {}
	maxheap(int n)
	{
		size = 0;
		capacity = pow((double)2, (double)n);
		heap = new maxheap_node[capacity];
	}
	void adjust(maxheap_node*heap_, int s, int m)
	{
		maxheap_node node_ = heap_[s];
		for (int j = 2 * s; j <= m; j *= 2)
		{
			if (j < m&&heap_[j].up < heap_[j + 1].up)
			{
				++j;
				if (!(node_.up < heap_[j].up))
				{
					break;
				}
				heap_[s] = heap_[j];
				s = j;
			}
		}
		heap_[s] = node_;
	}

	//maxheap_node*creat_maxheap(maxheap_node*heap_,int size_)
	//{
	//	for (int i=size_/2;i>0;i--)
	//{
	//	adjust(heap_, i, size_);
	//}
	//return heap_;
	//}
	void heap_sort(maxheap_node*heap_)
	{
		for (int i = size / 2; i > 0; --i)
		{
			adjust(heap_, i, size);
		}
	}
	void push(maxheap_node node_)
	{
		heap[size+1] = node_;
		size++;
		heap_sort(heap);
	}
	maxheap_node pop()
	{
		maxheap_node temp = heap[1];
		size--;
		heap[1] = heap[size+1];
		heap_sort(heap);
		return temp;
	}
};
