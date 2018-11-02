#pragma once

#include<ilcplex/ilocplex.h>
#include"Schedule.h"
#include<iostream>
using namespace std;


class model
{
private:
	IloNumVarArray paths;  //path vars
//	IloNumVarArray assign_vars;   //shift-task assign vars
	IloNumVarArray penalty_vars;
	IloNumVarArray over_cover_vars;
	IloRangeArray task_cover_cons;   //cover cons
	/*
	IloRangeArray shift_assign_cons;
	IloRangeArray connect_cons;
	IloRangeArray time_cons;
	*/
	IloObjective obj_;
	IloEnv env;
	IloModel model_;
	IloCplex solve_;

	Sche*sche_;
	vector<Route*>SP_Rts;
	vector<Route*>Rts; 


public:
	model(Sche*_sche); 
	void init();
	void add_column(vector<Route*>Rts_);
	void add_column2(vector<Route*>SP_Rts_);
	void Solve_IP();
	bool solve_LP();
	bool CG_solve(); 
	pair<bool, int*> Bellman_ford();
	vector<Route*> Solve_SP();
	void Check_Rc(vector<Route*> New_Rts);
};




#include"model.h"

#define Max_CG_iter 50
#define INF 99999999
#define RC_EPS 1.0e-6

model::model(Sche*_sche)
{
	sche_ = _sche;
	Rts = sche_->find_dfs_routes(sche_->get_Task_List());  
	cout << "initial route size:" << Rts.size() << endl;
	/*
	int s = 0;
	for (int i=0; i< sche_->get_Task_List().size();i++)
	{
		int m = 0;
		for (int j=0;j<Rts.size();j++)
		{
			if (Rts[j]->cover(sche_->get_Task_List()[i]))
			{
				m++;
			}
		}
		if (m==0)
		{
			s++;
		}
	}
	cout << "task_not_covered" << s << endl;
	*/
	init();
	add_column(Rts);
}

void model::init()
{
	model_ = IloModel(env, "minimize");
	paths = IloNumVarArray(env);
	//assign_vars = IloNumVarArray(env);
	penalty_vars = IloNumVarArray(env);
	over_cover_vars = IloNumVarArray(env);
	model_.add(paths);
	//model_.add(assign_vars);
	model_.add(penalty_vars);
	model_.add(over_cover_vars);
	obj_ = IloAdd(model_, IloMinimize(env));
	size_t cover_cons_size = sche_->get_Task_List().size();
	//task_cover_cons
	task_cover_cons= IloRangeArray(env);   
	for (size_t i = 0; i<cover_cons_size; i++)
	{
		string cons_name = "task_cons" + to_string(i);
		task_cover_cons.add(IloRange(env, 1, 1, cons_name.c_str()));
	}
	model_.add(task_cover_cons);
	/*
	//shift_assign_cons
	shift_assign_cons = IloRangeArray(env);
	size_t shift_assign_cons_size = Rts.size();
	for (size_t i = 0; i<shift_assign_cons_size; i++)
	{
		string cons_name = "shift_assign_cons" + to_string(i);
		shift_assign_cons.add(IloRange(env, -INFINITY, 1, cons_name.c_str()));
	}
	model_.add(shift_assign_cons);
	//connect_cons
	connect_cons = IloRangeArray(env);
	size_t connect_cons_size = Rts.size()*sche_->get_Shift_List().size();
	for (size_t i = 0; i<connect_cons_size; i++)
	{
		string cons_name = "connect_cons" + to_string(i);
		connect_cons.add(IloRange(env, -INFINITY, 0, cons_name.c_str()));
	}
	model_.add(connect_cons);
	time_cons = IloRangeArray(env);
	//time_cons
	int m = 0;
	for (int i = 0; i < Rts.size(); i++)
	{
		for (int j = 0; j < sche_->get_Shift_List().size(); j++)
		{
			string cons_name = "time_cons" + to_string(m);
			time_cons.add(IloRange(env, -INFINITY, sche_->get_Shift_List()[j]->get_ET(), cons_name.c_str()));
			m++;
		}
	}
	model_.add(time_cons);
	*/
	solve_ = IloCplex(model_);
	cout << "finish model-init!!!!" << endl;
}

void model::add_column(vector<Route*>Rts_)
{
	for (int i = 0; i<Rts_.size(); i++)
	{
		IloNumColumn col(env);
		col += obj_(100);
		for (int j = 0; j<sche_->get_Task_List().size(); j++)
		{
			if (Rts_[i]->cover(sche_->get_Task_List()[j]))
			{
				col += task_cover_cons[j](1);
			}
		}
		/*
			for (int k=0;k<sche_->get_Shift_List().size();k++)
			{
					col += connect_cons[i*sche_->get_Shift_List().size()+k](-1);
			}
			*/
		string var_name = "Rts_" + to_string(i);
		paths.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		col.end();
	}
	for (int i = 0; i < sche_->get_Task_List().size(); i++)
	{
		IloNumColumn col(env);
		col += obj_(10000);
		col += task_cover_cons[i](1);
		string var_name = "Penalty_var" + to_string(i);
		penalty_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		col.end();
	}
	for (int i = 0; i < sche_->get_Task_List().size(); i++)
	{
		IloNumColumn col(env);
		col += obj_(20000);
		col += task_cover_cons[i](-1);
		string var_name = "Over_cover_var" + to_string(i);
		over_cover_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		col.end();
	}
	/*
	int s = 0;
	for (int i = 0; i<Rts_.size(); i++)
	{
		for (int j=0;j<sche_->get_Shift_List().size();j++)
		{

			IloNumColumn col(env);
			for (int k= 0; k<Rts_.size(); k++)
			{
				if (i==k)
				{
					col += shift_assign_cons[k](1);
				}
			}
			col += connect_cons[s](1);
			col += time_cons[s](Rts_[i]->get_task_seq()[Rts_[i]->get_task_seq().size()-1]->get_ET()); 
			col += obj_(1);
			string var_name = "assign_vars_" + to_string(s);
			assign_vars.add(IloNumVar(col, 0, 1, ILOFLOAT,var_name.c_str()));
			s++;
			col.end();
		}
	}
	*/
	cout << "finish add column!!!!" << endl;

}

void model::add_column2(vector<Route*>SP_Rts_)
{
	for (int i = 0; i<SP_Rts_.size(); i++)
	{
		IloNumColumn col(env);
		col += obj_(100);
		for (int j = 0; j<sche_->get_Task_List().size(); j++)
		{
			if (SP_Rts_[i]->cover(sche_->get_Task_List()[j]))
			{
				col += task_cover_cons[j](1);
			}
		}
		/*
		for (int k=0;k<sche_->get_Shift_List().size();k++)
		{
		col += connect_cons[i*sche_->get_Shift_List().size()+k](-1);
		}
		*/
		string var_name = "Rts_" + to_string(Rts.size()-SP_Rts_.size()+i);
		paths.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		col.end();
	}
	cout << "finish add column!!!!" << endl;
}


bool model::CG_solve()
{
		cout << "<<<<<<<<<<start column generation>>>>>>>>>>>" << endl;
		int iter = 0;
		int s = 1;
		//iter <= Max_CG_iter&&(
		while (SP_Rts.size()>0||s>0)
		{
			cout << "now is iteration" << iter << endl;
			s = 0;
			iter++;
			clock_t s_t = clock();
			cout << "MP solve..." << endl;
			bool can = solve_LP();
			//check RC
			for (int i=0;i<SP_Rts.size();i++)
			{
				double my_rc = SP_Rts[i]->Cmpt_RC();
				cout << "my_rc" << my_rc << endl;
				double cplex_rc = solve_.getReducedCost(paths[paths.getSize()-SP_Rts.size()+i]);
				cout << "cplex_rc" << cplex_rc << endl;
				if (abs(my_rc +cplex_rc)>1)
				{
					cout << "find  error!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					exit(0);
				}
			}
			SP_Rts.clear();
			if (!can)
			{
				cout << "LP solve....infeasible" << endl;
				return false;
			}
			double MP_time = clock() - s_t;
			cout << "MP solve " << MP_time / CLK_TCK << " second...." << endl;
			cout << "SP solve..." << endl;
			s_t = clock();
			Solve_SP();
			cout << "To add" << SP_Rts.size()<<"routes";
			double SP_time = clock() - s_t;
			cout << "SP solve " << SP_time / CLK_TCK << " second..." << endl;
		}
		cout << "CG_total_iteration:" << iter << endl;
		cout << "<<<<<Finish CG!!!!! >>>>>>>" << endl;
		return true;
}

vector<Route*> model::Solve_SP()
{
	vector<Route*>Bellman_Rts;
	vector<int>Rts_Id;
	vector<Task*>Task_seq;
	int num = sche_->get_Task_List().size() + 1;
	pair<bool, int*>sp_result = Bellman_ford();
	if (!sp_result.first)
	{
		cout << "Bellman_error!!!!" << endl;
		exit(0);
	}
	for (int i=1;i<num;i++)
	{
		if (sp_result.second[i] != -1)
		{
			cout << "shortest path of task" << i << endl;
			Rts_Id.push_back(i);
			cout << i << "---";
			int pre_ = sp_result.second[i];
			while (pre_ != 0)
			{
				cout << pre_ << "---";
				Rts_Id.push_back(pre_);
				pre_ = sp_result.second[pre_];
			}
			cout << pre_ << endl;
			for (int j = Rts_Id.size(); j > 0; j--)
			{
				Task_seq.push_back(sche_->get_Task_List()[Rts_Id[j - 1] - 1]);
			}
			Route*new_Rt = new Route(Rts.size(), Task_seq);
			Bellman_Rts.push_back(new_Rt);
			Rts_Id.clear();
			Task_seq.clear();
		}

	}
	cout << "Find Bellman Rts:" << Bellman_Rts.size() << endl;
	if (Bellman_Rts.size()<sche_->get_Task_List().size())
	{
		cout << "error!!!!!!" << endl;
		exit(0);
	}

	Check_Rc(Bellman_Rts);
	//vector<Route*>to_add_Rts;
	for (auto& r : Bellman_Rts)
	{
		if (r->Cmpt_RC()>0)
		{
			SP_Rts.push_back(r);
			Rts.push_back(r);
	  }
	}
	add_column2(SP_Rts);
	return SP_Rts;
}
pair<bool, int*> model::Bellman_ford()    //Shortest path---Bellmen ford 
{
	int Max_relax_num = 30;
	//initialize
	int num = sche_->get_Task_List().size();
	double *dis = new double[num+1]; int *pre = new int[num+1];
	int origin =0;
	pre[origin] = origin;
	for (int i = 1; i<num + 1; i++)
	{
		pre[i] = -1;
	}
	for (int i = 0; i <num+1;i++) 
	{
		dis[i] = (i == origin ? 0 : INF);
	}

	vector<Task*>new_task_list;
	Task*dummy_task = new Task(0, 0, 300, 0);
	//dummy_task->set_dual(-INF);
	new_task_list.push_back(dummy_task);
	for (auto& t : sche_->get_Task_List())
	{
		new_task_list.push_back(t);
	}

	for (int i=0;i<new_task_list.size()-1;i++)     
	{
		for (auto& t1 : new_task_list)
		{
			for (auto&t2 : new_task_list)
			{
				if (t1->get_task_Id() != t2->get_task_Id()&&(t1->get_task_Id()==0||t2->get_ST()-t1->get_ET()>=10))
				{
					if (dis[t2->get_task_Id()] > dis[t1->get_task_Id()]-t2->get_dual())
					{
						dis[t2->get_task_Id()] = dis[t1->get_task_Id()]-t2->get_dual();
						pre[t2->get_task_Id()] =t1->get_task_Id();
					}
				}
			}
		}
	}

	
	bool flag = false; //判断是否含有负权回路  
	for (auto& t1 : new_task_list)
	{
		for (auto&t2 : new_task_list)
		{
			if (dis[t2->get_task_Id()] > dis[t1->get_task_Id()]-t2->get_dual())
			{
				flag = true;
				break;
			}
		}
	}
	new_task_list.clear();
	pair<bool, int*>result_;
	result_.first = flag;
	result_.second = pre;
	return result_;
}

void model::Check_Rc(vector<Route*> New_Rts)
{
	int count = 0;
	for (auto&r : New_Rts)
	{
		r->Cmpt_RC();
		if (r->get_RC() >RC_EPS)
		{
			count++;
		}
	}
	cout << "routes with rc>0 : " << count << endl;
}

bool model::solve_LP()
{
	solve_.exportModel("model_lp.lp");
	try
	{
		solve_.solve();
		solve_.out() << "Solution status:" << solve_.getStatus() << endl;
		solve_.out() << "Obj_Val" << solve_.getObjValue() << endl;
		IloNumArray vals(env);
	    solve_.getValues(vals, paths);
		env.out() << "paths_Values = " << vals << endl;
		int g = 0;
		vector<int>task_covered;
		for (int i = 0; i<vals.getSize(); i++)
		{
			if (vals[i] != 0)
			{
				g++;
				cout << "route_var" << vals[i] << ",";
				Rts[i]->print();
				cout << endl;
				for (int j = 0; j<Rts[i]->get_task_seq().size(); j++)
				{
					task_covered.push_back(Rts[i]->get_task_seq()[j]->get_task_Id());
				}
			}
		}
		cout << endl;
		cout << "total_choosed_route:" << g << endl;

		int s = 0;
		for (int i = 0; i<sche_->get_Task_List().size(); i++)
		{
			bool cover = false;
			for (int j = 0; j<task_covered.size(); j++)
			{
				if (task_covered[j] == sche_->get_Task_List()[i]->get_task_Id())
				{
					cover = true;
					break;
				}
			}
			if (!cover)
			{
				s++;
				cout << "not cover task" << i + 1 << endl;
			}
		}
		cout << "Total_uncovered_route:" << s << endl;
		/*
		solve_.getValues(vals, assign_vars);
		for (int i = 0; i<vals.getSize(); i++)
		{
			if (vals[i] != 0)
			{
				cout << "assign_var" << vals[i] << ",";
			}
		}
		*/
		solve_.getValues(vals, penalty_vars);
		env.out() << "penalty_Values = " << vals << endl;
		if (solve_.getStatus() == IloCplex::Infeasible)
		{
			return false;
		}
	}
	catch (IloException& e) {
		cerr << " ERROR: " << e << endl;
	}
	//set dual 
	IloNumArray duals(env, task_cover_cons.getSize());
	solve_.getDuals(duals, task_cover_cons);
	env.out() << "Duals = " << duals << endl;
	for (int i=0;i<sche_->get_Task_List().size();i++)
	{
		sche_->get_Task_List()[i]->set_dual(duals[i]);
	}
	return true;
}


void model::Solve_IP()
{
	cout << "<<<<<<<<start solve IP...." << endl;
	try
	{
		model_.add(IloConversion(env, paths, ILOBOOL));
		model_.add(IloConversion(env, over_cover_vars, ILOBOOL));
		model_.add(IloConversion(env, penalty_vars, ILOBOOL));

	}
	catch (IloException& e) {
		cerr << " ERROR: " << e << endl;
	}
	try {
		solve_.solve();
		solve_.out() << "Solution status:" << solve_.getStatus() << endl;
		solve_.out() << "Obj_Val" << solve_.getObjValue() << endl;
		IloNumArray vals(env);
		solve_.getValues(vals, paths);
		env.out() << "paths_Values = " << vals << endl;
		int g = 0;
		vector<int>task_covered;
		for (int i = 0; i<vals.getSize(); i++)
		{
			if (vals[i] != 0)
			{
				g++;
				cout << "route_var" << vals[i] << ",";
				Rts[i]->print();
				cout << endl;
				for (int j=0;j<Rts[i]->get_task_seq().size();j++)
				{
					task_covered.push_back(Rts[i]->get_task_seq()[j]->get_task_Id());
				}
			}
		}
		cout << endl;
		cout << "total_choosed_route:" << g << endl;
		int s = 0;
		for (int i=0;i<sche_->get_Task_List().size();i++)
		{
			bool cover = false;
			for (int j=0;j<task_covered.size();j++)
			{
				if (task_covered[j]==sche_->get_Task_List()[i]->get_task_Id())
				{
					cover = true;
					break;
				}
			}
			if (!cover)
			{
				s++;
				cout << "not cover task" << i + 1 << endl;
			}
		}
		cout << "Total_uncovered_route:" << s << endl;
		/*
		solve_.getValues(vals, assign_vars);
		for (int i=0;i<vals.getSize();i++)
		{
			if (vals[i] != 0)
			{
				cout << "assign_var" << vals[i] << ",";
			}
		}
		//env.out() << "assign_Values = " << vals << endl;
		*/
		solve_.getValues(vals, penalty_vars);
		env.out() << "penalty_Values = " << vals << endl;
		solve_.getValues(vals, over_cover_vars);
		env.out() << "over_cover_Values = " << vals << endl;
	}
	catch (IloException& e) {
		cerr << " ERROR: " << e << endl;
	}
	if (solve_.getStatus() == IloCplex::Infeasible)
	{
		cout << "warning: IP infiasible!!!!" << endl;
	}

}




#pragma once
#include<vector>
#include"Task.h"
#include<iostream>
using namespace std;


class Route
{
private:
	static int count_;
	int ID;
	vector<Task*>task_seq;

	int tw1;   //earliest time 
	int tw2;   //completion time of all tasks in the sequence 

	double RC;

public:
	Route();
	Route(int ID_, vector<Task*>seq_);
	void set_ID(int i) { ID = i; };
	int get_ID() { return ID; };

	void set_task_seq(vector<Task*>seq_) { task_seq = seq_; };
	vector<Task*> get_task_seq() { return task_seq; };

	void set_RC(double i) { RC = i; };
	double get_RC() { return RC; };

	bool cover(Task*task_);
	double Cmpt_RC();
	void print();


};


#include"Route.h"
#define Rt_cost 100
int Route::count_ = 0;

Route::Route()
{
}
Route::Route(int ID_, vector<Task*>seq_)
{
	ID = ID_;
	task_seq = seq_;
}

double Route::Cmpt_RC()    //z-c
{
	double Rc = 0;
	for (auto&t : this->get_task_seq())
	{
		Rc += t->get_dual();
	}
	Rc -= Rt_cost;
	set_RC(Rc);
	return Rc;
}


void Route::print()
{
	cout << "Route_Info:";
	for (auto&t : task_seq)
	{
		cout << t->get_task_Id() << "-";
	}
	cout << endl;

}


bool Route::cover(Task*task_)
{
	bool cover = false;
	for (auto&t : task_seq)
	{
		if (t->get_task_Id()==task_->get_task_Id())
		{
			cover = true;
			break;
		}
	}

	return cover;
}




#pragma once

#include"Shift.h"
#include"Route.h"
#include <vector>
using namespace std;

class Sche
{
private:
	vector<Task*>Task_List;
	vector<Shift*>Shift_List;
	vector<Route*>Task_seq;


public:
	Sche();
	void set_Task_List(vector<Task*>list_) { Task_List = list_; };
	vector<Task*>get_Task_List() { return Task_List; };

	void set_Shift_List(vector<Shift*>list_) { Shift_List = list_; };
	vector<Shift*>get_Shift_List() { return Shift_List; };

	vector<Route*>merge_routes(vector<Route*>Rts);  //find route for those tasks which are not covered.
	vector<Task*> find_next_tasks(Task*task_);
	vector<Task*> find_limited_tasks(Task*task_,int num);
	void Dfs(Task*cur_task_,vector<Task*>Cur_task_seq, vector<Route*>&Rts_container);
	vector<Route*>find_dfs_routes(vector<Task*>task_list_);
};




#include "Schedule.h"
#include<algorithm>
using namespace std;

Sche::Sche()
{

}
/*
vector<Route*>find_init_routes()
{

}
*/
bool cmp(int a,int b)
{
	if (a<b)
	{
		return true;
	}
	return false;
}
vector<Task*> Sche::find_next_tasks(Task*task_)
{
	vector<Task*>next_tasks_set;
	for (auto&t : Task_List)
	{
		if (t->get_task_Id()==task_->get_task_Id())
		{
			continue;
		}
		if (task_->get_ET()+10<=t->get_ST())
		{
			next_tasks_set.push_back(t);
		}
	}
	return next_tasks_set;
}

vector<Task*> Sche::find_limited_tasks(Task*task_, int num)
{
	vector<Task*>limited_next_tasks_set;
	vector<Task*>next_tasks_set=find_next_tasks(task_);
	vector<int>time;
	for (auto&t : next_tasks_set)
	{
		time.push_back(t->get_ST() - task_->get_ET());
	}
	sort(time.begin(), time.end(), cmp);
	if (num>next_tasks_set.size())
	{
		num = next_tasks_set.size();
	}
	int time_ = 0;
	for (int i=0;i<num;i++)
	{
		for (int j=0;j<time.size();j++)
		{
				if (time[j] == time_)
				{
					continue;
				}
				else
				{
					time_ = time[j];
					break;
				}
		}
		for (auto&t : next_tasks_set)
		{
			if (t->get_ST()-task_->get_ET()==time_)
			{
				limited_next_tasks_set.push_back(t);
				break;
			}
		}
	}
	return limited_next_tasks_set;
}

void Sche::Dfs(Task*cur_task_, vector<Task*>Cur_task_seq,vector<Route*>&Rts_container)
{
	int i = 0;
	vector<Task*>next_tasks = find_limited_tasks(cur_task_,4);
	if (next_tasks.size() == 0)
	{
		i++;
		cout << "save a new route" << endl;
		Route*new_Rt = new Route(i,Cur_task_seq);
		Rts_container.push_back(new_Rt);
		new_Rt->print();
		return;
	}
	if (Rts_container.size()>=20)   //limit the amount of routes
	{
		return;
	}
	else
	{
		for (auto& t : next_tasks)
		{
			Cur_task_seq.push_back(t);
			Dfs(t, Cur_task_seq, Rts_container);
			Cur_task_seq.pop_back();
		}	
	}
	return;
}
vector<Route*>Sche::merge_routes(vector<Route*>Rts)
{
	vector<Route*>merged_routes;
	vector<Task*>new_seq;
	int s = Rts.size();
	for (auto& r1 : Rts)
	{
		int m = 0;
		bool can = false;
		if (r1->get_task_seq()[0]->get_ST()>540) //start time > 540
		{
			for (auto& r2 : Rts)
			{
				if (m>=1)
				{
					break;
				}
				if (r2->get_task_seq()[0]->get_ST()<=420)
				{
					if (r2->cover(r1->get_task_seq()[0]))   //can merge 
					{
						for (int i=0;i<r2->get_task_seq().size();i++)
						{
							if (r2->get_task_seq()[i]!=r1->get_task_seq()[0])
							{
								new_seq.push_back(r2->get_task_seq()[i]);
							}
							else
							{
								break;
							}
						}
						for (int j=0;j<r1->get_task_seq().size();j++)
						{
							new_seq.push_back(r1->get_task_seq()[j]);
						}
						cout << "pre_merge";
						cout << "r1-----";
						r1->print();
						cout << "r2-----";
						r2->print();
						Route*new_Rt = new Route(s, new_seq);
						m++;
						cout << "merged";
						new_Rt->print();
						merged_routes.push_back(new_Rt);
						can = true;
						new_seq.clear();
						s++;
					}
				}
			}
			if (!can)
			{
				merged_routes.push_back(r1);   //can not merge
			}
		}
		else
		{
			merged_routes.push_back(r1);
		}
	}
	return merged_routes;
}
vector<Route*>Sche::find_dfs_routes(vector<Task*>task_list_)   //using dfs to generate task sequence for every task
{
	vector<vector<Route*>>Dfs_Rts(task_list_.size());
	vector<Route*>unmerged_Rts;
	vector<Route*>merged_Rts;
	int i = 0;
	vector<Task*>Cur_task_seq;
	for (auto &t : task_list_)
	{
		/*
		if (t->get_ST()>=420)    //task must start in two hour of start of shift
		{
			i++;
			continue; 
		}
		*/
		Cur_task_seq.push_back(t);
		Dfs(t, Cur_task_seq, Dfs_Rts[i]);
		Cur_task_seq.clear();
		i++;
	}
	cout << "Dfs_Rts_size:" << Dfs_Rts[0].size() << endl;
	for (auto &r : Dfs_Rts)
	{
		if (r.size()!=0)
		{
			for (auto& seq: r)
			{
				unmerged_Rts.push_back(seq);
			}
		}
	}
	merged_Rts=merge_routes(unmerged_Rts);
	cout << "<<<<<<Finish finding Rts by Dfs!!!!!" << endl;
	return merged_Rts;
}





#include"IO.h"
#include"model.h"
#include<iostream>
using namespace std;

int main()
{
	Sche*sche_=new Sche();
	IO*io_=new IO();
	io_->Input(sche_);
	//sche_->find_all_dfs_routes(sche_->get_Task_List());
	model*model_ = new model(sche_);
	//model_->solve_LP();
	//cout << "finish_LP" << endl;
	model_->CG_solve();
	model_->Solve_IP();
	cout << "Finish/////////////////////" << endl;
	system("pause");
	return 0;
}































