#include <iostream>
#include <fstream>
#include <string>
#include "forecast.h"
#include <vector>
#include<algorithm>
using namespace std;
#define TXTPATH "D:/data/单天多模型同行_day6-10/"

void readforecast();
void init();
bool cmp(forecast* &a, forecast* &b);
vector<forecast*> _forelist;

int main()
{
	readforecast();
	init();
	system("pause");
	return 0;
}

void readforecast() {
	string filename = TXTPATH + string("reProcess_day10_R10.csv");
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
	//double measure = 0;
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
		//token = strtok_s(NULL, ",", &temp);
		//measure = atof(token);
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

		forecast* newfore = new forecast(x, y, dateno, time, speed5);
		_forelist.push_back(newfore);
		//			cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
	}

file.close();
sort(_forelist.begin(), _forelist.end(), cmp);
cout<< "success stage1" << endl;
}
	void init() {
		ofstream outFile;

		outFile.open("day10model5.csv", ios::out);
		cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		cout << "size:" << _forelist.size() << endl;
		int acc = 0;
		int loc = 0;
		for (int i = 0; i < _forelist.size(); i++) {
			pair<int, int> position(_forelist[i]->getX(), _forelist[i]->getY());
			loc = _forelist[i]->getType(position);
			acc = _forelist[i]->getDay4Accuracy(position);
			outFile << _forelist[i]->getX() << "," << _forelist[i]->getY() <<  "," << _forelist[i]->getTime() << "," << _forelist[i]->getSpeed() << "," << acc << "," << loc  << endl;

		}

		outFile.close();
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

