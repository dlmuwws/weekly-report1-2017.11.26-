#include<ilcplex/ilocplex.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include"class_set.h"

#include<iostream>
using namespace std;

#define Days 7
#define airports 5
#define base_num 3  //维修机场的个数
#define max_weight 4000
#define max_volume 3000
#define M 9999999
#define aircraft_fc 100
#define A 10
#define o_airp_num 3

typedef vector<treenode* >string_;
typedef vector<string_>strings_;


vector<vector<event_node*>>daily_nodes(int airport_num);
vector<vector<event_node*>>weekly_nodes(int airport_num);
tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>find_rotation(vector<leg*>&leg_list);
vector<oper_rotation*>get_rotation_list(tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>&rotation_sets, vector<flight*>&flight_list);
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
int base_index(int i,int*base)
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
		pair<vector<leg*>, vector<flight*>>flights_data;
		///读取航班数据
		flights_data = io->read_flights();
		vector<leg*>leg_list = flights_data.first;
		vector<flight*>flight_list = flights_data.second;
		///构建航班环
		tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>rotation_sets;
		rotation_sets = find_rotation(leg_list);
		///备选航班环集合
		vector<oper_rotation*>oper_rotation_list;
		oper_rotation_list = get_rotation_list(rotation_sets, flight_list);
		///读取OD数据
		vector<OD*>OD_info = io->read_OD_info();
		vector<oper_rotation*>SI;
		SI= leg_list[7]->get_Sl(oper_rotation_list);
		cout << SI.size() << endl;
		
		vector<vector<event_node*>>daily_nodes_=daily_nodes(5);
		cout << daily_nodes_.size() << endl;
		cout << daily_nodes_[1].size() << endl;
		vector<vector<event_node*>>weekly_nodes_ = weekly_nodes(5);
		cout << weekly_nodes_.size() << endl;
		cout <<weekly_nodes_[1].size() << endl;


		arc*arc_ = new arc();
		vector<vector<arc*>>G1_;
		vector<vector<arc*>>G2_;
		G1_=arc_->get_day_ground_arcs(daily_nodes_, 5);
		G2_=arc_->get_week_ground_arcs(weekly_nodes_, 5);
		cout << G1_.size()<<endl;
		cout << G1_[3].size()<<endl;
		cout << G2_.size()<<endl;
		cout << G2_[1].size()<<endl;

		cout << leg_list[7]->get_y1_d(G2_)->end_->time << endl;
		cout << leg_list[7]->departure_t << endl;

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

		//variables
		IloNumVarArray flow_var(env);
		IloNumVarArray ground_var(env);
		IloNumVarArray string_var(env);
	

		//add constraints
		//demand constraints
		for (int i=0;i<OD_info.size();i++)
		{
			string name = string("od") +string("demand_cons");
			demand_cons.add(IloRange(env, 0, OD_info[i]->quantity, name.c_str()));
		}
		cout << "demand_con_size:"<<demand_cons.getSize() << endl;
		INT_model.add(demand_cons);
		//weight constraints
		for (int i = 0; i<leg_list.size(); i++)
		{
			string name = string("leg") + string("weight_cons");
			weight_cons.add(IloRange(env, -max_weight, 0, name.c_str()));
		}
		cout << "weight_con_size:" << weight_cons.getSize() << endl;
		INT_model.add(weight_cons);
		
		
		//cover_constraints
		for (int j = 0; j < flight_list.size(); j++)
		{
			string name = string("cover_cons");
			cover_cons.add(IloRange(env, 0, 1, name.c_str()));
		}
		cout << "cover_con_size:" << cover_cons.getSize() << endl;
		INT_model.add(cover_cons);
		//aircraft_constraints
		
		string name = string("aircraft_cons");
		IloRange aircraft_cons(env, 0, A, name.c_str());
		INT_model.add(aircraft_cons);

		//balance_constraint1
		for (int i = 0; i<leg_list.size(); i++)
		{
			string name = string("balance_cons");
			balance_cons1.add(IloRange(env, 0, 0, name.c_str()));
		}

		cout << "balance_cons_size:" << balance_cons1.getSize() << endl;
		INT_model.add(balance_cons1);

		//balance_constraint2
		for (int i = 0; i<leg_list.size(); i++)
		{
			string name = string("balance_cons");
			balance_cons2.add(IloRange(env, 0, 0, name.c_str()));
		}

		cout << "balance_cons_size:" << balance_cons2.getSize() << endl;
		INT_model.add(balance_cons2);



		 //add variables列添加//
		//flow_var
		INT_model.add(flow_var);
		vector<oper_path*>path_list;// 包含了所有OD的所有Path   ...初始path加上后面列生成不断加进来的

		//string var
		for (int i=0;i<oper_rotation_list.size();i++)
		{
			IloNumColumn col(env);
			col += _maximum(-oper_rotation_list[i]->get_string_cost()-aircraft_fc*oper_rotation_list[i]->get_rs());        //每个环飞了几天就有几个cA
			for (int j=0;j<oper_rotation_list[i]->flights.size();j++)
			{
				col += weight_cons[oper_rotation_list[i]->flights[j]->index - 1](-max_weight);
			}
			for (int j = 0; j<oper_rotation_list[i]->flights.size(); j++)
			{
				col += cover_cons[oper_rotation_list[i]->flights[j]->index - 1](1);
			}
			col += balance_cons1[oper_rotation_list[i]->flights[0]->index - 1](1);
			col += balance_cons2[oper_rotation_list[i]->flights[oper_rotation_list[i]->flights.size()-1]->index - 1](1);
			col += aircraft_cons(oper_rotation_list[i]->get_rs());
			
			string var_name = string("string_var");
			string_var.add(IloNumVar(col, 0, 1, ILOFLOAT, var_name.c_str()));
		}
		INT_model.add(string_var);
		cout << "_" << string_var.getSize() << endl;

		//ground_var








		IloCplex MP_solve(INT_model);

		//Column Generation
		
		for (;;)
		{
		
			MP_solve.solve();   

			IloNumArray vals(env);
			IloNumArray dualprice(env);
			env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
			MP_solve.getValues(vals, flow_var);
			env.out() << "Values        = " << vals << endl;
			env.out() << "Slacks        = " << vals << endl;
			MP_solve.getDuals(dualprice, weight_cons);
			env.out() << "Duals         = " << dualprice << endl;
			MP_solve.getReducedCosts(vals, flow_var);
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
			for (int i=0;i<OD_info.size	();i++)
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
				cout << "gggggggggggggggggggggggggggggggggggggggg" <<OD_info.size()<< endl;
				cout << "mp_" << mp_ << endl;
				double reduced_cost = mp_ - demand_price[i];        //Caculate Reduced cost
				if (reduced_cost<=0)
				{
					t++;
				}
				else
				{
					path_list.push_back(path_);
				}
			}

			if (t==OD_info.size())           //所有path的reduced cost均大于等于0，停止
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
					}
					}
					s++;
					}
					}
					
					string var_name = string("pathflow_var");
					flow_var.add(IloNumVar(col, 0, associated_od->quantity, ILOFLOAT, var_name.c_str()));
				}
				//cout << "mmmmm" << endl;
				cout << "_" << flow_var.getSize() << endl;
			}

		}
		
		//MP_solve.solve();
		INT_model.add(IloConversion(env,rotation_var, ILOINT));
		INT_model.add(IloConversion(env,flight_var, ILOINT));
		MP_solve.solve();
		IloNumArray vals(env);
		IloNumArray dualprice(env);
		env.out() << "Solution value  = " << MP_solve.getObjValue() << endl;
		MP_solve.getValues(vals, flow_var);
		env.out() << "Values        = " << vals << endl;
//		MP_solve.getSlacks(vals, flow_cons);
		env.out() << "Slacks        = " << vals << endl;
		MP_solve.getDuals(dualprice, weight_cons);
		env.out() << "Duals         = " << dualprice << endl;
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




tuple<vector<string_>, vector<pair<string_, string_>>, vector<tuple<string_, string_, string_>>>find_rotation(vector<leg*>&leg_list_)
{

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
		for (int j = 1; j <= airports; j++)
		{
			for (int i = 0; i < leg_nodes.size(); i++)
			{
				if (leg_nodes[i]->leg_->origin_airp == j&&leg_nodes[i]->leg_->date == t)
				{
					child_legs.push_back(leg_nodes[i]);
				}
			}
			airp_child_legs.push_back(child_legs);
			child_legs.clear();
		}
		day_child_legs.push_back(airp_child_legs);
		airp_child_legs.clear();
	}

	cout << "nodes" <<day_child_legs[1][2].size() << endl;
	cout << "ok" << endl;

	//建立每个airports多天的航班树
	vector<vector<flight_tree*>>day_flight_trees;
	vector<flight_tree*>airp_flight_trees;
	for (int j = 1; j <= Days; j++)
	{
		for (int i = 1; i <= airports; i++)
		{
			airp_flight_trees.push_back(new flight_tree(i, j, day_child_legs[j - 1][i - 1]));
		}
		day_flight_trees.push_back(airp_flight_trees);
		airp_flight_trees.clear();
	}


	cout << "ok" << endl;

	//建立以每个过夜机场为出发机场的一周的每天的航班衔接树
	vector<vector<flight_string*>>day_flight_strings;
	vector<flight_string*>airp_flight_strings;
	for (int i = 1; i <= Days; i++)
	{
		for (int j = 1; j <= airports; j++)
		{
			flight_string*flight_string_ = new flight_string(j, i, day_child_legs[i - 1][j - 1]);
			vector<treenode*>nodes_ = flight_string_->source->source->child_legs;
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
	}
	//cout << day_strings_vec[6].size()<< endl;

	//细分一天的航班串
	vector<vector<string_>>s1(Days);  //从维修机场到维修机场的航班串
	vector<vector<string_>>s2(Days);  //从维修机场到过夜机场的航班串
	vector<vector<string_>>s3(Days);  //从过夜机场到过夜机场的航班串
	vector<vector<string_>>s4(Days);  //从过夜机场到维修机场的航班串
	int*base = new int[base_num];
	base[0] = 1; base[1] = 2; base[2] = 4;   //几个维修机场
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

	//对生成的航班串进行组合，生成航班环，然后生成航班环集合


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

	return rotation_sets;

}






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
		oper_rotation*oper_rotation_ = new oper_rotation(i,1, flights);
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
		oper_rotation*oper_rotation_ = new oper_rotation(i + size1,2, flights);
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
		oper_rotation*oper_rotation_ = new oper_rotation(i + size1 + size2, 3,flights);
		oper_rotation_list.push_back(oper_rotation_);
		flights.clear();
	}
	return oper_rotation_list;

}


vector<vector<event_node*>>daily_nodes(int airport_num)
{
	vector<vector<event_node*>>nodes(airport_num);
	for (int i = 0; i<airport_num; i++)
	{
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t = 2; t <= 24; t += 2)
		{
			nodes[i].push_back(new event_node(i, t*60, nodes[i][n]));
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
		nodes[i].push_back(new event_node(i, 0, NULL));
		int n = 0;
		for (int t = 2; t <= 168; t += 2)
		{
			nodes[i].push_back(new event_node(i, t*60, nodes[i][n]));
			n++;
		}
	}
	return nodes;
}
