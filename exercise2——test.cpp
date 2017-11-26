#include "queue.h"
#include<stdio.h>
#include <iostream>
using namespace std;

int main()
{
	queue *q = new queue(5);      //创建队列

	customer c1("王xx",20);
	customer c2("李x",24);
	customer c3("张xx",22);
	customer c4("徐x",30);
	customer c5("刘xx",32);
	q->in_queue(c1);                  //插入元素
	q->in_queue(c2);
	q->in_queue(c3);
	q->in_queue(c4);
	q->in_queue(c5);
	q->queue_traverse();           //遍历

	cout << endl;
	customer  e;
	q->out_queue(e);               //取出元素
	e.print();


	q->out_queue(e);              //再次取出一个元素
	e.print();

	cout << endl;
	q->queue_traverse();           //再次遍历

	q->clearqueue();                      //清空
	q->queue_traverse();

	cout << endl;
	q->in_queue(customer("黄x",30));            //再次插入
	q->in_queue(customer("朱x", 30));
	q->queue_traverse();

	getchar();               //保留结果
	return 0;
}
