#include"Util.h"
#include<iostream>
#include<math.h>
using namespace std;

#define reviseefficient 1  //迂回系数

//工厂到仓库
double getDistance(WareHouse p1, Factory p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*reviseefficient;
}

//仓库到顾客
double getDistance(WareHouse p1, Customer p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*reviseefficient;
}

//工厂到顾客
double getDistance(Factory p1, Customer p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*reviseefficient;
}

//运费：工厂到仓库	
double getFreight(WareHouse wh, Factory fac) {
	return ((0.92 + 0.0034*(getDistance(wh, fac)))*wh.getD());
}

//运费：仓库到顾客
double getFreight(WareHouse wh, Customer cus) {
	double d = getDistance(wh, cus);
	return (d < 30 ?wh.getlof ()*cus.getD() : (5.45 + 0.0037*d)*cus.getD());
}

double TotalProductionCost(vector<Factory>*fac) {
	double tpc(0.0);
	for (int i = 0; i < fac->size(); ++i) {
		if ((*fac)[i].New())
			tpc += 4000000 + (*fac)[i].getD()*(*fac)[i].getPf;
		else
			tpc += (*fac)[i].getD()*(*fac)[i].getPf;

	}
	return tpc;
}