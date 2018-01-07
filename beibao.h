#pragma once
#include<math.h>

class BBnode {
public:
	BBnode*  parent;     
	bool leftChild;   
	BBnode(BBnode* par, bool ch) {
		parent = par;
		leftChild = ch;
	}
	BBnode() {

	}
};

class HeapNode {
public:
	BBnode* liveNode;   
	double  upperProfit; 
	double  profit; 
	double  weight;   
	int     level;  
	HeapNode(BBnode* node, double up, double pp, double ww, int lev) {
		liveNode = node;
		upperProfit = up;
		profit = pp;
		weight = ww;
		level = lev;
	}
	HeapNode() {

	}
	int compareTo(HeapNode o) {
		double xup = o.upperProfit;
		if (upperProfit < xup)
			return -1;
		if (upperProfit == xup)
			return 0;
		else
			return 1;
	}
};

class Element {
public:
	int id;
	double d;
	Element() {

	}
	Element(int idd, double dd) {
		id = idd;
		d = dd;
	}
	int compareTo(Element x) {
		double xd = x.d;
		if (d<xd)return -1;
		if (d == xd)return 0;
		return 1;
	}
	bool equals(Element x) {
		return d == x.d;
	}
};

class MaxHeap {
public:
	HeapNode *nodes;
	int nextPlace;
	int maxNumber;
	MaxHeap(int n) {
		maxNumber = pow((double)2, (double)n);
		nextPlace = 1;
		nodes = new HeapNode[maxNumber];
	}
	MaxHeap() {
	}
	void put(HeapNode node) {
		nodes[nextPlace] = node;
		nextPlace++;
		heapSort(nodes);
	}
	HeapNode removeMax() {
		HeapNode tempNode = nodes[1];
		nextPlace--;
		nodes[1] = nodes[nextPlace];
		heapSort(nodes);
		return tempNode;
	}
	void heapAdjust(HeapNode *  nodes, int s, int m) {
		HeapNode rc = nodes[s];
		for (int j = 2 * s; j <= m; j *= 2) {
			if (j<m&&nodes[j].upperProfit<nodes[j + 1].upperProfit)
				++j;
			if (!(rc.upperProfit<nodes[j].upperProfit))
				break;
			nodes[s] = nodes[j];
			s = j;
		}
		nodes[s] = rc;
	}
	void heapSort(HeapNode * nodes) {
		for (int i = (nextPlace - 1) / 2; i>0; --i) {
			heapAdjust(nodes, i, nextPlace - 1);
		}
	}
};
