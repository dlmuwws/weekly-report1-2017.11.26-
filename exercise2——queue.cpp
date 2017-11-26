#include "queue.h"
//#include "stdio.h"
#include<iostream>
#include "customer.h"
using namespace std;


queue::queue(int n)  //实例化，初始化
{
	queue_cap = n;
	queue_len = 0;
	q = new customer[n];  //创建指针数组  %% customer 构造函数要初始化
	head = 0;
	tail = 0;
}

void queue::clearqueue()
{
	head = 0;
	tail = 0;
	queue_len = 0;
}

bool queue::queue_empty()
{
	if (queue_len == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool queue::queue_full()
{
	if (queue_len == queue_cap)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int queue::get_queue_len()
{
	return queue_len;
}

bool queue::in_queue(customer element)
{
	if (queue_full())
	{
		return false;
	}
	else
	{
		q[tail] = element;  //数组，元素的下标从0开始
		tail++;                 //尾指针向后移动一位
		tail = tail % queue_cap;    //防止越界
		queue_len++;      //队列长度增加1
		return true;
	}
}

bool queue::out_queue(customer &element)
{
	if (queue_empty())
	{
		return false;
	}
	else
	{
		element = q[head];   //取出当前队列第一个元素
		head++;                 //头指针向后移动一位
		head = head%queue_cap;    //防止越界
		queue_len--;      //队列长度减少1
		return true;
	}
}


void queue::queue_traverse()    //遍历队列
{
	for (int i = head; i<head + queue_len; i++)
	{
		int j = i%queue_cap;
		q[j].print();
	}
}
