#pragma once
#include"Util.h"

double getDistance(WareHouse p1, Factory p2);
double getDistance(WareHouse p1, Customer p2);
double getDistance(Factory p1, Customer p2);
double getFreight(WareHouse wh, Factory fac);
double getFreight(WareHouse wh, Customer cus);
double TotalProductionCost(vector<Factory>*fac);
double TotalStorageCost(vector<WareHouse>*wh);
double TotalOperationCost(vector<WareHouse> *wh);
pair<double, int> getMinDistance(const vector<double> &d);
int index_of_Minmf(const vector<double>& f);
void AllocateCustomerDemand(vector<Customer>&cus, vector<WareHouse>&wh);
void AllocateWarehouseDemand(vector<WareHouse> &wh, vector<Factory> &fac);
vector<pair<Factory, bool>> NewFactory(vector<Factory>fac);
vector<pair<WareHouse, bool>> NewWarehouse(vector<WareHouse>wh);
void setSetable(vector<WareHouse> &wh);
double StorageCost(WareHouse wh);
double OperationCost(WareHouse wh);