#include "stdafx.h"
#include"insitu.h"
#include<iostream>
using namespace std;




insitu::insitu(int x, int long y, int dateno, int time, double speed) :
	_x(x), _y(y), _dateno(dateno), _time(time), _speed(speed)
{
}

void insitu::print() {
	cout << "#In-situInfo :";
	cout << "\tX " << _x << "\tY " << _y << "\tdateno " << _dateno << "\ttime " << _time << "\tspeed " << _speed;
	cout << "\n";

}