#pragma once

#include<vector>
#include<fstream>
#include<string>
#include<limits.h>
#include<float.h>
using namespace std;

class WareHouse {
private:
	int x, y,demand, fac_index;
	bool isNew,isSetable;
	double storagef, movef,localf, tmf;

public:
	
	WareHouse(int xv, int yv) :x(xv), y(yv), demand(0), fac_index(0), isNew(false),isSetable(false), storagef(DBL_MAX), movef(DBL_MAX),localf(DBL_MAX), tmf(0.0) {}
	
	void setD(int dv) {demand=dv ; };
	void setFIndex(int i) { fac_index = i; };

	int getX() { return x; };
	int getY() { return y; };
	int getD() { return demand; };
	int getfIndex() { return fac_index; };

	void setnew(int f) {
		if (f = 1)
			isNew = true;
		else
			isNew = false;
	};

	bool New() { return isNew; };
	bool Y() { return isSetable; };//是否可以建立？

	void setSf(float s) { storagef = s; };
	void setMf(float m) { movef = m; };
	void setlocalf(float f) { localf = f; };
	void setY(bool b) { isSetable=b; };
	void setTMf(double mf) { tmf = mf; };

	double getSf() { return storagef; };
	double getMf() { return movef; };
	double getlof() { return localf; };
	double getTMf() { return tmf; };
};

class Factory {
private:
	int x, y, production,demand;
	bool isNew;
	double producef,storagef, movef, storage_limit;

public:
	//构造函数
	Factory(int xv, int yv) :x(xv), y(yv), production(0), demand(0),isNew(false), producef(DBL_MAX), storagef(DBL_MAX), movef(DBL_MAX), storage_limit(0) {}

	void setD(int dv) { demand = dv; };
	void setP(int pv) { production = pv; };
	

	int getX() { return x; };
	int getY() { return y; };
	int getD() { return demand; };
	int getP() { return production; };
	

	void setnew(int f) {
		if (f = 1)
			isNew = true;
		else
			isNew = false;
	};

	bool New() { return isNew; };

	void setSf(float s) { storagef = s; };
	void setMf(float m) { movef = m; };
	void setPf(float p) { producef=p; };
	void setlim(float lim) { storage_limit =lim; };
	

	double getSf() { return storagef; };
	double getMf() { return movef; };
	double getPf() { return producef; };
	double getlim() { return storage_limit; };
	
};

class Customer {
private:
	int x, y, demand,warehouse_index;
	double mf;

public:
	Customer(int xv, int yv) :x(xv), y(yv), demand(0),warehouse_index(0),mf(0.0) {}

	void setD(int dv) { demand = dv; };
	void setWarehoueIndex(int dv) { warehouse_index = dv; };
	void setTmf(double tmf) { mf=tmf; };
	
	int getX() { return x; };
	int getY() { return y; };
	int getD() { return demand; };
	int getWarehouseIndex() { return warehouse_index; };
	double getTotalTranportCost() { return mf; }
};

//用于输入的函数
vector<WareHouse>* InputWH();
vector<Factory>* InputFac();
vector<Customer>* InputCus();
