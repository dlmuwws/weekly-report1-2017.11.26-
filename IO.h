#pragma once
#include "forecast.h"
#define TXTPATH "D:/data_suyi/read/"
#include "cityinfo.h"
#include"insitu.h"
#include<vector>
#include"schedule.h"

class IO 
{
public:
	IO();
	void readInfo(schedule*sche);
	void readCityInfo(vector<cityinfo*>_citylist);
	void readForecast(schedule*sche);
	void readInsitu(schedule*sche);

};