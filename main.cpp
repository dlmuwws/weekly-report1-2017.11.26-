// Data_process.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "forecast.h"
#include <vector>
#include<algorithm>
#include"insitu.h"
#define TXTPATH "D:/data_suyi/read/"

void readforecast();
void init();
bool cmp(forecast* &a, forecast* &b);
void readmeasure();
bool cmp_measure(insitu* &a, insitu* &b);
vector<forecast*> _forelist;
vector<insitu*> _insitulist;
int main()
{	
	
	readforecast();
	readmeasure();
	init();
	system("pause");
    return 0;
}

void readforecast() {
		string filename = TXTPATH + string("test1.csv");
		ifstream file;
		file.open(filename.c_str());
		cout << "#Read geo information from " << filename << "\n";
		string buff;
		char* token;
		char* temp;
		int x = 0;
		int y = 0;
		int dateno = 0;
		int time = 0;
		int modelno = 0;
		double speed = 0;
		char a;
		getline(file, buff);
		cout << buff << endl;
		while (!file.eof())
		{
			getline(file, buff);
			if (buff == "")
				continue;
			token = strtok_s((char*)buff.c_str(), ",", &temp);
			x = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			y = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			dateno = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			time = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			modelno = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			speed = atof(token);
//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
//			if (dateno == 1 && modelno == 5) {
				forecast* newfore = new forecast(x, y, dateno, time, modelno, speed);
				_forelist.push_back(newfore);
	//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
//			}
		}
		file.close();
		sort(_forelist.begin(), _forelist.end(), cmp);
		cout << "success stage1" << endl;
/*		for (int i = 0; i < _forelist.size(); i++)
		{
			_forelist[i]->print();
		}*/

	}
void init() {
	ofstream outFile;

	outFile.open("practise.csv", ios::out);
	cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "size:" << _forelist.size() << endl;
	int acc = 0;
	int loc = 0;
	for (int i = 0; i < _forelist.size(); i++) {
		pair<int, int> position(_forelist[i]->getX(), _forelist[i]->getY());
		loc = _forelist[i]->getType(position);
		outFile << _forelist[i]->getX() << "," << _forelist[i]->getY() << "," <<_forelist[i]->getTime()<<","<< _forelist[i]->getSpeed() <<","<<acc<<","<<loc<<","<<_insitulist[i]->getSpeed()<< endl;
	}

	outFile.close();
}
void readmeasure() {

		string filename = TXTPATH + string("test_measure.csv");
		ifstream file;
		file.open(filename.c_str());
		cout << "#Read In-situ information from " << filename << "\n";
		string buff;
		char* token;
		char* temp;
		int x = 0;
		int y = 0;
		int dateno = 0;
		int time = 0;
		double speed = 0;
		int count = 0;
		while (!file.eof())
		{
			getline(file, buff);
			if (buff == "")
				continue;
			token = strtok_s((char*)buff.c_str(), ",", &temp);
			x = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			y = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			dateno = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			time = atoi(token);
			token = strtok_s(NULL, ",", &temp);
			speed = atof(token);
//			if (dateno == 1 ) {
				insitu* newinsitu = new insitu(x, y, dateno, time, speed);
				_insitulist.push_back(newinsitu);
				cout << x << "," << y << endl;
//			}
		}
		sort(_insitulist.begin(), _insitulist.end(), cmp_measure);
		file.close();


}
bool cmp(forecast* &a, forecast* &b) {
	 
		if (a->getX()< b->getX())
		return true;
	else if (a->getX() == b->getX())
	{
		if (a->getY() < b->getY())
			return true;
	}
		return false;
}
bool cmp_measure(insitu* &a, insitu* &b) {

	if (a->getX()< b->getX())
		return true;
	else if (a->getX() == b->getX())
	{
		if (a->getY() < b->getY())
			return true;
	}
	return false;
}