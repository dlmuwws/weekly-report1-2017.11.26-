#include"point.h"
#include"marked_point.h"
#include<vector>
#include<queue>
using namespace std;



class BFS
{
private:
	point *source;             //起点
	point *destination;      //终点
	queue<marked_point*> ingvisitpoints;    //待访问队列
	vector<marked_point*>visitedpoints;     //访问过的点
	vector<point*>bestroute;        //最短路径
public:
	BFS();
	point* getsource(){return source; };
	//void clearqueue(queue<marked_point*>& q);   //清空queue
	void push_ingvisitpoint(marked_point*point_) { ingvisitpoints.push(point_); };
	queue<marked_point*>getingvisitpoints() { return ingvisitpoints; };
	void push_visitedpoint(marked_point*point_) { visitedpoints.push_back(point_); };
	vector<marked_point*>getvisitedpoints() { return visitedpoints; };
	void push_bestroute(point*point_) { bestroute.push_back(point_); };
	vector<point*>getbestroute(point*source_, point*destination_);
	void print(vector<point*>bestroute_);
};
