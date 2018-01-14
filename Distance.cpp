#include"Util.h"
#include<iostream>
#include<math.h>
#include<limits.h>
using namespace std;

#define revise_coefficient 1  //迂回系数
#define sevice_level 300  //服务水平(miles)
#define sale_mutiplier  1//销售量乘数

//距离：工厂到仓库
double getDistance(WareHouse p1, Factory p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*revise_coefficient;
}

//距离：仓库到顾客
double getDistance(WareHouse p1, Customer p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*revise_coefficient;
}

//距离：工厂到顾客
double getDistance(Factory p1, Customer p2) {
	return sqrt((p1.getX - p2.getX)*(p1.getX - p2.getX) + (p1.getY - p2.getY)*(p1.getY - p2.getY))*revise_coefficient;
}

//运费：工厂到仓库	
double getFreight(WareHouse wh, Factory fac) {
	return ((0.92 + 0.0034*(getDistance(wh, fac))));
}

//运费：仓库到顾客
double getFreight(WareHouse wh, Customer cus) {
	double d = getDistance(wh, cus);
	return (d < 30 ?wh.getlof () : (5.45 + 0.0037*d));
}

//生产成本
double TotalProductionCost(vector<Factory>*fac) {
	double tpc(0.0);
	for (int i = 0; i < fac->size(); ++i) {
		if ((*fac)[i].New())
			tpc += 4000000 + (*fac)[i].getD()*(*fac)[i].getPf();
		else
			tpc += (*fac)[i].getD()*(*fac)[i].getPf();

	}
	return tpc;
}

//库存成本
double TotalStorageCost(vector<WareHouse>*wh) {
	double tsc(0.0);
	for (int i = 0; i < wh->size(); ++i) 
		tsc += 35.3*pow(((*wh)[i].getD()),0.58);
	//35.3=0.12*26*11.3
	return tsc;
}

//单库存持有成本
double StorageCost(WareHouse wh) {
	double sc(0.0);
		sc = 35.3*pow((wh.getD()), 0.58);
	//35.3=0.12*26*11.3
	return sc;
}

//仓库运作成本
double TotalOperationCost(vector<WareHouse> *wh) {
	double tsc(0.0),thc(0.0);
	for (int i = 0; i < wh->size(); ++i) {
		tsc += (*wh)[i].getSf() * 26 * 11.3*pow(((*wh)[i].getD()), 0.58);
		thc += (*wh)[i].getMf()*((*wh)[i].getD());
	}

	return tsc + thc;
}

//单库存运作成本
double OperationCost(WareHouse wh) {
	double sc(0.0), hc(0.0);
		sc = wh.getSf() * 26 * 11.3*pow((wh.getD()), 0.58);
		hc = wh.getMf()*(wh.getD());

		return sc + hc;
	}




//最短距离的仓库
pair<double,int> getMinDistance(const vector<double> &d) {
	pair<double, int> min(DBL_MAX, 0);
	for (int i = 0; i < d.size(); ++i) {
		if (d[i] < min.first) {
			min.first = d[i];
			min.second = i;
		}
	}
	return min;
}


//最小运费的仓库
int index_of_Minmf(const vector<double>& f) {
	double min(DBL_MAX);
	int index(0);
	for (int i = 0; i < f.size(); ++i) {
		if (f[i] < min) {
			min = f[i];
			index = i;
		}
	}
	return index;
}

//客户需求分配
void AllocateCustomerDemand(vector<Customer>&cus,vector<WareHouse>&wh) {
	
	for (int i = 0; i < cus.size(); ++i) {
		
		vector<WareHouse> temp,tempWithin;
		vector<double> tempd;
		vector<double> tempFrieght;
			
		for (int j = 0; j < wh.size(); ++j) {
			double d = getDistance(wh[j], cus[i]);
			tempd.push_back(d);
			double f = getFreight(wh[j], cus[i]);
			
			if (d < sevice_level) {
				tempWithin.push_back(wh[j]);
				tempFrieght.push_back(f);
				temp.push_back(wh[j]);
			}
			else
				temp.push_back(wh[j]);
		}
		
		if (!tempWithin.empty()&&!tempFrieght.empty()) {
			int index = index_of_Minmf(tempFrieght);
			int tempdemand = wh[index].getD();
			wh[index].setD(tempdemand + cus[i].getD());	
			cus[i].setWarehoueIndex(index);
			cus[i].setTmf(cus[i].getD()*getFreight(wh[index], cus[i]));
		}
		else {
			int index = getMinDistance(tempd).second;
			int tempdemand = wh[index].getD();
			wh[index].setD(tempdemand + cus[i].getD());
			cus[i].setWarehoueIndex(index);
			cus[i].setTmf(cus[i].getD()*getFreight(wh[index], cus[i]));
		}
	}
}

//仓库需求分配
void AllocateWarehouseDemand(vector<WareHouse> &wh,vector<Factory> &fac) {

	//由于工厂到仓库采取整车补货，装卸成本较低因此采用比例运价，即选择最近的工厂补货

	for (int i = 0; i < wh.size(); ++i) {

		vector<Factory> temp;
		vector<double> tempd;

		for (int j = 0; j < fac.size(); ++j) {
			double d = getDistance(wh[i], fac[j]);
			tempd.push_back(d);
            temp.push_back(fac[j]);
		}

		int index = getMinDistance(tempd).second;
	    int tempdemand = fac[index].getD();
		fac[index].setD(tempdemand + wh[i].getD());
		wh[i].setFIndex(index);
		wh[i].setTMf(wh[i].getD()*getFreight(wh[i], fac[index]));
		
	}

}

//生成参与单纯形法的变量新工厂和仓库的布尔值作为0-1变量
vector<pair<Factory, bool>> NewFactory( vector<Factory>fac) {
	vector<pair<Factory, bool>> nf;
	
	for (int i = 0; i < fac.size(); ++i) {
		if (fac[i].New() == 1) {
			pair<Factory, bool> np(fac[i],1);
			nf.push_back(np);
		} 
	}
}

vector<pair<WareHouse, bool>> NewWarehouse(vector<WareHouse>wh) {
	vector<pair<WareHouse, bool>> nw;

	for (int i = 0; i < wh.size(); ++i) {
		if (wh[i].New() == 1) {
			pair<WareHouse, bool> np(wh[i], 1);
			nw.push_back(np);
		}
	}
}

//判断是否可以建造
void setSetable(vector<WareHouse> &wh) {
	for (int i = 0; i < wh.size(); i++) {
		if (wh[i].getD() >= 10400)
			wh[i].setY(1);
	}
}
