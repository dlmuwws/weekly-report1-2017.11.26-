#include"point.h"
#include<vector>

class list
{
public:

	vector<point*>pointlist;
	void setpointlist(vector<point*>points) { pointlist = points; };
	vector<point*> getpointlist() { return pointlist; };
	point* getpoint(int index);

};
