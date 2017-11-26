#include "stdafx.h"
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include "forecast.h"
#include <vector>
#include "IO.h"
#include"cityinfo.h"
#include"insitu.h"
#include"schedule.h"

IO::IO() {

}
void IO::readInfo(schedule* sche) {
	vector<cityinfo*> _citylist;
	vector<forecast*> _forelist;
	vector<insitu*>_insitulist;
//	vector<point>coordinate;
//	readCityInfo(_citylist);
	readInsitu(sche);
//	readForecast(sche);
}
void IO::readCityInfo(vector<cityinfo*>_citylist)
{
	string filename = TXTPATH + string("CityData.csv");
	ifstream file;
	file.open(filename.c_str());
	cout << "#Read city information from " << filename << "\n";
	string buff;
	char* token;
	char* temp;
	int cid = 0;
	int x = 0;
	int y = 0;

	getline(file, buff);
	while (!file.eof())
	{
		getline(file, buff);
		token = strtok_s((char*)buff.c_str(), ",", &temp);
		cid = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		x = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		y = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		cityinfo* newcity = new cityinfo(cid,x, y);
		_citylist.push_back(newcity);
		

	}
	file.close();
	for (int i = 0; i < _citylist.size(); i++)
	{
		_citylist[i]->print();
	}

}
void IO::readForecast(schedule*sche)
{ 
	vector<forecast*> _forelist = sche->getfore();
	string filename = TXTPATH + string("ForecastDataforTraining.csv");
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
	
	getline(file, buff);
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
		modelno = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		speed = atof(token);
		if(dateno == 1)
		{
			forecast* newfore = new forecast(x, y, dateno, time, modelno, speed);
			_forelist.push_back(newfore); 
		}
		
	//	cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tmodelno " << modelno << "\tspeed " << speed << endl;
	}
	sche->setfore(_forelist);
	file.close();
/*	for (int i = 0; i < _forelist.size(); i++)
	{
		_forelist[i]->print();
	}*/

}
void IO::readInsitu(schedule*sche)
{
	map<point*, vector<double>> maps = sche->getmaps();
	vector<double> list;
	vector<insitu*>_insitulist = sche->getinsitu();
	string filename = TXTPATH + string("In-situMeasurementforTraining.csv");
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
	getline(file, buff);
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
			point* newpoint = new point(x, y);
			maps[newpoint].push_back(speed);
			insitu* newinsitu = new insitu(x, y, dateno, time, speed);
			_insitulist.push_back(newinsitu);
			
//		cout << "\tX " << x << "\tY " << y << "\tdateno " << dateno << "\ttime " << time << "\tspeed " << speed << endl;
	}
	sche->setinsitu(_insitulist);
	sche->setmaps(maps);
	file.close();
/*	for (int i = 0; i < _insitulist.size(); i++)
	{
		_insitulist[i]->print();
	}*/
	
}