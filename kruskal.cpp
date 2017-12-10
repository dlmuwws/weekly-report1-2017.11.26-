// kruskal.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include"vector"
#include<algorithm>
#define vexnum 8
struct node
{
	int x;
	int y;
	int length;
};
bool cmp(node a, node b);
int find(int a);
void node_union(int x,int y);

int father[11];
int main()
{   

	node list[10];
	list[0] = { 2, 1, 3 };
	list[1] = { 3, 1, 2 };
	list[2] = { 3, 2, 4 };
	list[3] = { 2, 4, 2 };
	list[4] = { 3, 4, 3 };
	list[5] = { 4, 5, 5 };
	list[6] = { 3, 5, 2 };
	list[7] = { 5, 6, 4 };
	list[8] = { 7, 6, 5 };
	list[9] = { 8, 5, 5 };
	list[10] = { 7, 8, 4 };
	sort(list, list + 11, cmp);
	int count = 0;
	int value = 0;
	for (int i = 0; i < 11; i++) {
		cout << list[i].x << " " << list[i].y << " " << list[i].length << endl;
	}
	for (int i = 0; i < 11; i++) {
		father[i] = i;
	}
	for (int i = 0; i < 11; i++) {
		
		if (find(list[i].x) != find(list[i].y))
		{
			value = value + list[i].length;
			node_union(list[i].x,list[i].y);
			count++;
		}
		if (count == vexnum - 1)
			break;
	}
	cout << "the cost of min spanning tree: " << value << endl;
	
	system("pause");
    return 0;
}

bool cmp(node a,node b) {
	return a.length < b.length;
}

int find(int a ) {
	if (father[a] == a) return a;
	else return father[a] = find(father[a]);
}
void node_union(int a, int b ) {
	int fa = find(a);
	int fb = find(b);	
	if (fa != fb)
		father[fb] = fa;

}

