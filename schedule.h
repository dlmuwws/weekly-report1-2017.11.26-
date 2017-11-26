#pragma once
#include"insitu.h"
#include<vector>
#include"forecast.h"
#include<iostream>
using namespace std;
#include"point.h"
#include<map>
class schedule{
private:
	vector<insitu*> _insitulist;
	vector<forecast*>_pointlist;
	map<point*, vector<double>> _maps;

public:
	schedule();
	map<point*, vector<double>> getmaps() {
		return _maps;
	}
	void setmaps(map<point*, vector<double>>maps) {
		_maps = maps;
	}
	vector<insitu*>getinsitu() { return _insitulist; }
	void setinsitu(vector<insitu*>insitulist) { _insitulist = insitulist; }
	void setfore(vector<forecast*>forelist) { _pointlist = forelist; }
	vector<forecast*>getfore() { return _pointlist; }
};