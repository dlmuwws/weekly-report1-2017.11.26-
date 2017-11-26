// Map.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"IO.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include"forecast.h"
#include<map>

int main()
{ 
	IO* io = new IO();
	schedule*sche = new schedule();
	io->readInfo(sche);
//	vector<forecast*> points = sche->getfore();
//	vector<insitu*>insitulist = sche->getinsitu();
	map<point*, vector<double>> maps = sche->getmaps(); 
	map<point*, vector<double>>::iterator iter;
	for (iter = maps.begin(); iter != maps.end(); iter++) {
		cout << iter->first << endl;
	}

	system("pause");
	return 0;
//	cout << points.size() << endl;
//	cout << insitulist.size() << endl; 
}

