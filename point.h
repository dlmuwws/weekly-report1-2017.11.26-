
#include<vector>
using namespace std;



class point
{
private:
	int x;
	int y;    
	int index;   //点的标号
	int state;  //访问状态
	vector <point*>cangotopoints_;  
	vector <point*>adjcentpoints_;

public:
	point();
	int get_x() { return x; };
	int get_y() { return y; };
	int getindex(int x, int y);
	void setstate(int a) { state = a;}
	int getstate() { return state;}
	void set_pointlist(vector<point *>points);
	vector<point> get_adjcentpoints();
	void pushCanGoToBlock(point*point);
	vector<point*> getCangoTopoints() { return cangotopoints_;}
};
