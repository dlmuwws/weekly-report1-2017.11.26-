
#include<ilcplex/ilocplex.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<queue>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"class_set.h"
#include"arc.h"
#include<iostream>
using namespace std;

#define Days 7
#define airports 8
#define base_num 2  //维修机场的个数
#define max_weight 1000
#define aircraft_fc 300
#define A 12
#define Min_groundtime 40
#define count_time 240
#define INF 999999999
#define RC_EPS 1.0e-6


typedef vector<treenode*>string_;
typedef vector<string_>strings_;
typedef struct seq_node //  
{
	int index;
	vector<pair<int,double>>children;
}seq_node;
/*
typedef struct Edge //边  
{
	int u, v;
	double cost_;
	Edge(int i, int j, double _cost_) { u = i; v = j; cost_ = _cost_; };
}Edge;
*/
double**set_leg_fc(int airp_num);
int **creat_matrix1(vector<leg*>&leglist_);
vector<vector<event_node*>>daily_nodes(int airport_num);
vector<vector<event_node*>>weekly_nodes(int airport_num);
vector<vector<string_>>find_oneday_string(vector<leg*>&leg_list_);
double cacu_string_cost(string_ _string_, vector<leg*>&weekly_leg_list);
vector<oper_rotation*>add_string(int*base, vector<vector<string_>>type_strings, double aircraft_dual, vector<leg*>leg_list, int M_num, vector<vector<G_arc*>>daily_gc_, vector<leg*>weekly_leg_list_, vector<seq_node>nodes1, vector<seq_node>nodes2);
bool can_connect(string_ string_1, string_ string_2);
//pair<double*, int*>string_Dijkstra(int source, double**cost_matrix, int num);
pair<double*, int*>string_Dijkstra2(int source, double**cost_matrix, int num, vector<vector<string_>>three_day_strings, int M_num);
//pair<bool, int*>Bellman_Ford(int nodenum, int original, vector<Edge>edge, int edgenum);
pair<bool, int*>SPFA1(vector<seq_node>nodes, int source, int num_);
pair<bool, int*>SPFA2(vector<seq_node>nodes, int source, int num_, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num);
//pair<bool, int*>Bellman_Ford2(int nodenum, int original, vector<Edge>edge, int edgenum, vector<vector<string_>>three_day_strings, int M_num);
vector<oper_rotation*>two_day_find_sp(int*base, vector<seq_node>&nodes, vector<vector<pair<string_, int>>>&two_day_strings_, int M_num, vector<leg*>&leg_list);
vector<oper_rotation*>three_day_find_sp(int*base, vector<seq_node>&nodes, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num, vector<leg*>&leg_list);
vector<oper_rotation*>two_day_BFS(double**cost_matrix_, int M1, int M2, int num_, vector<string_>S, int M_num);
vector<oper_rotation*>three_day_BFS(double**cost_matrix_, int M1, int M2, int num_, vector<string_>S, int M_num);
vector<seq_node>init_twoday_string_Graph(int*base, vector<vector<pair<string_, int>>>&two_day_strings_, int M_num, double aircraft_dual_, vector<leg*>week_leg_list);
vector<seq_node>update_twoday_string_graph(vector<seq_node>nodes, double aircraft_dual_, vector<leg*>week_leg_list, vector<vector<pair<string_, int>>>&two_day_strings_, int M_num);
vector<seq_node>init_threeday_string_Graph(int*base, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num, double aircraft_dual_, vector<leg*>week_leg_list);
vector<seq_node>update_threeday_string_graph(vector<seq_node>nodes, double aircraft_dual_, vector<leg*>week_leg_list, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num);
//vector<oper_rotation*>BFS_add_string(int*base, vector<vector<vector<string_>>>type_strings, double aircraft_dual, vector<leg*>leg_list, int M_num);
vector<G_arc*>s2_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc);
vector<G_arc*>s3_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc);
vector<G_arc*>s4_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc);
int get_rs_2(vector<G_arc*>string_arcs_);
bool is_base(int i, int*base)
{

	for (int j = 0; j<base_num; j++)
	{
		if (i == base[j])
		{
			return true;
		}
	}
	return false;

}



int main()
{
	//创建点
	cout << "creat nodes!!!!" << endl;
	vector<vector<event_node*>>d_nodes = daily_nodes(airports);
	vector<vector<event_node*>>w_nodes = weekly_nodes(airports);
	//创建Ground arc
	cout << "creat ground arcs!!!!" << endl;
	G_arc*G_ = new G_arc();
	vector<vector<G_arc*>>d_G = G_->get_day_ground_arcs(d_nodes, airports);
	vector<vector<G_arc*>>w_G = G_->get_week_ground_arcs(w_nodes, airports);
	//创建leg arc
	double**leg_fc_ = set_leg_fc(airports);
	cout << "creat leg arcs!!!!" << endl;
	vector<leg*>daily_leg_list;
	vector<leg*>weekly_leg_list;
	leg*leg_ = new leg();
	daily_leg_list = leg_->get_day_leglist(d_nodes, airports, 1, leg_fc_);
	cout << "--------------print daily legs info:---------------" << endl;
	for (int i = 0; i<daily_leg_list.size(); i++)
	{
		cout << daily_leg_list[i]->index << "," << daily_leg_list[i]->origin_airp << "," << daily_leg_list[i]->departure_t << "," << daily_leg_list[i]->dest_airp << "," << daily_leg_list[i]->arrival_t << "," << daily_leg_list[i]->date << "," << daily_leg_list[i]->firm << "," << daily_leg_list[i]->fixed_cost;
		cout << endl;
	}
	weekly_leg_list = leg_->get_week_leglist(d_nodes, airports, leg_fc_);
	for (int i = 0; i<weekly_leg_list.size(); i++)
	{
		weekly_leg_list[i]->set_index(i);
	}
	cout << "---------------print weekly legs info:--------------------" << endl;
	for (int i = 0; i<weekly_leg_list.size(); i++)
	{
		cout << weekly_leg_list[i]->index << "," << weekly_leg_list[i]->index2 << "," << weekly_leg_list[i]->origin_airp << "," << weekly_leg_list[i]->departure_t << "," << weekly_leg_list[i]->dest_airp << "," << weekly_leg_list[i]->arrival_t << "," << weekly_leg_list[i]->date << "," << weekly_leg_list[i]->firm << "," << weekly_leg_list[i]->fixed_cost;
		cout << endl;
	}

	int **relation_matrix = creat_matrix1(weekly_leg_list);
	cout << "---------------------find one day leg sequence:--------------------" << endl;
	vector<vector<string_>>type_strings_ = find_oneday_string(daily_leg_list);
	cout << "type1_string_size:" << type_strings_[0].size() << endl;   //2
	cout << "type2_string_size:" << type_strings_[1].size() << endl;   //6
	cout << "type3_string_size:" << type_strings_[2].size() << endl;    //6
	cout << "type4_string_size:" << type_strings_[3].size() << endl;    //3

	IO*io = new IO();
	vector<OD*>OD_info = io->read_OD_info();


	///solve model using cplex
	cout << "-------------------start solve integrated_model:-----------------" << endl;
	IloEnv env;
	try
	{
		IloModel INT_model(env);
		//objective
		IloObjective _maximum = IloAdd(INT_model, IloMaximize(env));
		//constraints
		IloRangeArray demand_cons(env);
		IloRangeArray weight_cons(env);
		IloRangeArray cover_cons(env);
		IloRangeArray balance_cons1(env);
		IloRangeArray balance_cons2(env);
		//variables
		IloNumVarArray flow_vars(env);
		IloNumVarArray ground_vars(env);
		IloNumVarArray string_vars(env);

		char str[5];
		char str1[5];
		cout << "-------------------add constraints:-----------------" << endl;
		//demand constraints
		for (int i = 0; i<OD_info.size(); i++)
		{
			_itoa_s(OD_info[i]->get_index(), str, 10);
			string name = string("od_demand_cons_") + string(str);
			demand_cons.add(IloRange(env, -IloInfinity, OD_info[i]->quantity, name.c_str()));
		}
		cout << "demand_con_size:" << demand_cons.getSize() << endl;
		INT_model.add(demand_cons);

		//weight constraints
		for (int i = 0; i<weekly_leg_list.size(); i++)                //对于一周每天的leg来说
		{
			_itoa_s(weekly_leg_list[i]->index, str, 10);
			string name = string("weekly_leg") + string("weight_cons") + string(str);
			weight_cons.add(IloRange(env, -IloInfinity, 0, name.c_str()));
		}
		cout << "weight_con_size:" << weight_cons.getSize() << endl;
		INT_model.add(weight_cons);

		//cover_constraints
		for (int j = 0; j <daily_leg_list.size(); j++)
		{
			_itoa_s(daily_leg_list[j]->index, str, 10);
			string name = string("cover_cons") + string(str);
			cover_cons.add(IloRange(env, -IloInfinity, 1, name.c_str()));
		}
		cout << "cover_con_size:" << cover_cons.getSize() << endl;
		INT_model.add(cover_cons);

		//aircraft_constraints
		string name = string("aircraft_cons");
		IloRange aircraft_cons(env, -IloInfinity, A, name.c_str());
		INT_model.add(aircraft_cons);

		//balance_constraint1
		for (int i = 0; i<daily_leg_list.size(); i++)
		{
			_itoa_s(daily_leg_list[i]->index, str, 10);
			string name = string("balance1_cons") + string(str);
			balance_cons1.add(IloRange(env, 0, 0, name.c_str()));
		}
		cout << "balance1_cons_size:" << balance_cons1.getSize() << endl;
		INT_model.add(balance_cons1);

		//balance_constraint2
		for (int i = 0; i<daily_leg_list.size(); i++)
		{
			_itoa_s(daily_leg_list[i]->index, str, 10);
			string name = string("balance2_cons") + string(str);
			balance_cons2.add(IloRange(env, 0, 0, name.c_str()));
		}

		cout << "balance2_cons_size:" << balance_cons2.getSize() << endl;
		INT_model.add(balance_cons2);

		cout << "-------------------add variables:-------------------" << endl;
		//flow_var
		INT_model.add(flow_vars);
		
		//string var
		INT_model.add(string_vars);
		int*base_ = new int[base_num];
		base_[0] = 1; base_[1] = 2;// base_[2] = 11;
		
		//add ground_var
		vector<G_arc*>G_arc_list;
		for (int i = 0; i < d_G.size(); i++)
		{
			for (int j = 0; j < d_G[i].size(); j++)
			{
				G_arc_list.push_back(d_G[i][j]);
			}
		}
		for (int i = 0; i<G_arc_list.size(); i++)
		{
			IloNumColumn col(env);
			col += _maximum(-aircraft_fc*G_arc_list[i]->get_pj());
			for (int k = 0; k<daily_leg_list.size(); k++)
			{
				if (daily_leg_list[k]->get_y1_d(d_G) == G_arc_list[i])
				{
					col += balance_cons1[k](-1);
				}
				if (daily_leg_list[k]->get_y2_d(d_G) == G_arc_list[i])
				{
					col += balance_cons1[k](1);
				}
				if (daily_leg_list[k]->get_y1_a(d_G) == G_arc_list[i])
				{
					col += balance_cons2[k](-1);
				}
				if (daily_leg_list[k]->get_y2_a(d_G) == G_arc_list[i])
				{
					col += balance_cons2[k](1);
				}
			}
			col += aircraft_cons(G_arc_list[i]->get_pj());
			_itoa_s(G_arc_list[i]->end_->airport, str, 10);
			_itoa_s(i, str1, 10);
			string var_name = string("airport_") + string(str) + string("_groundarc_") + string(str1) + string("var");
			ground_vars.add(IloNumVar(col, 0, A, ILOFLOAT, var_name.c_str()));

		}
		INT_model.add(ground_vars);
		cout << "ground_vars_size:" << ground_vars.getSize() << endl;

		vector<pair<string_, int>>s2;
		vector<pair<string_, int>>s3;
		vector<pair<string_, int>>s4;
		for (int i = 0; i<type_strings_[1].size(); i++)
		{
			s2.push_back(pair<string_, int>(type_strings_[1][i], get_rs_2(s2_string_rs(type_strings_[1][i], d_G))));
		}
		for (int i = 0; i<type_strings_[2].size(); i++)
		{

			s3.push_back(pair<string_, int>(type_strings_[2][i], get_rs_2(s3_string_rs(type_strings_[2][i], d_G))));
		}
		for (int i = 0; i<type_strings_[3].size(); i++)
		{

			s4.push_back(pair<string_, int>(type_strings_[3][i], get_rs_2(s4_string_rs(type_strings_[3][i], d_G))));
		}
		vector<vector<pair<string_, int>>>two_day_strings;
		two_day_strings.push_back(s2); two_day_strings.push_back(s4);
		vector<vector<pair<string_, int>>>three_day_strings;
		three_day_strings.push_back(s2); three_day_strings.push_back(s3); three_day_strings.push_back(s4);

		vector<seq_node>nodes1 = init_twoday_string_Graph(base_, two_day_strings, base_num, 0,weekly_leg_list);
		vector<seq_node>nodes2 = init_threeday_string_Graph(base_, three_day_strings, base_num, 0, weekly_leg_list);

		IloCplex MP_solve(INT_model);
		cout << "-------------------column generation:---------------------" << endl;
		vector<oper_path*>path_list;
		vector<oper_path*>new_path_list;
		vector<oper_rotation*>string_list;
		vector<oper_rotation*>to_add_strings;
		vector<oper_rotation*>_add_strings;
	//	vector<double>rc_
		IloInt a = 0;       //列生成迭代次数
		IloInt b = 0;    //string 个数
		IloInt c = 0;    //path 个数
		for (;;)
		{
			MP_solve.exportModel("model4_.lp");
			MP_solve.solve();
			a++;
			IloNumArray vals(env);
			IloNumArray dualprice(env);
			cout << "-------------------print solution situtaion:-----------------" << endl;
			env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
			MP_solve.getValues(vals, flow_vars);
			env.out() << "flow_vars_Values = " << vals << endl;
			MP_solve.getValues(vals, string_vars);
			env.out() << "string_vars_Values= " << vals << endl;
			MP_solve.getValues(vals, ground_vars);
			env.out() << "ground_vars_Values= " << vals << endl;
			MP_solve.getReducedCosts(vals, string_vars);
			env.out() << "string_rc= " << vals << endl;
			MP_solve.getDuals(dualprice, demand_cons);
			env.out() << "demand_Duals = " << dualprice << endl;
			MP_solve.getDuals(dualprice, weight_cons);
			env.out() << "weight_Duals = " << dualprice << endl;
			MP_solve.getDuals(dualprice, cover_cons);
			env.out() << "cover_Duals= " << dualprice << endl;
			MP_solve.getDuals(dualprice, balance_cons1);
			env.out() << "balance1_Duals = " << dualprice << endl;
			MP_solve.getDuals(dualprice, balance_cons2);
			env.out() << "balance2_Duals = " << dualprice << endl;
			env.out() << "aircraft_num_Duals = " << MP_solve.getDual(aircraft_cons) << endl;
			cout << "Solution status: " << MP_solve.getStatus() << endl;
			IloNumArray demand_price(env, OD_info.size());
			IloNum aircraft_num_dual;
		    
			//get_duals
			for (int i = 0; i<OD_info.size(); i++)
			{
				demand_price[i] = MP_solve.getDual(demand_cons[i]);
			}
			for (int i = 0; i < weekly_leg_list.size(); i++)
			{
				weekly_leg_list[i]->set_capacity_dual(MP_solve.getDual(weight_cons[i]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j]->set_cover_dual(MP_solve.getDual(cover_cons[j]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j]->set_balance1_dual(MP_solve.getDual(balance_cons1[j]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j]->set_balance2_dual(MP_solve.getDual(balance_cons2[j]));
			}
			for (int i = 0; i < daily_leg_list.size(); i++)
			{
				for (int j = 0; j < weekly_leg_list.size(); j++)
				{
					if (weekly_leg_list[j]->index2==i)
					{
						weekly_leg_list[j]->set_balance1_dual(MP_solve.getDual(balance_cons1[i]));
					}
				}
			}
			for (int i = 0; i < daily_leg_list.size(); i++)
			{
				for (int j = 0; j < weekly_leg_list.size(); j++)
				{
					if (weekly_leg_list[j]->index2 == i)
					{
						weekly_leg_list[j]->set_balance2_dual(MP_solve.getDual(balance_cons2[i]));
					}
				}
			}
			
			for (int i = 0; i < daily_leg_list.size(); i++)
			{
				for (int j = 0; j < weekly_leg_list.size(); j++)
				{
					if (weekly_leg_list[j]->index2 == i)
					{
						weekly_leg_list[j]->set_cover_dual(MP_solve.getDual(cover_cons[i]));
					}
				}
			}
			aircraft_num_dual = MP_solve.getDual(aircraft_cons);
			for (int i = 0; i < weekly_leg_list.size(); i++)
			{
				weekly_leg_list[i]->set_var_cost(weekly_leg_list[i]->var_cost + weekly_leg_list[i]->capacity_dual);
			}
			/*
			for (int i = 0; i<_add_strings.size(); i++)
			{
				cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << _add_strings[i]->cacu_RC(MP_solve.getDual(aircraft_cons), weekly_leg_list) << endl;
			}
			_add_strings.clear();
			*/
			for (int i = 0; i < _add_strings.size(); i++)
			{
				double my_rc = _add_strings[i]->cacu_RC(MP_solve.getDual(aircraft_cons), weekly_leg_list);
				cout << "8888888888" << my_rc << endl;
				double cplex_rc = MP_solve.getReducedCost(string_vars[string_vars.getSize() - _add_strings.size() + i]);
				cout << "8888888888" << cplex_rc << endl;
				if (abs(my_rc-cplex_rc)>1)
				{
					cout << "error............................." << endl;
					exit(0);
				}
			}
			_add_strings.clear();
			vector<oper_rotation*>().swap(_add_strings);
			//add path and caculate path reduced cost
			IloInt t = 0;
			for (int i = 0; i < OD_info.size(); i++)
			{
				oper_path*path_ = new oper_path(i, OD_info[i]->find_shortest_path(relation_matrix,weekly_leg_list));
				double reduced_cost = path_->cacu_mp(OD_info) - demand_price[i];
				if (reduced_cost <= RC_EPS)
				{
					t++;
					cout << "path_rc:" << reduced_cost;
					delete path_;
					path_ = NULL;
				}
				else
				{
					cout << "path_rc:" << reduced_cost << endl;
					path_list.push_back(path_);
					new_path_list.push_back(path_);
				}
				cout << endl;
			}
			if (t != OD_info.size())
			{
				cout << "now, add--" << new_path_list.size() << "--new paths" << endl;
				for (int i = 0; i<new_path_list.size(); i++)
				{
					IloNumColumn col(env);
					OD*associated_od = OD_info[new_path_list[i]->get_OD_index()];
					col += _maximum(new_path_list[i]->cacu_mp(OD_info));
					col += demand_cons[new_path_list[i]->get_OD_index()](1);
					vector<int>beta_ = new_path_list[i]->get_beta(weekly_leg_list);  //beta stand index of leg covered by the path
					for (int j = 0; j<beta_.size(); j++)
					{
						col += weight_cons[beta_[j]](1);
					}
					_itoa_s(path_list.size()-new_path_list.size()+i+1, str, 10);
					_itoa_s(new_path_list[i]->get_OD_index(), str1, 10);
					string var_name = string("od") + string(str1) + string("_pathflow") + string(str);
					flow_vars.add(IloNumVar(col, 0, associated_od->quantity, ILOFLOAT, var_name.c_str()));
				}
				//cout << "flow_vars_size:" << flow_vars.getSize() << endl;
			}
			//add new strings
			//caculate reduced cost of all to_add_strings
			//for (int i = 0; i<to_add_strings.size(); i++)
			//{
				//to_add_strings[i]->add_gc(d_G);
			//}

			cout << "----------------------to_add-strings------------------------" << endl;
			to_add_strings = add_string(base_, type_strings_, aircraft_num_dual, daily_leg_list, base_num, d_G, weekly_leg_list,nodes1,nodes2);
			for (int i = 0; i<to_add_strings.size(); i++)
			{
				cout << to_add_strings[i]->legs.size() << endl;
				for (int j = 0; j<to_add_strings[i]->legs.size(); j++)
				{
					cout << to_add_strings[i]->legs[j]->index << ",";
				}
				cout << endl;
			}

			IloInt q = 0;
			for (int i = 0; i<to_add_strings.size(); i++)
			{
				double rc = to_add_strings[i]->cacu_RC(aircraft_num_dual,weekly_leg_list);
				//IloNum cplex_rc;
				//cplex_rc=MP_solve.getReducedCost()
				if (rc <=RC_EPS)
				{
					q++;
					//to_add_strings[i]
					delete to_add_strings[i];
					to_add_strings[i] = NULL;
					cout << "string_rc-------------------------:" << rc << endl;
				}
				else
				{
					cout << "string_rc:-------------------------" << rc << endl;
					string_list.push_back(to_add_strings[i]);
					_add_strings.push_back(to_add_strings[i]);
				}
			}
			//vector<double>myrc_;
			if (q != to_add_strings.size())
			{
				cout << "now, add--" << _add_strings.size() << "--new strings" << endl;
				
				for (int i = 0; i <_add_strings.size(); i++)
				{
					IloNumColumn col(env);
					col += _maximum(-_add_strings[i]->get_string_cost() - aircraft_fc*_add_strings[i]->get_rs());        //每个环飞了几天就有几个cA
					for (int j = 0; j < _add_strings[i]->legs.size(); j++)
					{
						for (int k = 0; k<7; k++)
						{
							col += weight_cons[_add_strings[i]->legs[j]->index + daily_leg_list.size()*k](-max_weight);
						}
					}
					for (int j = 0; j < _add_strings[i]->legs.size(); j++)
					{
						col += cover_cons[_add_strings[i]->legs[j]->index](1);
					}
					col += balance_cons1[_add_strings[i]->legs[0]->index](1);
					col += balance_cons2[_add_strings[i]->legs[_add_strings[i]->legs.size() - 1]->index](-1);
					col += aircraft_cons(_add_strings[i]->get_rs());
					_itoa_s(string_list.size()-_add_strings.size()+i+1, str, 10);
					//_itoa_s(a, str1, 10);
					string var_name = string("string_var_") + string(str);
					string_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
				}
			}

			if (t == OD_info.size() && q == to_add_strings.size())           //所有path和string的reduced cost均小于等于0，停止
			{
				cout << "--------stop_cg!!!!!!!!---------" << endl;
				break;
			}
			to_add_strings.clear();
			new_path_list.clear();
			vector<oper_rotation*>().swap(to_add_strings);
			vector<oper_path*>().swap(new_path_list);
		}
		INT_model.add(IloConversion(env, string_vars, ILOINT));
		INT_model.add(IloConversion(env, ground_vars, ILOINT));
		MP_solve.solve();
		IloNumArray flow_values(env);
		IloNumArray string_values(env);
		IloNumArray ground_values(env);
		//IloNumArray dualprice(env);
		cout << "-------------------optimal solution result:-----------------" << endl;
		env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
		MP_solve.getValues(flow_values, flow_vars);
		env.out() << "flow_vars_Values= " << flow_values << endl;
		for (int i=0;i<flow_vars.getSize();i++)
		{
			if (flow_values[i]!=0)
			{
				cout << flow_vars[i].getName() << endl;
				cout << "the_path_detail:" << endl;
				for (int j = 0; j<path_list[i]->legs.size(); j++)
				{
					cout << "leg_index:" << path_list[i]->legs[j]->index << " , ";
				}
				cout << endl;
			}
			
		}
		MP_solve.getValues(string_values, string_vars);
		env.out() << "string_vars_Values = " << string_values << endl;
		int aircraft_num_ = 0;

		for (int i = 0; i<string_vars.getSize(); i++)
		{
			if (string_values[i]>0.5)
			{
				cout << string_vars[i].getName() << endl;
				cout << "the_string_detail:" << endl;
				for (int j = 0; j<string_list[i]->legs.size(); j++)
				{
					cout << "leg_index:" << string_list[i]->legs[j]->index << " , ";
				}
				cout << endl;
				aircraft_num_ += string_list[i]->get_rs();
			}
		}
		cout << endl;
		MP_solve.getValues(ground_values, ground_vars);
		env.out() << "ground_vars_Values = " << ground_values << endl;
		for (int i=0;i<ground_vars.getSize();i++)
		{
			aircraft_num_ += ground_values[i] * G_arc_list[i]->get_pj();
		}
		cout << "using  " << aircraft_num_ << "  aircrafts" << endl;
		cout << "Solution status: " << MP_solve.getStatus() << endl;
	}

	catch (IloException& ex)
	{
		cerr << "Error: " << ex << endl;
	}
	catch (...)
	{
		cerr << "Error" << endl;
	}
	env.end();
	cout << "------------------------finish solve!!!!-------------------" << endl;
	system("pause");
	return 0;
}

int **creat_matrix1(vector<leg*>&leglist_)
{
	int num = leglist_.size();
	int ** relation_matrix = new int *[num];
	for (int i = 0; i < num; i++)
	{
		relation_matrix[i] = new int[num];
	}
	for (int i = 0; i<leglist_.size(); i++)
	{
		for (int j = 0; j<leglist_.size(); j++)
		{
			if (leglist_[i]->date <= leglist_[j]->date)
			{
				if (leglist_[i]->dest_airp != leglist_[j]->origin_airp || leglist_[j]->departure_t - leglist_[i]->arrival_t < Min_groundtime)
				{

					relation_matrix[i][j] = 0;
					continue;
				}
				if (i != j &&leglist_[i]->dest_airp == leglist_[j]->origin_airp &&leglist_[j]->departure_t - leglist_[i]->arrival_t >= Min_groundtime)
				{

					relation_matrix[i][j] = 1;
					continue;
				}
			}
			else if (leglist_[i]->date >= leglist_[j]->date && leglist_[i]->dest_airp == leglist_[j]->origin_airp)
			{
				relation_matrix[i][j] = -1;
				continue;
			}
			else
			{
				relation_matrix[i][j] = 0;
			}
		}
	}


	return relation_matrix;

}

//find one day flight sequence
vector<vector<string_>>find_oneday_string(vector<leg*>&leg_list_)
{
	vector<vector<string_>>type_strings;

	vector<treenode*>leg_nodes;
	for (int i = 0; i<leg_list_.size(); i++)
	{
		leg_nodes.push_back(new treenode(leg_list_[i]));
	}
	//cout << leg_nodes[1]->leg_->origin_airp << endl;
	//找从每天从各个机场出发的leg

	//vector<vector<treenode*>>day_child_legs;
	vector < vector<treenode*>>airp_child_legs;
	vector<treenode*>child_legs;

	//for (int t = 1; t <= Days; t++)
	//{
		for (int j = 0; j <= airports - 1; j++)
		{
			for (int i = 0; i < leg_nodes.size(); i++)
			{
				if (leg_nodes[i]->leg_->origin_airp == j)
				{
					child_legs.push_back(leg_nodes[i]);
				}
			}
			airp_child_legs.push_back(child_legs);
			child_legs.clear();
			vector<treenode*>().swap(child_legs);
		}
		//day_child_legs.push_back(airp_child_legs);
		//airp_child_legs.clear();
	//}

	//cout << "nodes" << day_child_legs[6][2].size() << endl;
	//cout << "ok" << endl;

	//建立每个airports多天的航班树
	//vector<vector<flight_tree*>>day_flight_trees;
	vector<flight_tree*>airp_flight_trees;
	//for (int j = 1; j <= Days; j++)
	//{
		for (int i = 0; i <= airports - 1; i++)
		{
			airp_flight_trees.push_back(new flight_tree(i, 1, airp_child_legs[i]));
		}
	//	day_flight_trees.push_back(airp_flight_trees);
		//airp_flight_trees.clear();
	//}


	//cout << "ok" << endl;

	//建立以每个过夜机场为出发机场的一周的每天的航班衔接树
	//vector<vector<flight_string*>>day_flight_strings;
	vector<flight_string*>airp_flight_strings;
	vector<treenode*>nodes_;
	//for (int i = 1; i <= Days; i++)
	//{
	for (int j = 0; j <= airports - 1; j++)
		{
			flight_string*flight_string_ = new flight_string(j, 1, airp_child_legs[j]);
			nodes_ = flight_string_->source->source->child_legs;
			flight_string_->creat_string(nodes_, airp_flight_trees);
			airp_flight_strings.push_back(flight_string_);
		}
		//day_flight_strings.push_back(airp_flight_strings);
		//airp_flight_strings.clear();
	//}

	//cout << "ok" << endl;

	cout << "oooooooooooooooooooooooooo" << endl;

	//dfs遍历找到所有的航班串
	//typedef vector<treenode* >string_;
	//typedef vector<string_>strings_;
	vector<string_>airp_string_vec(airports);   //存放一条路径
	vector<strings_>airp_strings_vec(airports);  //存放每个机场的所有路径

	vector<string_>day_strings_vec;//存放一天所有的串



	//for (int i = 1; i <= Days; i++)
	//{
		for (int j = 1; j <= airports; j++)
		{
			treenode*current_ = airp_flight_strings[j - 1]->source->source;
			airp_flight_strings[j - 1]->dfs(airp_strings_vec[j - 1], airp_string_vec[j - 1], current_);
			for (int k = 0; k<leg_nodes.size(); k++)
			{
				leg_nodes[k]->visited = 0;    //为了不影响找下个机场的串
			}
		}
		
		for (int k = 1; k <= airports; k++)
		{
			for (int m = 0; m<airp_strings_vec[k - 1].size(); m++)
			{
				day_strings_vec.push_back(airp_strings_vec[k - 1][m]);
			}
		}
		/*
		for (int k = 1; k <= airports; k++)
		{
			airp_string_vec[k - 1].clear();
		}
		
		for (int k = 1; k <= airports; k++)
		{
			airp_strings_vec[k - 1].clear();
		}
		*/
		//cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << endl;
	//}
	//cout << day_strings_vec[6].size()<< endl;


	cout << "oooooooooooooooooooooooooo" << endl;

	//细分一天的航班串
	vector<string_>s1;  //从维修机场到维修机场的航班串
	vector<string_>s2;  //从维修机场到过夜机场的航班串
	vector<string_>s3;  //从过夜机场到过夜机场的航班串
	vector<string_>s4;  //从过夜机场到维修机场的航班串
	int*base = new int[base_num];
	base[0] = 1; base[1] = 2; //base[2] = 11;   //几个维修机场
	
		for (int i = 0; i<day_strings_vec.size(); i++)
		{
			if (is_base(day_strings_vec[i].front()->leg_->origin_airp, base) && is_base(day_strings_vec[i].back()->leg_->dest_airp, base))
			{
				s1.push_back(day_strings_vec[i]);
			}
			else if (is_base(day_strings_vec[i].front()->leg_->origin_airp, base) && !is_base(day_strings_vec[i].back()->leg_->dest_airp, base))
			{
				s2.push_back(day_strings_vec[i]);
			}
			else if (!is_base(day_strings_vec[i].front()->leg_->origin_airp, base) && !is_base(day_strings_vec[i].back()->leg_->dest_airp, base))
			{
				s3.push_back(day_strings_vec[i]);
			}
			else
			{
				s4.push_back(day_strings_vec[i]);
			}
		}
	






	/*
	cout << "type1_string_:" << endl;
	for (int i = 0; i<s1[0].size(); i++)
	{
		cout <<"leg_size:"<< s1[0][i].size() << endl;
		for (int j = 0; j<s1[0][i].size(); j++)
		{
			cout << s1[0][i][j]->leg_->index << ",";
		}
		cout << endl;
	}
	cout << "type2_string_:" << endl;
	for (int i = 0; i<s2[0].size(); i++)
	{
		cout << "leg_size:"<<s2[0][i].size() << endl;
		for (int j = 0; j<s2[0][i].size(); j++)
		{
			cout << s2[0][i][j]->leg_->index << ",";
		}
		cout << endl;
	}
	cout << "type3_string_:" << endl;
	for (int i = 0; i<s3[0].size(); i++)
	{
		cout <<"leg_size:"<< s3[0][i].size() << endl;
		for (int j = 0; j<s3[0][i].size(); j++)
		{
			cout << s3[0][i][j]->leg_->index << ",";
		}
		cout << endl;
	}
	cout << "type4_string_:" << endl;
	for (int i = 0; i<s4[0].size(); i++)
	{
		cout <<"leg_size:"<< s4[0][i].size() << endl;
		for (int j = 0; j<s4[0][i].size(); j++)
		{
			cout << s4[0][i][j]->leg_->index << ",";
		}
		cout << endl;
	}
	*/
	type_strings.push_back(s1);
	type_strings.push_back(s2);
	type_strings.push_back(s3);
	type_strings.push_back(s4);



	cout << "oooooooooooooooooooooooooo" << endl;
	return type_strings;

}


double cacu_string_cost(string_ _string_, vector<leg*>&weekly_leg_list)
{
	double cost_ = 0;
	for (int j = 0; j<_string_.size(); j++)
	{
		cost_ += _string_[j]->leg_->fixed_cost + _string_[j]->leg_->cover_dual;
	}
	for (int i = 0; i < _string_.size(); i++)
	{
		for (int j = 0; j<weekly_leg_list.size(); j++)
		{
			if (weekly_leg_list[j]->index2 == _string_[i]->leg_->index)
			{
				//cout << weekly_leg_list[j]->leg_capacity << endl;
				//cout << weekly_leg_list[j]->capacity_dual << endl;
				cost_ = cost_ - weekly_leg_list[j]->leg_capacity*weekly_leg_list[j]->capacity_dual;
			}
		}
	}
	//-_string_[j]->leg_->leg_capacity*_string_[j]->leg_->capacity_dual;
	return cost_;
}


//string shortest path
vector<oper_rotation*>add_string(int*base, vector<vector<string_>>type_strings, double aircraft_dual, vector<leg*>leg_list, int M_num, vector<vector<G_arc*>>daily_gc_, vector<leg*>weekly_leg_list_, vector<seq_node>nodes1, vector<seq_node>nodes2) // type_strings是各种string,s1-s4
{
	vector<string_>s1 = type_strings[0];   //一天的从M-M的串
	//vector<string_>s2 = type_strings[1];//一天的从M-O的串
	//vector<string_>s3 = type_strings[2];//O-O
	//vector<string_>s4 = type_strings[3];//O-M

	//vector<pair<string_, int>>s1;
	vector<pair<string_, int>>s2;
	vector<pair<string_, int>>s3;
	vector<pair<string_, int>>s4;

	for (int i=0;i<type_strings[1].size();i++)
	{

		s2.push_back(pair<string_, int>(type_strings[1][i], get_rs_2(s2_string_rs(type_strings[1][i], daily_gc_))));
	}
	for (int i = 0; i<type_strings[2].size(); i++)
	{

		s3.push_back(pair<string_, int>(type_strings[2][i], get_rs_2(s3_string_rs(type_strings[2][i], daily_gc_))));
	}
	for (int i = 0; i<type_strings[3].size(); i++)
	{

		s4.push_back(pair<string_, int>(type_strings[3][i], get_rs_2(s4_string_rs(type_strings[3][i], daily_gc_))));
	}

	vector<oper_rotation*>all_strings;
	
	vector<vector<oper_rotation*>>one_day_strings(M_num*M_num);
	vector<oper_rotation*>one_day_string(M_num*M_num);
	vector<vector<string_>>s1_types(M_num*M_num);
    	int t = 0;
		for (int j=0;j<M_num;j++)
		{
			for (int k=0;k<M_num;k++)
			{
				for (int i = 0; i<s1.size(); i++)
				{
				    if (s1[i].front()->leg_->origin_airp==base[j]&&s1[i].back()->leg_->dest_airp==base[k])
				   {
					s1_types[t].push_back(s1[i]);
			       }
			    }
				t++;
	    }
	}
	vector<leg*>legs;
	for (int k=0;k<t;k++)
	{
		for (int i = 0; i <s1_types[k].size(); i++)
		{
			for (int j = 0; j < s1_types[k][i].size(); j++)
			{
				legs.push_back(leg_list[s1_types[k][i][j]->leg_->index]);
			}
			one_day_strings[k].push_back(new oper_rotation(i, legs));
			legs.clear();
		}
	}
	for (int k = 0; k < t; k++)
	{
		for (int i = 0; i < one_day_strings[k].size(); i++)
		{
			one_day_strings[k][i]->add_gc(daily_gc_);   //for caculating amount of aircraft
		}
	}
	for (int k = 0; k < t; k++)
	{
		double rc_ = one_day_strings[k][0]->cacu_RC(aircraft_dual,weekly_leg_list_);
		one_day_string[k] = one_day_strings[k][0];
		for (int i = 1; i < one_day_strings[k].size(); i++)
		{
			double _rc = one_day_strings[k][i]->cacu_RC(aircraft_dual,weekly_leg_list_);
			if (_rc > rc_)
			{
				one_day_string[k] = one_day_strings[k][i];
			}
		}
		//all_strings.push_back(one_day_string);
	}
	for (int i=0;i<one_day_string.size();i++)
	{
		all_strings.push_back(one_day_string[i]);
	}

	//cout << "000000000000000000" << endl;
	vector<vector<pair<string_,int>>>two_day_strings;
	two_day_strings.push_back(s2); two_day_strings.push_back(s4);
	vector<seq_node>new_nodes=update_twoday_string_graph(nodes1, aircraft_dual, weekly_leg_list_, two_day_strings, M_num);
	vector<oper_rotation*>two_day_find_sps_ = two_day_find_sp(base,new_nodes, two_day_strings, M_num, leg_list);
	for (int i = 0; i<two_day_find_sps_.size(); i++)
	{
		two_day_find_sps_[i]->add_gc(daily_gc_);   //for caculating amount of aircraft
	}
	for (int i = 0; i<two_day_find_sps_.size(); i++)
	{
		all_strings.push_back(two_day_find_sps_[i]);
	}

	cout << "22222222" << endl;
	vector<vector<pair<string_, int>>>three_day_strings;
	three_day_strings.push_back(s2); three_day_strings.push_back(s3); three_day_strings.push_back(s4);
	cout << "22222222" << endl;
	vector<seq_node>new_node2 = update_threeday_string_graph(nodes2, aircraft_dual, weekly_leg_list_, three_day_strings, M_num);
	cout << "22222222" << endl;  
	vector<oper_rotation*>three_day_find_sps_ = three_day_find_sp(base, new_node2,three_day_strings, M_num, leg_list);

	//cout << "kkkkkkkkkkkkk" << endl;
	for (int i = 0; i<three_day_find_sps_.size(); i++)
	{
		three_day_find_sps_[i]->add_gc(daily_gc_);   //for caculating amount of aircraft
	}
	for (int i = 0; i<three_day_find_sps_.size(); i++)
	{
		all_strings.push_back(three_day_find_sps_[i]);
	}
	//cout << "all_strings_size:::" << all_strings.size() << endl;
	return all_strings;
}

bool can_connect(string_ string_1, string_ string_2)
{
	for (int i = 0; i<string_1.size(); i++)
	{
		for (int j = 0; j<string_2.size(); j++)
		{
			if (string_1[i]->leg_->index == (string_2[j]->leg_->index))
			{
				return false;
			}
		}
	}
	return true;
}

pair<double*, int*>string_Dijkstra2(int source, double**cost_matrix, int num, vector<vector<string_>>three_day_strings,int M_num)
{

	int size1 = three_day_strings[0].size();
	int size2 = three_day_strings[1].size();
	int size3 = three_day_strings[2].size();

	cout << "size1" <<size1<< endl;
	cout << "size1" <<size2<< endl;
	cout << "size1" << size3<<endl;
	cout << "num" << num << endl;
	vector<string_>s2_ = three_day_strings[0];
	vector<string_>s3_ = three_day_strings[1];
	vector<string_>s4_ = three_day_strings[2];

	//int node_num = M_num + size1 + size2 + size3 + M_num;
	//cout << endl;
	vector<bool> isvisited(num, false);                 //是否已经在S集合中  
	double*dis_ = new double[num];
	int*pre_ = new int[num];
	for (int i = 0; i < num; ++i)
	{
		dis_[i] = cost_matrix[source][i];
		if (cost_matrix[source][i] < INF)
			pre_[i] = source;
		else
			pre_[i] = -1;
	}
	pre_[source] = -1;
	isvisited[source] = true;
	int u = source;
	for (int i = 1; i < num; i++)
	{
		int nextVertex = u;
		cout << "----"<<u << endl;
		double tempDistance = INF;
		if (u >= M_num + size1&&u<M_num + size1+size2)
		{
			cout << "hhhhhhhhhh" << endl;
			for (int j = 0; j < num; ++j)
			{
				if ((isvisited[j] == false) && (dis_[j] < tempDistance) && can_connect(s2_[pre_[u] - M_num], s4_[j - M_num - size1 - size2]))
				{
					cout << "fffffff" << endl;
					nextVertex = j;
					tempDistance = dis_[j];
				}
			}
		}
		else
		{
			cout << "-----hhhh" << endl;
			for (int j = 0; j < num; ++j)
			{
			if ((isvisited[j] == false) && (dis_[j] < tempDistance))
			{
						nextVertex = j;
						tempDistance = dis_[j];
			}
			}

			cout << "0000" << tempDistance << "9999" << nextVertex << endl;
		}
		
		isvisited[nextVertex] = true;
		pre_[nextVertex] = u;
		dis_[nextVertex] = tempDistance;
		u = nextVertex;
		for (int j = 0; j < num; j++)
		{
			if (isvisited[j] == false && cost_matrix[u][j] < INF)
			{
				double temp = dis_[u] + cost_matrix[u][j];
				if (temp < dis_[j])
				{
					dis_[j] = temp;
					pre_[j] = u;
				}
			}
		}
	}

	pair<double*, int*>result_(dis_, pre_);
	return result_;
}

/*
pair<double*, int*>string_Dijkstra(int source, double**cost_matrix, int num)
{

	//cout << endl;
	vector<bool> isvisited(num, false);                 //是否已经在S集合中  
	double*dis_ = new double[num];
	int*pre_ = new int[num];
	for (int i = 0; i < num; ++i)
	{
		dis_[i] = cost_matrix[source][i];
		if (cost_matrix[source][i] < INF)
			pre_[i] = source;
		else
			pre_[i] = -1;
	}
	pre_[source] = -1;
	isvisited[source] = true;
	int u = source;
	for (int i = 1; i < num; i++)
	{
		int nextVertex = u;
		double tempDistance = INF;
		for (int j = 0; j < num; ++j)
		{
				if ((isvisited[j] == false) && (dis_[j] < tempDistance))
				{
					nextVertex = j;
					tempDistance = dis_[j];
				}
		}
		isvisited[nextVertex] = true;
		pre_[nextVertex] = u;
		dis_[nextVertex] = tempDistance;
		u = nextVertex;

		for (int j = 0; j < num; j++)
		{
			if (isvisited[j] == false && cost_matrix[u][j] < INF)
			{
				double temp = dis_[u] + cost_matrix[u][j];
				if (temp < dis_[j])
				{
					dis_[j] = temp;
					pre_[j] = u;
				}
			}
		}
	}

	pair<double*, int*>result_(dis_, pre_);
	return result_;
}
*/

vector<seq_node>init_twoday_string_Graph(int*base, vector<vector<pair<string_,int>>>&two_day_strings_, int M_num,double aircraft_dual_,vector<leg*>week_leg_list)
{
	
	vector<pair<string_,int>>s2_ = two_day_strings_[0];
	vector<pair<string_,int>>s4_ = two_day_strings_[1];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s4_.size();
	int node_num = size1 + size2 + M_num + M_num;
	cout << "-----------------" << s4_.size() << endl;
	vector<seq_node>nodes(node_num);
	//vector<Edge>edges;
	cout << "-----------------" << s4_.size() << endl;
	//int s = 0;
	
	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num + size1; j++)
		{
			if (s2_[j - M_num].first.front()->leg_->origin_airp == base[i])
			{
				nodes[i].index = i;
				//edges[s].u = i; edges[s].v = j;
				double cost_ = s2_[j - M_num].first.front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s2_[j - M_num].second;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				//edges.push_back(Edge(i, j, cost_));
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				//	s++;
			}
		}
	}

	cout << "-----------------" << s4_.size() << endl;

	for (int i = M_num; i < M_num + size1; i++)
	{
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2_[i - M_num].first.back()->leg_->dest_airp == s4_[j - M_num - size1].first.front()->leg_->origin_airp&&can_connect(s2_[i - M_num].first, s4_[j - M_num - size1].first))
			{
				//edges[s].u = i; edges[s].v = j;
				//edges[s].cost_ = cacu_string_cost(s4_[j - M_num - size1], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[j - M_num - size1], daily_gc_));
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				//s++;
				nodes[i].index = i;
				//nodes[i].children.push_back(j);
				double cost_ = cacu_string_cost(s4_[j - M_num - size1].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s4_[j - M_num - size1].second;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				//cout << "rrrrrrrrrrrrr" << cost_matrix[i][j]<<endl;
				//edges.push_back(Edge(i, j, cost_));
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1; i < M_num + size1 + size2; i++)
	{
		for (int j = M_num + size1 + size2; j <M_num + size1 + size2 + M_num; j++)
		{

			if (s4_[i - M_num - size1].first.back()->leg_->dest_airp == base[j - M_num - size1 - size2])
			{
				//edges[s].u = i; edges[s].v = j;
				//edges[s].cost_ = -s4_[i - M_num - size1].back()->leg_->balance2_dual;
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				nodes[i].index = i;
				//nodes[i].children.push_back(j);
				double cost_ = -s4_[i - M_num - size1].first.back()->leg_->balance2_dual;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				//edges.push_back(Edge(i, j, cost_));
				//s++;
			}
		}
	}
	return nodes;
}

vector<seq_node>update_twoday_string_graph(vector<seq_node>nodes, double aircraft_dual_, vector<leg*>week_leg_list, vector<vector<pair<string_, int>>>&two_day_strings_, int M_num)
{
	vector<pair<string_, int>>s2_ = two_day_strings_[0];
	vector<pair<string_, int>>s4_ = two_day_strings_[1];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s4_.size();
	int node_num = size1 + size2 + M_num + M_num;
	vector<seq_node>new_nodes;

	for (int i=0;i<M_num;i++)
	{
		for (int j=0;j<nodes[i].children.size();j++)
		{
			nodes[i].children[j].second= s2_[nodes[i].children[j].first- M_num].first.front()->leg_->balance1_dual + cacu_string_cost(s2_[nodes[i].children[j].first - M_num].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s2_[nodes[i].children[j].first- M_num].second;
		}
	}

	for (int i = M_num; i<M_num+size1; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = cacu_string_cost(s4_[nodes[i].children[j].first - M_num - size1].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s4_[nodes[i].children[j].first - M_num - size1].second;
		}
	}

	for (int i = M_num+size1; i<M_num+size1+size2; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = -s4_[i - M_num - size1].first.back()->leg_->balance2_dual;
		}
	}

	new_nodes = nodes;
	return new_nodes;
}


vector<seq_node>init_threeday_string_Graph(int*base, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num, double aircraft_dual_, vector<leg*>week_leg_list)
{
	
	vector<pair<string_, int>>s2_ = three_day_strings_[0];
	vector<pair<string_, int>>s3_ = three_day_strings_[1];
	vector<pair<string_, int>>s4_ = three_day_strings_[2];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s3_.size();
	int size3 = s4_.size();
	
	int node_num = M_num + size1 + size2 + size3 + M_num;

	vector<seq_node>nodes(node_num);
	//vector<Edge>edges;
	cout << "-----------------" << s4_.size() << endl;
	//int s = 0;
	double cost_;
	for (int i = 0; i < M_num; i++)
	{
		nodes[i].index = i;
		for (int j = M_num; j < M_num + size1; j++)
		{
			if (s2_[j - M_num].first.front()->leg_->origin_airp == base[i])
			{

				
				cost_ = s2_[j - M_num].first.front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s2_[j - M_num].second;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				
			}
		}
	}

	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num; i < M_num + size1; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2_[i - M_num].first.back()->leg_->dest_airp == s3_[j - M_num - size1].first.front()->leg_->origin_airp)
			{
				if (can_connect(s2_[i - M_num].first, s3_[j - M_num - size1].first))
				{
					
					cost_ = cacu_string_cost(s3_[j - M_num - size1].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s3_[j - M_num - size1].second;
					nodes[i].children.push_back(pair<int, double>(j, cost_));
					
				}
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1; i < M_num + size1 + size2; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1 + size2; j <M_num + size1 + size2 + size3; j++)
		{
			if (s3_[i - M_num - size1].first.back()->leg_->dest_airp == s4_[j - M_num - size1 - size2].first.front()->leg_->origin_airp)
			{
				//cout << "hhhhhhhhhhhhhhh" << endl;
				if (can_connect(s3_[i - M_num - size1].first, s4_[j - M_num - size1 - size2].first))
				{
					
					cost_ = cacu_string_cost(s4_[j - M_num - size1 - size2].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s4_[j - M_num - size1 - size2].second;
					// cout << "----888888888--" << s4_.size() << endl;
					nodes[i].children.push_back(pair<int, double>(j, cost_));
				
				}
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1 + size2; i < M_num + size1 + size2 + size3; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1 + size2 + size3; j <M_num + size1 + size2 + size3 + M_num; j++)
		{
			if (s4_[i - M_num - size1 - size2].first.back()->leg_->dest_airp == base[j - M_num - size1 - size2 - size3])
			{
				
				cost_ = -s4_[i - M_num - size1 - size2].first.back()->leg_->balance2_dual;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
			}
		}
	}

	return nodes;
}

vector<seq_node>update_threeday_string_graph(vector<seq_node>nodes, double aircraft_dual_, vector<leg*>week_leg_list, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num)
{

	cout << "111111111111" << endl;
	vector<pair<string_, int>>s2_ = three_day_strings_[0];
	vector<pair<string_, int>>s3_ = three_day_strings_[1];
	vector<pair<string_, int>>s4_ = three_day_strings_[2];
	

	int size1 = s2_.size();
	int size2 = s3_.size();
	int size3 = s4_.size();

	int node_num = M_num + size1 + size2 + size3 + M_num;
	vector<seq_node>new_nodes;

	for (int i = 0; i<M_num; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = s2_[nodes[i].children[j].first - M_num].first.front()->leg_->balance1_dual + cacu_string_cost(s2_[nodes[i].children[j].first - M_num].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s2_[nodes[i].children[j].first - M_num].second;
		}
	}

	cout << "111111111111" << endl;
	for (int i = M_num; i<M_num + size1; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = cacu_string_cost(s3_[nodes[i].children[j].first - M_num - size1].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s3_[nodes[i].children[j].first - M_num - size1].second;
		}
	}
	cout << "111111111111" << endl;
	for (int i = M_num+size1; i<M_num + size1+size2; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = cacu_string_cost(s4_[nodes[i].children[j].first - M_num - size1-size2].first, week_leg_list) + (aircraft_fc + aircraft_dual_)*s4_[nodes[i].children[j].first - M_num - size1-size2].second;
		}
	}
	cout << "111111111111" << endl;
	for (int i = M_num + size1+size2; i<M_num + size1 + size2+size3; i++)
	{
		for (int j = 0; j<nodes[i].children.size(); j++)
		{
			nodes[i].children[j].second = -s4_[i - M_num - size1-size2].first.back()->leg_->balance2_dual;
		}
	}
	cout << "111111111111" << endl;
	new_nodes = nodes;
	return new_nodes;
}



vector<oper_rotation*>two_day_find_sp(int*base,vector<seq_node>&nodes, vector<vector<pair<string_, int>>>&two_day_strings_, int M_num, vector<leg*>&leg_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	vector<pair<string_, int>>s2_ = two_day_strings_[0];
	vector<pair<string_, int>>s4_ = two_day_strings_[1];
	

	int size1 = s2_.size();
	int size2 = s4_.size();
	int node_num = size1 + size2 + M_num + M_num;
	/*
	vector<string_>s2_ = two_day_strings_[0];
	vector<string_>s4_ = two_day_strings_[1];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s4_.size();
	int node_num = size1 + size2 + M_num+M_num;
	cout << "-----------------" << s4_.size() << endl;
	/*
	double ** cost_matrix = new double *[node_num];
	for (int i = 0; i < node_num; i++)
	{
		cost_matrix[i] = new double[node_num];
	}

	for (int i = 0; i < node_num; i++)
	{
		for (int j = 0; j< node_num; j++)
		{
			cost_matrix[i][j] = INF;
		}
	}
	
	vector<seq_node>nodes(node_num);
	//vector<Edge>edges;
	cout << "-----------------" << s4_.size() << endl;
	//int s = 0;
	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num + size1; j++)
		{
			if (s2_[j - M_num].front()->leg_->origin_airp == base[i])
			{
				nodes[i].index = i;
				//edges[s].u = i; edges[s].v = j;
				double cost_=s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num],week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				nodes[i].children.push_back(pair<int,double>(j,cost_));
				// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				//edges.push_back(Edge(i, j, cost_));
			   //cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
			//	s++;
			}
		}
	}

	cout << "-----------------" << s4_.size() << endl;

	for (int i = M_num; i < M_num + size1; i++)
	{
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2_[i - M_num].back()->leg_->dest_airp == s4_[j - M_num - size1].front()->leg_->origin_airp&&can_connect(s2_[i - M_num], s4_[j - M_num - size1]))
			{
				//edges[s].u = i; edges[s].v = j;
				//edges[s].cost_ = cacu_string_cost(s4_[j - M_num - size1], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[j - M_num - size1], daily_gc_));
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				//s++;
				nodes[i].index = i;
				//nodes[i].children.push_back(j);
				double cost_ = cacu_string_cost(s4_[j - M_num - size1],week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[ j - M_num - size1], daily_gc_));
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				//cout << "rrrrrrrrrrrrr" << cost_matrix[i][j]<<endl;
				//edges.push_back(Edge(i, j, cost_));
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1; i < M_num + size1 + size2; i++)
	{
		for (int j = M_num + size1 + size2; j <M_num + size1 + size2 + M_num; j++)
		{

			if (s4_[i - M_num - size1].back()->leg_->dest_airp == base[j - M_num - size1 - size2])
			{
				//edges[s].u = i; edges[s].v = j;
				//edges[s].cost_ = -s4_[i - M_num - size1].back()->leg_->balance2_dual;
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				nodes[i].index = i;
				//nodes[i].children.push_back(j);
				double cost_= -s4_[i - M_num - size1].back()->leg_->balance2_dual;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				//edges.push_back(Edge(i, j, cost_));
				//s++;
			}
		}
	}
	*/

	cout << "99999999999999999999999999999999999" << endl;
	vector<oper_rotation*>two_day_sps;
	//int t = 0;
	vector<leg*>legs;
	pair<bool, int*>sp_info;
	int t = 0;
	for (int i = 0; i<M_num; i++)
	{
		cout << "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjj" <<nodes.size()<< endl;
		//cout << "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjj" << edges.size()<< endl;
		sp_info = SPFA1(nodes, i, node_num);
		if (sp_info.first)
		{
			for (int j = M_num + size1 + size2; j < node_num; j++)
			{
				t++;
				cout << "arrive base" << base[j - M_num - size1 - size2] << ".";
				cout << s4_[sp_info.second[j] - M_num - size1].first.size() << endl;
				for (int k = 0; k < s2_[sp_info.second[sp_info.second[j]] - M_num].first.size(); k++)
				{
					legs.push_back(leg_list[s2_[sp_info.second[sp_info.second[j]] - M_num].first[k]->leg_->index]);
				}
				for (int k = 0; k < s4_[sp_info.second[j] - M_num - size1].first.size(); k++)
				{
					legs.push_back(leg_list[s4_[sp_info.second[j] - M_num - size1].first[k]->leg_->index]);
				}
				cout << "departure from" << base[i] << "。";
				two_day_sps.push_back(new oper_rotation(t, legs));
				legs.clear();
				vector<leg*>().swap(legs);
			}
		}
		else
		{
			cout << "have_negative_circle" << endl;
		}
	}

	/*
	for (int i = 0; i < node_num; i++)
	{
		delete[] cost_matrix[i];
	}
	delete[] cost_matrix;
	*/
	

	return two_day_sps;
	/*
	vector<vector<string_>>two_strings(M_num*M_num);
	int t = 0;
	for (int i = 0; i < M_num; i++)
	{
		for (int k = 0; k < M_num; k++)
		{
			//sp_info = string_Dijkstra(i, cost_matrix, node_num);
			double tempDistance = INF;
			int s2_index = 0;
			for (int j = 0; j < s2_.size(); j++)
			{
				if (cost_matrix[i][M_num + j] < tempDistance)
				{
					tempDistance = cost_matrix[i][M_num + j];
					s2_index = j;
				}
			}
			two_strings[t].push_back(s2_[s2_index]);

			tempDistance = INF;
			int s4_index = 0;
			for (int j = 0; j < s4_.size(); j++)
			{
				if (s4_[j].back()->leg_->dest_airp == base[k])
				{
					if (cost_matrix[M_num + s2_index][M_num + size1 + j] < tempDistance)
					{
						tempDistance = cost_matrix[M_num + s2_index][M_num + size1 + j];
						s4_index = j;
					}
				}
			}
			two_strings[t].push_back(s4_[s4_index]);
			t++;
		}
	}
	for (int i=0;i<two_strings.size();i++)
	{
		for (int j=0;j<two_strings[i].size();j++)
		{
			for (int k=0;k<two_strings[i][j].size();k++)
			{
				legs.push_back(two_strings[i][j][k]->leg_);
			}
		}
		two_day_sps.push_back(new oper_rotation(1, legs));
		legs.clear();
	}
	/*
		for (int j = M_num + size1 + size2; j<node_num; j++)
		{
			t++;
		//	cout << "arrive base" << base[j - M_num - size1 - size2] << "。";
		//	cout << s4_[sp_info.second[j] - M_num - size1].size() << endl;
			for (int k = 0; k<s2_[sp_info.second[sp_info.second[j]] - M_num].size(); k++)
			{
				legs.push_back(leg_list[s2_[sp_info.second[sp_info.second[j]] - M_num][k]->leg_->index]);
			}
			for (int k = 0; k < s4_[sp_info.second[j] - M_num - size1].size(); k++)
			{
				legs.push_back(leg_list[s4_[sp_info.second[j] - M_num - size1][k]->leg_->index]);
			}
		//	cout << "departure from" << base[i] << "。";
			two_day_sps.push_back(new oper_rotation(t, legs));
			legs.clear();
		}
	}
	
	cout << "555555555555555555555" << two_day_sps.size() << endl;
	for (int i=0;i<two_day_sps.size();i++)
	{
		for (int j=0;j<two_day_sps[i]->legs.size();j++)
		{
			cout << two_day_sps[i]->legs[j]->index << ",";
		}
		cout << endl;
	}

	//cout << "555555555555555555555" << two_day_sps[0]->legs.size() << endl;
	*/
	
}

pair<bool, int*>SPFA1(vector<seq_node>nodes,int source,int num_)
{
	double*dis_ = new double[num_];
	int*pre_ = new int[num_];
	queue<int>queue_;
	vector<bool>visit_(num_, false);  
	int*count = new int[num_];  //入队次数
	for (int i=0;i<num_;i++)
	{
		dis_[i] = INF;
	}
	for (int i = 0; i<num_; i++)
	{
		pre_[i] = -1;
	}
	for (int i = 0; i<num_; i++)
	{
		count[i] = 0;
	}

	dis_[source] = 0;  
	queue_.push(source);
	count[source]++;
	visit_[source] = true;

	while (!queue_.empty())
	{
		cout<<"---------------"<<queue_.size() << endl;
		int u = queue_.front();
		visit_[u] = false;
		queue_.pop();
	//	cout << "oooooooooooo" << nodes[u].children.size() << endl;
		for (int i=0;i<nodes[u].children.size();i++)
		{
			/*
			double _cost_;
			//cout << "lllllllllllllllllllllllll" << endl;
		//	cout << "oooooooooooo" << edges.size() << endl;
			for (int k=0;k<edges.size();k++)
			{
				//cout << "jjjjjjjjjjjjjjjjjjjjjj" << endl;
				if (edges[k].u==u&&edges[k].v==nodes[u].children[i])
				{
					//cout << "find" << endl;
					_cost_ = edges[k].cost_;
					break;
				}
			}
			*/
			if (dis_[nodes[u].children[i].first]>dis_[u]+nodes[u].children[i].second)  //松弛
			{
				//cout << "ok" << endl;
				dis_[nodes[u].children[i].first] = dis_[u] + nodes[u].children[i].second;
				pre_[nodes[u].children[i].first] = u;
				if (!visit_[nodes[u].children[i].first])   //i不在队列
				{
					queue_.push(nodes[u].children[i].first);
					count[nodes[u].children[i].first]++;
					if (count[nodes[u].children[i].first] >= num_)  //存在负权环
					{
						return pair<bool, int*>(false, pre_);
					}
					visit_[nodes[u].children[i].first] = true;
				}
			}
		}
	}
	return pair<bool, int*>(true, pre_);
}

pair<bool, int*>SPFA2(vector<seq_node>nodes, int source, int num_, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num)
{

	vector<pair<string_, int>>s2_ = three_day_strings_[0];
	vector<pair<string_, int>>s3_ = three_day_strings_[1];
	vector<pair<string_, int>>s4_ = three_day_strings_[2];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s3_.size();
	int size3 = s4_.size();

	//int node_num = M_num + size1 + size2 + size3 + M_num;

	double*dis_ = new double[num_];
	int*pre_ = new int[num_];
	queue<int>queue_;
	vector<bool>visit_(num_, 0);
	int*count = new int[num_];
	for (int i = 0; i<num_; i++)
	{
		dis_[i] = INF;
	}
	for (int i = 0; i<num_; i++)
	{
		pre_[i] = -1;
	}
	for (int i = 0; i<num_; i++)
	{
		count[i] = 0;
	}

	dis_[source] = 0;
	queue_.push(source);
	count[source]++;
	visit_[source] = 1;

	while (!queue_.empty())
	{
		int u = queue_.front();
		visit_[u] = 0;
		queue_.pop();
		if (u>=M_num+size1&&u<M_num+size1+size2)
		{
			for (int i = 0; i<nodes[u].children.size(); i++)
			{

				if (dis_[nodes[u].children[i].first]>dis_[u] + nodes[u].children[i].second &&can_connect(s2_[pre_[u]-M_num].first,s4_[nodes[u].children[i].first -M_num-size1-size2].first))
				{
					dis_[nodes[u].children[i].first] = dis_[u] + nodes[u].children[i].second;
					pre_[nodes[u].children[i].first] = u;
					if (!visit_[nodes[u].children[i].first])
					{
						queue_.push(nodes[u].children[i].first);
						count[nodes[u].children[i].first]++;
						if (count[nodes[u].children[i].first] >= num_)
						{
							return pair<bool, int*>(false, pre_);
						}
						visit_[nodes[u].children[i].first] = 1;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i<nodes[u].children.size(); i++)
			{

				if (dis_[nodes[u].children[i].first]>dis_[u] + nodes[u].children[i].second)
				{
					dis_[nodes[u].children[i].first] = dis_[u] + nodes[u].children[i].second;
					pre_[nodes[u].children[i].first] = u;
					if (!visit_[nodes[u].children[i].first])
					{
						queue_.push(nodes[u].children[i].first);
						count[nodes[u].children[i].first]++;
						if (count[nodes[u].children[i].first] >= num_)
						{
							return pair<bool, int*>(false, pre_);
						}
						visit_[nodes[u].children[i].first] = 1;
					}
				}
			}
		}
	}
	return pair<bool, int*>(true, pre_);
}


/*
pair<bool,int*>Bellman_Ford(int nodenum,int original, vector<Edge>edge,int edgenum)
{
	double *dis=new double[nodenum];int *pre=new int[nodenum];
	pre[original] = original;
	for (int i = 0; i <nodenum; ++i) //初始化  
	{
		dis[i] = (i == original ? 0 : INF);
	}
	for (int i = 0; i <= nodenum ; ++i)
	{
		for (int j = 0; j <edgenum; ++j)
		{
			if (dis[edge[j].v] > dis[edge[j].u] + edge[j].cost_) //松弛 
			{
				dis[edge[j].v] = dis[edge[j].u] + edge[j].cost_;
				pre[edge[j].v] = edge[j].u;
			}
		}
	}
	bool flag = 1; //判断是否含有负权回路  
	for (int i = 0; i <=edgenum; ++i)
	{
		if (dis[edge[i].v] > dis[edge[i].u] + edge[i].cost_)
		{
			flag = 0;
			break;
		}
	}
	//vector<int>path_index;
	pair<bool, int*>result_;
	result_.first = flag;
	result_.second = pre;
	return result_;
}



pair<bool, int*>Bellman_Ford2(int nodenum, int original, vector<Edge>edge, int edgenum, vector<vector<string_>>three_day_strings,int M_num)
{

	int size1 = three_day_strings[0].size();
	int size2 = three_day_strings[1].size();
	int size3 = three_day_strings[2].size();

	vector<string_>s2_ = three_day_strings[0];
	vector<string_>s3_ = three_day_strings[1];
	vector<string_>s4_ = three_day_strings[2];

	double *dis = new double[nodenum]; int *pre = new int[nodenum];
	pre[original] = original;
	for (int i = 0; i <nodenum; ++i) //初始化  
	{
		dis[i] = (i == original ? 0 : INF);
	}
	for (int i = 0; i <= nodenum; ++i)
	{
		for (int j = 0; j <edgenum; ++j)
		{
			if (edge[j].v>=M_num+size1+size2&&edge[j].v<M_num+size1+size2+size3)
			{
				if (dis[edge[j].v] > dis[edge[j].u] + edge[j].cost_&&can_connect(s2_[pre[edge[j].u] - M_num], s4_[edge[j].v - M_num - size1 - size2])) //松弛 
				{
					dis[edge[j].v] = dis[edge[j].u] + edge[j].cost_;
					pre[edge[j].v] = edge[j].u;
				}
			}
			else
			{
				if(dis[edge[j].v] > dis[edge[j].u] + edge[j].cost_) //松弛 
				{
					dis[edge[j].v] = dis[edge[j].u] + edge[j].cost_;
					pre[edge[j].v] = edge[j].u;
				}
			}
		}
	}
	bool flag = 1; //判断是否含有负权回路  
	for (int i = 0; i <= edgenum; ++i)
	{
		if (dis[edge[i].v] > dis[edge[i].u] + edge[i].cost_)
		{
			flag = 0;
			break;
		}
	}
	//vector<int>path_index;
	pair<bool, int*>result_;
	result_.first = flag;
	result_.second = pre;
	return result_;
}
void print_path(int root) //打印最短路的路径（反向）  
{
	while (root != pre[root]) //前驱  
	{
		printf("%d-->", root);
		root = pre[root];
	}
	if (root == pre[root])
		printf("%d\n", root);
}
*/

vector<oper_rotation*>three_day_find_sp(int*base, vector<seq_node>&nodes, vector<vector<pair<string_, int>>>&three_day_strings_, int M_num, vector<leg*>&leg_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	cout << "11111111111111111" << endl;
	vector<pair<string_, int>>s2_ = three_day_strings_[0];
	vector<pair<string_, int>>s3_ = three_day_strings_[1];
	vector<pair<string_, int>>s4_ = three_day_strings_[2];
	cout << "-----------------" << s2_.size() << endl;
	cout << "-----------------" << s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s3_.size();
	int size3 = s4_.size();

	int node_num = M_num + size1 + size2 + size3 + M_num;
	
	/*
	double ** cost_matrix = new double *[node_num];
	for (int i = 0; i < node_num; i++)
	{
		cost_matrix[i] = new double[node_num];
	}
	//初始化
	for (int i = 0; i < node_num; i++)
	{
		for (int j = 0; j< node_num; j++)
		{
			cost_matrix[i][j] = INF;
		}
	}
	
	*/
	//vector<Edge>edges(node_num*node_num);

	//vector<seq_node>nodes(node_num);
	//vector<Edge>edges;
	/*
	cout << "-----------------" << s4_.size() << endl;
	//int s = 0;
	double cost_;
	for (int i = 0; i < M_num; i++)
	{
		nodes[i].index = i;
		for (int j = M_num; j < M_num + size1; j++)
		{
			if (s2_[j - M_num].front()->leg_->origin_airp == base[i])
			{
				
				//nodes[i].children.push_back(j);
				//edges[s].u = i; edges[s].v = j;
				cost_ = s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				//edges.push_back(Edge(i, j, cost_));
				//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				//	s++;
			}
		}
	}

	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num; i < M_num + size1; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2_[i - M_num].back()->leg_->dest_airp == s3_[j - M_num - size1].front()->leg_->origin_airp)
			{
				if (can_connect(s2_[i - M_num], s3_[j - M_num - size1]))
				{
					//	edges[s].u = i; edges[s].v = j;
					//	edges[s].cost_ = cacu_string_cost(s3_[j - M_num - size1], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s3_string_rs(s3_[j - M_num - size1], daily_gc_));
						//	cout << "iiii99999iii" << cost_matrix[i][j] << endl;
						//nodes[i].children.push_back(j);
						//edges[s].u = i; edges[s].v = j;
					cost_ = cacu_string_cost(s3_[j - M_num - size1], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s3_string_rs(s3_[j - M_num - size1], daily_gc_));
					nodes[i].children.push_back(pair<int, double>(j, cost_));
					// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
					//edges.push_back(Edge(i, j, cost_));
				//	s++;
					//cost_matrix[i][j] = cacu_string_cost(s3_[j - M_num - size1],week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s3_string_rs(s3_[j - M_num - size1], daily_gc_));
					//cout << "iiiiiiiiiiiiii" << cost_matrix[i][j] << endl;
				}
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1; i < M_num + size1 + size2; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1 + size2; j <M_num + size1 + size2 + size3; j++)
		{
			if (s3_[i - M_num - size1].back()->leg_->dest_airp == s4_[j - M_num - size1 - size2].front()->leg_->origin_airp)
			{
				//cout << "hhhhhhhhhhhhhhh" << endl;
				if (can_connect(s3_[i - M_num - size1], s4_[j - M_num - size1 - size2]))
				{
					//cout << "888888"<<endl;
					//edges[s].u = i; edges[s].v = j;
					//edges[s].cost_ = cacu_string_cost(s4_[j - M_num - size1 - size2], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[j - M_num - size1 - size2], daily_gc_));
					//	cout << "iiii99999iii" << cost_matrix[i][j] << endl;
					//nodes[i].children.push_back(j);
					//edges[s].u = i; edges[s].v = j;
					//cout << "----888888888--" << s4_.size() << endl;
					cost_ = cacu_string_cost(s4_[j - M_num - size1 - size2], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[j - M_num - size1 - size2], daily_gc_));
					// cout << "----888888888--" << s4_.size() << endl;
					nodes[i].children.push_back(pair<int, double>(j, cost_));
					// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
					//edges.push_back(Edge(i, j, cost_));
				//	s++;
				//	cost_matrix[i][j] = cacu_string_cost(s4_[j - M_num - size1 - size2],week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s4_string_rs(s4_[j - M_num - size1 - size2], daily_gc_)) ;
					//cout << "iii44444ii" << cost_matrix[i][j] << endl;
				}
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	for (int i = M_num + size1 + size2; i < M_num + size1 + size2 + size3; i++)
	{
		nodes[i].index = i;
		for (int j = M_num + size1 + size2 + size3; j <M_num + size1 + size2 + size3 + M_num; j++)
		{
			if (s4_[i - M_num - size1 - size2].back()->leg_->dest_airp == base[j - M_num - size1 - size2 - size3])
			{
				//edges[s].u = i; edges[s].v = j;
				//edges[s].cost_ = -s4_[i - M_num - size1 - size2].back()->leg_->balance2_dual;
				//	cout << "iiii99999iii" << cost_matrix[i][j] << endl;
			
				//nodes[i].children.push_back(j);
				//edges[s].u = i; edges[s].v = j;
			    cost_ = -s4_[i - M_num - size1 - size2].back()->leg_->balance2_dual;
				nodes[i].children.push_back(pair<int, double>(j, cost_));
				// cost_matrix[i][j]= s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num], week_leg_list) + (aircraft_fc + aircraft_dual_)*get_rs_2(s2_string_rs(s2_[j - M_num], daily_gc_));
				//edges.push_back(Edge(i, j, cost_));
				//s++;
			//	cost_matrix[i][j] = -s4_[i - M_num - size1 - size2].back()->leg_->balance2_dual;
				//cout << "iiiiiiii55555i" << cost_matrix[i][j] << endl;
			}
		}
	}
	cout << "-----------------" << s4_.size() << endl;
	//有了cost矩阵，可以直接算最短路了,用Dijk
	*/
	//cout << "jjjjjjjjjjjjjjjjjjjj" << endl;
	//vector<vector<string_>>three_strings(M_num*M_num);
	vector<oper_rotation*>three_day_sps;
	int t = 0;
	vector<leg*>legs;   //legs clear
	pair<bool, int*>sp_info;
//	int t = 0;
	/*
	for (int i = 0; i < M_num; i++)
	{
		for (int k = 0; k < M_num; k++)
		{
			//sp_info = string_Dijkstra(i, cost_matrix, node_num);
			double tempDistance = INF;
			int s2_index = 0;
			for (int j = 0; j < s2_.size(); j++)
			{
				if (cost_matrix[i][M_num + j] < tempDistance)
				{
					tempDistance = cost_matrix[i][M_num + j];
					s2_index = j;
				}
			}
			three_strings[t].push_back(s2_[s2_index]);

		     tempDistance = INF;
			int s3_index = 0;
			for (int j = 0; j < s3_.size(); j++)
			{
					if (cost_matrix[M_num + s2_index][M_num + size1 + j] < tempDistance)
					{
						tempDistance = cost_matrix[M_num + s2_index][M_num + size1 + j];
						s3_index = j;
					}
			}
			three_strings[t].push_back(s3_[s3_index]);
			 tempDistance = INF;
			int s4_index = 0;
			for (int j = 0; j < s4_.size(); j++)
			{
				if (s4_[j].back()->leg_->dest_airp == base[k])
				{
					if (cost_matrix[M_num + size1 + s3_index][M_num + size1 + size2 + j] < tempDistance&&can_connect(s2_[s2_index],s4_[j]))
					{
						tempDistance = cost_matrix[M_num +size1+s3_index][M_num + size1 +size2+ j];
						s4_index = j;
					}
				}
			}
			three_strings[t].push_back(s4_[s4_index]);
			t++;
		}
	}

	for (int i = 0; i<three_strings.size(); i++)
	{
		for (int j = 0; j<three_strings[i].size(); j++)
		{
			for (int k = 0; k<three
			_strings[i][j].size(); k++)
			{
				legs.push_back(three_strings[i][j][k]->leg_);
			}
		}
		three_day_sps.push_back(new oper_rotation(1, legs));
		legs.clear();
	}
	cout << "555555555555555555555" << three_day_sps.size() << endl;
	for (int i = 0; i<three_day_sps.size(); i++)
	{
		for (int j = 0; j<three_day_sps[i]->legs.size(); j++)
		{
			cout << three_day_sps[i]->legs[j]->index << ",";
		}
		cout << endl;
	}

	*/


	cout << "111111111111111111111" << endl;
	for (int i = 0; i<M_num; i++)
	{
		sp_info = SPFA2(nodes,i, node_num, three_day_strings_,M_num);
		for (int j = M_num + size1 + size2 + size3; j<node_num; j++)
		{
			cout << "arrive at base" << base[j - M_num - size1 - size2 - size3] << ".";
			for (int k = 0; k<s2_[sp_info.second[sp_info.second[sp_info.second[j]]] - M_num].first.size(); k++)
			{
				legs.push_back(leg_list[s2_[sp_info.second[sp_info.second[sp_info.second[j]]] - M_num].first[k]->leg_->index]);
			}
			for (int k = 0; k<s3_[sp_info.second[sp_info.second[j]] - M_num - size1].first.size(); k++)
			{
				legs.push_back(leg_list[s3_[sp_info.second[sp_info.second[j]] - M_num - size1].first[k]->leg_->index]);
			}
			for (int k = 0; k<s4_[sp_info.second[j] - M_num - size1 - size2].first.size(); k++)
			{
				legs.push_back(leg_list[s4_[sp_info.second[j] - M_num - size1 - size2].first[k]->leg_->index]);
			}
			cout << "departure from base" << base[i] << ".";
			three_day_sps.push_back(new oper_rotation(1, legs));
			legs.clear();
			vector<leg*>().swap(legs);
		}
	}
	/*

	for (int i = 0; i < node_num; i++)
	{
		delete[] cost_matrix[i];
	}
	delete[] cost_matrix;
	*/
	return three_day_sps;
}


vector<vector<event_node*>>daily_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 240, NULL));
		int n = 0;
		for (int t = 8; t <= 24; t += 4)
		{
			nodes[i].push_back(new event_node(i, t * 60, nodes[i][n]));
			n++;
		}
	}
	return nodes;

}
vector<vector<event_node*>>weekly_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 240, NULL));
		int n = 0;
		for (int t = 8; t <= 168; t += 4)
		{
			nodes[i].push_back(new event_node(i, t * 60, nodes[i][n]));
			n++;
		}
	}
	return nodes;
}


//BFS find all strings

vector<oper_rotation*>two_day_BFS(double**cost_matrix_, int M1, int M2, int num_, vector<string_>S, int M_num)
{

	int*cumu_rc_ = new int[num_];
	int*pre_ = new int[num_];

	for (int i = 0; i < num_; i++)
	{
		cumu_rc_[i] = 0;
	}
	cumu_rc_[M1] = 0;

	for (int i = 0; i < num_; i++)
	{
		if (cost_matrix_[M1][i]< INF)
		{
			pre_[i] = M1;
		}
		else
		{
			pre_[i] = -1;
		}
	}
	pre_[M1] = -1;

	queue<int>queue_;
	queue_.push(M1);
	vector<leg*>legs;
	vector<oper_rotation*>leg_strings_;
	vector<string_>strings_;


	while (!queue_.empty())
	{
		int u = queue_.front();
		//cout << "u" << u << endl;
		for (int i = 0; i < num_; i++)
		{
			if (cost_matrix_[u][i]<INF)
			{
				pre_[i] = u;
				if (i == M2)
				{
					strings_.push_back(S[pre_[pre_[i]] - M_num]);
					strings_.push_back(S[pre_[i] - M_num]);
					for (int i = 0; i<strings_.size(); i++)
					{
						for (int j = 0; j<strings_[i].size(); j++)
						{
							legs.push_back(strings_[i][j]->leg_);
						}
					}
					//cout << "find__" << endl;
					leg_strings_.push_back(new oper_rotation(1, legs));
					legs.clear();
					strings_.clear();
				}
				else
				{
					queue_.push(i);
				}
			}
		}
		queue_.pop();
		//cout << "next" << endl;
	}
	return leg_strings_;
}

vector<oper_rotation*>three_day_BFS(double**cost_matrix_, int M1, int M2, int num_, vector<string_>S, int M_num)          //BFS遍历所有可行路径
{
	//cout << "source" << M1 << endl;

	int*cumu_rc_ = new int[num_];
	int*pre_ = new int[num_];

	for (int i = 0; i < num_; i++)
	{
		cumu_rc_[i] = 0;
	}
	cumu_rc_[M1] = 0;

	for (int i = 0; i < num_; i++)
	{
		if (cost_matrix_[M1][i]< INF)
		{
			pre_[i] = M1;
		}
		else
		{
			pre_[i] = -1;
		}
	}
	pre_[M1] = -1;

	queue<int>queue_;
	queue_.push(M1);
	vector<leg*>legs;
	vector<oper_rotation*>leg_strings_;
	vector<string_>strings_;
	while (!queue_.empty())
	{
		int u = queue_.front();
		//cout << "u" << u << endl;
		for (int i = 0; i < num_; i++)
		{
			if (cost_matrix_[u][i]<INF)
			{
				pre_[i] = u;
				if (i == M2)
				{
					strings_.push_back(S[pre_[pre_[pre_[i]]] - M_num]);
					strings_.push_back(S[pre_[pre_[i]] - M_num]);
					strings_.push_back(S[pre_[i] - M_num]);
					for (int i = 0; i<strings_.size(); i++)
					{
						for (int j = 0; j<strings_[i].size(); j++)
						{
							legs.push_back(strings_[i][j]->leg_);
						}
					}
					//cout << "find__" << endl;
					leg_strings_.push_back(new oper_rotation(1, legs));
					legs.clear();
					strings_.clear();
				}
				else
				{
					queue_.push(i);
				}
			}
		}
		queue_.pop();
		//cout << "next" << endl;
	}
	return leg_strings_;
}
/*
vector<oper_rotation*>BFS_add_string(int*base, vector<vector<vector<string_>>>type_strings, double aircraft_dual, vector<leg*>leg_list, int M_num) // type_strings是各种string,s1-s4
{
	vector<string_>s1 = type_strings[0][0];   //一天的从M-M的串
	vector<string_>s2 = type_strings[1][0];//一天的从M-O的串
	vector<string_>s3 = type_strings[2][0];//O-O
	vector<string_>s4 = type_strings[3][0];//O-M

	vector<oper_rotation*>all_strings;

	vector<leg*>legs;
	for (int i = 0; i<s1.size(); i++)
	{
		for (int j = 0; j<s1[i].size(); j++)
		{
			legs.push_back(leg_list[s1[i][j]->leg_->index]);
		}
		all_strings.push_back(new oper_rotation(i, legs));
		legs.clear();
	}

	//cout << "all_strings_size:::" << all_strings.size() << endl;

	vector<string_>two_day_strings;
	vector<string_>three_day_strings;
	for (int i = 0; i<s2.size(); i++)
	{
		two_day_strings.push_back(s2[i]);
		three_day_strings.push_back(s2[i]);
	}
	for (int i = 0; i<s3.size(); i++)
	{
		three_day_strings.push_back(s3[i]);
	}
	for (int i = 0; i<s4.size(); i++)
	{
		two_day_strings.push_back(s4[i]);
		three_day_strings.push_back(s4[i]);
	}

	int size1 = s2.size();
	int size2 = s4.size();
	int node_num = size1 + size2 + M_num + M_num;
	double ** cost_matrix = new double *[node_num];
	for (int i = 0; i < node_num; i++)
	{
		cost_matrix[i] = new double[node_num];
	}
	//初始化
	for (int i = 0; i < node_num; i++)
	{
		for (int j = 0; j< node_num; j++)
		{
			cost_matrix[i][j] = INF;
		}
	}

	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num + size1; j++)
		{
			if (s2[j - M_num].front()->leg_->origin_airp == base[i])
			{
				cost_matrix[i][j] = s2[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2[j - M_num]);
			}
		}
	}

	for (int i = M_num; i < M_num + size1; i++)
	{
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2[i - M_num].back()->leg_->dest_airp == s4[j - M_num - size1].front()->leg_->origin_airp&&can_connect(s2[i - M_num], s4[j - M_num - size1]))
			{
				cost_matrix[i][j] = cacu_string_cost(s4[j - M_num - size1]);
			}
		}
	}

	for (int i = M_num + size1; i < M_num + size1 + size2; i++)
	{
		for (int j = M_num + size1 + size2; j <M_num + size1 + size2 + M_num; j++)
		{

			if (s4[i - M_num - size1].back()->leg_->dest_airp == base[j - M_num - size1 - size2])
			{

				cost_matrix[i][j] = -s4[i - M_num - size1].back()->leg_->balance2_dual;
			}
		}
	}

	int size1_ = s2.size();
	int size2_ = s3.size();
	int size3_ = s4.size();


	int node_num1 = M_num + size1_ + size2_ + size3_ + M_num;
	double ** cost_matrix1 = new double *[node_num1];
	for (int i = 0; i < node_num1; i++)
	{
		cost_matrix1[i] = new double[node_num1];
	}

	for (int i = 0; i < node_num1; i++)
	{
		for (int j = 0; j< node_num1; j++)
		{
			cost_matrix1[i][j] = INF;
		}
	}
	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num + size1_; j++)
		{
			if (s2[j - M_num].front()->leg_->origin_airp == base[i])
			{
				cost_matrix1[i][j] = s2[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2[j - M_num]);
			}
		}
	}
	for (int i = M_num; i < M_num + size1_; i++)
	{
		for (int j = M_num + size1_; j <M_num + size1_ + size2_; j++)
		{
			if (s2[i - M_num].back()->leg_->dest_airp == s3[j - M_num - size1_].front()->leg_->origin_airp&&can_connect(s2[i - M_num], s3[j - M_num - size1_]))
			{
				cost_matrix1[i][j] = cacu_string_cost(s3[j - M_num - size1]);
			}
		}
	}
	for (int i = M_num + size1_; i < M_num + size1_ + size2_; i++)
	{
		for (int j = M_num + size1_ + size2_; j <M_num + size1_ + size2_ + size3_; j++)
		{
			if (s3[i - M_num - size1_].back()->leg_->dest_airp == s4[j - M_num - size1_ - size2_].front()->leg_->origin_airp&&can_connect(s3[i - M_num - size1_], s4[j - M_num - size1_ - size2_]))
			{
				cost_matrix1[i][j] = cacu_string_cost(s4[j - M_num - size1_ - size2_]);
			}
		}
	}

	for (int i = M_num + size1_ + size2_; i < M_num + size1_ + size2_ + size3_; i++)
	{
		for (int j = M_num + size1_ + size2_ + size3_; j <M_num + size1_ + size2_ + size3_ + M_num; j++)
		{
			if (s4[i - M_num - size1_ - size2_].back()->leg_->dest_airp == base[j - M_num - size1_ - size2_ - size3_])
			{
				cost_matrix1[i][j] = s4[i - M_num - size1_ - size2_].back()->leg_->balance2_dual;
			}
		}
	}


	//find all two day strings and three day strings
	vector<vector<oper_rotation*>>BFS_strings_;
	for (int i = 0; i<M_num; i++)
	{
		for (int j = M_num + two_day_strings.size(); j<node_num; j++)
		{
			BFS_strings_.push_back(two_day_BFS(cost_matrix, i, j, node_num, two_day_strings, M_num));
		}
	}
	for (int i = 0; i<M_num; i++)
	{
		for (int j = M_num + three_day_strings.size(); j<node_num1; j++)
		{
			BFS_strings_.push_back(three_day_BFS(cost_matrix1, i, j, node_num1, three_day_strings, M_num));
		}
	}
	for (int i = 0; i<BFS_strings_.size(); i++)
	{
		for (int j = 0; j<BFS_strings_[i].size(); j++)
		{
			all_strings.push_back(BFS_strings_[i][j]);
		}
	}
	cout << "all_strings_size:::" << all_strings.size() << endl;
	//cout << "all_strings_size:::" << all_strings.size() << endl;
	return all_strings;
}
*/

double**set_leg_fc(int airp_num)
{
	double**leg_fc = new double*[airp_num];
	for (int i = 0; i < airp_num; i++)
	{
		leg_fc[i] = new double[airp_num];
	}
	for (int i = 0; i<airp_num; i++)
	{
		for (int j = 0; j<airp_num; j++)
		{
			leg_fc[i][j] = 0;
		}
	}
	for (int i = 0; i<airp_num; i++)
	{
		for (int j = 0; j<airp_num; j++)
		{
			if (i != j)
			{
				leg_fc[i][j] = (rand() % (10+1)) + 90;   //(rand() % (b - a + 1)) + a
			}
		}
	}
	for (int i = 0; i<airp_num; i++)
	{
		for (int j = 0; j<airp_num; j++)
		{
			leg_fc[i][j] = leg_fc[j][i];   //A-B的cost等于B-A的cost
		}
	}
	return leg_fc;
}


vector<G_arc*>s2_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc)
{
	vector<G_arc*>all_string_arcs;
	for (int i = 0; i < _string_.size() - 1; i++)
	{
		//leg arc
		all_string_arcs.push_back(new G_arc(new event_node(_string_[i]->leg_->origin_airp, _string_[i]->leg_->departure_t), new event_node(_string_[i]->leg_->dest_airp, _string_[i]->leg_->arrival_t + Min_groundtime)));

		for (int j = 0; j < daily_gc[_string_[i]->leg_->dest_airp].size(); j++)
		{
			if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time >= _string_[i]->leg_->arrival_t + Min_groundtime)
			{
				if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time <= _string_[i + 1]->leg_->departure_t)
				{
					if (daily_gc[_string_[i]->leg_->dest_airp][j]->end_->time <= _string_[i + 1]->leg_->departure_t)
					{
						all_string_arcs.push_back(daily_gc[_string_[i]->leg_->dest_airp][j]);
					}
				}
			}
		}

	}

	all_string_arcs.push_back(new G_arc(new event_node(_string_[_string_.size() - 1]->leg_->origin_airp, _string_[_string_.size() - 1]->leg_->departure_t), new event_node(_string_[_string_.size() - 1]->leg_->dest_airp, _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)));

	for (int j = 0; j < daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp].size(); j++)
	{
		if (daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]->start_->time >= _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)
		{
			if (daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]->end_->time >= _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)
			{
				all_string_arcs.push_back(daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]);
			}
		}
	}

	return all_string_arcs;
}

vector<G_arc*>s3_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc)
{
	vector<G_arc*>all_string_arcs;
	for (int j = 0; j < daily_gc[_string_[0]->leg_->origin_airp].size(); j++)
	{
		if (daily_gc[_string_[0]->leg_->origin_airp][j]->end_->time <= _string_[0]->leg_->departure_t)
		{
			if (daily_gc[_string_[0]->leg_->origin_airp][j]->start_->time <= _string_[0]->leg_->departure_t)
			{
				all_string_arcs.push_back(daily_gc[_string_[0]->leg_->origin_airp][j]);
			}
		}
	}
	for (int i = 0; i < _string_.size() - 1; i++)
	{
		//leg arc
		all_string_arcs.push_back(new G_arc(new event_node(_string_[i]->leg_->origin_airp, _string_[i]->leg_->departure_t), new event_node(_string_[i]->leg_->dest_airp, _string_[i]->leg_->arrival_t + Min_groundtime)));
		for (int j = 0; j < daily_gc[_string_[i]->leg_->dest_airp].size(); j++)
		{
			if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time >= _string_[i]->leg_->arrival_t + Min_groundtime)
			{
				if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time <= _string_[i + 1]->leg_->departure_t)
				{
					if (daily_gc[_string_[i]->leg_->dest_airp][j]->end_->time <= _string_[i + 1]->leg_->departure_t)
					{
						all_string_arcs.push_back(daily_gc[_string_[i]->leg_->dest_airp][j]);
					}
				}
			}
		}
	}

	all_string_arcs.push_back(new G_arc(new event_node(_string_[_string_.size() - 1]->leg_->origin_airp, _string_[_string_.size() - 1]->leg_->departure_t), new event_node(_string_[_string_.size() - 1]->leg_->dest_airp, _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)));
	for (int j = 0; j < daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp].size(); j++)
	{
		if (daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]->start_->time >= _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)
		{
			if (daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]->end_->time >= _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)
			{
				all_string_arcs.push_back(daily_gc[_string_[_string_.size() - 1]->leg_->dest_airp][j]);
			}
		}
	}
	return all_string_arcs;
}
vector<G_arc*>s4_string_rs(string_ _string_, vector<vector<G_arc*>>daily_gc)
{

	vector<G_arc*>all_string_arcs;
	for (int j = 0; j < daily_gc[_string_[0]->leg_->origin_airp].size(); j++)
	{
		if (daily_gc[_string_[0]->leg_->origin_airp][j]->end_->time <= _string_[0]->leg_->departure_t)
		{
			if (daily_gc[_string_[0]->leg_->origin_airp][j]->start_->time <= _string_[0]->leg_->departure_t)
			{
				all_string_arcs.push_back(daily_gc[_string_[0]->leg_->origin_airp][j]);
			}
		}
	}
	for (int i = 0; i < _string_.size() - 1; i++)
	{
		//leg arc
		all_string_arcs.push_back(new G_arc(new event_node(_string_[i]->leg_->origin_airp, _string_[i]->leg_->departure_t), new event_node(_string_[i]->leg_->dest_airp, _string_[i]->leg_->arrival_t + Min_groundtime)));
		for (int j = 0; j < daily_gc[_string_[i]->leg_->dest_airp].size(); j++)
		{
			if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time >= _string_[i]->leg_->arrival_t + Min_groundtime)
			{
				if (daily_gc[_string_[i]->leg_->dest_airp][j]->start_->time <= _string_[i + 1]->leg_->departure_t)
				{
					if (daily_gc[_string_[i]->leg_->dest_airp][j]->end_->time <= _string_[i + 1]->leg_->departure_t)
					{
						all_string_arcs.push_back(daily_gc[_string_[i]->leg_->dest_airp][j]);
					}
				}
			}
		}
	}
	all_string_arcs.push_back(new G_arc(new event_node(_string_[_string_.size() - 1]->leg_->origin_airp, _string_[_string_.size() - 1]->leg_->departure_t), new event_node(_string_[_string_.size() - 1]->leg_->dest_airp, _string_[_string_.size() - 1]->leg_->arrival_t + Min_groundtime)));

	return all_string_arcs;
}

int get_rs_2(vector<G_arc*>string_arcs_)
{
	int count_ = 0;
	for (int i = 0; i<string_arcs_.size(); i++)
	{
		if (string_arcs_[i]->start_->time <= count_time&&string_arcs_[i]->end_->time >= count_time)
		{
			count_++;
		}
	}
	return count_;
}







#include"class_set.h"
#include<vector>
#include<iostream>
#include <fstream>
#include <string>
#include<tuple>
#include<algorithm>
#include<queue>
using namespace std;


#define Min_groundtime 40
#define Days 7
#define airports 8
#define INF 9999999
#define max_weight 1000
#define T  10080
#define count_time 240
#define aircraft_fc 300
//#define leg_fc 8
#define leg_vc 2
#define base_num 2
#define o_base_num 2
#define PATH "C:/Users/wws199633/Desktop/"

tuple<double*, int*, int*> Dijkstra(int source, int s_t, int num, pair<double, int> ** cost_time_matrix_, int max_time, vector<leg*>leglist_);


bool is_base_(int i, int*base)
{

	for (int j = 0; j<base_num; j++)
	{
		if (i == base[j])
		{
			return true;
		}
	}
	return false;

}

bool is_o_base_(int i, int*base)
{

	for (int j = 0; j<o_base_num; j++)
	{
		if (i == base[j])
		{
			return true;
		}
	}
	return false;
}
int G_arc::get_pj()
{
	int pj = 0;
	if (start_->time <= count_time&&end_->time >= count_time)
	{
		pj = 1;
	}
	return pj;
}
int oper_rotation::get_rs()
{
	//cout << "rs---------------" << all_string_arcs.size() << endl;
	int count_ = 0;
	for (int i = 0; i<all_string_arcs.size(); i++)
	{
		if (all_string_arcs[i]->start_->time <= count_time&&all_string_arcs[i]->end_->time >= count_time)
		{
			count_++;
		}
	}
	return count_;
}
double oper_rotation::cacu_RC(double aircraft_num_dual, vector<leg*>&weekly_leg_list)
{
	double rc = 0;
	//cout << "string_length" << legs.size() << endl;
	for (int i = 0; i < legs.size(); i++)
	{
		//	cout << "index" <<legs[i]->index<< endl;
	//	cout << "leg_fc" << legs[i]->fixed_cost << endl;
	//	cout << "cover dual" << legs[i]->cover_dual << endl;
		//cout << "capacity dual" << legs[i]->capacity_dual << endl;
		//cout << "--------"<<legs[i]->leg_capacity << endl;
		rc += -legs[i]->fixed_cost - legs[i]->cover_dual;
	}
    for (int i = 0; i < legs.size(); i++)
   {
		for (int j= 0; j<weekly_leg_list.size(); j++)
		{
			if (weekly_leg_list[j]->index2==legs[i]->index)
			{
				//cout << weekly_leg_list[j]->leg_capacity << endl;
				//cout << weekly_leg_list[j]->capacity_dual << endl;
				rc = rc + weekly_leg_list[j]->leg_capacity*weekly_leg_list[j]->capacity_dual;
			}
		}
	}
	//cout << "rs" << this->get_rs() << endl;
	//cout << "balance1 dual" << legs.front()->balance1_dual << endl;
	//cout << "balance2 dual" << legs.back()->balance2_dual << endl;
	//cout << "aircraft_num_dual" << aircraft_num_dual << endl;
	rc = rc - (aircraft_fc + aircraft_num_dual)*this->get_rs() - legs.front()->balance1_dual + legs.back()->balance2_dual;
	return rc;
}

void oper_rotation::add_gc(vector<vector<G_arc*>>daily_gc)
{
	for (int i = 0; i<legs.size() - 1; i++)
	{
		//leg arc
		all_string_arcs.push_back(new G_arc(new event_node(legs[i]->origin_airp, legs[i]->departure_t), new event_node(legs[i]->dest_airp, legs[i]->arrival_t + Min_groundtime)));
		if (legs[i + 1]->departure_t>legs[i]->arrival_t + Min_groundtime)
		{
			for (int j = 0; j < daily_gc[legs[i]->dest_airp].size(); j++)
			{
				if (daily_gc[legs[i]->dest_airp][j]->start_->time >= legs[i]->arrival_t + Min_groundtime&&daily_gc[legs[i]->dest_airp][j]->end_->time <= legs[i + 1]->departure_t)
				{
					all_string_arcs.push_back(daily_gc[legs[i]->dest_airp][j]);
				}
			}
		}
		if (legs[i + 1]->departure_t<legs[i]->arrival_t + Min_groundtime)
		{
			for (int j = 0; j < daily_gc[legs[i]->dest_airp].size(); j++)
			{
				if (daily_gc[legs[i]->dest_airp][j]->start_->time >= legs[i]->arrival_t + Min_groundtime&&daily_gc[legs[i]->dest_airp][j]->end_->time >= legs[i]->arrival_t + Min_groundtime)
				{
					all_string_arcs.push_back(daily_gc[legs[i]->dest_airp][j]);
				}
				else if (daily_gc[legs[i]->dest_airp][j]->start_->time <= legs[i + 1]->departure_t&&daily_gc[legs[i]->dest_airp][j]->end_->time <= legs[i + 1]->departure_t)
				{
					all_string_arcs.push_back(daily_gc[legs[i]->dest_airp][j]);
				}
			}
		}
	}
	all_string_arcs.push_back(new G_arc(new event_node(legs[legs.size() - 1]->origin_airp, legs[legs.size() - 1]->departure_t), new event_node(legs[legs.size() - 1]->dest_airp, legs[legs.size() - 1]->arrival_t + Min_groundtime)));
}



vector<vector<G_arc*>>G_arc::get_day_ground_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num)
{
	vector<vector<G_arc*>>G(airport_num);
	for (int j = 0; j<airport_num; j++)
	{
		for (int i = 0; i < daily_nodes_[j].size() - 1; i++)
		{
			G[j].push_back(new G_arc(daily_nodes_[j][i], daily_nodes_[j][i + 1]));
		}
		G[j].push_back(new G_arc(daily_nodes_[j][daily_nodes_[j].size() - 1], daily_nodes_[j][0]));      //过夜弧
	}
	cout << "test:过夜弧" <<G[1][G[1].size()-1]->end_->time<< ","<<G[1][G[1].size() - 1] ->start_->time<< endl;
	cout << G[1].size() << endl;
	return G;
}

vector<vector<G_arc*>>G_arc::get_week_ground_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num)
{
	vector<vector<G_arc*>>G(airport_num);
	for (int j = 0; j < airport_num; j++)
	{
		for (int i = 0; i < weekly_nodes_[j].size() - 1; i++)
		{
			G[j].push_back(new G_arc(weekly_nodes_[j][i], weekly_nodes_[j][i + 1]));
		}
		G[j].push_back(new G_arc(weekly_nodes_[j][weekly_nodes_[j].size() - 1], weekly_nodes_[j][0]));      //过夜弧
	}
	//cout << "test:" << endl;
	//cout << "test:过夜弧" << G[1][G[1].size() - 1]->end_->time << "," << G[1][G[1].size() - 1]->start_->time << endl;
	//cout << G[1].size() << endl;
	return G;
}

vector<leg*>leg::get_day_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num, int day_, double**leg_fc_)
{
	int *base_ = new int[base_num];
	base_[0] = 1; base_[1] = 2;// base_[2] = 11;
	int *o_base_ = new int[o_base_num];
	o_base_[0] = 3; o_base_[1] = 4;// base_[2] = 11;
	int index = 0;
	vector<leg*>day_leg_list;
	for (int i = 0; i<airport_num; i++)
	{
		if (!is_base_(i, base_))
		{
			for (int j = 0; j < daily_nodes_[i].size() - 2; j++)
			{
				for (int k = 0; k < airport_num; k++)
				{
					if (i != k && !is_base_(k, base_))
					{
						day_leg_list.push_back(new leg(index, day_, max_weight,i, daily_nodes_[i][j]->time + (day_ - 1) * 1440, k, daily_nodes_[k][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[i][k], index));
						index++;
					}
				}
			}
		}
	}
	for (int i = 0; i<airport_num; i++)
	{
		if (!is_base_(i, base_))
		{
				for (int k = 0; k < airport_num; k++)
				{
					if (i != k && !is_base_(k, base_)&&is_o_base_(k,o_base_))
					{
						day_leg_list.push_back(new leg(index, day_, max_weight, i, daily_nodes_[i][daily_nodes_[i].size()-2]->time + (day_ - 1) * 1440, k, daily_nodes_[k][daily_nodes_[k].size()-1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[i][k], index));
						index++;
					}
				}
		}
    }
	for (int j = 0; j < (daily_nodes_[1].size() + 1) / 2; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight,1, daily_nodes_[1][j]->time + (day_ - 1) * 1440, 3, daily_nodes_[3][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[1][3], index));
		index++;
	}
	for (int j = (daily_nodes_[0].size() - 1) / 2; j < daily_nodes_[0].size() - 1; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight, 0, daily_nodes_[0][j]->time + (day_ - 1) * 1440, 1, daily_nodes_[1][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[0][1], index));
		index++;
	}

	for (int j = 0; j < (daily_nodes_[2].size() + 1) / 2; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight, 2, daily_nodes_[2][j]->time + (day_ - 1) * 1440, 4, daily_nodes_[4][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[2][4], index));
		index++;
	}
	for (int j = (daily_nodes_[3].size() - 1) / 2; j < daily_nodes_[3].size() - 1; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight, 3, daily_nodes_[3][j]->time + (day_ - 1) * 1440, 2, daily_nodes_[2][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[3][2], index));
		index++;
	}
	/*
	for (int j = 0; j < (daily_nodes_[11].size() + 1) / 2; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight, 11, daily_nodes_[11][j]->time + (day_ - 1) * 1440, 6, daily_nodes_[6][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[11][6], index));
		index++;
	}
	for (int j = (daily_nodes_[8].size() - 1) / 2; j < daily_nodes_[8].size() - 1; j++)
	{
		day_leg_list.push_back(new leg(index, day_, max_weight, 8, daily_nodes_[8][j]->time + (day_ - 1) * 1440, 11, daily_nodes_[11][j + 1]->time + (day_ - 1) * 1440 - Min_groundtime, 0, leg_vc, leg_fc_[8][11], index));
		index++;
	}

	*/
	//cout << "test" << day_leg_list.size() << endl;
	return day_leg_list;
}

vector<leg*>leg::get_week_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num, double**leg_fc_)
{
	int index_ = 0;
	vector<leg*>week_leg_list;
	for (int i = 1; i <= 7; i++)
	{
		vector<leg*>day_leg_ = this->get_day_leglist(daily_nodes_, airport_num, i, leg_fc_);
		for (int j = 0; j<day_leg_.size(); j++)
		{
			week_leg_list.push_back(day_leg_[j]);
		}
	}
	return week_leg_list;
}

vector<oper_rotation*>leg::dayleg_get_S(vector<oper_rotation*>rotation_lists_)
{
	vector<oper_rotation*>Sl;
	for (int i = 0; i<rotation_lists_.size(); i++)
	{
		for (int j = 0; j<rotation_lists_[i]->legs.size(); j++)
		{
			if (rotation_lists_[i]->legs[j]->index2 == this->index2)
			{
				Sl.push_back(rotation_lists_[i]);
				break;
			}
		}
	}
	return Sl;
}

G_arc*leg::get_y1_d(vector<vector<G_arc*>>G)
{
	G_arc*arc_ = new G_arc();
	for (int i = 0; i<G[origin_airp].size(); i++)
	{
		if (departure_t == G[origin_airp][i]->end_->time)
		{
			arc_ = G[origin_airp][i];
		}
	}
	return arc_;
}
G_arc*leg::get_y2_d(vector<vector<G_arc*>>G)
{
	G_arc*arc_ = new G_arc();
	for (int i = 0; i<G[origin_airp].size(); i++)
	{
		if (departure_t == G[origin_airp][i]->start_->time)
		{
			arc_ = G[origin_airp][i];
			//break;
		}
	}
	return arc_;
}
G_arc*leg::get_y1_a(vector<vector<G_arc*>>G)
{
	G_arc*arc_ = new G_arc();
	for (int i = 0; i<G[dest_airp].size(); i++)
	{
		if (arrival_t + Min_groundtime == G[dest_airp][i]->end_->time)
		{
			arc_ = G[dest_airp][i];
		}
	}
	return  arc_;
}
G_arc*leg::get_y2_a(vector<vector<G_arc*>>G)
{
	G_arc*arc_ = new G_arc();
	for (int i = 0; i<G[dest_airp].size(); i++)
	{
		if (arrival_t + Min_groundtime == G[dest_airp][i]->start_->time)
		{
			arc_ = G[dest_airp][i];
		}
	}
	return arc_;
}



int OD::delivery_time()
{
	int max_delivery_time;
	if (date1_<date2_)
	{
		max_delivery_time = (1440 - h1 * 60 - m1 + (date2_ - date1_ - 1) * 24 * 60 + h2 * 60 + m2);
	}
	if (date1_ == date2_)
	{
		max_delivery_time = h2 * 60 + m2 - (h1 * 60 + m1);
	}
	if(date1_>date2_)
	{
		max_delivery_time = T - (date1_-1) * 24 * 60 - h1 * 60 - m1 + (date2_ - 1) * 24 * 60 + h2 * 60 + m2;
	}
	return max_delivery_time;
}

bool _connect(treenode*node_, flight_tree*tree_)  //将上个树的叶子节点和下棵树连接起来，并进行剪枝判断
{
	vector<treenode*>can_add_legs = tree_->source->child_legs;
	vector<treenode*>to_add_legs;
	int count = 0;
	for (int i = 0; i<tree_->source->child_legs.size(); i++)
	{

		int dt = can_add_legs[i]->leg_->departure_t; int at = node_->leg_->arrival_t;
		if (dt - at >= Min_groundtime)
		{
			count++;
			to_add_legs.push_back(can_add_legs[i]);
		}
	}
	if (count == 0)
	{
		//cout << "can not connect!!!" << endl;
		return false;
	}
	node_->child_legs = to_add_legs;
	return true;
}

bool flight_string::creat_string(vector<treenode*>&nodes, vector<flight_tree*>trees)
{
	vector<treenode*>leave_nodes;
	int con = 0;
	for (int j = 0; j<nodes.size(); j++)
	{
		for (int k = 0; k<trees.size(); k++)
		{
			if (nodes[j]->leg_->dest_airp == trees[k]->index)
			{
				int count = _connect(nodes[j], trees[k]);
				if (count == 1)
				{
					con++;
					for (int s = 0; s < nodes[j]->child_legs.size(); s++)
					{
						leave_nodes.push_back(nodes[j]->child_legs[s]);
					}
				}
			}
		}
	}
	if (con == 0)
	{
		cout << "stop the construction of this flight_string!!!" << endl;
		return false;
	}

	
	creat_string(leave_nodes, trees);   //递归调用。
	//清楚内存
	//leave_nodes.clear();
	return true;
}

bool flight_string::dfs(vector<vector<treenode*>>&strings_, vector<treenode*>&string_, treenode*current_)   //返回从根节点到叶节点的一天的串
{
	int *base_ = new int[base_num];
	base_[0] = 1; base_[1] = 2; //base_[2] = 11;
	//current_->visited = 1;
	if (current_->child_legs.size() == 0)
	{
		//(current_->leg_ != NULL&&is_base_(current_->leg_->dest_airp, base_)) ||
		//strings_.push_back(string_);
		//cout << "10000" << current_->leg_->index << endl;
		//	cout << "999999999" << endl;
		strings_.push_back(string_);
		string_.pop_back();
		return false;
	}
	/*
	if (current_->child_legs.size() == 0)
	{
	cout<<"10000"<<current_->leg_->index << endl;
	cout << "999999999" << endl;
	strings_.push_back(string_);
	string_.pop_back();
	return false;
	}
	*/
	for (int i = 0; i<current_->child_legs.size(); i++)
	{
		//	cout << "7777777777"<<current_->child_legs[i]->leg_->index << endl;
		//if (current_->child_legs[i]->visited == 0)
		//{
		//	cout << "888888" << current_->child_legs[i]->leg_->index << endl;
		treenode*next_node = current_->child_legs[i];
		string_.push_back(next_node);
		dfs(strings_, string_, next_node);
		//}
	}
	string_.pop_back();
	//cout << "string_size" << string_.size() << endl;
	return true;
}

double oper_path::cacu_mp(vector<OD*>OD_info)   //caculate margin profits
{
	double freight_ = OD_info[this->OD_index]->freight;
	//cout << legs.size() << endl;
	for (int i = 0; i<legs.size(); i++)
	{
	//	cout << "leg_index" << legs[i]->index << endl;
		//cout << "nnnnnnnnnnn" << legs[i]->var_cost << endl;
		//cout << "nnnnnnnnnnnnn" << legs[i]->capacity_dual;
		freight_ = freight_ - legs[i]->var_cost;
	}
	//cout << "mp_" << freight_ << endl;
	return freight_;
}

vector<int>oper_path::get_beta(vector<leg*>leglist_)
{
	vector<int>beta_;   //存储path包含的leg的序号
	for (int i = 0; i<leglist_.size(); i++)
	{
		for (int j = 0; j<this->legs.size(); j++)
		{
			if (leglist_[i] == this->legs[j])
			{
				beta_.push_back(i);
			}
		}
	}
	return beta_;
}

bool cmp(tuple<vector<int>, double, int, int>p1, tuple<vector<int>, double, int, int>p2)
{
	if (get<1>(p1) < get<1>(p2))
	{
		return true;
	}
	else
		return false;
}



vector<leg*>OD::find_shortest_path(int**relation_matrix,vector<leg*>&leglist_)
{
	//先求关系矩阵0   -1   1         

	//cout << "OD" << this->index <<":"<< endl;
	//cout << date1_ << "," << date2_ << endl;
	//cout << "-------------------" << this->delivery_time() << endl;
	int num = leglist_.size();
	
	//j建立cost,time矩阵pair <cost,time>

	pair<double, int> ** cost_time_matrix = new pair<double, int> *[num];
	for (int i = 0; i < num; i++)
	{
		cost_time_matrix[i] = new pair<double, int>[num];
	}

	for (int i = 0; i<num; i++)
	{
		for (int j = 0; j < num; j++)
		{

			if (relation_matrix[i][j] == 0)
			{
				if (i == j)
				{
					cost_time_matrix[i][j] = pair<double, int>(0, 0);
				}
				else
				{
					cost_time_matrix[i][j] = pair<double, int>(INF, INF);
				}
			}

			if (relation_matrix[i][j] == 1)
			{
				int time_ = leglist_[j]->arrival_t - leglist_[i]->arrival_t;    //包括了transit time
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, int>(cost_, time_);
			}
			if (relation_matrix[i][j] == -1)
			{
				int time_ = T - leglist_[i]->arrival_t + leglist_[j]->arrival_t;
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, int>(cost_, time_);
			}

			//要不要考虑在机场储存货物的cost？？？
		}
	}

	//求包含这个OD的O的legs
	vector<pair<int, int>>Olegs_index;
	for (int i = 0; i<num; i++)
	{
		if (leglist_[i]->origin_airp == this->O_airp - 1)
		{
			if (leglist_[i]->date >= date1_&&leglist_[i]->departure_t >= ((date1_ - 1) * 24 + h1) * 60 + m1&&leglist_[i]->arrival_t - (((date1_ - 1) * 24 + h1) * 60 + m1) < this->delivery_time())
			{
				Olegs_index.push_back(pair<int, int>(i, leglist_[i]->arrival_t - (((date1_ - 1) * 24 + h1) * 60 + m1)));
			}
			else if (leglist_[i]->date < date1_&&leglist_[i]->arrival_t + (T - (((date1_ - 1) * 24 + h1) * 60 + m1)) < this->delivery_time())
			{
				Olegs_index.push_back(pair<int, int>(i, leglist_[i]->arrival_t + (T - (((date1_ - 1) * 24 + h1) * 60 + m1))));
			}
		}
	}


	vector<tuple<vector<int>, double, int, int>>ODpaths_;   //所有路集合
	for (int i = 0; i<Olegs_index.size(); i++)       //对每一个从O出发的leg找一次最短路
	{
	//	cout << "OD_delivery_time:" << this->delivery_time() << endl;
		tuple<double*, int*, int*>result_ = Dijkstra(Olegs_index[i].first, Olegs_index[i].second, num, cost_time_matrix, this->delivery_time(), leglist_);
		//打印路径
		for (int j = 0; j< num; j++)
		{
			if (leglist_[j]->dest_airp == D_airp - 1 && (get<1>(result_)[j] != 0))   
			{
				vector<int>leg_index;
				//cout << "exist path:" << endl;
				//cout << j << ",";
				if (j != Olegs_index[i].first)
				{
					leg_index.push_back(j);
					int pre_leg = get<2>(result_)[j];
					while (pre_leg != Olegs_index[i].first)
					{
					//	cout << pre_leg << ",";
						leg_index.push_back(pre_leg);
						pre_leg = get<2>(result_)[pre_leg];
					}
				//	cout << Olegs_index[i].first << ".";
					leg_index.push_back(Olegs_index[i].first);
				}
				else
				{
					leg_index.push_back(Olegs_index[i].first);   //直达
				}
			//	cout << endl;
				ODpaths_.push_back(make_tuple(leg_index, get<0>(result_)[j], i, j));
			}
		}
	}

	//cout << "OD_paths_size:" << ODpaths_.size() << endl;

	//给ODpaths排序，然后返回最短路
	vector<leg*>to_add_path1;
	//vector<vector<leg*>>to_add_path2;
	if (ODpaths_.size() != 0)
	{
		sort(ODpaths_.begin(), ODpaths_.end(), cmp);       //ODpath[0]存放了从O到D的cost最小的路径
		tuple<vector<int>, double, int, int>opt_path = ODpaths_[0];

		for (int i = 0; i<get<0>(opt_path).size(); i++)
		{
			to_add_path1.push_back(leglist_[get<0>(opt_path)[i]]);
		}
		/*
		vector<leg*>path_;
		for (int i = 0; i<ODpaths_.size(); i++)
		{
			for (int j = 0; j<get<0>(ODpaths_[i]).size(); j++)
			{
				path_.push_back(leglist_[get<0>(ODpaths_[i])[j]]);
			}
			to_add_path2.push_back(path_);
			path_.clear();
		}
		*/
	}
	//cout << "jjjjjjjjjjjjjjjjjjjjjjjj" << endl;
	//vector<leg*>to_add_path=to_add_path1;
	
	for (int i = 0; i < num; i++)
	{
		delete[] cost_time_matrix[i];
	}
	delete[] cost_time_matrix;

	return to_add_path1;
}


vector<leg*>IO::read_daily_flights()
{
	//vector<flight*>flight_list;
	vector<leg*>leg_list;
	string filename = PATH + string("flights_data1.csv");
	ifstream infile;
	infile.open(filename.c_str());
	cout << "#Read flights data from " << filename << "\n";
	string buff;
	char* token;
	char* temp;
	int index;
	int origin_airp;
	int dest_airp;
	int departure_t;
	int arrival_t;
	int date;
	bool firm;
	double v_c;
	double f_c;
	int index2;

	while (getline(infile, buff))
	{
		token = strtok_s((char*)buff.c_str(), ",", &temp);
		index = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		date = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		departure_t = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		origin_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		arrival_t = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		dest_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		firm = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		v_c = atof(token);
		token = strtok_s(NULL, ",", &temp);
		f_c = atof(token);
		token = strtok_s(NULL, ",", &temp);
		index2 = atoi(token);

		leg*leg_ = new leg(index, date, max_weight, origin_airp, departure_t, dest_airp, arrival_t, firm, v_c, f_c, index2);
		//	leg(int index_, int date_, int capacity_, int o_airp, int d_t, int d_airp, int a_t, bool firm_, double v_c, double f_c, int index2_) :date(date_), index(index_), leg_capacity(capacity_), firm(firm_), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), var_cost(v_c), fixed_cost(f_c), index2(index2_) {}
		leg_list.push_back(leg_);
		//flight_list.push_back(new flight(index, date, leg_, leg_, origin_airp, dest_airp, departure_t, arrival_t, firm, index2));
	}
	infile.close();
	cout << "test:" << endl;
	cout << leg_list[1]->arrival_t << endl;
	cout << "finish read flights data" << endl;
	//pair<vector<leg*>, vector<flight*>>flights_data;
	//flights_data.first = leg_list; flights_data.second = flight_list;
	return leg_list;
}

vector<leg*>IO::read_weekly_flights()
{
	//vector<flight*>flight_list;
	vector<leg*>leg_list;
	string filename = PATH + string("flights_data1.csv");
	ifstream infile;
	infile.open(filename.c_str());
	cout << "#Read flights data from " << filename << "\n";
	string buff;
	char* token;
	char* temp;
	int index;
	int origin_airp;
	int dest_airp;
	int departure_t;
	int arrival_t;
	int date;
	bool firm;
	double v_c;
	double f_c;
	int index2;

	while (getline(infile, buff))
	{
		token = strtok_s((char*)buff.c_str(), ",", &temp);
		index = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		date = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		departure_t = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		origin_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		arrival_t = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		dest_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		firm = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		v_c = atof(token);
		token = strtok_s(NULL, ",", &temp);
		f_c = atof(token);
		token = strtok_s(NULL, ",", &temp);
		index2 = atoi(token);

		leg*leg_ = new leg(index, date, max_weight,origin_airp, departure_t, dest_airp, arrival_t, firm, v_c, f_c, index2);
	//	leg(int index_, int date_, int capacity_, int o_airp, int d_t, int d_airp, int a_t, bool firm_, double v_c, double f_c, int index2_) :date(date_), index(index_), leg_capacity(capacity_), firm(firm_), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), var_cost(v_c), fixed_cost(f_c), index2(index2_) {}
		leg_list.push_back(leg_);
		//flight_list.push_back(new flight(index, date, leg_, leg_, origin_airp, dest_airp, departure_t, arrival_t, firm, index2));
	}
	infile.close();
	cout << "test:" << endl;
	cout << leg_list[1]->arrival_t << endl;
	cout << "finish read flights data" << endl;
	//pair<vector<leg*>, vector<flight*>>flights_data;
	//flights_data.first = leg_list; flights_data.second = flight_list;
	return leg_list;
}


vector<OD*>IO::read_OD_info()

{
	vector<OD*>OD_info;
	string filename = PATH + string("ODs_data.csv");
	ifstream infile;
	infile.open(filename.c_str());
	cout << "#Read OD data from " << filename << "\n";
	string buff;
	char* token;
	char* temp;
	int index;
	int type;
	int o_airp;
	int d_airp;
	int date1;
	int h1;
	int m1;
	int date2;
	int h2;
	int m2;
	double vol;
	double demand;
	double vol_unit;
	double freight;


	while (getline(infile, buff))
	{
		token = strtok_s((char*)buff.c_str(), ",", &temp);
		index = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		type = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		o_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		d_airp = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		date1 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		h1 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		m1 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		date2 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		h2 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		m2 = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		vol = atof(token);
		token = strtok_s(NULL, ",", &temp);
		demand = atof(token);
		token = strtok_s(NULL, ",", &temp);
		vol_unit = atof(token);
		token = strtok_s(NULL, ",", &temp);
		freight = atof(token);

		OD*OD_ = new OD(index, type, o_airp, d_airp, date1, h1, m1, date2, h2, m2, vol, demand, vol_unit, freight);
		OD_info.push_back(OD_);
	}

	infile.close();
	//cout << "test:" << endl;
	//cout << OD_info[1]->D_airp << endl;
	//cout << OD_info.size() << endl;
	cout << "finish read OD data" << endl;

	return OD_info;
}

//单源最短路
tuple<double*, int*, int*> Dijkstra(int source, int s_t, int num, pair<double, int> ** cost_time_matrix_, int max_time, vector<leg*>leglist_)
{

	//cout << "source" << source << endl;

	vector<bool> isvisited(num, false);                 //是否已经访问过,找到最短路  
	double*dis_ = new double[num];                 //源点到这个点的最短路
	int*cumu_time_ = new int[num];    //有最短路的话，用的时间是多少
	

	int*pre_ = new int[num];

	for (int i = 0; i < num; i++)
	{
		cumu_time_[i] = 0;
	}

	isvisited[source] = true;
	cumu_time_[source] = s_t;
	int u = source;

	for (int i = 0; i < num; i++)
	{
		if (cumu_time_[source] + cost_time_matrix_[source][i].second >= max_time)
		{
			dis_[i] = INF;
		}
		else
		{
			dis_[i] = cost_time_matrix_[source][i].first;
			//cout << "......." << dis_[i] << endl;
		}
	}

	for (int i = 0; i < num; i++)
	{
		if (cost_time_matrix_[source][i].first < INF)
		{
			pre_[i] = source;
		}
		else
		{
			pre_[i] = -1;
		}
	}
	pre_[source] = -1;


	for (int i = 1; i < num; i++)
	{
		int nextnode = u;
		double tempdis_ = INF;
		bool find = false;
		for (int j = 0; j < num; j++)
		{
			if ((isvisited[j] == false) && (dis_[j] < INF) && (pre_[j] == -1))
			{
				pre_[j] = u;
			}
			if ((isvisited[j] == false) && (dis_[j] < tempdis_) && cumu_time_[pre_[j]] + cost_time_matrix_[pre_[j]][j].second <= max_time) //寻找不在S集合中的distance最小的节点  
			{
				find = true;
				nextnode = j;
				tempdis_ = dis_[j];
			}
		}
		if (nextnode == source || !find)
		{
			break;
		}

		isvisited[nextnode] = true;
		cumu_time_[nextnode] = cumu_time_[pre_[nextnode]] + cost_time_matrix_[pre_[nextnode]][nextnode].second;  //更新时间
		u = nextnode;

		for (int j = 0; j < num; j++)
		{
			if (isvisited[j] == false && cost_time_matrix_[u][j].first < INF)
			{
				double temp = dis_[u] + cost_time_matrix_[u][j].first;
				if (temp < dis_[j])
				{
					dis_[j] = temp;
					pre_[j] = u;
				}
			}
		}
	}
	tuple<double*, int*, int*>result_;
	result_ = make_tuple(dis_, cumu_time_, pre_);

	return result_;

}


vector<vector<leg*>>OD::BFS(vector<BFS_treenode*>nodes_set, pair<double, int> ** cost_time_matrix_, int source, int s_t, int num_, int max_time, vector<leg*>weekly_legs_)          //BFS遍历所有可行路径
{
	//以source为root的搜索树
	cout << "source" << source << endl;

	BFS_treenode*root_ = nodes_set[source];
	root_->set_cumu_time(s_t);
	queue<BFS_treenode*>queue_;
	queue_.push(root_);
	vector<leg*>path_;
	vector<vector<leg*>>paths_;

	if (root_->leg_->dest_airp == D_airp - 1)      //可直达的路径
	{
		//cout << "直达" << endl;
		path_.push_back(root_->leg_);
		paths_.push_back(path_);
		path_.clear();
		return paths_;
	}
	while (!queue_.empty())
	{
		BFS_treenode* u = queue_.front();

		for (int i = 0; i < u->children.size(); i++)
		{
			if (u->cumu_time + cost_time_matrix_[u->leg_->index][u->children[i]->leg_->index].second <= max_time)
			{
				u->children[i]->set_cumu_time(u->cumu_time + cost_time_matrix_[u->leg_->index][u->children[i]->leg_->index].second);
				u->children[i]->set_pre_(u);
				if (u->children[i]->leg_->dest_airp == D_airp - 1)
				{
					path_.push_back(weekly_legs_[u->children[i]->leg_->index]);
					BFS_treenode* _pre = u->children[i]->pre_;
					while (_pre != root_)
					{
						path_.push_back(weekly_legs_[_pre->leg_->index]);
						_pre = _pre->pre_;

					}
					path_.push_back(weekly_legs_[root_->leg_->index]);
					paths_.push_back(path_);
					path_.clear();
				}
				else
				{
					nodes_set[u->children[i]->leg_->index]->set_pre_(u);
					nodes_set[u->children[i]->leg_->index]->set_cumu_time(u->cumu_time + cost_time_matrix_[u->leg_->index][u->children[i]->leg_->index].second);
					queue_.push(nodes_set[u->children[i]->leg_->index]);
				}
			}
		}
		queue_.pop();
	}
	return paths_;
}

vector<vector<leg*>>OD::find_all_path(vector<leg*>&leglist_)
{
	//先求关系矩阵0   -1   1         

	size_t num = leglist_.size();
	int ** relation_matrix = new int *[num];
	for (int i = 0; i < num; i++)
	{
		relation_matrix[i] = new int[num];
	}
	for (int i = 0; i<leglist_.size(); i++)
	{
		for (int j = 0; j<leglist_.size(); j++)
		{
			if (leglist_[i]->date <= leglist_[j]->date)
			{
				if (leglist_[i]->dest_airp != leglist_[j]->origin_airp || leglist_[j]->departure_t - leglist_[i]->arrival_t < Min_groundtime)
				{

					relation_matrix[i][j] = 0;
					continue;
				}
				if (i != j &&leglist_[i]->dest_airp == leglist_[j]->origin_airp &&leglist_[j]->departure_t - leglist_[i]->arrival_t >= Min_groundtime)
				{

					relation_matrix[i][j] = 1;
					continue;
				}
			}
			else if (leglist_[i]->date >= leglist_[j]->date && leglist_[i]->dest_airp == leglist_[j]->origin_airp)
			{
				relation_matrix[i][j] = -1;
				continue;
			}
			else
			{
				relation_matrix[i][j] = 0;
			}
		}
	}
	//j建立cost,time矩阵pair <cost,time>

	pair<double, int> ** cost_time_matrix = new pair<double, int> *[num];
	for (int i = 0; i < num; i++)
	{
		cost_time_matrix[i] = new pair<double, int>[num];
	}

	for (int i = 0; i<num; i++)
	{
		for (int j = 0; j < num; j++)
		{

			if (relation_matrix[i][j] == 0)
			{
				if (i == j)
				{
					cost_time_matrix[i][j] = pair<double, int>(0, 0);
				}
				else
				{
					cost_time_matrix[i][j] = pair<double, int>(INF, INF);
				}
			}

			if (relation_matrix[i][j] == 1)
			{
				int time_ = leglist_[j]->arrival_t - leglist_[i]->arrival_t;    //包括了transit time
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, int>(cost_, time_);
			}
			if (relation_matrix[i][j] == -1)
			{
				int time_ = T - leglist_[i]->arrival_t + leglist_[j]->arrival_t;
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, int>(cost_, time_);
			}

			//要考虑在机场储存货物的cost
		}
	}

	//BFS tree
	vector<BFS_treenode*>nodes_set;
	vector<BFS_treenode*>children_;
	for (int i = 0; i<leglist_.size(); i++)
	{
		for (int j = 0; j<leglist_.size(); j++)
		{
			if (i != j&&cost_time_matrix[i][j].first<INF)
			{
				children_.push_back(new BFS_treenode(leglist_[j]));
			}
		}
		nodes_set.push_back(new BFS_treenode(leglist_[i], children_));
		children_.clear();
	}


	//求包含这个OD的O的legs
	vector<pair<int, int>>Olegs_index;
	for (int i = 0; i<num; i++)
	{
		if (leglist_[i]->origin_airp == this->O_airp - 1 && leglist_[i]->departure_t >= ((date1_ - 1) * 24 + h1) * 60 + m1&&leglist_[i]->arrival_t - (((date1_ - 1) * 24 + h1) * 60 + m1)<this->delivery_time())
		{
			Olegs_index.push_back(pair<int, int>(i, leglist_[i]->arrival_t - (((date1_ - 1) * 24 + h1) * 60 + m1)));
		}
	}

	//vector<tuple<vector<int>, double, int, int>>ODpaths_;   //所有路集合

	vector < vector<leg*>>to_add_paths;
	vector < vector<leg*>>to_add_paths_;
	for (int i = 0; i < Olegs_index.size(); i++)       //对每一个从O出发的leg找一次最短路
	{
		to_add_paths_ = BFS(nodes_set, cost_time_matrix, Olegs_index[i].first, Olegs_index[i].second, num, this->delivery_time(), leglist_);
		cout << to_add_paths_.size() << endl;
		for (int j = 0; j<to_add_paths_.size(); j++)
		{
			to_add_paths.push_back(to_add_paths_[j]);
		}
		to_add_paths_.clear();
	}

	return to_add_paths;
}






#pragma once


#pragma once
#include<vector>
#include"arc.h"
using namespace std;

class oper_rotation;
class leg   //航程
{
public:
	int index;
	int index2;
	int origin_airp;
	int dest_airp;
	int departure_t;
	int arrival_t;
	int date;
	bool firm;
	double leg_capacity;
	double var_cost;   //单位载重的燃油消耗成本--取决于fleet type?
	double fixed_cost;  //空载成本+landcost

						//子问题dual price
	double capacity_dual;
	double cover_dual;
	double balance1_dual;
	double balance2_dual;


	leg() {};
	void set_index(int i) { index = i; };
	void set_date(int t_) { date = t_; };
	void set_departure_t(int dt_) { departure_t = dt_; };
	void set_arrival_t(int at_) { arrival_t = at_; };
	void set_fixed_cost(double cost_) { fixed_cost = cost_; }
	leg(int index_, int date_,int capacity_, int o_airp, int d_t, int d_airp, int a_t, bool firm_, double v_c, double f_c, int index2_) :date(date_), index(index_), leg_capacity(capacity_),firm(firm_), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), var_cost(v_c), fixed_cost(f_c), index2(index2_) {}
	int cacu_ft() { return arrival_t - departure_t; };   //计算leg的flight time
	void set_var_cost(double cost_) { var_cost = cost_; };
	void set_capacity_dual(double d) { capacity_dual = d; };
	void set_cover_dual(double cost_) { cover_dual = cost_; };
	void set_balance1_dual(double cost_) { balance1_dual = cost_; };
	void set_balance2_dual(double cost_) { balance2_dual = cost_; };

	vector<oper_rotation*>dayleg_get_S(vector<oper_rotation*>rotation_lists_);    //包含这个leg的string集合
																				  //vector<oper_rotation*>weekleg_get_S(vector<oper_rotation*>rotation_lists_);
	G_arc*get_y1_d(vector<vector<G_arc*>>G);
	G_arc*get_y2_d(vector<vector<G_arc*>>G);
	G_arc*get_y1_a(vector<vector<G_arc*>>G);
	G_arc*get_y2_a(vector<vector<G_arc*>>G);
	vector<leg*>leg::get_day_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num, int day_, double**leg_fc_);
	vector<leg*>leg::get_week_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num, double**leg_fc_);

};

class BFS_treenode
{
public:
	leg*leg_;
	vector<BFS_treenode*>children;
	int cumu_time;
	BFS_treenode* pre_;
	void set_cumu_time(int i) { cumu_time = i; };
	void set_pre_(BFS_treenode*_pre) { pre_ = _pre; };
	BFS_treenode(leg*_leg) { leg_ = _leg; cumu_time = 0; pre_ = NULL; };
	BFS_treenode(leg*_leg, vector<BFS_treenode*>children_) { leg_ = _leg; children = children_; cumu_time = 0; pre_ = NULL; };
};


class flight   //航班
{
public:
	int index;
	int index2;
	int date;
	leg*first_leg;
	leg*last_leg;
	int origin_airp;
	int dest_airp;
	int departure_t;
	int arrival_t;
	bool firm;
	flight(int index_, int date_, leg*f_l, leg*l_l, int o_airp, int d_airp, int d_t, int a_t, bool firm_, int index2_) :index(index_), date(date_), first_leg(f_l), last_leg(l_l), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), firm(firm_), index2(index2_) {}
	double cacu_fc() {
		double fc = first_leg->fixed_cost;
		return fc;
	}
};


class OD
{
public:
	int index;
	int type;
	int O_airp;
	int D_airp;
	int date1_;   //送到始发地机场的时间
	int h1;
	int m1;
	int date2_;
	int h2;   //送达目的地机场的时间
	int m2;
	double vol;   //cargo的体积
	double quantity; //cargo的重量
	double vol_unit; //单位重量的cargo的体积
	double freight;  //该OD的运费费率
	int get_index() { return index; };
	vector<vector<leg*>>od_paths;
	OD(int index_, int type_, int O, int D, int _date1_, int h1_, int m1_, int _date2_, int h2_, int m2_, double vol_, double quantity_, double vol_unit_, double freight_) :
		index(index_), type(type_), O_airp(O), D_airp(D), date1_(_date1_), h1(h1_), m1(m1_), date2_(_date2_), h2(h2_), m2(m2_), quantity(quantity_), vol(vol_), vol_unit(vol_unit_), freight(freight_) {}
	//pair<vector<leg*>, vector<vector<leg*>>>find_shortest_path(vector<leg*>&leglist_); //找到这个od此时的最短路
	vector<vector<leg*>>OD::BFS(vector<BFS_treenode*>nodes_set, pair<double, int> ** cost_time_matrix_, int source, int s_t, int num_, int max_time, vector<leg*>weekly_legs_); //BFS遍历所有可行路径
	vector<leg*>find_shortest_path(int**relation_matrix, vector<leg*>&leglist_);
	vector<vector<leg*>>find_all_path(vector<leg*>&leglist_);
	int delivery_time();
};

class aircraft  //飞机
{
public:
	int fleettype;
	double fixedcost;

};

class airport
{
public:
	int index;
	bool base_;  //是否是维修机场
	bool overnight;  //是否是过夜机场
	double landcost;
	airport(int index_, bool _base_, bool overnight_, double lancost_) :index(index_), base_(_base_), overnight(overnight_), landcost(lancost_) {};
};

class treenode
{
public:
	leg*leg_;
	bool visited;
	vector<treenode*>child_legs;
	treenode()
	{
		leg_ = NULL;
		visited = 0;
	}
	treenode(leg*a_leg)
	{
		leg_ = a_leg;
		visited = 0;
	}

};


class flight_tree   //航班树
{
public:
	treenode *source;
	int index;   //记录这个tree是哪个机场的
	int date;   //这个tree是哪天的
	flight_tree(int i, int t, vector<treenode*>child_legs_) {
		index = i; date = t; source = new treenode(); source->child_legs = child_legs_;
	}

};

class flight_string   //一天的航班衔接树
{
public:
	flight_tree*source;
	int index;   //以哪个机场为起始机场,第几天的航班串
	int date;
	flight_string(int i, int t, vector<treenode*>child_legs_) { index = i; date = t; source = new flight_tree(i, t, child_legs_); }
	bool creat_string(vector<treenode*>&nodes, vector<flight_tree*>trees);   //创建以i机场为起点的航班串
	bool dfs(vector<vector<treenode*>>&strings_, vector<treenode*>&string_, treenode*current);
};


class oper_rotation
{
public:
	int index_;
	vector<leg*>legs;
	vector<G_arc*>all_string_arcs;
	oper_rotation(int _index_, vector<leg*>&legs_) :index_(_index_), legs(legs_) {};
	//vector<int>get_legs_ID();         //这个环包含哪些flights
	//vector<int>get_days_ID();             //这个航班环包含哪几天的航班串
	vector<leg*>get_legs_() { return legs; };
	double get_string_cost()
	{
		double cost_ = 0;
		for (int i = 0; i<legs.size(); i++)
		{
			cost_ += legs[i]->fixed_cost;
		}
		return cost_;
	}
	void add_gc(vector<vector<G_arc*>>daily_gc);      //把原来的string加上地面弧(为了算rs）
	int get_rs();
	double cacu_RC(double aircraft_num_dual, vector<leg*>&weekly_leg_list);
};


class oper_path
{
public:
	int index;
	int OD_index;
	double flow_;
	double margin_p;  //margin profits
	vector<leg*>legs;
	int get_OD_index() { return OD_index; }
	double get_flow_() { return flow_; }
	vector<leg*>get_path() { return legs; }
	oper_path(int OD_index_, vector<leg*>legs_) :OD_index(OD_index_), legs(legs_) {};
	double cacu_mp(vector<OD*>OD_info);   //caculate margin profits
	vector<int>get_beta(vector<leg*>leglist_);
	void delete_(){
		for (vector<leg*>::iterator iter = legs.begin(); iter != legs.end(); iter++)
		{
			delete *iter;
		}
	}
};
	



class IO
{
public:
	IO() {};
	vector<leg*>read_daily_flights();
	vector<leg*>read_weekly_flights();
	vector<OD*>read_OD_info();
	//output

};










#pragma once
#pragma once
#include<vector>
using namespace std;

class event_node
{
public:
	int airport;
	int time;
	event_node*last_node;
	event_node(int i, int time_, event_node*last_node_) :airport(i), time(time_), last_node(last_node_) {}
	event_node(int i, int time_) :airport(i), time(time_) {}
};

class G_arc
{
public:
	event_node*start_;
	event_node*end_;
	G_arc() {};
	G_arc(event_node*_start_, event_node*_end_) :start_(_start_), end_(_end_) {}
	int get_pj();
	vector<vector<G_arc*>>get_day_ground_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num);
	vector<vector<G_arc*>>get_week_ground_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num);
	//vector<vector<G_arc*>>get_day_flight_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num);
	//vector<vector<G_arc*>>get_week_flight_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num);

};











