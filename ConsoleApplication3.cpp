// ConsoleApplication3.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"mycplex.h"
#include<ilcplex/ilocplex.h>
using namespace std;

void readData(const char* filename, IloNum& rollWidth,
	IloNumArray& size, IloNumArray& amount);

void report1(IloCplex &cutsolver, IloNumVarArray cut, IloRangeArray sizenum);

void report2(IloCplex& patSolver, IloNumVarArray Use,IloObjective obj);

void report3(IloCplex& cutSolver, IloNumVarArray Cut);

int main()
{
//	MyCplex cplex;
//  cplex.test();
	IloEnv env;
	try {
		IloInt i, j;
		IloNum rollwidth;
		IloNumArray _size(env);
		IloNumArray _demand(env);
		readData("cutstock.dat",
			rollwidth, _size, _demand);
 		
		IloModel cutmodel(env);
		/*MP:浪费最小化，等价于所有patterns用的25寸木头的最小化*/
		IloObjective rollsused = IloAdd(cutmodel, IloMinimize(env));
		/*Constraints：每种尺寸的木头数要大于客户的需求，sizenum>=demand*/
		IloRangeArray sizenum = IloAdd(cutmodel,IloRangeArray(env,_demand, IloInfinity));
		IloNumVarArray cut(env);
		/*增加一个新的变量，也就是新的列向量，加到obj function （新未知数系数为1）和 constraints(新未知数系数为rollwith/size，目的是制造初始可行解)当中*/
		IloInt nwidth = _size.getSize();
		for (j = 0; j < nwidth; j++) {
			cut.add(IloNumVar(rollsused(1) + sizenum[j](int(rollwidth / _size[j]))));
		}
		IloCplex cutsolver(cutmodel);

		/*SP：MAX Zj-Cj,因为所有Cj为1，在这里采用Min 1-Zj,*/
		IloModel patternmodel(env);
		IloObjective Reducedcost = IloAdd(patternmodel, IloMinimize(env,1));
		IloNumVarArray use(env, nwidth, 0.0, IloInfinity, ILOINT);
		/*对于每一个长度为17英寸的木材，3x1+5x2+7x3<=17*/
		patternmodel.add(IloScalProd(_size, use) <= rollwidth);
		IloCplex patternsolver(patternmodel);
		/*dual*/
		IloNumArray price(env,nwidth);
		/*新产生的列*/
		IloNumArray newpattern(env, nwidth);

		for (;;) {
			cutsolver.solve();
			/*解一次MP*/
			report1(cutsolver, cut, sizenum);
			for (i = 0; i < nwidth; i++) {
				/*求dual---wj*/
				price[i] = -cutsolver.getDual(sizenum[i]);
				
			}
			/*将wj传给sub problem*/
			Reducedcost.setLinearCoefs(use, price);
			patternsolver.solve();

			report2(patternsolver, use, Reducedcost);
			/*当cj-zj>=0时，opt*/
			if (patternsolver.getValue(Reducedcost) >= 0) break;
			/*获得aj*/
			patternsolver.getValues(newpattern,use);
			/*加入新的列向量*/
			cut.add(IloNumVar(rollsused(1) + sizenum(newpattern)));
		}
		cutmodel.add(IloConversion(env, cut, ILOINT));
		cutsolver.solve();
		report3(cutsolver, cut);


	}
	catch(IloException &ex){
		cerr << "Error: " << ex << endl;
	}
	catch (...) {
		cerr << "Error " << endl;
	}
	env.end();
	system("pause");
	return 0;
}
/*读数据*/
void readData(const char* filename, IloNum& rollWidth,
	IloNumArray& size, IloNumArray& amount)
{
	ifstream in(filename);
	if (in) {
		in >> rollWidth;
		in >> size;
		in >> amount;
	}
	else {
		cerr << "No such file: " << filename << endl;
		throw(1);
	}
}

void report1(IloCplex &cutsolver, IloNumVarArray cut, IloRangeArray sizenum) {
	/*共用了多少根17英寸木头*/
	cout << "Total rolls:" << cutsolver.getObjValue() << endl;
	
	for (IloInt i = 0; i < cut.getSize(); i++) {
		cout << "cut" << i << "=" << cutsolver.getValue(cut[i]) << endl;
	}
	for (IloInt j = 0; j < sizenum.getSize(); j++) {
		cout << "the num of "<< j<<"th size:" << cutsolver.getDual(sizenum[j]) << endl;
	}
}

void report2(IloCplex& patSolver, IloNumVarArray Use,
	IloObjective obj)
{
	cout << endl;
	cout << "Reduced cost is " << patSolver.getValue(obj) << endl;
	cout << endl;
	if (patSolver.getValue(obj) <= 0) {
		for (IloInt i = 0; i < Use.getSize(); i++) {
			cout << "  Use" << i << " = " << patSolver.getValue(Use[i]) << endl;
		}
		cout << endl;
	}
}

void report3(IloCplex& cutSolver, IloNumVarArray Cut)
{
	cout << endl;
	cout << "Best integer solution uses "
		<< cutSolver.getObjValue() << " rolls" << endl;
	cout << endl;
	for (IloInt j = 0; j < Cut.getSize(); j++) {
		cout << "  Cut" << j << " = " << cutSolver.getValue(Cut[j]) << endl;
	}
}