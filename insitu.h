#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>


class insitu {
private:
	int _x;
	int _y;
	int _dateno;
	int _time;
	double _speed;
public:
	insitu();
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
	insitu(int x, int long y, int dateno, int time, double speed);
	void print();
	};