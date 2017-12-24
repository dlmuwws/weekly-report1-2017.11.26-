#pragma once
#include<ilcplex/ilocplex.h>  
#include<iostream>
using namespace std;
class MyCplex
{
private:
	IloEnv env;

	IloModel model;
	IloCplex cplex;

	IloObjective objective;
	IloNumVarArray vars;
	IloRangeArray constraints;

public:
	MyCplex();
	void test();
	~MyCplex();
	void addbyrow();
	void addcoef();
};