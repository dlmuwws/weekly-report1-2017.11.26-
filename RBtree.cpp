// RBtree.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>   
#include"RBtree.h"     
using namespace std;

int main()
{
	RBtree tree;
	cout << "Insert 9 numbers:" << endl;
	int a[9] = { 8,11,17,15,6,1,22,25,27 };
	int i;
	for (i = 0; i<9; i++)
	{
		tree.Insert(a[i]);
	}
	//RBtreeNode *node= tree.Search(a[3]);
	//tree.Preorder(node);
	cout << "Delete 11:" << endl;
	tree.Delete(11);
	cout << "blackHeight:" << tree.GetBlackHeight(tree.Getroot()) << endl;
	system("pause");
	return 0;
}


