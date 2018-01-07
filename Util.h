#pragma once

#include<vector>
#include<fstream>
#include<string>
#include<limits.h>
#include<float.h>
using namespace std;

class WareHouse {
private:
	int x, y,demand;
	bool isNew;
	double storagef, movef,localf;

public:
	
	WareHouse(int xv, int yv) :x(xv), y(yv), demand(0), isNew(false), storagef(DBL_MAX), movef(DBL_MAX),localf(DBL_MAX){}
	
	void setD(int dv) {demand=dv ; };

	int getX() { return x; };
	int getY() { return y; };
	int getD() { return demand; };

	void setnew(int f) {
		if (f = 1)
			isNew = true;
		else
			isNew = false;
	};

	bool New() { return isNew; };		

	void setSf(float s) { storagef = s; };
	void setMf(float m) { movef = m; };
	void setlocalf(float f) { localf = f; };

	double getSf() { return storagef; };
	double getMf() { return movef; };
	double getlof() { return localf; };
};

class Factory {
private:
	int x, y, production,demand;
	bool isNew;
	double producef,storagef, movef, storage_limit;

public:
	Factory(int xv, int yv) :x(xv), y(yv), production(0), demand(0), isNew(false), producef(DBL_MAX), storagef(DBL_MAX), movef(DBL_MAX), storage_limit(0) {}

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
	int x, y, demand;

public:
	Customer(int xv, int yv) :x(xv), y(yv), demand(0) {}

	void setD(int dv) { demand = dv; };
	
	int getX() { return x; };
	int getY() { return y; };
	int getD() { return demand; };
	
};

