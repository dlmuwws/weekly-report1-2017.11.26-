#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include<vector>


class forecast {
private:
	int _x;
	int _y;
	int _dateno;
	int _time;
	double _speed;
public:
	void setX(int x) { _x = x; }
	int getX() { return _x; }
	void setY(int y) { _y = y; }
	int getY() { return _y; }
	void setDateNo(int dateno) { _dateno = dateno; }
	int getDateNo() { return _dateno; }
	void setTime(int time) { _time = time; }
	int getTime() { return _time; }
	void setSpeed(double speed) { _speed = speed; }
	double getSpeed() { return _speed; }
	forecast(int x, int long y, int dateno, int time, double speed);
	void print();
	int isInpolygon(int n, vector<float> polyX, vector<float> polyY, float x, float y);
	int getType(pair<int, int>position);
	int getDay1Accuracy(pair<int, int>position);
	int getDay2Accuracy(pair<int, int>position);
	int getDay3Accuracy(pair<int, int>position);
	int getDay4Accuracy(pair<int, int>position);
	int getDay5Accuracy(pair<int, int>position);
};
