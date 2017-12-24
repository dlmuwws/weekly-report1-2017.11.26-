#include"stdafx.h"
#include "mycplex.h"  



MyCplex::MyCplex()
{
	model = IloModel(env, "myCplex");
	vars = IloNumVarArray(env);
	constraints = IloRangeArray(env);
}


MyCplex::~MyCplex()
{
	env.end();
}


void MyCplex::test()
{
	//objective = IloAdd(model, IloMaximize(env));

	/*By column*/

/*	constraints.add(IloRange(env, 0, 20, "constraint_1"));
	constraints.add(IloRange(env, 0, 30, "constraint_2"));

	model.add(constraints);

	IloNumArray parameters(env, 2);
	parameters[0] = -1;
	parameters[1] = 1;
	vars.add(IloNumVar(objective(1) + constraints(parameters), 0, 40, ILOFLOAT, "var_1"));

	vars.add(IloNumVar(objective(2) + constraints[0](1) + constraints[1](-3), 0, IloInfinity, ILOFLOAT, "var_2"));

	vars.add(IloNumVar(objective(3) + constraints[0](1) + constraints[1](1), 0, IloInfinity, ILOFLOAT, "var_3"));

	model.add(vars);*/
    /*By Row*/

/*	vars.add(IloNumVar(env, 0.0, 40.0));
	vars.add(IloNumVar(env));
	vars.add(IloNumVar(env));

	model.add(IloMaximize(env, vars[0] + 2 * vars[1] + 3 * vars[2]));

	constraints.add(-vars[0] + vars[1] + vars[2] <= 20.0);
	constraints.add(vars[0] - 3 * vars[1] + vars[2] <= 30.0);
	vars[0].setName("x1");
	vars[1].setName("x2");
	vars[2].setName("x3");
	model.add(constraints);*/

	addcoef();
	cplex = IloCplex(model);
	cplex.solve();
	IloNumArray values(env);
	cplex.out() << "solution status:" << cplex.getStatus() << endl;
	cplex.out() << "objective value:" << cplex.getObjValue() << endl;
	cplex.getValues(values, vars);
	cplex.out() << "Values: " << values << endl;
	cplex.exportModel("model.lp");

}

void MyCplex::addbyrow()
{
//	IloEnv env =model.getEnv();
//	IloNumVarArray x;
//	IloRangeArray constraint;
	vars.add(IloNumVar(env,0.0, 40.0));
	vars.add(IloNumVar(env));
	vars.add(IloNumVar(env));

	model.add(IloMaximize(env, vars[0] + 2 * vars[1] + 3 * vars[2]));

	constraints.add(-vars[0] + vars[1] + vars[2] <= 30.0);
	constraints.add(vars[0] - 3 * vars[1] + vars[2] <= 20.0);
	vars[0].setName("x1");
	vars[1].setName("x2");
	vars[2].setName("x3");
	model.add(constraints);
}
void MyCplex::addcoef() {
	IloObjective obj =IloMaximize(env);
	constraints.add(IloRange(env, -IloInfinity, 20));
	constraints.add(IloRange(env, -IloInfinity, 30));

	vars.add(IloNumVar(env, 0.0, 40.0));
	vars.add(IloNumVar(env));
	vars.add(IloNumVar(env));

	obj.setLinearCoef(vars[0], 1);
	obj.setLinearCoef(vars[1], 2);
	obj.setLinearCoef(vars[2], 3);

	constraints[0].setLinearCoef(vars[0], -1);
	constraints[0].setLinearCoef(vars[1], 1);
	constraints[0].setLinearCoef(vars[2], 1);
	constraints[1].setLinearCoef(vars[0], 1);
	constraints[1].setLinearCoef(vars[1], -3);
	constraints[1].setLinearCoef(vars[2], 1);

	constraints[0].setName("c1");
	constraints[1].setName("c2");

	vars[0].setName("x1");
	vars[1].setName("x2");
	vars[1].setName("x3");

	model.add(obj);
	model.add(constraints);
}