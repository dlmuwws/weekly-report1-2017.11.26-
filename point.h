#include<vector>
#include<stdio.h>
using namespace std;



class point              // 每个点的基本信息：位置，编号，访问状态，时间—风速，相邻点(有连接的点)
{
private:
	int x;
	int y;
	int index;             //点的标号
	int state;             //访问状态
	vector<pair<int, int>>time_wind_;   //时刻风速
	vector<point*>adjcentpoints;

public:
	point();
	int get_x() { return x; };
	int get_y() { return y; };
	int getindex(int x, int y);

	vector<pair<int, int>>set_time_wind_(int a);
	vector<pair<int, int>>get_time_wind() { return time_wind_; }
	pair<int,int> get_the_time_wind_(vector<pair<int, int>>time_wind_,int time);     //输入time 得到一组time_wind_
	void setstate(int a) { state = a;}
	int getstate() { return state;}
	void pushadjcentpoint(point*point_) { adjcentpoints.push_back(point_); };
	vector<point*> get_adjcentpoints(point*point_);
};
