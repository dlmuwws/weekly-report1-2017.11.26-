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
vector<oper_rotation*>add_string(int*base, vector<vector<vector<string_>>>type_strings, double aircraft_dual, vector<flight*>flight_list, int M_num);
bool can_connect(string_ string_1, string_ string_2);
pair<double*, int*>string_Dijkstra(int source, int**cost_matrix, int num);
vector<oper_rotation*>two_day_find_sp(int*base, vector<vector<string_>>two_day_strings, int M_num, vector<flight*>&flight_list);
vector<oper_rotation*>three_day_find_sp(int*base, vector<vector<string_>>three_day_strings, int M_num, vector<flight*>&flight_list);

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
	IO*io = new IO();
	//创建点
	cout << "test:" << endl;
	vector<vector<event_node*>>d_nodes = daily_nodes(airports);
	vector<vector<event_node*>>w_nodes = weekly_nodes(airports);
	//创建Ground arc
	G_arc*G_ = new G_arc();
	vector<vector<G_arc*>>d_G=G_->get_day_ground_arcs(d_nodes, airports);
	vector<vector<G_arc*>>w_G=G_->get_week_ground_arcs(w_nodes, airports);
	//创建leg arc

	cout << "ok" << endl;
	vector<leg*>daily_leg_list;
	vector<leg*>weekly_leg_list;
	leg*leg_ = new leg();
	daily_leg_list=leg_->get_day_leglist(d_nodes, airports,1);
	for (int i = 0; i<daily_leg_list.size(); i++)
	{
		cout << daily_leg_list[i]->index << "," << daily_leg_list[i]->origin_airp << "," << daily_leg_list[i]->departure_t << "," << daily_leg_list[i]->dest_airp << "," << daily_leg_list[i]->arrival_t << "," << daily_leg_list[i]->date << "," << daily_leg_list[i]->firm;
		cout << endl;
	}
	weekly_leg_list = leg_->get_week_leglist(d_nodes, airports);
	for (int i=0;i<weekly_leg_list.size();i++)
	{
		weekly_leg_list[i]->set_index(i + 1);
	}
	//print leg
	cout << "print leg info:" << endl;

	for (int i=0;i<weekly_leg_list.size();i++)
	{
		cout << weekly_leg_list[i]->index << "," << weekly_leg_list[i]->origin_airp << "," << weekly_leg_list[i]->departure_t << "," << weekly_leg_list[i]->dest_airp << "," << weekly_leg_list[i]->arrival_t << "," << weekly_leg_list[i]->date << "," << weekly_leg_list[i]->firm;
			cout << endl;
	}

     
	vector<vector<vector<string_>>>type_strings_=find_oneday_string(weekly_leg_list);
	cout << "kkkk" << endl;
	cout << "ok" << endl;
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
	
	

	///读取OD数据



	vector<OD*>OD_info = io->read_OD_info();
	///利用cplex求解主问题
	/*
	IloEnv env;
	try
	{
		IloModel INT_model(env);
		//objective
		IloObjective _maximum = IloAdd(INT_model, IloMaximize(env));
		//constraints
		IloRangeArray demand_cons(env);
		IloRangeArray weight_cons(env);
		IloRangeArray vol_cons(env);
		//IloRangeArray flow_cons(env);
		IloRangeArray dec_cons(env);
		IloRangeArray cover_cons(env);
		IloRangeArray aircraft_cons(env);
		IloRangeArray balance_cons(env);

		//variables
		IloNumVarArray flow_vars(env);
		IloNumVarArray flight_vars(env);
		IloNumVarArray string_vars(env);


		//add constraints
		//demand constraints
		char str[5];
		for (int i = 0; i<OD_info.size(); i++)
		{
			_itoa_s(OD_info[i]->get_index(), str, 10);
			string name = string("od_demand_cons_") + string(str);
			demand_cons.add(IloRange(env, 0, OD_info[i]->quantity, name.c_str()));
		}
		cout << "demand_con_size:" << demand_cons.getSize() << endl;
		INT_model.add(demand_cons);
		//weight constraints
		for (int i = 0; i<leg_list.size(); i++)
		{
			_itoa_s(leg_list[i]->index, str, 10);
			string name =  string("leg_weight_cons_")+string(str);
			weight_cons.add(IloRange(env, -max_weight, 0, name.c_str()));
		}
		cout << "weight_con_size:" << weight_cons.getSize() << endl;
		INT_model.add(weight_cons);
		//volume constraints
		for (int i = 0; i<leg_list.size(); i++)
		{
			_itoa_s(leg_list[i]->index, str, 10);
			string name = string("leg_volumn_cons_") + string(str);
			vol_cons.add(IloRange(env, 0, max_volume, name.c_str()));
		}
		cout << "vol_con_size:" << vol_cons.getSize() << endl;
		INT_model.add(vol_cons);
		/*
		//flow_constraints
		for (int i=0;i<OD_info.size();i++)
		{
		for (int j = 0; j < flight_list.size(); j++)
		{
		string name = string("flow_cons");
		flow_cons.add(IloRange(env, -IloInfinity, 0, name.c_str()));
		}
		}
		cout << "flow_con_size:" << flow_cons.getSize() << endl;
		INT_model.add(flow_cons);
		
		//dec_constraints
		for (int j = 0; j < flight_list.size(); j++)
		{
			_itoa_s(flight_list[j]->index, str, 10);
			string name = string("dec_cons")+string(str);
			dec_cons.add(IloRange(env, flight_list[j]->firm, 1, name.c_str()));
		}
		cout << "dec_con_size:" << dec_cons.getSize() << endl;
		INT_model.add(dec_cons);
		//cover_constraints
		for (int j = 0; j < flight_list.size(); j++)
		{
			_itoa_s(flight_list[j]->index, str, 10);
			string name = string("cover_cons_")+string(str);
			cover_cons.add(IloRange(env, 0, 0, name.c_str()));
		}
		cout << "cover_con_size:" << cover_cons.getSize() << endl;
		INT_model.add(cover_cons);
		//aircraft_constraints
		for (int i = 0; i<Days; i++)
		{
			_itoa_s(i+1, str, 10);
			string name = string("aircraft_cons_")+string(str);
			aircraft_cons.add(IloRange(env, 0, A, name.c_str()));
		}
		cout << "aircraft_con_size:" << aircraft_cons.getSize() << endl;
		INT_model.add(aircraft_cons);

		//balance_constraints
		for (int i = 0; i<o_airp_num; i++)
		{
			_itoa_s(i+1, str, 10);
			string name = string("balance_cons_")+string(str);
			balance_cons.add(IloRange(env, 0, 0, name.c_str()));
		}
		cout << "balance_cons_size:" << balance_cons.getSize() << endl;
		INT_model.add(balance_cons);


		//add variables列添加//
		//flow_vars
		INT_model.add(flow_vars);
		vector<oper_path*>path_list;// 包含了所有OD的所有Path   ...初始path加上后面列生成不断加进来的

									//加入初始解
									//for (int i = 0; i < OD_info.size(); i++)
									//{
									//    oper_path*path_ = new oper_path(i, OD_info[i]->find_shortest_path(leg_list));
									//  path_list.push_back(path_);
									//}
									/*
									for (int i=0;i<path_list.size();i++)
									{
									IloNumColumn col(env);
									OD*associated_od = OD_info[path_list[i]->get_OD_index()];
									col += _maximum(path_list[i]->cacu_mp(OD_info));
									col += demand_cons[path_list[i]->get_OD_index()](1);
									vector<int>beta_=path_list[i]->get_beta(leg_list);
									for (int j=0;j<beta_.size();j++)
									{
									col += weight_cons[beta_[j]](1);
									}
									for (int j = 0; j<beta_.size(); j++)
									{
									col += vol_cons[beta_[j]](associated_od->vol_unit);
									}
									/*
									IloInt s = 0;
									for (int j=0;j<OD_info.size();j++)
									{
									for (int k=0;k<flight_list.size();k++)
									{
									if (path_list[i]->get_OD_index()==j)
									{
									for (int a=0;a<beta_.size();a++)
									{
									if (belong_to_flight(leg_list[beta_[a]],flight_list[k]))
									{
									col += flow_cons[s](1);
									}
									}flow_vars
									}
									s++;
									}
									}

									string var_name = string("pathflow_vars");
									flow_vars.add(IloNumVar(col, 0, associated_od->quantity,ILOFLOAT, var_name.c_str()));
									}
									//cout << "mmmmm" << endl;
									cout << "_"<<flow_vars.getSize() << endl;
									


									//flight_vars
		for (int i = 0; i<flight_list.size(); i++)
		{
			IloNumColumn col(env);
			col += _maximum(-(flight_list[i]->cacu_fc()));
			/*
			IloInt h = 0;
			for (int j = 0; j<OD_info.size(); j++)
			{
			col += flow_cons[h](-M);
			h++;
			}
			
			col += weight_cons[i](-max_weight);
			col += dec_cons[i](1);
			col += cover_cons[i](-1);
			_itoa_s(flight_list[i]->index, str, 10);
			string var_name = string("flight_vars_")+string(str);
			flight_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		}
		INT_model.add(flight_vars);

		cout << "_" << flight_vars.getSize() << endl;
		//rotation var
		for (int i = 0; i<oper_rotation_list.size(); i++)
		{
			IloNumColumn col(env);
			int size1_ = oper_rotation_list[i]->get_flights_ID().size();
			//cout << "size1" << size1_ << endl;
			int size2_ = oper_rotation_list[i]->get_days_ID().size();
			//cout << "size2" << size2_ << endl;
			col += _maximum(-(aircraft_fc*size2_));        //每个环飞了几天就有几个cA
			for (int j = 0; j<size1_; j++)
			{
				col += cover_cons[(oper_rotation_list[i]->get_flights_ID())[j] - 1](1);
			}
			for (int j = 0; j<size2_; j++)
			{
				col += aircraft_cons[(oper_rotation_list[i]->get_days_ID())[j] - 1](1);
			}
			vector<flight*>flights_ = oper_rotation_list[i]->get_flights_();
			int*base = new int[base_num];
			base[0] = 1; base[1] = 2; //base[2] = 4;   //几个维修机场
			col += balance_cons[base_index(flights_[0]->first_leg->origin_airp, base)](1);
			col += balance_cons[base_index(flights_[flights_.size() - 1]->last_leg->dest_airp, base)](-1);
			_itoa_s(oper_rotation_list[i]->index_, str, 10);
			string var_name = string("string_vars_")+string(str);
			string_vars.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		}
		INT_model.add(string_vars);
		cout << "_" << string_vars.getSize() << endl;
		IloCplex MP_solve(INT_model);

		//Column Generation
		for (;;)
		{
			MP_solve.exportModel("model_.lp");
			MP_solve.solve();
			IloNumArray vals(env);
			IloNumArray dualprice(env);
			env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
			MP_solve.getValues(vals, flow_vars);
			env.out() << "Values        = " << vals << endl;
			MP_solve.getValues(vals,string_vars);
			env.out() << "Values        = " << vals << endl;
			MP_solve.getValues(vals, flight_vars);
			env.out() << "Values        = " << vals << endl;
			env.out() << "Slacks        = " << vals << endl;
			MP_solve.getDuals(dualprice, weight_cons);
			env.out() << "Duals         = " << dualprice << endl;
			MP_solve.getReducedCosts(vals, flow_vars);
			env.out() << "Reduced Costs = " << vals << endl;
			cout << "Solution status: " << MP_solve.getStatus() << endl;
			IloNumArray w_price(env, leg_list.size());
			IloNumArray v_price(env, leg_list.size());
			IloNumArray demand_price(env, OD_info.size());

			for (int i = 0; i < leg_list.size(); i++)
			{
				w_price[i] = MP_solve.getDual(weight_cons[i]);
			}
			for (int i = 0; i < leg_list.size(); i++)
			{
				v_price[i] = MP_solve.getDual(vol_cons[i]);
			}
			for (int i = 0; i<OD_info.size(); i++)
			{
				demand_price[i] = MP_solve.getDual(demand_cons[i]);
			}

			for (int j = 0; j < leg_list.size(); j++)
			{
				leg_list[j]->set_var_cost(leg_list[j]->var_cost + v_price[j] + w_price[j]);
			}

			IloInt t = 0;
			for (int i = 0; i < OD_info.size(); i++)
			{
				oper_path*path_ = new oper_path(i, OD_info[i]->find_shortest_path(leg_list));
				double mp_ = path_->cacu_mp(OD_info);
				cout << "gggggggggggggggggggggggggggggggggggggggg" << OD_info.size() << endl;
				cout << "mp_" << mp_ << endl;
				double reduced_cost = mp_ - demand_price[i];        //Caculate Reduced cost
				if (reduced_cost <= 0)
				{
					t++;
				}
				else
				{
					path_list.push_back(path_);
				}
			}

			if (t == OD_info.size())           //所有path的reduced cost均大于等于0，停止
			{
				cout << "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb" << endl;
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
					vector<int>beta_ = path_list[i]->get_beta(leg_list);
					for (int j = 0; j<beta_.size(); j++)
					{
						col += weight_cons[beta_[j]](1);
					}
					for (int j = 0; j<beta_.size(); j++)
					{
						col += vol_cons[beta_[j]](associated_od->vol_unit);
					}
					
					IloInt s = 0;
					for (int j=0;j<OD_info.size();j++)
					{
					for (int k=0;k<flight_list.size();k++)
					{
					if (path_list[i]->get_OD_index()==j)
					{
					for (int a=0;a<beta_.size();a++)
					{
					if (belong_to_flight(leg_list[beta_[a]],flight_list[k]))
					{
					col += flow_cons[s](1);
					}
					}
					}
					s++;
					}
					}
					
					_itoa_s(path_list[i]->get_OD_index(), str, 10);
					string var_name = string("od_")+string(str)+string("pathflow_vars_");
					flow_vars.add(IloNumVar(col, 0, associated_od->quantity, ILOFLOAT, var_name.c_str()));
				}
				//cout << "mmmmm" << endl;
				cout << "_" << flow_vars.getSize() << endl;
			}

		}
		//MP_solve.solve();
		INT_model.add(IloConversion(env, string_vars, ILOBOOL));
		INT_model.add(IloConversion(env, flight_vars, ILOBOOL));
		MP_solve.solve();
		IloNumArray vals(env);
		IloNumArray dualprice(env);
		env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
		MP_solve.getValues(vals, flow_vars);
		env.out() << "Values        = " << vals << endl;
		MP_solve.getValues(vals, string_vars);
		env.out() << "Values        = " << vals << endl;
		MP_solve.getValues(vals, flight_vars);
		env.out() << "Values        = " << vals << endl;
//		MP_solve.getSlacks(vals, weight_cons);
//		env.out() << "Slacks        = " << vals << endl;
//		MP_solve.getDuals(dualprice, weight_cons);
//		env.out() << "Duals         = " << dualprice << endl;
		//MP_solve.getReducedCosts(vals, flow);
		//env.out() << "Reduced Costs = " << vals << endl;
		cout << "Solution status: " << MP_solve.getStatus() << endl;
	}
	catch (IloException& ex) {
		cerr << "Error: " << ex << endl;
	}
	catch (...) {
		cerr << "Error" << endl;
	}

	env.end();
	*/
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
			cout << "jjjjjjjjjjjj"<<child_legs.size() << endl;
			airp_child_legs.push_back(child_legs);
			child_legs.clear();
		}
		day_child_legs.push_back(airp_child_legs);
		airp_child_legs.clear();
	}

	cout << "nodes" << day_child_legs[6][1].size() << endl;
	cout << "ok" << endl;

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


	cout << "ok" << endl;

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

	cout << "ok" << endl;

	

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

		cout << "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk" << endl;
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
	//对生成的航班串进行组合，生成航班环，然后生成航班环集合

	/*
	//一天环
	vector<string_>oneday_;
	for (int t = 0; t<Days; t++)
	{
		for (int i = 0; i<s1[t].size(); i++)
		{
			oneday_.push_back(s1[t][i]);
		}
	}
	cout << oneday_.size() << endl;
	//cout << "111" << endl;

	//两天环
	vector<pair<string_, string_>>twoday_;
	for (int t = 0; t < Days; t++)
	{
		if (t < Days - 1)
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s1[t + 1].size(); j++)
				{
					if (s1[t][i].back()->leg_->dest_airp == s1[t + 1][j].front()->leg_->origin_airp)
					{
						twoday_.push_back(pair<string_, string_>(s1[t][i], s1[t + 1][j]));
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s1[0].size(); j++)
				{
					if (s1[t][i].back()->leg_->dest_airp == s1[0][j].front()->leg_->origin_airp)
					{
						twoday_.push_back(pair<string_, string_>(s1[t][i], s1[0][j]));
					}
				}
			}
		}
	}

	//cout << twoday_.size() << endl;
	//cout << "111" << endl;

	for (int t = 0; t < Days; t++)
	{
		if (t < Days - 1)
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s4[t + 1].size(); j++)
				{
					if (s2[t][i].back()->leg_->dest_airp == s4[t + 1][j].front()->leg_->origin_airp)
					{
						twoday_.push_back(pair<string_, string_>(s2[t][i], s4[t + 1][j]));
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s4[0].size(); j++)
				{
					if (s2[t][i].back()->leg_->dest_airp == s4[0][j].front()->leg_->origin_airp)
					{
						twoday_.push_back(pair<string_, string_>(s2[t][i], s4[0][j]));
					}
				}
			}
		}
	}

	cout << twoday_.size() << endl;
	//cout << "111" << endl;
	//三天环
	vector<tuple<string_, string_, string_>>threeday_;
	for (int t = 0; t < Days; t++)
	{
		if (t<Days - 2)
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s1[t + 1].size(); j++)
				{
					for (int k = 0; k < s1[t + 2].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s1[t + 1][j].front()->leg_->origin_airp&&s1[t + 1][j].back()->leg_->dest_airp == s1[t + 2][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s1[t + 1][j], s1[t + 2][k]));
						}
					}
				}
			}
		}
		else if (t == Days - 2)
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s1[t + 1].size(); j++)
				{
					for (int k = 0; k < s1[0].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s1[t + 1][j].front()->leg_->origin_airp&&s1[t + 1][j].back()->leg_->dest_airp == s1[0][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s1[t + 1][j], s1[0][k]));
						}
					}
				}
			}

		}
		else
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s1[0].size(); j++)
				{
					for (int k = 0; k < s1[1].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s1[0][j].front()->leg_->origin_airp&&s1[0][j].back()->leg_->dest_airp == s1[1][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s1[0][j], s1[1][k]));
						}
					}
				}
			}
		}
	}

	//第二种情况
	for (int t = 0; t < Days; t++)
	{
		if (t<Days - 2)
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s2[t + 1].size(); j++)
				{
					for (int k = 0; k < s4[t + 2].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s2[t + 1][j].front()->leg_->origin_airp&&s2[t + 1][j].back()->leg_->dest_airp == s4[t + 2][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s2[t + 1][j], s4[t + 2][k]));
						}
					}
				}
			}
		}
		else if (t == Days - 2)
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s2[t + 1].size(); j++)
				{
					for (int k = 0; k< s4[0].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s2[t + 1][j].front()->leg_->origin_airp&&s2[t + 1][j].back()->leg_->dest_airp == s4[0][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s2[t + 1][j], s4[0][k]));
						}
					}
				}
			}

		}
		else
		{
			for (int i = 0; i < s1[t].size(); i++)
			{
				for (int j = 0; j < s2[0].size(); j++)
				{
					for (int k = 0; k < s4[1].size(); k++)
					{
						if (s1[t][i].back()->leg_->dest_airp == s2[0][j].front()->leg_->origin_airp&&s2[0][j].back()->leg_->dest_airp == s4[1][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s1[t][i], s2[0][j], s4[1][k]));
						}
					}
				}
			}
		}
	}

	//第三种情况

	for (int t = 0; t < Days; t++)
	{
		if (t<Days - 2)
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s3[t + 1].size(); j++)
				{
					for (int k = 0; k < s4[t + 2].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s3[t + 1][j].front()->leg_->origin_airp&&s3[t + 1][j].back()->leg_->dest_airp == s4[t + 2][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s3[t + 1][j], s4[t + 2][k]));
						}
					}
				}
			}
		}
		else if (t == Days - 2)
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s3[t + 1].size(); j++)
				{
					for (int k = 0; k < s4[0].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s3[t + 1][j].front()->leg_->origin_airp&&s3[t + 1][j].back()->leg_->dest_airp == s4[0][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s3[t + 1][j], s4[0][k]));
						}
					}
				}
			}

		}
		else
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s3[0].size(); j++)
				{
					for (int k = 0; k < s4[1].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s3[0][j].front()->leg_->origin_airp&&s3[0][j].back()->leg_->dest_airp == s4[1][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s3[0][j], s4[1][k]));
						}
					}
				}
			}
		}
	}



	//第4种情况

	for (int t = 0; t < Days; t++)
	{
		if (t<Days - 2)
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s4[t + 1].size(); j++)
				{
					for (int k = 0; k < s1[t + 2].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s4[t + 1][j].front()->leg_->origin_airp&&s4[t + 1][j].back()->leg_->dest_airp == s1[t + 2][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s4[t + 1][j], s1[t + 2][k]));
						}
					}
				}
			}
		}
		else if (t == Days - 2)
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s4[t + 1].size(); j++)
				{
					for (int k = 0; k < s1[0].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s4[t + 1][j].front()->leg_->origin_airp&&s4[t + 1][j].back()->leg_->dest_airp == s1[0][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s4[t + 1][j], s1[0][k]));
						}
					}
				}
			}

		}
		else
		{
			for (int i = 0; i < s2[t].size(); i++)
			{
				for (int j = 0; j < s4[0].size(); j++)
				{
					for (int k = 0; k < s1[1].size(); k++)
					{
						if (s2[t][i].back()->leg_->dest_airp == s4[0][j].front()->leg_->origin_airp&&s4[0][j].back()->leg_->dest_airp == s1[1][k].front()->leg_->origin_airp)
						{
							threeday_.push_back(make_tuple(s2[t][i], s4[0][j], s1[1][k]));
						}
					}
				}
			}
		}
	}

	cout << "三天环:" << threeday_.size() << endl;

	tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>rotation_sets;

	rotation_sets = make_tuple(oneday_, twoday_, threeday_);
	*/
	return type_strings;

}




/*

vector<oper_rotation*>get_rotation_list(tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>&rotation_sets, vector<flight*>&flight_list)
{

	vector<oper_rotation*>oper_rotation_list;
	int size1 = get<0>(rotation_sets).size();
	int size2 = get<1>(rotation_sets).size();
	int size3 = get<2>(rotation_sets).size();

	vector<flight*>flights;
	for (int i = 0; i<size1; i++)
	{
		string_ current1_;
		current1_ = get<0>(rotation_sets)[i];
		//vector<flight*>flights;
		for (int j = 0; j<current1_.size(); j++)
		{
			flights.push_back(flight_list[(current1_[j]->leg_->index) - 1]);
		}
		oper_rotation*oper_rotation_ = new oper_rotation(i, flights);
		oper_rotation_list.push_back(oper_rotation_);
		flights.clear();
	}
	flights.clear();
	for (int i = 0; i < size2; i++)
	{
		pair<string_, string_> current2_;
		current2_ = get<1>(rotation_sets)[i];
		//vector<flight*>flights;
		for (int j = 0; j < current2_.first.size(); j++)
		{
			flights.push_back(flight_list[(current2_.first[j]->leg_->index) - 1]);
		}
		for (int j = 0; j < current2_.second.size(); j++)
		{
			flights.push_back(flight_list[(current2_.second[j]->leg_->index) - 1]);
		}
		oper_rotation*oper_rotation_ = new oper_rotation(i + size1, flights);
		oper_rotation_list.push_back(oper_rotation_);
		flights.clear();
	}

	flights.clear();
	for (int i = 0; i < size3; i++)
	{
		tuple<string_, string_, string_>current3_;
		current3_ = get<2>(rotation_sets)[i];
		//	vector<flight*>flights;
		string_ string1_ = get<0>(current3_);
		for (int j = 0; j<string1_.size(); j++)
		{
			flights.push_back(flight_list[(string1_[j]->leg_->index) - 1]);
		}
		string_ string2_ = get<1>(current3_);
		for (int j = 0; j<string2_.size(); j++)
		{
			flights.push_back(flight_list[(string2_[j]->leg_->index) - 1]);
		}

		string_ string3_ = get<2>(current3_);
		for (int j = 0; j<string3_.size(); j++)
		{
			flights.push_back(flight_list[(string3_[j]->leg_->index) - 1]);
		}
		oper_rotation*oper_rotation_ = new oper_rotation(i + size1 + size2, flights);
		oper_rotation_list.push_back(oper_rotation_);
		flights.clear();
	}
	return oper_rotation_list;

}
*/
double cacu_string_cost(string_ _string_)
{
	double cost_ = 0;
	for (int j = 0; j<_string_.size(); j++)
	{
		if (j == 0)
		{
			cost_ += _string_[j]->leg_->balance1_dual;
		}
		cost_ += -_string_[j]->leg_->fixed_cost + _string_[j]->leg_->leg_capacity*_string_[j]->leg_->capacity_dual - _string_[j]->leg_->cover_dual;
		if (j == _string_.size() - 1)
		{
			cost_ += _string_[j]->leg_->balance2_dual;
		}
	}
	return cost_;
}



vector<oper_rotation*>add_string(int*base,vector<vector<vector<string_>>>type_strings,double aircraft_dual,vector<flight*>flight_list,int M_num) // type_strings是各种string,s1-s4
{
	vector<string_>s1 = type_strings[0][0];   //一天的从M-M的串
	vector<string_>s2 = type_strings[1][0];//一天的从M-O的串
	vector<string_>s3 = type_strings[2][0];//O-O
	vector<string_>s4 = type_strings[3][0];//O-M

	vector<oper_rotation*>all_strings;

	vector<flight*>flights;
	for (int i=0;i<s1.size();i++)
	{
		for (int j=0;j<s1[i].size();j++)
		{
			flights.push_back(flight_list[s1[i][j]->leg_->index]);
		}
		all_strings.push_back(new oper_rotation(i, flights));
		flights.clear();
	}

	//两天和三天的string的最小cost计算
	vector<vector<string_>>two_day_strings;
	two_day_strings.push_back(s2); two_day_strings.push_back(s3);

	vector<oper_rotation*>two_day_find_sps_=two_day_find_sp(base, two_day_strings,M_num ,flight_list);

	for (int i=0;i<two_day_find_sps_.size();i++)
	{
		all_strings.push_back(two_day_find_sps_[i]);
	}

	vector<vector<string_>>three_day_strings;
	three_day_strings.push_back(s2); three_day_strings.push_back(s3); three_day_strings.push_back(s4);
	vector<oper_rotation*>three_day_find_sps_ = three_day_find_sp(base, three_day_strings, M_num, flight_list);

	for (int i = 0; i<three_day_find_sps_.size(); i++)
	{
		all_strings.push_back(three_day_find_sps_[i]);
	}

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
}

vector<oper_rotation*>two_day_find_sp(int*base,vector<vector<string_>>two_day_strings,int M_num, vector<flight*>&flight_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	int size1 = two_day_strings[0].size();
	int size2 = two_day_strings[1].size();
	int node_num = size1 + size2 + M_num;
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
	for (int i = 0; i < M_num; i++)
	{
		for (int j = M_num; j < M_num+size1; j++)
		{
			if (two_day_strings[0][j-M_num].front()->leg_->origin_airp==base[i])
			{
				cost_matrix[i][j] = two_day_strings[0][j - M_num].front()->leg_->balance1_dual+cacu_string_cost(two_day_strings[0][j - M_num]);
			}
		}
	}
	for (int i = M_num; i < M_num+size1; i++)
	{
		for (int j = M_num + size1; j <M_num+size1+size2 ; j++)
		{
			if (two_day_strings[0][i- M_num].back()->leg_->dest_airp== two_day_strings[1][j- M_num-size1].front()->leg_->origin_airp&&can_connect(two_day_strings[0][i - M_num], two_day_strings[1][j - M_num - size1]))
			{
				cost_matrix[i][j] = cacu_string_cost(two_day_strings[1][j - M_num-size1]);
			}
		}
	}

	for (int i = M_num + size1; i < M_num + size1+size2; i++)
	{
		for (int j = M_num + size1+size2; j <M_num + size1 + size2+M_num; j++)
		{
			if (two_day_strings[1][i - M_num-size1].back()->leg_->dest_airp == base[j-M_num-size1-size2])
			{
				cost_matrix[i][j] = two_day_strings[1][j - M_num - size1].back()->leg_->balance2_dual;
			}
		}
	}

	//有了cost矩阵，可以直接算最短路了,用Dijk

	vector<oper_rotation*>two_day_sps;
	int t = 0;
	for (int i=0;i<M_num;i++)
	{
		pair<double*, int*>sp_info = string_Dijkstra(base[i], cost_matrix, node_num);
		for (int j=M_num+size1+size2;j<node_num;j++)
		{
			t++;
			vector<flight*>flights;
				cout << "到达维修站" << base[j] << ".";
				for (int k=0;k<two_day_strings[1][sp_info.second[j]-M_num-size1].size();k++)
				{
					flights.push_back(flight_list[two_day_strings[1][sp_info.second[j] - M_num - size1][k]->leg_->index]);
				}
				for (int k = 0; k<two_day_strings[0][sp_info.second[sp_info.second[j] - M_num]].size(); k++)
				{
					flights.push_back(flight_list[two_day_strings[0][sp_info.second[sp_info.second[j] - M_num]][k]->leg_->index]);
				}

				cout << "从维修站"<<base[i]<<"出发"<< ".";
			
			two_day_sps.push_back(new oper_rotation(t,flights));
		}
	}
	
	return two_day_sps;
}

//
vector<oper_rotation*>three_day_find_sp(int*base, vector<vector<string_>>three_day_strings, int M_num, vector<flight*>&flight_list)   //s2[0]和s4[1]  //找出从各个M出发的最短两天string
{
	int size1 = three_day_strings[0].size();
	int size2 = three_day_strings[1].size();
	int size3 = three_day_strings[2].size();
	int node_num = size1 + size2 +size3+ M_num;
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
				cost_matrix[i][j] = three_day_strings[0][j - M_num].front()->leg_->balance1_dual + cacu_string_cost(three_day_strings[0][j - M_num]);
			}
		}
	}
	for (int i = M_num; i < M_num + size1; i++)
	{
		for (int j = M_num + size1; j <M_num + size1 + size2; j++)
		{
			if (three_day_strings[0][i - M_num].back()->leg_->dest_airp == three_day_strings[1][j - M_num - size1].front()->leg_->origin_airp&&can_connect(three_day_strings[0][i - M_num], three_day_strings[1][j - M_num - size1]))
			{
				cost_matrix[i][j] = cacu_string_cost(three_day_strings[1][j - M_num - size1]);
			}
		}
	}
	for (int i = M_num+size1; i < M_num + size1+size2; i++)
	{
		for (int j = M_num + size1+size2; j <M_num + size1 + size2+size3; j++)
		{
			if (three_day_strings[1][i - M_num-size1].back()->leg_->dest_airp == three_day_strings[2][j - M_num - size1-size2].front()->leg_->origin_airp&&can_connect(three_day_strings[1][i - M_num-size1], three_day_strings[2][j - M_num - size1-size2]))
			{
				cost_matrix[i][j] = cacu_string_cost(three_day_strings[2][j - M_num - size1-size2]);
			}
		}
	}

	for (int i = M_num + size1+size2; i < M_num + size1 + size2+size3; i++)
	{
		for (int j = M_num + size1 + size2+size3; j <M_num + size1 + size2 +size3+ M_num; j++)
		{
			if (three_day_strings[2][i - M_num - size1-size2].back()->leg_->dest_airp == base[j - M_num - size1 - size2-size3])
			{
				cost_matrix[i][j] = three_day_strings[2][j - M_num - size1-size2].back()->leg_->balance2_dual;
			}
		}
	}

	//有了cost矩阵，可以直接算最短路了,用Dijk

	vector<oper_rotation*>three_day_sps;
	int t = 0;
	for (int i = 0; i<M_num; i++)
	{
		pair<double*, int*>sp_info = string_Dijkstra(base[i], cost_matrix, node_num);
		for (int j = M_num + size1 + size2+size3; j<node_num; j++)
		{
			t++;
			vector<flight*>flights;
			cout << "到达维修站" << base[j] << ".";
			for (int k = 0; k<three_day_strings[2][sp_info.second[j] - M_num - size1-size2].size(); k++)
			{
				flights.push_back(flight_list[three_day_strings[2][sp_info.second[j] - M_num - size1-size2][k]->leg_->index]);
			}
			for (int k = 0; k<three_day_strings[1][sp_info.second[sp_info.second[j]] - M_num - size1].size(); k++)
			{
				flights.push_back(flight_list[three_day_strings[1][sp_info.second[sp_info.second[j]] - M_num - size1][k]->leg_->index]);
			}
			for (int k = 0; k<three_day_strings[0][sp_info.second[sp_info.second[sp_info.second[j]]] - M_num].size(); k++)
			{
				flights.push_back(flight_list[three_day_strings[0][sp_info.second[sp_info.second[sp_info.second[j]]] - M_num][k]->leg_->index]);
			}
			cout << "从维修站" << base[i] << "出发" << ".";

			three_day_sps.push_back(new oper_rotation(t, flights));
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




//h文件

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
	leg(int index_, int date_, int o_airp, int d_t, int d_airp, int a_t, bool firm_, double v_c,double f_c,int index2_) :date(date_), index(index_), firm(firm_), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), var_cost(v_c), fixed_cost(f_c),index2(index2_) {}
	int cacu_ft() { return arrival_t - departure_t; };   //计算leg的flight time
	void set_var_cost(double cost_) { var_cost = cost_; };
	void set_capacity_dual(double d) { capacity_dual = d; };
	void set_cover_dual(double cost_) { cover_dual = cost_; };
	void set_balance1_dual(double cost_) { balance1_dual = cost_; };
	void set_balance2_dual(double cost_) { balance2_dual = cost_; };

	vector<oper_rotation*>get_Sl(vector<oper_rotation*>rotation_lists_);
	G_arc*get_y1_d(vector<vector<G_arc*>>G);
	G_arc*get_y2_d(vector<vector<G_arc*>>G);
	G_arc*get_y1_a(vector<vector<G_arc*>>G);
	G_arc*get_y2_a(vector<vector<G_arc*>>G);
	vector<leg*>get_day_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num,int day_);
	vector<leg*>leg::get_week_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num);

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
	flight(int index_, int date_, leg*f_l, leg*l_l, int o_airp, int d_airp, int d_t, int a_t, bool firm_,int index2_) :index(index_), date(date_), first_leg(f_l), last_leg(l_l), origin_airp(o_airp), dest_airp(d_airp), departure_t(d_t), arrival_t(a_t), firm(firm_) ,index2(index2_){}
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
	vector<leg*>find_shortest_path(vector<leg*>&leglist_);   //找到这个od此时的最短路
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
	vector<flight*>flights;
	oper_rotation(int _index_, vector<flight*>&flights_) :index_(_index_), flights(flights_) {};
	vector<int>get_flights_ID();         //这个环包含哪些flights
	vector<int>get_days_ID();             //这个航班环包含哪几天的航班串
	vector<flight*>get_flights_() { return flights; };
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

};


class IO
{
public:
	IO() {};
	pair<vector<leg*>, vector<flight*>>read_flights();
	vector<OD*>read_OD_info();
	//output


};




//arc h文件
 
 #pragma once
#include<vector>
using namespace std;

class event_node
{
public:
	int airport;
	int time;
	event_node*last_node;
	event_node(int i, int time_, event_node*last_node_):airport(i),time(time_),last_node(last_node_){}

};

class G_arc
{
public:
	event_node*start_;
	event_node*end_;
	G_arc() {};
	G_arc(event_node*_start_, event_node*_end_):start_(_start_),end_(_end_){}
	int get_pj();
	vector<vector<G_arc*>>get_day_ground_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num);
	vector<vector<G_arc*>>get_week_ground_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num);
	//vector<vector<G_arc*>>get_day_flight_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num);
	//vector<vector<G_arc*>>get_week_flight_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num);

};

 

 
//cpp

#include"class_set.h"
#include<vector>
#include<iostream>
#include <fstream>
#include <string>
#include<tuple>
#include<algorithm>
using namespace std;


#define Min_groundtime 40
#define Days 7
#define airports 5
#define INF 9999999
#define T  10080
#define count_time 0
#define PATH "C:/Users/wws199633/Desktop/"

tuple<double*, int*, int*> Dijkstra(int source, int num, pair<double, int> ** cost_time_matrix_, int max_time, vector<leg*>leglist_);


int G_arc::get_pj()
{
	int pj=0;
	if (start_->time<=count_time&&end_->time>=count_time)
	{
		pj = 1;
	}
	return pj;
}
/*
vector<vector<event_node*>>event_node::daily_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i=0;i<airport_num;i++)
	{
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t=2;t<=24;t+=2)
		{
			nodes[i].push_back(new event_node(i, t, nodes[i][n]));
			n++;
		}
	}
	return nodes;
}
vector<vector<event_node*>>event_node::weekly_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t = 2; t <= 148; t += 2)
		{
			nodes[i].push_back(new event_node(i, t, nodes[i][n]));
			n++;
		}
	}
	return nodes;
}
*/
vector<vector<G_arc*>>G_arc::get_day_ground_arcs(vector<vector<event_node*>>daily_nodes_, int airport_num)
{
	vector<vector<G_arc*>>G(airport_num);
	for (int j=0;j<airport_num;j++)
	{
		for (int i = 0; i < daily_nodes_[j].size()-1; i++)
		{
			G[j].push_back(new G_arc(daily_nodes_[j][i], daily_nodes_[j][i + 1]));
		}
	}

	cout << "test:" << endl;
	cout << G[1].size() << endl;
	return G;
}

vector<vector<G_arc*>>G_arc::get_week_ground_arcs(vector<vector<event_node*>>weekly_nodes_, int airport_num)
{
	vector<vector<G_arc*>>G(airport_num);
	for (int j = 0; j<airport_num; j++)
	{
		for (int i = 0; i < weekly_nodes_[j].size()-1; i++)
		{
			G[j].push_back(new G_arc(weekly_nodes_[j][i], weekly_nodes_[j][i + 1]));
		}
	}
	cout << "test:" << endl;
	cout << G[1].size() << endl;
	return G;
}
vector<leg*>leg::get_day_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num,int day_)
{
	int index = 1;
	vector<leg*>day_leg_list;
	for (int i=0;i<airport_num;i++)
	{
		for (int j=1;j<daily_nodes_[i].size()-2;j++)        //最晚22点
		{
			for (int k=0;k<airport_num;k++)
			{
				if (i!=k)
				{
					day_leg_list.push_back(new leg(index, day_, i, daily_nodes_[i][j]->time+(day_-1)*1440, k, daily_nodes_[k][j + 1]->time+(day_ - 1) * 1440 - Min_groundtime, 0, 0, 0, index));
					index++;
				}
			}
		}
	}
	cout << "test" << day_leg_list.size() << endl;
	return day_leg_list;
}

vector<leg*>leg::get_week_leglist(vector<vector<event_node*>>daily_nodes_, int airport_num)
{
	int index_ = 0;
	vector<leg*>week_leg_list;
	for (int i=1;i<=7;i++)
	{
		vector<leg*>leg_=this->get_day_leglist(daily_nodes_, airport_num, i);
		for (int j=0;j<leg_.size();j++)
		{
			week_leg_list.push_back(leg_[j]);
		}
	}
	return week_leg_list;
	/*
	vector<leg*>week_leg_list;

	vector<leg*>&day_leglist
	for (int j=1;j<=7;j++)
	{
		for (int i = 0; i < day_leglist.size(); i++)
		{
			leg*_leg_= day_leglist[i];
			_leg_->set_date(j);
			_leg_->set_index(index_);
			_leg_->set_departure_t(_leg_->departure_t + 1440 *( j-1));
			_leg_->set_arrival_t(_leg_->arrival_t + 1440 *( j-1));
			//cout << _leg_->index << "," << leg_->origin_airp << "," << day_leglist[i]->departure_t << "," << day_leglist[i]->dest_airp << "," << day_leglist[i]->arrival_t << "," << leg_->date << "," << day_leglist[i]->firm;
			cout << endl;
			week_leg_list.push_back(_leg_);
			index_++;
		}
	}
	cout << "test" << week_leg_list.size() << endl;
	*/
	
}

vector<oper_rotation*>leg::get_Sl(vector<oper_rotation*>rotation_lists_) 
{
	vector<oper_rotation*>Sl;
	for (int i=0;i<rotation_lists_.size();i++)
	{
		for (int j=0;j<rotation_lists_[i]->flights.size();j++)
		{
			if (rotation_lists_[i]->flights[j]->first_leg->index2==this->index2)
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
	for (int i=0;i<G[origin_airp-1].size();i++)
	{
		if (departure_t==G[origin_airp-1][i]->end_->time)
		{
			return G[origin_airp - 1][i];
		}
	}
	
}

G_arc*leg::get_y2_d(vector<vector<G_arc*>>G)
{
	//G_arc*y2_d;
	for (int i = 0; i<G[origin_airp - 1].size(); i++)
	{
		if (departure_t == G[origin_airp - 1][i]->start_->time)
		{
			return  G[origin_airp - 1][i];
			//break;
		}
	}
	//return y2_d;
}
G_arc*leg::get_y1_a(vector<vector<G_arc*>>G)
{
	
	for (int i = 0; i<G[dest_airp - 1].size(); i++)
	{
		if (arrival_t == G[dest_airp - 1][i]->end_->time)
		{

			return  G[dest_airp - 1][i];
		}
	}

}
G_arc*leg::get_y2_a(vector<vector<G_arc*>>G)
{
	
	for (int i = 0; i<G[dest_airp - 1].size(); i++)
	{
		if (arrival_t == G[dest_airp - 1][i]->start_->time)
		{

			return G[dest_airp - 1][i];
			
		}
	}
	
}



int OD::delivery_time()
{
	int max_delivery_time;
	if (date1_<date2_)
	{
		max_delivery_time = (1440 - h1 * 60 - m1 + (date2_ - date1_ - 1) * 24 * 60 + h2 * 60 + m2);
	}
	else if (date1_ = date2_)
	{
		max_delivery_time = h2 * 60 + m2 - (h1 * 60 + m1);
	}
	else
	{
		max_delivery_time = T - date1_ * 24 * 60 - h1 * 60 - m1 + (date2_ - 1) * 24 * 60 + h2 * 60 + m2;
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
			cout << "hhhhhhhhh" << endl;
			count++;
			to_add_legs.push_back(can_add_legs[i]);
		}
	}
	if (count == 0)
	{
		cout << "can not connect!!!" << endl;
		return false;
	}
	node_->child_legs = to_add_legs;
	return true;
}

bool flight_string::creat_string(vector<treenode*>&nodes, vector<flight_tree*>trees)  //创建以某个航班出发的一天的航班串,trees有时间限制，只选择这一天的trees
{
	//vector<treenode*>nodes = this->source->source->child_legs;   //nodes是需要进行衔接的点集合
	cout <<"test:"<< nodes.size() << endl;
	vector<treenode*>leave_nodes;
	int con = 0;
	for (int j = 0; j<nodes.size(); j++)
	{
		for (int k = 0; k<trees.size(); k++)
		{
			if (nodes[j]->leg_->dest_airp == trees[k]->index)   //节点的到达机场和tree的出发机场一样
			{
				cout << "llllllllllllll" << endl;
				int count = _connect(nodes[j], trees[k]);
				if (count == 1)
				{
					cout << "jjjjjjjjjjjjjjjjjjjjjj" << endl;
					con++;
					for (int s = 0; s < nodes[j]->child_legs.size(); s++)
					{
						leave_nodes.push_back(nodes[j]->child_legs[s]);
					}
				}
				//	break;
			}
		}
	}
	if (con == 0)
	{
		cout << "stop the construction of this flight_string!!!" << endl;
		return false;
	}
	creat_string(leave_nodes, trees);   //递归调用。
	return true;
}

bool flight_string::dfs(vector<vector<treenode*>>&strings_, vector<treenode*>&string_, treenode*current_)   //返回从根节点到叶节点的一天的串
{
	current_->visited = 1;
	if (current_->child_legs.size() == 0)
	{
		strings_.push_back(string_);
		cout << "碰到头停止" << strings_.size() << endl;
		cout << "strings_size" << strings_.back().size() << endl;
		cout << "stop search" << endl;
		string_.pop_back();
		return false;
	}
	for (int i = 0; i<current_->child_legs.size(); i++)
	{
		if (current_->child_legs[i]->visited == 0)
		{
			treenode*next_node = current_->child_legs[i];
			string_.push_back(next_node);
			cout << "string_" << string_.size() << endl;
			dfs(strings_, string_, next_node);
			cout << "string_" << string_.size() << endl;
			cout << "strings_size" << strings_.size() << endl;
		}
	}
	string_.pop_back();
	//cout << "string_size" << string_.size() << endl;
	return true;

}
/*
bool flight_string::dfs(vector<vector<treenode*>>&strings_, vector<treenode*>&string_, treenode*current)   //返回从根节点到叶节点的一天的串
{
	current->visited = 1;
	if (current->child_legs.size() == 0)
	{
		return false;
	}
	//int size_ = current->child_legs.size();
	for (int i = 0; i<current->child_legs.size(); i++)
	{
		if (current->child_legs[i]->visited == 0)
		{
			treenode*next_node = current->child_legs[i];
			string_.push_back(next_node);
			dfs(strings_, string_, next_node);
			strings_.push_back(string_);
		}
		//strings_.push_back(string_);
		//string_.clear();
	}
	return true;
}
*/
double oper_path::cacu_mp(vector<OD*>OD_info)   //caculate margin profits
{
	double freight_ = OD_info[this->OD_index]->freight;
	double var_costs = 0;
	for (int i = 0; i<this->legs.size(); i++)
	{
		var_costs += this->legs[i]->var_cost;
	}
	double margin_p = freight_ - var_costs;
	return margin_p;
}

vector<int>oper_path::get_beta(vector<leg*>leglist_)
{
	vector<int>beta_;   //存储path包含的leg的序号
	for (int i=0;i<leglist_.size();i++)
	{
		for (int j=0;j<this->legs.size();j++)
		{
			if (leglist_[i]==this->legs[j])
			{
				beta_.push_back(i);   
			}
		}
	}
	return beta_;
}

bool cmp(tuple<vector<int>, double,int,int>p1, tuple<vector<int>, double,int,int>p2)
{
	if (get<1>(p1) < get<1>(p2))
	{
		return true;
	}
	else
		return false;
}

vector<leg*>OD::find_shortest_path(vector<leg*>&leglist_)
{
	//先求关系矩阵0   -1   1         

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
	vector<int>Olegs_index;
	for (int i = 0; i<num; i++)
	{
		if (leglist_[i]->origin_airp == this->O_airp&&this->date1_ == leglist_[i]->date&&leglist_[i]->departure_t >= ((date1_ - 1) * 24 + h1) * 60 + m1)
		{
			Olegs_index.push_back(i);
		}
	}

	vector<tuple<vector<int>, double, int, int>>ODpaths_;   //所有路集合
	for (int i=0;i<Olegs_index.size();i++)       //对每一个从O出发的leg找一次最短路
	{
		tuple<double*, int*, int*>result_ = Dijkstra(Olegs_index[i], num, cost_time_matrix, this->delivery_time(),leglist_);
		//打印路径
		for (int j= 0; j< num; j++)
		{
			if (leglist_[j]->dest_airp == D_airp && (get<1>(result_)[j] != 0))   //可能有直达情况
			{
				vector<int>leg_index;
				cout << "exist path:" << endl;
				cout << j << ",";
				if (j!=Olegs_index[i])
				{
					leg_index.push_back(j);
					int pre_leg = get<2>(result_)[j];
					while (pre_leg != Olegs_index[i])
					{
						cout << pre_leg << ",";
						leg_index.push_back(pre_leg);
						pre_leg = get<2>(result_)[pre_leg];
					}
					cout << Olegs_index[i] << ".";
					leg_index.push_back(Olegs_index[i]);
				}
				else
				{
					leg_index.push_back(Olegs_index[i]);
				}
				cout << endl;
				ODpaths_.push_back(make_tuple(leg_index, get<0>(result_)[j], i, j));
			}
		}
	}
	
	cout << "OD_paths_size:" << ODpaths_.size() << endl;
	
	//给ODpaths排序，然后返回最短路
	vector<leg*>to_add_path;
	if (ODpaths_.size()!=0)
	{
		sort(ODpaths_.begin(), ODpaths_.end(), cmp);       //ODpath[0]存放了从O到D的cost最小的路径
		tuple<vector<int>, double, int, int>opt_path = ODpaths_[0];

		for (int i=0;i<get<0>(opt_path).size();i++)
		{
			to_add_path.push_back(leglist_[get<0>(opt_path)[i]]);
		}
	}
	else
	{
		cout << "no path!!!" << endl;
	}
    cout << "jjjjjjjjjjjjjjjjjjjjjjjj" << endl;
	return to_add_path;
}

vector<int>oper_rotation::get_flights_ID()
{
	vector<int>flights_indexs;
	for (int i=0;i<flights.size();i++)
	{
		flights_indexs.push_back(flights[i]->index);
	}
	return flights_indexs;
}

vector<int>oper_rotation::get_days_ID()
{
	vector<int>days_indexs;
	vector<int>mark_days(Days);
	for (int i = 0; i<flights.size(); i++)
	{
		if (mark_days[flights[i]->date-1]!=1)
		{
			days_indexs.push_back(flights[i]->date);
		}
		mark_days[flights[i]->date - 1] = 1;
	}
	return days_indexs;
}


pair<vector<leg*>, vector<flight*>>IO::read_flights()
{
	vector<flight*>flight_list;
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

		leg*leg_ = new leg(index, date, origin_airp, departure_t, dest_airp, arrival_t, firm, v_c, f_c,index2);
		leg_list.push_back(leg_);
		flight_list.push_back(new flight(index, date, leg_, leg_, origin_airp, dest_airp, departure_t, arrival_t, firm,index2));

	}

	infile.close();
	cout << "test:" << endl;
	cout << leg_list[1]->arrival_t << endl;
	cout << "finish read flights data" << endl;
	pair<vector<leg*>, vector<flight*>>flights_data;
	flights_data.first = leg_list; flights_data.second = flight_list;
	return flights_data;
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
	cout << "test:" << endl;
	cout << OD_info[1]->D_airp << endl;
	cout << OD_info.size() << endl;
	cout << "finish read OD data" << endl;

	return OD_info;
}

//单源最短路
tuple<double*,int*,int*> Dijkstra(int source, int num, pair<double, int> ** cost_time_matrix_,int max_time,vector<leg*>leglist_)
{

	//cout << "source" << source << endl;

vector<bool> isvisited(num,false);                 //是否已经访问过,找到最短路  
double*dis_ = new double[num];                 //源点到这个点的最短路
/*
for (int i = 0; i<num; i++)
{
	cout << dis_[i] << "    ";
}

*/
int*cumu_time_ = new int[num];    //有最短路的话，用的时间是多少
cout << endl;
cout << endl;
/*
for (int i = 0; i<num; i++)
{
	cout << cumu_time_[i] << "    ";
}
*/
int*pre_ = new int[num];
/*
for (int i = 0; i<num; i++)
{
	cout << pre_[i] << "    ";
}
cout << endl;
cout << endl;

*/
//*初始化

for (int i = 0; i < num; i++)
{
	cumu_time_[i] = 0;
}

isvisited[source] = true;
cumu_time_[source] = leglist_[source]->cacu_ft();
int u = source;

for (int i = 0; i < num; i++)
{
	if (cumu_time_[source]+cost_time_matrix_[source][i].second>=max_time)
	{
		//cout << "di" << i << "个" << "chaochushijian" << cost_time_matrix_[source][i].second;
		//cout << endl;
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
pre_[source]= -1;


//*开始使用贪心思想循环处理不在S集合中的每一个节点

for (int i = 1; i < num; i++)     
{

	//*选择u的下个节点中dis最小的一个节点
	int nextnode= u;
	double tempdis_ =INF;
	bool find= false;
	for (int j = 0; j < num; j++)
	{
		if ((isvisited[j] == false) && (dis_[j] < INF) && (pre_[j] == -1))
		{
			pre_[j] = u;
		}
		if ((isvisited[j] == false) && (dis_[j] < tempdis_)&&cumu_time_[pre_[j]] + cost_time_matrix_[pre_[j]][j].second <= max_time) //寻找不在S集合中的distance最小的节点  
		{
			    find = true;
		//		cout << "jjjjjj" << j << endl;
				nextnode = j;
				tempdis_ = dis_[j];
		}
	}
	if (nextnode==source||!find)
	{
		break;
	}
//	cout << "nnnnnnnnnn" << nextnode << endl;
		isvisited[nextnode] = true;//放入S集合中  
		cumu_time_[nextnode] = cumu_time_[pre_[nextnode]] + cost_time_matrix_[pre_[nextnode]][nextnode].second;  //更新时间
		u = nextnode;//下一次寻找的开始节点  
	
	 //*更新distance
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
 /*
 for (int i=0;i<num;i++)
 {
	 cout << cumu_time_[i] <<"    ";
 }
 cout << endl;
 cout << endl;
 cout << endl;
 for (int i = 0; i<num; i++)
 {
	 cout << dis_[i] << "    ";
 }
 cout << endl;
 cout << endl;
 cout << endl;
 for (int i = 0; i<num; i++)
 {
	 cout << pre_[i] << "    ";
 }
 */
 return result_;

}

