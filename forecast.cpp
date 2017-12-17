#include <vector>
#include"forecast.h"
#include<iostream>
using namespace std;




forecast::forecast(int x, int long y, int dateno, int time, double speed) :
	_x(x), _y(y), _dateno(dateno), _time(time), _speed(speed)
{
}

void forecast::print() {
	cout << "#ForecastInfo :";
	cout << "\tX " << _x << "\tY " << _y << "\tdateno " << _dateno << "\ttime " << _time << "\tspeed " << _speed;
	cout << "\n";

}
int forecast::getType(pair<int, int>position) {
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
	vector<float> coast2y = { 140,70,70,30,30,60,20,20,70,100,150,150,170,170 };
	vector<float> coast3x = { 0,60,60,40,40,70,70,110,150,0 };
	vector<float> coast3y = { 280,280,300,300,330,330,380,380,421,421 };

	if (isInpolygon(land1size, land1x, land1y, position.first, position.second) || isInpolygon(land2size, land2x, land2y, position.first, position.second)
		|| isInpolygon(land3size, land3x, land3y, position.first, position.second))
	{
		type = 3;
	}
	if (isInpolygon(coast1size, coast1x, coast1y, position.first, position.second) || isInpolygon(coast2size, coast2x, coast2y, position.first, position.second)
		|| isInpolygon(coast3size, coast3x, coast3y, position.first, position.second)) {
		if (type != 3) {
			type = 2;
		}
	}
	else {
		type = 1;
	}

	return type;
}
int forecast::isInpolygon(int n, vector<float> polyX, vector<float> polyY, float x, float y) {
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
int forecast::getDay1Accuracy(pair<int, int>position) {
	int type = 0;
	int blank = 0;
	int oneflr1size = 3;
	int oneflr2size = 8;
	int twoflr1size = 9;
	int twoflr2size = 4;
	int twoflr3size = 28;
	int twoflr4size = 4;
	int twoflr5size = 14;
	int oneflr3size = 3;
	vector<float> oneflr1x = { 175,190,210 };
	vector<float> oneflr1y = { 210,180,210 };
	vector<float> oneflr2x = { 280,275,340,360,370,380,360,330 };
	vector<float> oneflr2y = { 150,120,80,90,70,70,110,150 };
	vector<float> twoflr1x = { 0,10,10,40,85,80,110,140,0 };
	vector<float> twoflr1y = { 90,90,50,100,90,50,50,0,0 };
	vector<float> twoflr2x = { 175,140,190,210 };
	vector<float> twoflr2y = { 0,70,40,0 };
	vector<float> twoflr3x = { 320,350,350,380,380,390,390,370,400,420,430,460,460,470,430,400,390,280,280,270,260,240,210,140,100,80,0,0 };
	vector<float> twoflr3y = { 421,360,320,250,260,260,200,170,130,150,150,120,20,0,0,10,0,0,90,100,70,70,100,100,140,120,120,421 };
	vector<float> twoflr4x = { 500,500,515,515 };
	vector<float> twoflr4y = { 0,30,30,0 };
	vector<float> twoflr5x = { 548,530,530,490,480,470,460,460,440,440,390,400,370,548 };
	vector<float> twoflr5y = { 20,20,80,180,180,160,170,210,230,250,350,360,421,421 };
	vector<float> oneflr3x = { 548,520,548 };
	vector<float> oneflr3y = { 360,400,310 };

	if (isInpolygon(oneflr1size, oneflr1x, oneflr1y, position.first, position.second) || isInpolygon(oneflr2size, oneflr2x, oneflr2y, position.first, position.second)
		|| (isInpolygon(oneflr3size, oneflr3x, oneflr3y, position.first, position.second)))
	{
		blank = 1;
	}
	if (isInpolygon(twoflr1size, twoflr1x, twoflr1y, position.first, position.second) || isInpolygon(twoflr2size, twoflr2x, twoflr2y, position.first, position.second)
		|| isInpolygon(twoflr3size, twoflr3x, twoflr3y, position.first, position.second) || isInpolygon(twoflr4size, twoflr4x, twoflr4y, position.first, position.second)
		|| isInpolygon(twoflr5size, twoflr5x, twoflr5y, position.first, position.second)) {
		if (blank != 1) {
			type = 1;
		}
	}


	return type;
}
int forecast::getDay2Accuracy(pair<int, int>position) {
	int type = 0;
	int flr1size = 4;
	int flr2size = 7;
	int flr3size = 55;
	int flr4size = 7;
	int flr5size = 24;
	vector<float> flr1x = { 0,0,20,40 };
	vector<float> flr1y = { 420,400,400,420 };
	vector<float> flr2x = { 0,10,50,50,30,20,0 };
	vector<float> flr2y = { 130,130,105,70,55,90,100 };
	vector<float> flr3x = { 250,260,260,190,170,160,170,160,140,110,90,90,60,45,20,
		50,70,90,100,130,130,150,170,180,220,230,190,170,90,70,
		70,50,370,330,280,260,300,340,350,390,370,370,330,300,330,
		330,350,360,350,360,360,350,350,310,320 };
	vector<float> flr3y = { 421,390,360,280,300,300,270,250,260,260,270,240,240,250,230,
		220,180,180,190,170,200,180,180,160,190,160,140,150,60,70,
		20,0,0,40,40,100,120,65,80,90,110,140,150,170,
		200,160,180,210,230,250,270,270,330,410,421 };
	vector<float> flr4x = { 360,360,370,360,410,410,380 };
	vector<float> flr4y = { 421,390,380,310,330,350,421 };
	vector<float> flr5x = { 425,460,440,440,460,450,450,470,480,500,
		510,510,500,490,520,548,548,540,540,520,
		548,548,525,530,510 };
	vector<float> flr5y = { 421,350,350,280,260,220,170,170,190,190,160,
		130,80,35,0,0,20,20,90,200,185,
		390,421,350,421 };



	if (isInpolygon(flr1size, flr1x, flr1y, position.first, position.second) || isInpolygon(flr2size, flr2x, flr2y, position.first, position.second)
		|| isInpolygon(flr3size, flr3x, flr3y, position.first, position.second) || isInpolygon(flr4size, flr4x, flr4y, position.first, position.second)
		|| isInpolygon(flr5size, flr5x, flr5y, position.first, position.second)) {
		type = 1;

	}


	return type;
}


int forecast::getDay3Accuracy(pair<int, int>position) {
	int type = 0;
	int flr1size = 9;
	int flr2size = 3;
	int flr3size = 4;
	int flr4size = 11;
	int flr5size = 13;
	int flr6size = 5;
	vector<float> flr1x = { 0, 60, 80, 55, 55, 95, 106, 160, 0 };
	vector<float> flr1y = { 160,160,210,210,220,290,290,421,421 };
	vector<float> flr2x = { 240, 310, 230 };
	vector<float> flr2y = { 250,250,400 };
	vector<float> flr3x = { 290,338,370,290 };
	vector<float> flr3y = { 340,340,421,421 };
	vector<float> flr4x = { 360,360,390,460,548,548,500,470,475,435,380 };
	vector<float> flr4y = { 250,270,280,421,421,280,260,260,275,255,240 };
	vector<float> flr5x = { 548,548,400,360,290,270,240,210,155,185,225,310,430 };
	vector<float> flr5y = { 210,250,220,190,210,190,190,210,20 ,20 ,100,100,200 };
	vector<float> flr6x = { 380,410,530,548,548 };
	vector<float> flr6y = { 0,40,125,125,0 };

	if (isInpolygon(flr1size, flr1x, flr1y, position.first, position.second) || isInpolygon(flr2size, flr2x, flr2y, position.first, position.second)
		|| isInpolygon(flr3size, flr3x, flr3y, position.first, position.second) || isInpolygon(flr4size, flr4x, flr4y, position.first, position.second)
		|| isInpolygon(flr5size, flr5x, flr5y, position.first, position.second) || isInpolygon(flr6size, flr6x, flr6y, position.first, position.second)) {
		type = 1;

	}


	return type;
}
int forecast::getDay4Accuracy(pair<int, int>position) {
	int type = 0;

	int sets1_size = 4;
	int sets2_size = 5;
	int sets3_size = 16;
	int sets4_size = 3;

	vector<float>sets1_x = { 40,80,140,60 };
	vector<float>sets2_x = { 60,60,170,170,100 };
	vector<float>sets3_x = { 0,0,40,0,0,40,40,80,170,170,210,200,548,548,510,490 };
	vector<float>sets4_x = { 393,410,410 };
	vector<float>sets1_y = { 400,400,420,420 };
	vector<float>sets2_y = { 290,320,390,370,290 };
	vector<float>sets3_y = { 0,60,90,90,300,270,245,220,250,270,340,421,421,76,50,0 };
	vector<float>sets4_y = { 270,270,230 };


	if (isInpolygon(sets1_size, sets1_x, sets1_y, position.first, position.second) || isInpolygon(sets2_size, sets2_x, sets2_y, position.first, position.second) || isInpolygon(sets3_size, sets3_x, sets3_y, position.first, position.second))
	{
		if (!isInpolygon(sets4_size, sets4_x, sets4_y, position.first, position.second))
		{
			type = 1;
		}
	}
	return type;
}
int forecast::getDay5Accuracy(pair<int, int>position) {
	int type = 0;

	int sets1_size = 4;
	int sets2_size = 48;
	vector<float>sets1_x = { 0,20,20,0 };
	vector<float>sets2_x = { 0,50,90,120,150,180,200,140,140,190,220,200,220,320,320,340,340,400,270,310,365,548,548,
		531,527,548,548,515,490,425,390,390,180,180,160,140,130,130,120,105,83,83,60,80,80,60,30,0 };
	vector<float>sets1_y = { 400,400,420,420 };
	vector<float>sets2_y = { 220,250,230,250,230,240,230,180,140,140,190,220,250,260,300,300,330,380,340,395,420,421,33,33,17,17,0,0,
		20,30,30,0,0,20,20,0,0,80,80,0,0,13,30,50,80,80,40,0 };

	if (isInpolygon(sets1_size, sets1_x, sets1_y, position.first, position.second) || isInpolygon(sets2_size, sets2_x, sets2_y, position.first, position.second))
	{
		type = 1;
	}
	return type;
}
