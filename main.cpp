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
#include"allmodel.h"
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
vector<allmodel*>_alllist;
int main()
{	
	
	readforecast_new();
//	readforecast();
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
	string filename = TXTPATH + string("day5.csv");
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
	int loc = 0;
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
	int count = 0;
	int numcount = 1;
	int random = 0;
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
	//	dateno = atoi(token);
	//	token = strtok_s(NULL, ",", &temp);
		time = atoi(token);
		token = strtok_s(NULL, ",", &temp);
	//	measure = atof(token);
	//	token = strtok_s(NULL, ",", &temp);
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
		token = strtok_s(NULL, ",", &temp);
		loc = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		measure = atof(token);
		//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
	//	mergelist* newmerge = new mergelist(x, y, time, speed5, 0, 0, measure);
	//	_mergelist.push_back(newmerge);//读单模型
			//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
		if((numcount%18) ==1){
			random = (rand() % 18) + 3;
			cout <<numcount<<","<< random<<endl;
		}
		if (time == random) {
			allmodel* newall = new allmodel(x, y, time, speed1, speed2, speed3, speed4, speed5, speed6, speed7, speed8, speed9, speed10, loc,measure);
		_alllist.push_back(newall);

	}
		numcount++;
	}
	file.close();
//	sort(_forelist.begin(), _forelist.end(), cmp);
	cout << "success stage1" << endl;
	/*		for (int i = 0; i < _forelist.size(); i++)
	{
	_forelist[i]->print();
	}*/

}
void readforecast() {
	string filename = TXTPATH + string("reProcess_day7_R10.csv");
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
	int loc = 0;
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
	//int numcount = 0;
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
		//	mergelist* newmerge = new mergelist(x, y, time, speed5, 0, 0, measure);
		//	_mergelist.push_back(newmerge);//读单模型
		//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
			allmodel* newall = new allmodel(x, y, time, speed1, speed2, speed3, speed4, speed5, speed6, speed7, speed8, speed9, speed10, loc,measure);
			_alllist.push_back(newall);

		//numcount++;
	}
	file.close();
	//	sort(_forelist.begin(), _forelist.end(), cmp);
	cout << "success stage1" << endl;
	}
void init() {
	ofstream outFile;

	outFile.open("day5select.csv", ios::out);
	cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "size:" <<_alllist.size() << endl;
	int acc = 0;
	int loc = 0;
/*	for (int i = 0; i < _mergelist.size(); i++) {
		pair<int, int> position(_mergelist[i]->getX(), _mergelist[i]->getY());
		loc = _mergelist[i]->getType(position);
		acc = _mergelist[i]->getDay5Accuracy(position);
		outFile << _mergelist[i]->getX() << "," << _mergelist[i]->getY() << "," << _mergelist[i]->getTime()<<","<< _mergelist[i]->getSpeed() <<","<<acc<<","<<loc<<","<< _mergelist[i]->getMeasure()<< endl;
	//	cout << i << endl;
	}*//*单模型考虑准确度分布acc*/
	for (int i = 0; i < _alllist.size(); i++) {
		pair<int, int> position(_alllist[i]->getX(), _alllist[i]->getY());
		loc = _alllist[i]->getType(position);
		outFile << _alllist[i]->getX() << "," << _alllist[i]->getY() << "," << _alllist[i]->getSpeed1() << "," << _alllist[i]->getSpeed2() << "," << _alllist[i]->getSpeed3() << "," << _alllist[i]->getSpeed4() << "," << _alllist[i]->getSpeed5() << "," << _alllist[i]->getSpeed6() << "," << _alllist[i]->getSpeed7() << "," << _alllist[i]->getSpeed8() << "," << _alllist[i]->getSpeed9() << "," << _alllist[i]->getSpeed10()<< "," << loc << ","<<_alllist[i]->getMeasure()<< endl;
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
