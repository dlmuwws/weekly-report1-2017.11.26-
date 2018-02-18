#pragma once
#include <iostream>   
#include <vector>  
using namespace std;
class TreeNode {
public:
	int key;
	TreeNode* left;
	TreeNode* right;
	TreeNode* p;//指向父节点   
public:
	TreeNode();
	TreeNode(int val);
};
