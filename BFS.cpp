#include"BFS.h"
#include"point.h"
#include"marked_point.h"
#include<stdio.h>
#include<queue>
#include"param.h"
using namespace std;



BFS::BFS(point *_source)
{
	source = _source;
}

void BFS::clearqueue(queue<marked_point*>& q) {
	queue<marked_point*> empty;
	swap(empty, q);
}

vector<marked_point*>BFS::getbestroute(point *destination)                //求解最短路径
{
	visitedpoints.clear();
	BFS::clearqueue(ingvisitpoints);
	source->setstate(1);
	marked_point*marked_source = new marked_point(source);               //给第一个点标记
	marked_source->setfrontpoint(NULL);
	ingvisitpoints.push(marked_source);                             //第一个点入队

	int des_X = destination->get_x();
	int des_Y = destination->get_y();

	 //开始搜索。。。

	bool p = false; //记录目的地有没有找到，找到则结束搜索
	marked_point * marked_destination = NULL;

	while (!ingvisitpoints.empty() && !p )//&&ingvisitpoints.front()->gettime1()<param::maxtime)
	{
		marked_point* temp = ingvisitpoints.front();


  }
point*source = new point();
//第一个点的状态变为待访问，并将它放入队列

source->setstate(1);
marked_point*source_markedpoint = new marked_point(source);
marked_point *frontpoint=source_markedpoint.setfront(NULL);
