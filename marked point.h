#include "point.h"
#include<queue>
#include<vector>
#include<stdio.h>
using namespace std;


class marked_point                //给搜索过程中的点做标记
{
private:
	point *point_;
	queue<point*>ingvisit_point;    //将要访问的点的队列  (有入队出队操作)
	vector<marked_point*>visited_point;  //储存访问点的顺序
	point *front_point;
	//pair<int, int>time_wind_;
	int time1;      //第一次遍历到这个点的时间
	int time2;     //访问这个点的时间  由于某一点某时刻的风速原因，以及队列先进先出，导致time1与time2可能不相等

public:
	marked_point(point *point_);
	int gettime1() { return time1; };
	int gettime2() { return time2; };
	void setfrontpoint(point*_frontpoint) {front_point = _frontpoint;};
	pair<int, int>get_time_wind_(point*nextpoint);
        queue <point>get_ingvisit_point(point *point_);
	void push_ingvisit_point(point*nextpoint);    //将可行的下个点放进要访问的队列，插入队尾
	void getvisited_point(queue<point*>ingvisit_point);     //队列头出队，设为visited_point; 下一步插入visited_point的vector
	void pushvisited_point(marked_point*visited_point);   //用pushback函数将新访问的点插入；



};
