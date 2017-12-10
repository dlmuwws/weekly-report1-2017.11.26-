#include<stdio.h>
#include<string>
using namespace std;

class param
{
public:

	//t maxtime;
	static int max_x ;
	static int max_y;
	static int max_index;
	static int safty_wind;
	static int flytime ;
	void setmax_x() { max_x = 3; };
	void setmax_y(){ max_y = 4;};
	void setmax_index() {max_index = 12;};
	void setsafty_wind() { safty_wind = 15; };
	void setflytime() {flytime = 2;};
};
