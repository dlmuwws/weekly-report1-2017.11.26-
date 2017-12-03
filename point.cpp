#include"stdafx.h"
#include "point.h"


point::point(int x, int y) :
	_x(x), _y(y)
{
}
point::point() {

}

int point::getType(pair<int, int>position) {
	int type = 0;
	int land1size = 32;
	int land2size = 14;
	int land3size = 8;
	int coast1size = 39;
	int coast2size = 14;
	int coast3size = 10;
	vector<float> land1x = { 450,410,410,310,280,220,220,210,210,160,160,
		150,150,90,90,110,110,130,130,170,200,200,260,
		310,360,360,380,410,410,450,450,490 };
	vector<float> land1y = { 170,170,190,230,250,250,200,200,220,220,190,
		190,250,190,220,220,330,350,330,370,370,320,320,
		270,270,220,240,240,260,260,200,200 };
	vector<float> land2x = { 320,320,270,270,230,230,210,180,150,150,180,180,270,290 };
	vector<float> land2y = { 130,90,90,50,50,70,70,40,40,70,100,140,140,160 };
	vector<float> land3x = { 0 ,30,30,60,60,100,130,0 };
	vector<float> land3y = { 290,290,340,340,390,390,421,421 };
	vector<float> coast1x = { 450,420,330,330,300,300,265,265,230,230,200,200,170,
		170,140,140,80,70,70,100,100,120,120,140,140,170,
		210,210,270,310,370,370,400,460,460,500,520,520,480 };
	vector<float> coast1y = { 110,150,150,170,170,220,220,235,235,190,190,210,210,
		180,180,230,170,170,230,230,340,360,380,380,350,380,
		380,345,345,295,295,240,280,280,220,260,260,150,110 };
	vector<float> coast2x = { 330,330,280,280,220,220,180,140,140,170,170,260,280,300 };
	vector<float> coast2y = { 140,70,70,30,30,60,20,20,70,100,150,150,170,170};
	vector<float> coast3x = { 0,60,60,40,40,70,70,110,150,0 };
	vector<float> coast3y = { 280,280,300,300,330,330,380,380,421,421 };

	if (isInpolygon(land1size, land1x, land1y, position.first, position.second)|| isInpolygon(land2size, land2x, land2y, position.first, position.second)
	|| isInpolygon(land3size, land3x, land3y, position.first, position.second))
	{
		type = 1;
	}
	if (isInpolygon(coast1size, coast1x, coast1y, position.first, position.second) || isInpolygon(coast2size, coast2x, coast2y, position.first, position.second)
		|| isInpolygon(coast3size, coast3x, coast3y, position.first, position.second)) {
		if (type != 1) {
			type = 2;
		}
	}
	else {
			type = 3;
		}
	
	return type;
}
int point::isInpolygon(int n, vector<float> polyX, vector<float> polyY, float x, float y) {
	int   i, j = n - 1;
	bool  oddNodes = 0;

	for (i = 0; i<n; i++) {
		if (polyY[i]<y && polyY[j] >= y
			|| polyY[j]<y && polyY[i] >= y) {
			if (polyX[i] + (y - polyY[i]) / (polyY[j] - polyY[i])*(polyX[j] - polyX[i])<x) {
				oddNodes = !oddNodes;
			}
		}
		j = i;
	}

	return oddNodes;
}