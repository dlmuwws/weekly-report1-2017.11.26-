#pragma once
#include<math.h>
using namespace std;

class heapnode
{
public:
	int lc;       //下界
	int c_cost;
	int r_cost;
	int s;
	int *path;
	operator int() { return lc; }

	//重载大于号运算符，用于小根堆比较
	bool operator>(const heapnode &node_)
	{
		return lc > node_.lc;
	}
};


class minheap
{
public:
	int size;
	int capacity;
	heapnode*p_minheap;
	minheap() {}
	minheap(int n)
	{
		size = 0;
		capacity= pow((double)2, (double)n);
		p_minheap = new heapnode[capacity];
	}
	void adjust(heapnode*minheap_, int s, int m)
	{
		heapnode rc = minheap_[s];
		for (int j = 2 * s; j <= m; j *= 2)
		{
			if (j < m&&minheap_[j].lc> minheap_[j + 1].lc)
			{
				++j;
				if (!(rc.lc > minheap_[j].lc))
				{
					break;
				}
				minheap_[s] = minheap_[j];
				s = j;
			}
		}
		minheap_[s] = rc;
	}
	void heap_sort(heapnode*minheap_)
	{
		for (int i = size / 2; i > 0; --i)
		{
			adjust(minheap_, i, size);
		}
	}
	void push(heapnode node_)
	{
		p_minheap[size+1] = node_;
		size++;
		heap_sort(p_minheap);
	}
	heapnode pop()
	{
		heapnode temp = p_minheap[1];
		size--;
		p_minheap[1] = p_minheap[size+1];
		heap_sort(p_minheap);
		return temp;
	}
};
