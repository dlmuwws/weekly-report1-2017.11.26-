#include"point.h"
#include"marked_point.h"
#include<vector>
#include<queue>


class BFS
{
private:
	point *source;             //起点
	point *destination;      //终点
	queue<marked_point*> ingvisitpoints;   //待访问队列
	vector<marked_point*>visitedpoints;     //访问过的点
	vector<marked_point*>bestroute;        //最短路径
public:
	BFS(point *_source);
	point* getsource(){return source; };
	vector<marked_point*>getbestroute(point *destination);
	void clearqueue(queue<marked_point*>& q);   //清空queue
};
