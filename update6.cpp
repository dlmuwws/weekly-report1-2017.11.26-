#include<ilcplex/ilocplex.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include<stdlib.h>
#include<stdio.h>
#include"class_set.h"
#include"arc.h"
#include<iostream>
using namespace std;

#define Days 7
#define airports 5
#define base_num 2  //维修机场的个数
#define max_weight 4000
#define max_volume 3000
#define aircraft_fc 100
#define A 10
#define o_airp_num 2
#define INF 99999999

typedef vector<treenode* >string_;
typedef vector<string_>strings_;

vector<vector<event_node*>>daily_nodes(int airport_num);
vector<vector<event_node*>>weekly_nodes(int airport_num);

//vector<leg*>get_week_leglist(vector<leg*>&day_leglist);
vector<vector<vector<string_>>>find_oneday_string(vector<leg*>&leg_list_);
double cacu_string_cost(string_ _string_);
vector<oper_rotation*>add_string(int*base, vector<vector<vector<string_>>>type_strings, double aircraft_dual, vector<leg*>leg_list, int M_num);
bool can_connect(string_ string_1, string_ string_2);
pair<double*, int*>string_Dijkstra(int source, int**cost_matrix, int num);
vector<oper_rotation*>two_day_find_sp(int*base, vector<vector<string_>>&two_day_strings_, int M_num, vector<leg*>&leg_list);
vector<oper_rotation*>three_day_find_sp(int*base, vector<vector<string_>>three_day_strings, int M_num, vector<leg*>&leg_list);

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
int base_index(int i, int*base)
{
	int index_;
	for (int j = 0; j<base_num; j++)
	{
		if (i == base[j])
		{
			index_ = j;
			break;
		}
	}
	return index_;
}

bool belong_to_flight(leg*leg_, flight*flight_)
{
	if (leg_ == flight_->first_leg) { return true; }
	else if (leg_ == flight_->last_leg) { return true; }
	else { return false; }
}



int main()
{
	//创建点
	cout << "creat nodes:" << endl;
	vector<vector<event_node*>>d_nodes = daily_nodes(airports);
	vector<vector<event_node*>>w_nodes = weekly_nodes(airports);
	//创建Ground arc
	cout << "creat ground arcs:" << endl;
	G_arc*G_ = new G_arc();
	vector<vector<G_arc*>>d_G=G_->get_day_ground_arcs(d_nodes, airports);
	vector<vector<G_arc*>>w_G=G_->get_week_ground_arcs(w_nodes, airports);

	//创建leg arc

	cout << "creat leg arcs:" << endl;
	vector<leg*>daily_leg_list;
	vector<leg*>weekly_leg_list;
	leg*leg_ = new leg();
	daily_leg_list=leg_->get_day_leglist(d_nodes, airports,1);
	cout << "print daily legs info:" << endl;
	for (int i = 0; i<daily_leg_list.size(); i++)
	{
		cout << daily_leg_list[i]->index << "," << daily_leg_list[i]->origin_airp << "," << daily_leg_list[i]->departure_t << "," << daily_leg_list[i]->dest_airp << "," << daily_leg_list[i]->arrival_t << "," << daily_leg_list[i]->date << "," << daily_leg_list[i]->firm<<","<<daily_leg_list[i]->fixed_cost;
		cout << endl;
	}
	weekly_leg_list = leg_->get_week_leglist(d_nodes, airports);
	for (int i=0;i<weekly_leg_list.size();i++)
	{
		weekly_leg_list[i]->set_index(i);
	}
	//print leg
	cout << "print weekly legs info:" << endl;

	for (int i=0;i<weekly_leg_list.size();i++)
	{
		cout << weekly_leg_list[i]->index << "," << weekly_leg_list[i]->origin_airp << "," << weekly_leg_list[i]->departure_t << "," << weekly_leg_list[i]->dest_airp << "," << weekly_leg_list[i]->arrival_t << "," << weekly_leg_list[i]->date << "," << weekly_leg_list[i]->firm << "," << weekly_leg_list[i]->fixed_cost;
			cout << endl;
	}

	cout << "find one day strings:" << endl;
	vector<vector<vector<string_>>>type_strings_=find_oneday_string(weekly_leg_list);
	cout << "ok" << endl;
	/*
	cout << type_strings_.size()<<endl;
	cout << type_strings_[0][0].size() << endl;   //2
	cout << type_strings_[1][0].size() << endl;   //6
	cout << type_strings_[2][0].size() << endl;    //6
	cout << type_strings_[3][0].size() << endl;    //3

	cout << type_strings_[2][0][34].size() << endl;
	for (int i=0;i<type_strings_[2][0][34].size();i++)
	{
		cout << type_strings_[2][0][34][i]->leg_->index<<","<< type_strings_[2][0][34][i]->leg_->origin_airp<<","<< type_strings_[2][0][34][i]->leg_->dest_airp<<","<< type_strings_[2][0][34][i]->leg_->departure_t<<","<< type_strings_[2][0][34][i]->leg_->arrival_t;
		cout << endl;
	}

	cout<<type_strings_[0][0][2].front()->leg_->origin_airp << endl;
	cout << type_strings_[0][0][2].back()->leg_->origin_airp << endl;


	cout << type_strings_[0][0][15].size() << endl;
	for (int i = 0; i<type_strings_[0][0][15].size(); i++)
	{
		cout << type_strings_[0][0][15][i]->leg_->index << "," << type_strings_[0][0][15][i]->leg_->origin_airp << "," << type_strings_[0][0][15][i]->leg_->dest_airp << "," << type_strings_[0][0][15][i]->leg_->departure_t << "," << type_strings_[0][0][15][i]->leg_->arrival_t;
		cout << endl;
	}

	//cout << type_strings_[2][0][0][0]->leg_->index2 << endl;
	//cout << type_strings_[2][0][0][1]->leg_->index2 << endl;
	*/
	

	///读取OD数据
	IO*io = new IO();
	vector<OD*>OD_info = io->read_OD_info();
	///利用cplex求解主问题
	IloEnv env;
	try
	{
		IloModel INT_model(env);
		//objective
		IloObjective _maximum = IloAdd(INT_model, IloMaximize(env));
		//constraints
		IloRangeArray demand_cons(env);
		IloRangeArray weight_cons(env);
		//IloRangeArray vol_cons(env);
		//IloRangeArray flow_cons(env);
		//IloRangeArray dec_cons(env);
		IloRangeArray cover_cons(env);
		IloRangeArray balance_cons1(env);
		IloRangeArray balance_cons2(env);
	  //	IloRange artificial_con;

		//variables
		IloNumVarArray flow_vars(env);
		IloNumVarArray ground_vars(env);
		IloNumVarArray string_vars(env);

		char str[5];
		char str1[5];
		//add constraints
		//demand constraints
		for (int i = 0; i<OD_info.size(); i++)
		{
			_itoa_s(OD_info[i]->get_index(), str, 10);
			string name = string("od_demand_cons_") + string(str);
			demand_cons.add(IloRange(env, 0, OD_info[i]->quantity, name.c_str()));
		}
		cout << "demand_con_size:" << demand_cons.getSize() << endl;
		INT_model.add(demand_cons);



		//weight constraints
		for (int i = 0; i<weekly_leg_list.size(); i++)                //对于一周每天的leg来说
		{
			_itoa_s(weekly_leg_list[i]->index, str, 10);
			string name = string("weekly_leg") + string("weight_cons")+string(str);
			weight_cons.add(IloRange(env, -max_weight, 0, name.c_str()));
		}
		cout << "weight_con_size:" << weight_cons.getSize() << endl;
		INT_model.add(weight_cons);


		//cover_constraints
		for (int j = 0; j <daily_leg_list.size(); j++)
		{
			_itoa_s(daily_leg_list[j]->index, str, 10);
			string name = string("cover_cons")+string(str);
			cover_cons.add(IloRange(env, 0, 1, name.c_str()));
		}
		cout << "cover_con_size:" << cover_cons.getSize() << endl;
		INT_model.add(cover_cons);


		//aircraft_constraints
		string name = string("aircraft_cons");
		IloRange aircraft_cons(env, 0, A, name.c_str());
		INT_model.add(aircraft_cons);


		//balance_constraint1
		for (int i = 0; i<daily_leg_list.size(); i++)
		{
			_itoa_s(daily_leg_list[i]->index, str, 10);
			string name = string("balance1_cons")+string(str);
			balance_cons1.add(IloRange(env, 0, 0, name.c_str()));
		}
		cout << "balance1_cons_size:" << balance_cons1.getSize() << endl;
		INT_model.add(balance_cons1);


		//balance_constraint2
		for (int i = 0; i<daily_leg_list.size(); i++)
		{
			_itoa_s(daily_leg_list[i]->index, str, 10);
			string name = string("balance2_cons")+string(str);
			balance_cons2.add(IloRange(env, 0, 0, name.c_str()));
		}

		cout << "balance2_cons_size:" << balance_cons2.getSize() << endl;
		INT_model.add(balance_cons2);

//		string name = string("artificial_cons");
	//	artificial_con=IloRange(env, A, A);
		//INT_model.add(artificial_con);



		//add variables列添加//
		//flow_var
		INT_model.add(flow_vars);
		vector<oper_path*>path_list;
		

		cout << "ok1" << endl;
		//string var
		
		INT_model.add(string_vars);
		vector<oper_rotation*>string_list;
		
		cout << "ok1" << endl;

		//ground_var
		for (int i=0;i<d_G.size();i++)
		{
			for (int j=0;j<d_G[i].size()-1;j++)
			{
				IloNumColumn col(env);
				col += _maximum(-aircraft_fc*d_G[i][j]->get_pj());
				for (int k=0;k<daily_leg_list.size();k++)
				{
					if (daily_leg_list[k]->get_y1_d(d_G)==d_G[i][j])
					{
						col += balance_cons1[k](-1);
					}
					if (daily_leg_list[k]->get_y2_d(d_G) == d_G[i][j])
					{
						col += balance_cons1[k](1);
					}
					if (daily_leg_list[k]->get_y1_a(d_G) == d_G[i][j])
					{
						col += balance_cons2[k](-1);
					}
					if (daily_leg_list[k]->get_y2_a(d_G) == d_G[i][j])
					{
						col += balance_cons2[k](1);
					}
				}
				col += aircraft_cons(d_G[i][j]->get_pj());
				_itoa_s(i, str, 10);
				_itoa_s(j, str1, 10);
				string var_name = string("airport_")+string(str)+string("_groundarc_")+string(str1)+string("var");
				ground_vars.add(IloNumVar(col, 0, A, ILOFLOAT, var_name.c_str()));
			}
		}
		
		cout << "ok1" << endl;
		INT_model.add(ground_vars);

		cout << "ground_vars" << ground_vars.getSize() << endl;

		IloCplex MP_solve(INT_model);

		//Column Generation
		for (;;)
		{
			MP_solve.exportModel("model2_.lp");
			MP_solve.solve();
			cout << "ok1" << endl;
			IloNumArray vals(env);
			IloNumArray dualprice(env);
			env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
			MP_solve.getValues(vals, flow_vars);
			env.out() << "Values        = " << vals << endl;
			MP_solve.getValues(vals, string_vars);
			env.out() << "Values        = " << vals << endl;
			MP_solve.getValues(vals, ground_vars);
			env.out() << "Values        = " << vals << endl;
			env.out() << "Slacks        = " << vals << endl;
			MP_solve.getDuals(dualprice, weight_cons);
			env.out() << "Duals         = " << dualprice << endl;
			MP_solve.getDuals(dualprice, cover_cons);
			env.out() << "Duals         = " << dualprice << endl;
			MP_solve.getDuals(dualprice, balance_cons1);
			env.out() << "Duals         = " << dualprice << endl;
			MP_solve.getDuals(dualprice, balance_cons2);
			env.out() << "Duals         = " << dualprice << endl;
			env.out() << "Duals         = " << MP_solve.getDual(aircraft_cons) << endl;
			cout << "Solution status: " << MP_solve.getStatus() << endl;

			//duals
			IloNumArray demand_price(env, OD_info.size());
			//IloNumArray w_price(env,weekly_leg_list.size());
		//	IloNumArray leg_cover_dual(env, daily_leg_list.size());
			//IloNumArray balance1_dual(env, daily_leg_list.size());
			//IloNumArray balance2_dual(env, daily_leg_list.size());
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
			for (int i = 0; i < daily_leg_list.size(); i++)
			{
				daily_leg_list[i]->set_capacity_dual(MP_solve.getDual(weight_cons[i]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j]->set_cover_dual(MP_solve.getDual(cover_cons[j]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j] ->set_balance1_dual(MP_solve.getDual(balance_cons1[j]));
			}
			for (int j = 0; j < daily_leg_list.size(); j++)
			{
				daily_leg_list[j]->set_balance2_dual(MP_solve.getDual(balance_cons2[j]));
			}
			aircraft_num_dual = MP_solve.getDual(aircraft_cons);

			//add path and caculate path reduced cost
			IloInt t = 0;
			for (int i = 0; i < OD_info.size(); i++)
			{
				oper_path*path_ = new oper_path(i, OD_info[i]->find_shortest_path(weekly_leg_list));
				cout << "gggggggggggggggggggggggggggggggggggggggg" << OD_info.size() << endl;
				//caculate reduced cost
				double reduced_cost = path_->cacu_mp(OD_info)- demand_price[i];
				if (reduced_cost <= 0)
				{
					t++;
					cout << "aaaaaaaaaaaaaaa" << endl;
				}
				else
				{
					cout << "00000000000" << endl;
					path_list.push_back(path_);
				}
			}

			//add strings
			vector<oper_rotation*>to_add_strings;
			int*base_ = new int[base_num];
			base_[0] = 1; base_[1] = 2;
			to_add_strings = add_string(base_, type_strings_, aircraft_num_dual, daily_leg_list, base_num);

			//caculate reduced cost of all to_add_strings
			IloInt q = 0;
			for (int i = 0; i<to_add_strings.size(); i++)
			{
				double rc = to_add_strings[i]->cacu_RC(aircraft_num_dual);
				if (rc<=0)
				{
					q++;
					cout << "bbbbbbbbbbbbbbb" <<rc<< endl;
				}
				else
				{
					string_list.push_back(to_add_strings[i]);
				}
			}
			if (t == OD_info.size()&&q==to_add_strings.size())           //所有path和string的reduced cost均大于等于0，停止
			{
				
				cout <<"stop_cg!!!!!!!!" << endl;
				break;
			}
			else
			{
				
				for (int i = 0; i<path_list.size(); i++)
				{
					IloNumColumn col(env);
					OD*associated_od = OD_info[path_list[i]->get_OD_index()];
					col += _maximum(path_list[i]->cacu_mp(OD_info));
					col += demand_cons[path_list[i]->get_OD_index()](1);

					vector<int>beta_ = path_list[i]->get_beta(weekly_leg_list);  //beta stand index of leg covered by the path
					for (int j = 0; j<beta_.size(); j++)
					{
						col += weight_cons[beta_[j]](1);
					}
					_itoa_s(i + 1, str, 10);
					_itoa_s(path_list[i]->get_OD_index(), str1, 10);
					string var_name = string("od") + string(str1) + string("_pathflow") + string(str);
					flow_vars.add(IloNumVar(col, 0, associated_od->quantity, ILOFLOAT, var_name.c_str()));
				}

				cout << "_" << flow_vars.getSize() << endl;

				for (int i = 0; i < string_list.size(); i++)
				{
					IloNumColumn col(env);
					col += _maximum(-string_list[i]->get_string_cost() - aircraft_fc*string_list[i]->get_rs());        //每个环飞了几天就有几个cA
					for (int j = 0; j < string_list[i]->legs.size(); j++)
					{
						for (int k = 0; k<7; k++)
						{
							col += weight_cons[string_list[i]->legs[j]->index + daily_leg_list.size()*k](-max_weight);
						}
					}
					for (int j = 0; j < string_list[i]->legs.size(); j++)
					{
						col += cover_cons[string_list[i]->legs[j]->index](1);
					}
					col += balance_cons1[string_list[i]->legs[0]->index](1);
					col += balance_cons2[string_list[i]->legs[string_list[i]->legs.size() - 1]->index](-1);
					col += aircraft_cons(string_list[i]->get_rs());

					_itoa_s(i + 1, str, 10);
					string var_name = string("string_var_") + string(str);
					string_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
				}
				cout << "_" << string_vars.getSize() << endl;

			}
			
			
		}
					INT_model.add(IloConversion(env,string_vars, ILOINT));
					INT_model.add(IloConversion(env, ground_vars, ILOINT));
					MP_solve.solve();
					IloNumArray vals(env);
					IloNumArray dualprice(env);
					env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
					MP_solve.getValues(vals, flow_vars);
					env.out() << "Values        = " << vals << endl;
					MP_solve.getValues(vals, string_vars);
					env.out() << "Values        = " << vals << endl;
					MP_solve.getValues(vals, ground_vars);
					env.out() << "Values        = " << vals << endl;
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
					cout << "finish solve!!!!" << endl;
	               system("pause");
	               return 0;
}




vector<vector<vector<string_>>>find_oneday_string(vector<leg*>&leg_list_)
{
	vector<vector<vector<string_>>>type_strings;

	vector<treenode*>leg_nodes;
	for (int i = 0; i<leg_list_.size(); i++)
	{
		leg_nodes.push_back(new treenode(leg_list_[i]));
	}
	cout << "ok" << endl;
	cout << leg_nodes.size() << endl;

	//cout << leg_nodes[1]->leg_->origin_airp << endl;
	//找从每天从各个机场出发的leg

	vector<vector<vector<treenode*>>>day_child_legs;
	vector < vector<treenode*>>airp_child_legs;
	vector<treenode*>child_legs;

	for (int t = 1; t <= Days; t++)
	{
		for (int j = 0; j <= airports-1; j++)
		{
			for (int i = 0; i < leg_nodes.size(); i++)
			{
				if (leg_nodes[i]->leg_->origin_airp == j&&leg_nodes[i]->leg_->date == t)
				{
					child_legs.push_back(leg_nodes[i]);
				}
			}
			//cout << "jjjjjjjjjjjj"<<child_legs.size() << endl;
			airp_child_legs.push_back(child_legs);
			child_legs.clear();
		}
		day_child_legs.push_back(airp_child_legs);
		airp_child_legs.clear();
	}

	//cout << "nodes" << day_child_legs[6][1].size() << endl;
	//cout << "ok" << endl;

	//建立每个airports多天的航班树
	vector<vector<flight_tree*>>day_flight_trees;
	vector<flight_tree*>airp_flight_trees;
	for (int j = 1; j <= Days; j++)
	{
		for (int i = 0; i <= airports-1; i++)
		{
			airp_flight_trees.push_back(new flight_tree(i, j, day_child_legs[j - 1][i]));
		}
		day_flight_trees.push_back(airp_flight_trees);
		airp_flight_trees.clear();
	}


	//cout << "ok" << endl;

	//建立以每个过夜机场为出发机场的一周的每天的航班衔接树
	vector<vector<flight_string*>>day_flight_strings;
	vector<flight_string*>airp_flight_strings;
	vector<treenode*>nodes_;
	for (int i = 1; i <= Days; i++)
	{
		for (int j = 0; j <= airports-1; j++)
		{
			flight_string*flight_string_ = new flight_string(j, i, day_child_legs[i - 1][j]);
			nodes_ = flight_string_->source->source->child_legs;
			flight_string_->creat_string(nodes_, day_flight_trees[i - 1]);
			airp_flight_strings.push_back(flight_string_);
		}
		day_flight_strings.push_back(airp_flight_strings);
		airp_flight_strings.clear();
	}

	//cout << "ok" << endl;

	

	//dfs遍历找到所有的航班串
	//typedef vector<treenode* >string_;
	//typedef vector<string_>strings_;
	vector<string_>airp_string_vec(airports);   //存放一条路径
	vector<strings_>airp_strings_vec(airports);  //存放每个机场的所有路径

	vector<vector<string_>>day_strings_vec(Days);//存放一天所有的串

	for (int i = 1; i <= Days; i++)
	{
		for (int j = 1; j <= airports; j++)
		{
			treenode*current_ = day_flight_strings[i - 1][j - 1]->source->source;
			day_flight_strings[i - 1][j - 1]->dfs(airp_strings_vec[j - 1], airp_string_vec[j - 1], current_);
			for (int k = 0; k<leg_nodes.size(); k++)
			{
				leg_nodes[k]->visited = 0;    //为了不影响找下个机场的串
			}
		}
		for (int k = 1; k <= airports; k++)
		{
			for (int m = 0; m<airp_strings_vec[k - 1].size(); m++)
			{
				day_strings_vec[i - 1].push_back(airp_strings_vec[k - 1][m]);
			}
		}
		for (int k = 1; k <= airports; k++)
		{
			airp_string_vec[k - 1].clear();
		}
		for (int k = 1; k <= airports; k++)
		{
			airp_strings_vec[k - 1].clear();
		}

		//cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << endl;
	}
	//cout << day_strings_vec[6].size()<< endl;

	//细分一天的航班串
	vector<vector<string_>>s1(Days);  //从维修机场到维修机场的航班串
	vector<vector<string_>>s2(Days);  //从维修机场到过夜机场的航班串
	vector<vector<string_>>s3(Days);  //从过夜机场到过夜机场的航班串
	vector<vector<string_>>s4(Days);  //从过夜机场到维修机场的航班串
	int*base = new int[base_num];
	base[0] = 1; base[1] = 2; //base[2] = 4;   //几个维修机场
	for (int t = 1; t <= Days; t++)
	{
		for (int i = 0; i<day_strings_vec[t - 1].size(); i++)
		{
			if (is_base(day_strings_vec[t - 1][i].front()->leg_->origin_airp, base) && is_base(day_strings_vec[t - 1][i].back()->leg_->dest_airp, base))
			{
				s1[t - 1].push_back(day_strings_vec[t - 1][i]);
			}

			else if (is_base(day_strings_vec[t - 1][i].front()->leg_->origin_airp, base) && !is_base(day_strings_vec[t - 1][i].back()->leg_->dest_airp, base))
			{
				s2[t - 1].push_back(day_strings_vec[t - 1][i]);
			}
			else if (!is_base(day_strings_vec[t - 1][i].front()->leg_->origin_airp, base) && !is_base(day_strings_vec[t - 1][i].back()->leg_->dest_airp, base))
			{
				s3[t - 1].push_back(day_strings_vec[t - 1][i]);
			}
			else
			{
				s4[t - 1].push_back(day_strings_vec[t - 1][i]);
			}
		}
	}

	type_strings.push_back(s1);
	type_strings.push_back(s2);
	type_strings.push_back(s3);
	type_strings.push_back(s4);

	return type_strings;

}


double cacu_string_cost(string_ _string_)
{
	double cost_ = 0;
	for (int j = 0; j<_string_.size(); j++)
	{
		//if (j == 0)
		//{
		//	cost_ += _string_[j]->leg_->balance1_dual;
		//}
		cost_ += _string_[j]->leg_->fixed_cost - _string_[j]->leg_->leg_capacity*_string_[j]->leg_->capacity_dual + _string_[j]->leg_->cover_dual;
		//if (j == _string_.size() - 1)
		//{
			//cost_ += _string_[j]->leg_->balance2_dual;
		//}
	}
	return cost_;
}



vector<oper_rotation*>add_string(int*base,vector<vector<vector<string_>>>type_strings,double aircraft_dual,vector<leg*>leg_list,int M_num) // type_strings是各种string,s1-s4
{
	vector<string_>s1 = type_strings[0][0];   //一天的从M-M的串
	vector<string_>s2 = type_strings[1][0];//一天的从M-O的串
	vector<string_>s3 = type_strings[2][0];//O-O
	vector<string_>s4 = type_strings[3][0];//O-M


	//cout << "s1:::::::::::size" << s1.size() << endl;
	//cout << "s2:::::::::::size" << s2.size() << endl;
	//cout << "s3:::::::::::size" << s3.size() << endl;
	//cout << "s4::::::::::size" << s4.size() << endl;


	vector<oper_rotation*>all_strings;

	vector<leg*>legs;
	for (int i=0;i<s1.size();i++)
	{
		for (int j=0;j<s1[i].size();j++)
		{
			legs.push_back(leg_list[s1[i][j]->leg_->index]);
		}
		all_strings.push_back(new oper_rotation(i, legs));
		legs.clear();
	}



	//cout << "all_strings_size:::" << all_strings.size() << endl;


	//两天和三天的string的最小cost计算
	vector<vector<string_>>two_day_strings;
	two_day_strings.push_back(s2); two_day_strings.push_back(s4);

	//cout << "mmmmmmmmmmmmmmmm"<<two_day_strings[0].size() << endl;
	//cout << "mmmmmmmmmmmmmmmm" << two_day_strings[1].size() << endl;


	vector<oper_rotation*>two_day_find_sps_=two_day_find_sp(base, two_day_strings,M_num ,leg_list);

	for (int i=0;i<two_day_find_sps_.size();i++)
	{
		all_strings.push_back(two_day_find_sps_[i]);
	}

	//cout << "all_strings_size:::" << all_strings.size() << endl;

	vector<vector<string_>>three_day_strings;
	three_day_strings.push_back(s2); three_day_strings.push_back(s3); three_day_strings.push_back(s4);
	vector<oper_rotation*>three_day_find_sps_ = three_day_find_sp(base, three_day_strings, M_num, leg_list);

	for (int i = 0; i<three_day_find_sps_.size(); i++)
	{
		all_strings.push_back(three_day_find_sps_[i]);
	}

	//cout << "all_strings_size:::" << all_strings.size() << endl;
	return all_strings;
}

bool can_connect(string_ string_1,string_ string_2)
{
	for (int i=0;i<string_1.size();i++)
	{
		for (int j=0;j<string_2.size();j++)
		{
			if (string_1[i]->leg_->index2==(string_2[j]->leg_->index2))
			{
				return false;
			}
		}
	}
	return true;
}

pair<double*, int*>string_Dijkstra(int source, int**cost_matrix,int num)
{


	//cout << "test???????????????" <<source<< endl;
	/*
	for (int i=0;i<num;i++)
	{
		for (int j=0;j<num;j++)
		{
			cout << cost_matrix[i][j] << "   ";
		}
		cout << endl;
	}

	cout << "test//////////////////////////////////////////" << endl;
	for (int i = 0; i < num; ++i)
	{
		cout<<cost_matrix[1][i];
	}

	*/
	    cout << endl;
		vector<bool> isvisited(num,false);                 //是否已经在S集合中  
		double*dis_ = new double[num];
		int*pre_ = new int[num];
	/*初始化distance和prevVertex数组*/
		for (int i = 0; i < num; ++i)
		{
			dis_[i] = cost_matrix[source][i];
			if (cost_matrix[source][i] < INF)
				pre_[i] = source;
			else
				pre_[i] = -1;       //表示还不知道前一个节点是什么  
		}
		pre_[source] = -1;

		/*开始使用贪心思想循环处理不在S集合中的每一个节点*/
		isvisited[source]= true;          //开始节点放入S集合中  
		int u = source;

		for (int i = 1; i < num; i++)      //这里循环从1开始是因为开始节点已经存放在S中了，还有numOfVertex-1个节点要处理  
		{
			/*选择distance最小的一个节点*/
			int nextVertex = u;
			double tempDistance = INF;
			for (int j = 0; j < num; ++j)
			{
				if ((isvisited[j] == false) && (dis_[j] < tempDistance))//寻找不在S集合中的distance最小的节点  
				{
					nextVertex = j;
					tempDistance = dis_[j];
				}
			}
			isvisited[nextVertex] = true;//放入S集合中  
			u = nextVertex;//下一次寻找的开始节点  
			/*更新distance*/
			for (int j = 0; j < num; j++)
			{
				if (isvisited[j] == false && cost_matrix[u][j] < INF)
				{
					double temp = dis_[u] +cost_matrix[u][j];
					if (temp < dis_[j])
					{
						dis_[j] = temp;
						pre_[j] = u;
					}
				}
			}
		}

		pair<double*, int*>result_(dis_, pre_);
		/*
		cout << "dis__________" << endl;
		for (int i=0;i<num;i++)
		{
			cout << dis_[i] << "   ";
		}

		cout << "pre__________" << endl;
		for (int i = 0; i<num; i++)
		{
			cout << pre_[i] << "   ";
		}

		cout << "jkkllllllllllll" << endl;
		*/
		return result_;
}

vector<oper_rotation*>two_day_find_sp(int*base,vector<vector<string_>>&two_day_strings_,int M_num, vector<leg*>&leg_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	vector<string_>s2_ = two_day_strings_[0];
	vector<string_>s4_ = two_day_strings_[1];

//	cout << "llllllllllllllllllllllll" << s2_.size() << endl;
//	cout << "llllllllllllllllllllllll"<<s4_.size() << endl;

	int size1 = s2_.size();
	int size2 = s4_.size();
	int node_num = size1 + size2 + M_num+M_num;
	int ** cost_matrix = new int *[node_num];
	for (int i = 0; i < node_num; i++)
	{
		cost_matrix[i] = new int[node_num];
	}
	//初始化
	for (int i = 0; i < node_num; i++)
	{
		for (int j= 0; j< node_num; j++)
		{
			cost_matrix[i][j] = INF;
		}
	}
	/*
	cout << "ggggggggggggggggggggggggggggggggggggg"<<node_num << endl;

	for (int i = 0; i<node_num; i++)
	{
		for (int j = 0; j<node_num; j++)
		{
			cout << cost_matrix[i][j] << "   ";
		}
		cout << endl;
	}
	*/

	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num+size1; j++)
		{
			if (s2_[j-M_num].front()->leg_->origin_airp==base[i])
			{
				//cout << "fffffffffffffffffffffffff" << endl;
			//	cout << s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num]);
				cost_matrix[i][j] = s2_[ j - M_num].front()->leg_->balance1_dual+cacu_string_cost(s2_[ j - M_num]);
			}
		}
	}

	//cout << "test//////////////////////////////////////////" << endl;
//	for (int i = 0; i < node_num; ++i)
	//{
	//	cout << cost_matrix[1][i];
	//}

	for (int i = M_num; i < M_num+size1; i++)
	{
		for (int j = M_num + size1; j <M_num+size1+size2 ; j++)
		{
			if (s2_[i- M_num].back()->leg_->dest_airp== s4_[j- M_num-size1].front()->leg_->origin_airp&&can_connect(s2_[i - M_num], s4_[j - M_num - size1]))
			{
				//cout << "aaaaaaaaaaaaaaa" << endl;
				//cout<< cacu_string_cost(s4_[j - M_num - size1]);
				cost_matrix[i][j] = cacu_string_cost(s4_[j - M_num-size1]);
			}
		}
	}

	for (int i = M_num + size1; i < M_num + size1+size2; i++)
	{
		for (int j = M_num + size1+size2; j <M_num + size1 + size2+M_num; j++)
		{
			//cout << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" << endl;
			//cout << s4_[i - M_num - size1].back()->leg_->dest_airp << "he   " << base[j - M_num - size1 - size2] << endl;
			if (s4_[i - M_num-size1].back()->leg_->dest_airp == base[j-M_num-size1-size2])
			{
				//cout << "bbbbbbbbbbbbbbbb" << endl;
			//	cout << -s4_[ i- M_num - size1].back()->leg_->balance2_dual;
				cost_matrix[i][j] = -s4_[ i- M_num - size1].back()->leg_->balance2_dual;
			}
		}
	}


	/*
	cout << "after////////" << endl;

	for (int i = 0; i<node_num; i++)
	{
		for (int j = 0; j<node_num; j++)
		{
			cout << cost_matrix[i][j] << "   ";
		}
		cout << endl;
	}

	cout << endl;
	*/

	//有了cost矩阵，可以直接算最短路了,用Dijk



	vector<oper_rotation*>two_day_sps;
	int t = 0;
	vector<leg*>legs;
	pair<double*, int*>sp_info;
	for (int i=0;i<M_num;i++)
	{
		sp_info = string_Dijkstra(i, cost_matrix, node_num);
		for (int j=M_num+size1+size2;j<node_num;j++)
		{
			    t++;
				cout << "到达维修站" << base[j-M_num-size1-size2] << ".";
				//cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << endl;
				//cout << s4_[sp_info.second[j] - M_num - size1].size() << endl;
				for (int k=0;k<s4_[sp_info.second[j]-M_num-size1].size();k++)
				{
					legs.push_back(leg_list[s4_[sp_info.second[j] - M_num - size1][k]->leg_->index]);
				}
				for (int k = 0; k<s2_[sp_info.second[sp_info.second[j] - M_num]].size(); k++)
				{
					legs.push_back(leg_list[s2_[sp_info.second[sp_info.second[j] - M_num]][k]->leg_->index]);
				}
				//cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << endl;
				cout << "从维修站"<<base[i]<<"出发"<< ".";
			two_day_sps.push_back(new oper_rotation(t,legs));
			legs.clear();
		}
	}
	
	return two_day_sps;
}

//
vector<oper_rotation*>three_day_find_sp(int*base, vector<vector<string_>>three_day_strings, int M_num, vector<leg*>&leg_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	int size1 = three_day_strings[0].size();
	int size2 = three_day_strings[1].size();
	int size3 = three_day_strings[2].size();

	vector<string_>s2_ = three_day_strings[0];
	vector<string_>s3_ = three_day_strings[1];
	vector<string_>s4_ = three_day_strings[2];

	int node_num = M_num+size1 + size2 +size3+ M_num;
	int ** cost_matrix = new int *[node_num];
	for (int i = 0; i < node_num; i++)
	{
		cost_matrix[i] = new int[node_num];
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
			if (three_day_strings[0][j - M_num].front()->leg_->origin_airp == base[i])
			{
				cost_matrix[i][j] = s2_[j - M_num].front()->leg_->balance1_dual + cacu_string_cost(s2_[j - M_num]);
			}
		}
	}
	for (int i = M_num; i < M_num + size1; i++)
	{
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (s2_[i - M_num].back()->leg_->dest_airp == s3_[j - M_num - size1].front()->leg_->origin_airp&&can_connect(s2_[i - M_num], s3_[j - M_num - size1]))
			{
				cost_matrix[i][j] = cacu_string_cost(s3_[j - M_num - size1]);
			}
		}
	}
	for (int i = M_num+size1; i < M_num + size1+size2; i++)
	{
		for (int j = M_num + size1+size2; j <M_num + size1 + size2+size3; j++)
		{
			if (s3_[i - M_num-size1].back()->leg_->dest_airp == s4_[j - M_num - size1-size2].front()->leg_->origin_airp&&can_connect(s3_[i - M_num-size1], s4_[j - M_num - size1-size2]))
			{
				cost_matrix[i][j] = cacu_string_cost(s4_[j - M_num - size1-size2]);
			}
		}
	}

	for (int i = M_num + size1+size2; i < M_num + size1 + size2+size3; i++)
	{
		for (int j = M_num + size1 + size2+size3; j <M_num + size1 + size2 +size3+ M_num; j++)
		{
			if (s4_[i - M_num - size1-size2].back()->leg_->dest_airp == base[j - M_num - size1 - size2-size3])
			{
				cost_matrix[i][j] = s4_[ i - M_num - size1-size2].back()->leg_->balance2_dual;
			}
		}
	}

	//有了cost矩阵，可以直接算最短路了,用Dijk

	vector<oper_rotation*>three_day_sps;
	int t = 0;
	vector<leg*>legs;   //legs clear
	pair<double*, int*>sp_info;
	for (int i = 0; i<M_num; i++)
	{
		sp_info = string_Dijkstra(i, cost_matrix, node_num);
		for (int j = M_num + size1 + size2+size3; j<node_num; j++)
		{
			t++;
			
			cout << "到达维修站" << base[ j-M_num-size1-size2-size3] << ".";
			for (int k = 0; k<s4_[sp_info.second[j] - M_num - size1-size2].size(); k++)
			{
				legs.push_back(leg_list[s4_[sp_info.second[j] - M_num - size1-size2][k]->leg_->index]);
			}
			for (int k = 0; k<s3_[sp_info.second[sp_info.second[j]] - M_num - size1].size(); k++)
			{
				legs.push_back(leg_list[s3_[sp_info.second[sp_info.second[j]] - M_num - size1][k]->leg_->index]);
			}
			for (int k = 0; k<s2_[sp_info.second[sp_info.second[sp_info.second[j]]] - M_num].size(); k++)
			{
				legs.push_back(leg_list[s2_[sp_info.second[sp_info.second[sp_info.second[j]]] - M_num][k]->leg_->index]);
			}
			cout << "从维修站" << base[i] << "出发" << ".";

			three_day_sps.push_back(new oper_rotation(t, legs));
		
			legs.clear();
		}
	}

	return three_day_sps;
}


vector<vector<event_node*>>daily_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t = 4; t <= 24; t += 4)
		{
			nodes[i].push_back(new event_node(i, t * 60, nodes[i][n]));
			n++;
		}
	}
	cout << "test:" << endl;
	cout << nodes[1].size() << endl;
	return nodes;

}
vector<vector<event_node*>>weekly_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t = 4; t <= 168; t += 4)
		{
			nodes[i].push_back(new event_node(i, t * 60, nodes[i][n]));
			n++;
		}
	}
	cout << "test:" << endl;
	cout << nodes[1].size() << endl;
	return nodes;
}
