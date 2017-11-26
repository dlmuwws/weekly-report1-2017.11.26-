#include<stdio.h>
using namespace std;

class node
{
public:
	int data;    //数据域
	node *next;   //地址域(指针域)
	node();
	void print();
};
