// ConsoleApplication2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<map>
#include"point.h"
#include<vector>
#include"point.h"

int main()
{
	map<point*, double> mapping;
	map<point*, vector<double>> maps;
	vector<double> list;

	point* newpoint = new point(12, 12);
	list.push_back(12.0);
	list.push_back(15.0);
	mapping[newpoint] = 12.0;
	newpoint->setX (15);
	newpoint->setY ( 15);
	mapping[newpoint] = 123.0;
	maps[newpoint].push_back(20.0);

	maps[newpoint].push_back(30.0);


	vector<double>::iterator it;


	for (it = maps[newpoint].begin(); it != maps[newpoint].end(); it++)

		cout << *it << endl;
	
	system("pause");
    return 0;
}

