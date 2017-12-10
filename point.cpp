#include "point.h"
#include<stdio.h>
#include"list.h"
using namespace std;

point::point()
{
	int x=1;
	int y=1;
	int index=1;
	int state=0;
}

int point::getindex(int x,int y)
{
	int max_x = 4; int max_y = 3; int max_index = 12;   //假设现在只有12个点
	if (x <= 0 || x > max_x)           //x:1-4
	{
		return -1;
	}
	if (y <= 0 || y > max_y)          //y:1-3
	{
		return -1;
	}
	int index = (y - 1)*max_x + x;
	if (index > max_index)
	{
		return -1;
	}
	return index;
}

pair<int,int> point::get_the_time_wind_(vector<pair<int, int>>time_wind_, int time)
{
	pair<int,int> the_time_wind_ = time_wind_.at(time);
	return the_time_wind_;
}


vector <point*>point::get_adjcentpoints(point* point_)
{
	    list*pointlist;
		int x = point_->get_x();
		int y = point_->get_y();

		int index = point_->getindex(x - 1, y);      //左
		if (index !=-1)
		{
			point_->pushadjcentpoint(pointlist->getpoint(index));
		}

		int index = point_->getindex(x +1, y);     //右
		if (index != -1)
		{
			point_->pushadjcentpoint(pointlist->getpoint(index));
		}

		int index = point_->getindex(x , y+1);   //上
		if (index != -1)
		{
			point_->pushadjcentpoint(pointlist->getpoint(index));
		}

		int index = point_->getindex(x , y-1);  //下
		if (index != -1)
		{
			point_->pushadjcentpoint(pointlist->getpoint(index));
		}
}


vector<pair<int, int>>point::set_time_wind_(int a)     //a 表示有几组数据
{
	int time = 0;
	for (int i=1;i<=a;i++)
	{
		time_wind_.at(i).first = time;
		time_wind_.at(i).second = 10+rand() % 10;     //随机生成10-20内的数
		time = time + 2;
	}
}
