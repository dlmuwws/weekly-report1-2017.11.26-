
#include<vector>
#include<array>
#include<stdio.h>
using namespace std; 



class point              // 每个点的基本信息：位置，编号，访问状态，时间—风速，相邻点(有连接的点)
{
private:
	int x;
	int y;    
	int index;   //点的标号
	int state;  //访问状态
	array<int,18> wind;      //(3:00-21:00)
	//vector <point>cangotopoints_;  
	vector <point>adjcentpoints_;
	pair<int, int>time_wind_;

public:                             
	point();
	int get_x() { return x; };
	int get_y() { return y; };
	int getindex(int x, int y);
	int get_wind_(point*point_);
	int time_wind_.first();
	void setstate(int a) { state = a;}
	int getstate() { return state;}
	vector<point> get_adjcentpoints();


};

