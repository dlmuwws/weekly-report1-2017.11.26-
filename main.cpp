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
#include "mergelist.h"
#define TXTPATH "D:/data_suyi/read/"

void readforecast();
void readforecast_new();
void init();
bool cmp(forecast* &a, forecast* &b);
void readmeasure();
bool cmp_measure(insitu* &a, insitu* &b);
vector<forecast*> _forelist;
vector<insitu*> _insitulist;
vector<mergelist*>_mergelist;
int main()
{	
	
	readforecast_new();
//	readmeasure();
	init();
//	int x = 10;
//	int y = 410;
//	pair<int, int> position(x, y);
//	forecast* a = new forecast(x,y,0,0,0,0);
//	int acc;
//	acc = a->getDay5Accuracy(position);
//	cout << acc;
	system("pause");
    return 0;
}

void readforecast_new() {
	string filename = TXTPATH + string("reProcess_day5_R10.csv");
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
	double measure = 0;
	double speed1 = 0;
	double speed2 = 0;
	double speed3 = 0;
	double speed4 = 0;
	double speed5 = 0;
	double speed6 = 0;
	double speed7 = 0;
	double speed8 = 0;
	double speed9 = 0;
	double speed10 = 0;
	char a;
//	getline(file, buff);
//	cout << buff << endl;
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
		measure = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed1 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed2 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed3 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed4 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed5 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed6 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed7 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed8 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed9 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		speed10 = atof(token);
		//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
		mergelist* newmerge = new mergelist(x, y, time, speed5, 0, 0, measure);
		_mergelist.push_back(newmerge);
			//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
		
	}
	file.close();
	sort(_forelist.begin(), _forelist.end(), cmp);
	cout << "success stage1" << endl;
	/*		for (int i = 0; i < _forelist.size(); i++)
	{
	_forelist[i]->print();
	}*/

}
void readforecast() {
		string filename = TXTPATH + string("ForecastDataforTesting_201712.csv");
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
			if (dateno == 1 && modelno == 5) {
				forecast* newfore = new forecast(x, y, dateno, time, modelno, speed);
				_forelist.push_back(newfore);
	//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
			}
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

	outFile.open("day5model5.csv", ios::out);
	cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "size:" <<_mergelist.size() << endl;
	int acc = 0;
	int loc = 0;
	for (int i = 0; i < _mergelist.size(); i++) {
		pair<int, int> position(_mergelist[i]->getX(), _mergelist[i]->getY());
		loc = _mergelist[i]->getType(position);
		acc = _mergelist[i]->getDay5Accuracy(position);
		outFile << _mergelist[i]->getX() << "," << _mergelist[i]->getY() << "," << _mergelist[i]->getTime()<<","<< _mergelist[i]->getSpeed() <<","<<acc<<","<<loc<<","<< _mergelist[i]->getMeasure()<< endl;
	//	cout << i << endl;
	}

	outFile.close();
}
void readmeasure() {

		string filename = TXTPATH + string("In-situMeasurementforTraining_20171124.csv");
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
			if (dateno == 1 ) {
				insitu* newinsitu = new insitu(x, y, dateno, time, speed);
				_insitulist.push_back(newinsitu);
				cout << x << "," << y << endl;
			}
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