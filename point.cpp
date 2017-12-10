#include "point.h"
#include<stdio.h>
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

vector <point>point::get_adjcentpoints()
{

}

int point::get_wind_(point*point_)
{
	int wind = point_->time_wind_.second();
}
