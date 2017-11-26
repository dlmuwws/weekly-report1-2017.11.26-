#include "node.h"
#include <iostream>

class linked_list
{
private:
	node*pnode;
	int list_length;
public:                         //全部公共访问
	node *head;              //头指针
	linked_list();   //构造函数
	void clearlist();           //清空链表
	bool isempty();           //判断是否为空
	int length();                //链表长度
	bool getnode(int i,node*take_node);  //拿出第i个节点
	void list_traverse();                             //遍历链表
    bool node_insert(int i,node*insertnode);   //插入新节点到i位置
	bool node_delete(int i, node*deletenode);   //删除节点I
	bool node_headinsert(node*insertnode);  //将pnode插入到头节点后
	bool node_tailinsert(node*insertnode); //尾插入
};
