0
  Fork 0 dlmuwws/exercise3
 Code  Issues 0  Pull requests 0  Projects 0  Wiki  Insights  Settings
Branch: master Find file Copy pathexercise3/test.cpp
1593852  6 hours ago
@dlmuwws dlmuwws make a singly linked list
1 contributor
RawBlameHistory
50 lines (37 sloc)  781 Bytes
#include "linked_list.h"
#include<stdio.h>
#include <iostream>
using namespace std;
int main()
{
	node node1;
	node1.data = 3;
	linked_list *list=new linked_list();


	node node2;
	node2.data = 4;
	node node3;
	node3.data = 5;
	node node4;
	node4.data = 6;

	list->node_headinsert(&node1);
	list->node_headinsert(&node2);
	list->node_headinsert(&node3);
	list->node_headinsert(&node4);

	list->list_traverse();       //遍历结果6 5 4 3



	list->clearlist();

	//node node1;
	node1.data = 3;
	//node node2;
	node2.data = 4;
	//node node3;
	node3.data = 5;
	list->node_headinsert(&node1);
	list->node_headinsert(&node2);
	list->node_headinsert(&node3);

	node take_node;
	list->getnode(2, &take_node);
	cout << endl;
   cout << take_node.data<< endl;


	getchar();

	return 0;
}
