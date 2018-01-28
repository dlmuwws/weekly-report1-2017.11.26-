// MulticommodityNFP.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std ;
#include<ilcplex\ilocplex.h>

#include<vector>
#include"sp.h"

int dijkstra(vector<vector<int>> &graph, int start_vertex, int end_vertex, vector<int> &path);
int main()
{
	vector<int> row(vexnum, INF);
	vector<vector<int>> graph(vexnum, row);
	for (int i = 0; i < vexnum; i++)
		graph[i][i] = 0;

	graph[0][1] = 8;
	graph[1][0] = 8;
	graph[1][3] = 2;
	graph[0][3] = 25;
	graph[0][2] = 4;
	graph[2][3] = 9;
	graph[3][2] = 9;



/*	int k1 = dijkstra(graph, 0, 3, path1);
	int k2 = dijkstra(graph, 1, 3, path2);
	int k3 = dijkstra(graph, 1, 2, path3);
	cout << "the cost of dijkstra:" << k1 <<"," << k2 << "," << k3  <<endl;*/
	IloEnv  env;
	IloModel model(env);

	//  cplex.test();
	/*	IloEnv env;

	IloInt i, j;
	IloNum rollwidth;
	IloNumArray _size(env);
	IloNumArray _demand(env);

	IloModel cutmodel(env);
	IloObjective rollsused = IloAdd(cutmodel, IloMinimize(env));
	IloRangeArray sizenum = IloAdd(cutmodel, IloRangeArray(env, _demand, IloInfinity));
	IloNumVarArray cut(env);
	IloInt nwidth = _size.getSize();
	IloCplex cutsolver(cutmodel);

	IloModel patternmodel(env);
	IloObjective Reducedcost = IloAdd(patternmodel, IloMinimize(env, 1));
	IloNumVarArray use(env, nwidth, 0.0, IloInfinity, ILOINT);
	patternmodel.add(IloScalProd(_size, use) <= rollwidth);
	IloCplex patternsolver(patternmodel);
	IloNumArray price(env, nwidth);
	IloNumArray newpattern(env, nwidth);

	for (;;) {
	cutsolver.solve();
	for (i = 0; i < nwidth; i++) {
	price[i] = -cutsolver.getDual(sizenum[i]);

	}*/


	IloNumVarArray x(env);
	IloRangeArray c(env);
	IloNumVarArray flow(env);
	flow.add(IloNumVar(env, 0.0, IloInfinity));
	flow.add(IloNumVar(env, 0.0, IloInfinity));
	flow.add(IloNumVar(env, 0.0, IloInfinity));
	IloObjective cost = IloMinimize(env, 25 * flow[0] + 33 * flow[1] + 42 * flow[2]);
	//model.add(IloMinimize(env, 25*flow[0] + 33*flow[1] + 42*flow[2]));
	/*	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));
	x.add(IloNumVar(env, 0.0, IloInfinity));*/
	//	model.add(IloMinimize(env, 25 * x[0] + 33 * x[1] + 42 * x[2] + 10 * x[3] + 2 * x[4] + 11 * x[5] + 13 * x[6] + 21 * x[7] + 12 * x[8]));

	c.add(flow[0] == 10);
	c.add(flow[1] == 11);
	c.add(flow[2] == 12);
	c.add(0 * flow[0] + 0 * flow[1] + 0 * flow[2] <= 13);
	c.add(0 * flow[0] + 0 * flow[1] + 0 * flow[2] <= 15);

	model.add(c);
	model.add(cost);
	IloCplex cplex(model);
	cplex.exportModel("lpex1.lp");

	// Optimize the problem and obtain solution.
	if (!cplex.solve()) {
		env.error() << "Failed to optimize LP" << endl;
		throw(-1);
	}

	IloNumArray vals(env);
	IloNumArray dualprice(env);
	env.out() << "Solution status = " << cplex.getStatus() << endl;
	env.out() << "Solution value  = " << cplex.getObjValue() << endl;
	cplex.getValues(vals, flow);
	env.out() << "Values        = " << vals << endl;
	cplex.getSlacks(vals, c);
	env.out() << "Slacks        = " << vals << endl;
	cplex.getDuals(dualprice, c);
	env.out() << "Duals         = " << dualprice << endl;
	cplex.getReducedCosts(vals, flow);
	env.out() << "Reduced Costs = " << vals << endl;


	graph[0][2] += dualprice[3];
	graph[1][3] += dualprice[4];
	vector<int> path1(vexnum, -1);
	vector<int> path2(vexnum, -1);
	vector<int> path3(vexnum, -1);
	vector<int> k(3);
	k[0] = dijkstra(graph, 0, 3, path1);
	k[1] = dijkstra(graph, 1, 3, path2);
	k[2] = dijkstra(graph, 1, 2, path3);
//	cout << "the cost of dijkstra:" << k1 <<"," << k2 << "," << k3  <<endl;
	IloNumVarArray cut(env);
	for (int j = 0; j < 3; j++) {
		cut.add(IloNumVar(cost(k[j]) + c[j](1)));
		
	}
	c[3].setLinearCoef(cut[0], 0);
	c[3].setLinearCoef(cut[1], 0);
	c[3].setLinearCoef(cut[2], 0);
	c[4].setLinearCoef(cut[0], 1);
	c[4].setLinearCoef(cut[1], 1);
	c[4].setLinearCoef(cut[2], 1);
	model.add(c);
	model.add(cost);
	IloCplex cplex1(model);
	cplex1.exportModel("lpex1.lp");

	// Optimize the problem and obtain solution.
	if (!cplex1.solve()) {
		env.error() << "Failed to optimize LP" << endl;
		throw(-1);
	}

	IloNumArray vals1(env);
	IloNumArray dualprice1(env);
	env.out() << "Solution status = " << cplex1.getStatus() << endl;
	env.out() << "Solution value  = " << cplex1.getObjValue() << endl;
	cplex1.getValues(vals, flow);
	env.out() << "Values        = " << vals1 << endl;
	cplex1.getSlacks(vals, c);
	env.out() << "Slacks        = " << vals1 << endl;
	cplex1.getDuals(dualprice, c);
	env.out() << "Duals         = " << dualprice1 << endl;
	cplex1.getReducedCosts(vals, flow);
	env.out() << "Reduced Costs = " << vals1 << endl;
	
	env.end();
	system("pause");
	return 0;
	
}

