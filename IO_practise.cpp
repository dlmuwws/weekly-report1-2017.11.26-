// IO_practise.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>  
using namespace std;
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream> 
#include <vector>
#include"insitu.h"


#define TXTPATH "D:/data_suyi/read/"

void read(int time1);
void adding();
void init();
vector<insitu*>_insitulist;
int main()

{	
	int time = 3;
	read(time);
	init();
	time = 4;
	for (int i = 4; i < 21; i++) {
	_insitulist.clear();
	read(i);
	adding();
	}
	system("pause");
	return 0;
}
void read(int time1) {
	
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
	int count =0;
	while (!file.eof())
	{
		getline(file, buff);
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
		if (dateno == 1 && time == time1) {
			insitu* newinsitu = new insitu(x, y, dateno, time, speed);
			_insitulist.push_back(newinsitu);
		}
	}
	file.close();

}
void init() {
	ofstream outFile;

	outFile.open("data.csv", ios::out);
	cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	cout << "size:" << _insitulist.size() << endl;
	for (int i = 0; i < _insitulist.size(); i++) {
		outFile << _insitulist[i]->getX() << "," << _insitulist[i]->getY() << "," << _insitulist[i]->getSpeed() << endl;
	}

	outFile.close();
}
void adding() {
	vector<string> temp;
	cout << _insitulist.size() << endl;
	cout << _insitulist[0]->getSpeed() << endl;
	string filename = "data.csv";
	ifstream file;
	ofstream outFile;
	string line;
	int count = 0;
	file.open(filename.c_str());
	while (!file.eof()) {
		getline(file, line);
		temp.push_back(line);
	}
	file.close();
	outFile.open(filename.c_str());
	cout << "temp size:" << temp.size() << endl;
	for (int i = 0; i < temp.size(); i++) {
		if (count == temp.size()-1)
			continue;
		outFile << temp[i] <<"," << _insitulist[count]->getSpeed()<<endl;
		count++;
	}
	outFile.close();
}
