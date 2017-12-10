#include "point.h"
#include<queue>
#include<vector>
#include<stdio.h>
#include"list.h"
using namespace std;


class marked_point                //在搜索过程中给点做标记
{
private:
	point*point_;
	int index;      //这个点标号
	int front_point_index;    //上个点的标号
	int time1;          //第一次遍历到这个点的时间
	int time2;         //访问这个点的时间  由于某一点某时刻的风速原因，以及队列先进先出，导致time1与time2可能不相等

public:
	marked_point(point*point_);
	void settime1(int time) { time1 = time; };
	void settime2(int time) { time2 = time; };
	void setindex(point*point_) { index = point_->getindex; };
	void setfront_point_index(point*point_) { front_point_index= point_->getindex; };
	int gettime1() { return time1; };
	int gettime2() { return time2; };
	int getindex() { return index; };
	int getfront_point_index() { return front_point_index; };
};
