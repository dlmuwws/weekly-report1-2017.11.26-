#include"linked_list.h"
#include<iostream>
#include<stdio.h>
using namespace std;

linked_list::linked_list()
{
	pnode = new node;   //构造头节点
	pnode->data = 0;
	pnode->data=NULL;
	list_length=0;
}

bool linked_list::isempty()
{
	if (list_length ==0)
	{
		return true;
	}
	else
		return false;
}

int linked_list::length()
{
	return list_length;
}

void linked_list::clearlist()   //从头节点开始，找next，直到next 为NULL
{
	node*currentnode = pnode->next;
	while (currentnode->next!=NULL)   //当前节点
	{
		node*temp = currentnode->next;
		delete currentnode;   //删除当前节点
		currentnode = temp;
	}
	pnode->next = NULL;
	delete pnode;
}

bool linked_list::node_headinsert(node*insertnode)   //在头节点后插入新节点
{
	node *temp = pnode->next;   //将原来头节点后的节点储存起来
	node *newnode=new node;   //给要插入的新节点申请内存
	if (newnode == NULL)
	{
		return false;
	}
	newnode->data = insertnode->data;   //新节点的值等于传入的值
	pnode->next = newnode;   //新节点插入到头节点之后
	newnode->next = temp;     //原来的插入新节点之后
	list_length++;
	return true;
}
// 可以试一下指针的引用


bool linked_list::node_tailinsert(node*insertnode)
{
	node*currentnode = pnode;
	while (currentnode->next!=NULL)   //不是尾节点
	{
		currentnode = currentnode->next;   //往下个节点移
	}
	node*newnode = new node;
	if (newnode=NULL)
	{
		return false;
	}
	newnode->data = insertnode->data;
	currentnode->next = newnode;   // 此时的currentnode已经是尾节点，在其后面插入newnode
	newnode->next = NULL;
	list_length++;
	return true;
}

bool linked_list::node_insert(int i, node*insertnode)    //插入I节点之后
{
	if (i<0 || i>list_length)
	{
		return false;
	}
	node*temp = pnode;
	for (int k=0;k<i;k++)
	{
		temp = temp->next;       //i次循环找到第I 个节点
	 }
	node*newnode = new node;
	if (newnode = NULL)
	{
		return false;
	}
	newnode->data = insertnode->data;
	newnode->next = temp->next;
	temp->next = newnode;      //注意这两行的顺序不能颠倒
	list_length++;
	return true;
}

bool linked_list::node_delete(int i, node*deletenode)   //删除i节点后的下个节点
{
	if (i<0 || i>=list_length)        //不能=list_length
	{
		return false;
	}
	node*temp = pnode;
	node*tempbefore = NULL;    //找到要删除节点的上一个节点，再进行删除
	for (int k = 0; k<=i; k++)
	{
		tempbefore = temp;
		temp = temp->next;       //i+1次循环找到第I 个节点的下一个节点
	}
	tempbefore->next = temp->next;
	deletenode->data = temp->data;
	delete temp;
	temp = NULL;
	list_length--;
	return true;
}

bool linked_list::getnode(int i, node*take_node)
{
	if (i<0 || i >= list_length)
	{
		return false;
	}
	node*temp = pnode;
	node*tempbefore = NULL;
	for (int k = 0; k < i; k++)
	{
		tempbefore = temp;
		temp = temp->next;
	}
	take_node->data = temp->data;  //把找到的值存入take_node里
	return true;
}

void linked_list::list_traverse()     //遍历操作while循环
{
	node *temp = pnode;
	while (temp->next != NULL)
	{
		temp = temp->next;
		temp->print();
	}
}
