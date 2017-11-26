#pragma once
#include<iostream>
#include<vector>
using namespace std;
#include<array>

class point {
private:
	int _x;
	int _y;

public:
	point();
	point(int x, int y);
	void setX(int x) {
		_x = x;
	}
	int  getX() {
		return _x;
	}
	void setY(int y) {
		_y = y;
	}
	int getY() {
		return _y;
	}
};