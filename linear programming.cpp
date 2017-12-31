#include <ilcplex/ilocplex.h>
#include<iostream>
using namespace std;

int main(int argc, char **argv)
{
	IloEnv env;
	try {
		IloModel model(env);
		/*
		//行添加

		IloNumVarArray vars(env);
		vars.add(IloNumVar(env));
		vars.add(IloNumVar(env));                    //缺省时默认0-正无穷
		vars.add(IloNumVar(env));
		model.add(IloMinimize(env, -2 * vars[0] + 3 * vars[1] - 7 * vars[2]));   //添加目标函数
		/*
		model.add(vars[0] + vars[1] + 2 * vars[2] <= 3);           //添加约束
		model.add(vars[0] - vars[1] <= 2);
		model.add(-vars[1] + vars[2] <= 1);

		//or
		IloRangeArray constraints(env);
		constraints.add(IloRange(env, vars[0] + vars[1] + 2 * vars[2], 3,"c1"));        //添加约束
		constraints.add(IloRange(env,vars[0] -vars[1], 2,"c2"));
		constraints.add(IloRange(env,  -vars[1] + vars[2],1,"c3"));
		model.add(constraints);
		*/

		//列添加
		IloRangeArray constraints(env);
		constraints.add(IloRange(env, -IloInfinity, 3.0, "constraint1"));        //建立空约束
		constraints.add(IloRange(env, -IloInfinity, 2.0, "constraint2"));
		constraints.add(IloRange(env, -IloInfinity, 1.0, "constraint3"));

		IloObjective obj(env,IloMinimize(env));

		IloNumVarArray vars(env);
		vars.add(IloNumVar(obj(-2)+constraints[0](1)+constraints[1](1)+constraints[2](0)));                //默认变量范围为0—Infinit
		vars.add(IloNumVar(obj(3) + constraints[0](1) + constraints[1](-1) + constraints[2](-1)));
		vars.add(IloNumVar(obj(-7) + constraints[0](2) + constraints[1](0) + constraints[2](1)));

		model.add(constraints);
		model.add(obj);
		model.add(vars);

		IloCplex cplex(model);
		if (!cplex.solve()) {
			env.error() << "Failed to optimize LP." << endl;
			throw(-1);
		}

		IloNumArray vals(env);
		env.out() << "Solution status = " << cplex.getStatus() << endl;
		env.out() << "Solution value = " << cplex.getObjValue() << endl;
		cplex.getValues(vals, vars);
		env.out() << "Values = " << vals << endl;
		cplex.exportModel("model.lp");
	}
	catch (IloException& e) {
		cerr << "Concert exception caught: " << e << endl;
	}
	catch (...) {
		cerr << "Unknown exception caught" << endl;
	}

	env.end();
	system("pause");
	return 0;
}
