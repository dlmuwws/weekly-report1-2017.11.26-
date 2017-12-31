#include<ilcplex/ilocplex.h>
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

void readdata(const char*filename,IloNumArray&lumber_size, IloNumArray&lumber_cost, IloNumArray&order_size, IloNumArray&order_amount);
static void report1(IloCplex& MP_Solver, IloNumVarArray cuts,IloRangeArray constraints);


int main(int argc,char**argv)
{
	IloEnv env;
	try
	{
		IloNumArray lumber_size(env); IloNumArray lumber_cost(env); IloNumArray order_size(env); IloNumArray order_amount(env);
		if (argc >1)
		{
			readdata(argv[1], lumber_size, lumber_cost, order_size, order_amount);
		}
		else
		{
			readdata("D:/data/data.txt", lumber_size, lumber_cost, order_size, order_amount);
		}
		cout << order_amount.getSize() << endl;
		cout << "ok" << endl;
		//建立MP的model
		IloModel MP(env);
		IloObjective obj_MP(env,IloMinimize(env));
		IloRangeArray constraints(env);
		constraints.add(IloRange(env, 30,IloInfinity,"constraint1"));
		constraints.add(IloRange(env, 20, IloInfinity, "constraint2"));
		constraints.add(IloRange(env, 40, IloInfinity, "constraint3"));
		IloNumVarArray cuts(env);                                  //整体的切割方案（每种lumber用几个）
		cuts.add(IloNumVar(obj_MP(5) + constraints[0](2)));
		cuts.add(IloNumVar(obj_MP(5) + constraints[1](1)));          //初始化的解
		cuts.add(IloNumVar(obj_MP(5) + constraints[2](1)));
		MP.add(obj_MP);
		MP.add(constraints);
		MP.add(cuts);
		IloCplex MP_solve(MP);
		//cout << "ok" << endl;

		IloInt size=order_amount.getSize();
		IloNum lb = 0.0;
		IloNum ub = IloInfinity;
		IloNumVarArray cuts_plan(env,size,lb,ub,ILOINT);     //每种lumber的切割方案
		IloNumArray dualprice(env,1,1,1);          //影子价格

		cout << "ok" << endl;
		//SP1     //行添加
		IloModel SP1(env);
		IloObjective obj_SP1(env, IloMaximize(env, IloScalProd(dualprice, cuts_plan) - lumber_cost[0]));
		SP1.add(obj_SP1);
		SP1.add(IloScalProd(order_size, cuts_plan) <= lumber_size[0]);
		IloCplex SP1_solve(SP1);
		//SP2
		IloModel SP2(env);
		IloObjective obj_SP2(env, IloMaximize(env, IloScalProd(dualprice, cuts_plan) - lumber_cost[1]));
		SP2.add(obj_SP2);
		SP2.add(IloScalProd(order_size, cuts_plan) <= lumber_size[1]);
		IloCplex SP2_solve(SP2);
		//SP3
		IloModel SP3(env);
		IloObjective obj_SP3(env, IloMaximize(env, IloScalProd(dualprice, cuts_plan) - lumber_cost[2]));
		SP3.add(obj_SP3);
		SP3.add(IloScalProd(order_size, cuts_plan) <= lumber_size[2]);
		IloCplex SP3_solve(SP3);

		for (;;)
		{
			MP_solve.solve();
			report1(MP_solve,cuts,constraints);

			//先求影子价格
			for (IloInt i = 0; i < order_size.getSize(); i++)
			{
				dualprice[i] = MP_solve.getDual(constraints[i]);
			}

			SP1_solve.solve(); SP2_solve.solve(); SP3_solve.solve();
			vector<IloNum>reduced_cost;
			reduced_cost.push_back(SP1_solve.getObjValue());
			reduced_cost.push_back(SP2_solve.getObjValue());
			reduced_cost.push_back(SP3_solve.getObjValue());
			vector<IloInt>index{ 0,1,2 };

			for (IloInt i=0;i<order_size.getSize();i++)
			{
				for (IloInt j= i+1; j<order_size.getSize(); j++)
				{
					if (reduced_cost[i]<reduced_cost[j])
					{
						IloNum m = reduced_cost[i];                 IloInt n = index[i];
						reduced_cost[i] = reduced_cost[j];     index[i] = index[j];
						reduced_cost[j] = m;                          index[j] = index[i];
					}
				}
			}
			if (reduced_cost[0] <= 0)
			{
				cout << "get the opt soln!!!" << endl;
				break;
			}
			else   //column generation
			{
				IloNumArray vals(env);
				if (index[0] == 0)
				{
					SP1_solve.getValues(vals, cuts_plan);
					IloNumColumn col(obj_MP(lumber_cost[0]) + constraints[0](vals[0]) + constraints[1](vals[1]) + constraints[2](vals[2]));
					IloNumVar newcut(col);
					cuts.add(IloNumVar(newcut));
				}
				if (index[0] ==1)
				{
					SP2_solve.getValues(vals, cuts_plan);
					IloNumColumn col(obj_MP(lumber_cost[1]) + constraints[0](vals[0]) + constraints[1](vals[1]) + constraints[2](vals[2]));
					IloNumVar newcut(col);
					cuts.add(IloNumVar(newcut));
				}
				if (index[0] == 2)
				{
					SP3_solve.getValues(vals, cuts_plan);
					IloNumColumn col(obj_MP(lumber_cost[2]) + constraints[0](vals[0]) + constraints[1](vals[1]) + constraints[2](vals[2]));
					IloNumVar newcut(col);
					cuts.add(IloNumVar(newcut));
				}
			}
		}
		MP.add(IloConversion(env,cuts, ILOINT));
		MP_solve.solve();
		cout << "Solution status: " << MP_solve.getStatus() << endl;
}
	catch (IloException& ex) {
		cerr << "Error: " << ex << endl;
	}
	catch (...) {
		cerr << "Error" << endl;
	}
	env.end();
	system("pause");
	return 0;
}

void readdata(const char*filename, IloNumArray&lumber_size, IloNumArray&lumber_cost, IloNumArray&order_size, IloNumArray&order_amount)
{
	ifstream infile(filename);
	if (infile)
	{
		infile >> lumber_size;
		infile >> lumber_cost;
		infile >> order_size;
		infile >> order_amount;
		//cout << "finish" << endl;
	}
	else
	{
		cerr << "No such file: " << filename << endl;
		throw(1);
	}
	infile.close();

}


static void report1(IloCplex& MP_Solver, IloNumVarArray cuts,
	IloRangeArray constraints)
{
	cout << endl;
	cout << "objvalue " << MP_Solver.getObjValue() << endl;
	cout << endl;
	for (IloInt j = 0; j < cuts.getSize(); j++) {
		cout << "  Cut" << j << " = " << MP_Solver.getValue(cuts[j]) << endl;
	}
	cout << endl;
	for (IloInt i = 0; i < constraints.getSize(); i++) {
		cout << "order" << i <<"_dualcost"<< " = " << MP_Solver.getDual(constraints[i]) << endl;
	}
	cout << endl;
}
