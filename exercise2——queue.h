#pragma once
#include "customer.h"

class queue
{
private:    //成员变量
	customer *q;               //数组指针
	int queue_len;  //长度
	int queue_cap;  //容量
	int head; //队头
	int tail;  //队尾

public:      //成员函数
	queue(int n);  //构造函数
	void clearqueue();         //清空队列
	bool queue_empty();     //判空
	bool queue_full();         //判满
	int get_queue_len();     //队列长度
	bool in_queue(customer element);           //入队
	bool out_queue(customer &element);         //出队
	void queue_traverse();  //遍历队列
};
