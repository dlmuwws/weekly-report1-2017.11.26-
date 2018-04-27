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
#define PATH "C:/Users/wws199633/Desktop/"



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
				int count = _connect(nodes[j], trees[k]);
				if (count == 1)
				{
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

bool flight_string::dfs(vector<vector<treenode*>>&strings_, vector<treenode*>&string_, treenode*current)   //返回从根节点到叶节点的一天的串
{
	current->visited = 1;
	if (current->child_legs.size() == 0)
	{
		strings_.push_back(string_);
		cout << "strings_size" << strings_.back().size() << endl;
		cout << "stop search" << endl;
		return false;
	}
	for (int i = 0; i<current->child_legs.size(); i++)
	{
		if (current->child_legs[i]->visited == 0)
		{
			treenode*next_node = current->child_legs[i];
			string_.push_back(next_node);
			cout << "string_size" << string_.size() << endl;
			dfs(strings_, string_, next_node);
			cout << "string_size" << string_.size() << endl;
			cout << "strings_size" << strings_.size() << endl;
		}
	}
	string_.pop_back();
	cout << "string_size" << string_.size() << endl;
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
	/*
	for (int j = 0; j < leglist_.size(); j++)
	{
		for (int i = 0; i < leglist_.size(); i++)
		{
			cout << relation_matrix[j][i] << "     ";
		}
		cout << endl;
		cout << endl;
		cout << endl;
	}
	*/
	//j建立cost,time矩阵pair <cost,time>

	pair<double, double> ** cost_time_matrix = new pair<double, double> *[num];
	for (int i = 0; i < num; i++)
	{
		cost_time_matrix[i] = new pair<double, double>[num];
	}

	for (int i = 0; i<num; i++)
	{
		for (int j = 0; j < num; j++)
		{

			if (relation_matrix[i][j] == 0)
			{
				if (i == j)
				{
					cost_time_matrix[i][j] = pair<double, double>(0, 0);
				}
				else
				{
					cost_time_matrix[i][j] = pair<double, double>(INF, INF);
				}
			}

			if (relation_matrix[i][j] == 1)
			{
				double time_ = leglist_[j]->arrival_t - leglist_[i]->arrival_t;    //包括了transit time
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, double>(cost_, time_);
			}
			if (relation_matrix[i][j] == -1)
			{
				double time_ = T - leglist_[i]->arrival_t + leglist_[j]->arrival_t;
				double cost_ = leglist_[j]->var_cost;
				cost_time_matrix[i][j] = pair<double, double>(cost_, time_);
			}

			//要不要考虑在机场储存货物的cost？？？
		}
	}

	//cout << "ok" << endl;
	/*
	cout << "test:" << endl;
	for (int j = 0; j < leglist_.size(); j++)
	{
		for (int i = 0; i < leglist_.size(); i++)
		{
			cout << cost_time_matrix[j][i].first << "     " << cost_time_matrix[j][i].second << endl;
		}
	}

	*/
	//求包含这个OD的O的legs
	vector<int>Olegs_index;
	for (int i = 0; i<num; i++)
	{
		if (leglist_[i]->origin_airp == this->O_airp&&this->date1_ == leglist_[i]->date&&leglist_[i]->departure_t >= ((date1_ - 1) * 24 + h1) * 60 + m1)
		{
			Olegs_index.push_back(i);
		}
	}
	//cout << "o" << O_airp << endl;
	//for (int i=0;i<Olegs_index.size();i++)
	//{
	//	cout << Olegs_index[i] << "   " << endl;
	//}
	//cout << "ok" << Olegs_index.size() << endl;

	//初始化

	int ** path_ = new int *[num];
	for (int i = 0; i < num; i++)
	{
		path_[i] = new int[num];
	}
	double ** dis_ = new double *[num];
	for (int i = 0; i < num; i++)
	{
		dis_[i] = new double[num];
	}
	//初始化Path
	for (int i = 0; i<num; i++)
	{
		for (int j = 0; j<num; j++)
		{
			if (relation_matrix[i][j] != 0)
			{
				path_[i][j] = i;
			}
			else
				path_[i][j] = -1;
		}
	}
	//初始化Dis矩阵
	for (int i = 0; i<Olegs_index.size(); i++)
	{
		for (int j = 0; j<num; j++)
		{
			if (relation_matrix[Olegs_index[i]][j] == 1)
			{
				if (date2_ >= date1_)
				{
					if (((date2_ - 1) * 24 + h2) * 60 < leglist_[j]->arrival_t)       //i连接j的话无法在时间窗内到达
					{
						dis_[Olegs_index[i]][j] = INF;
					}
					else
					{
						dis_[Olegs_index[i]][j] = cost_time_matrix[Olegs_index[i]][j].first;
					}
				}
			}
			else if (relation_matrix[Olegs_index[i]][j] == -1)
			{
				if (date2_ >= date1_)
				{
					dis_[Olegs_index[i]][j] = INF;
				}
				else if (date2_ <= date1_)
				{
					if (leglist_[j]->arrival_t>((date2_ - 1) * 24 + h2) * 60)
					{
						dis_[Olegs_index[i]][j] = INF;
					}
					else
					{
						dis_[Olegs_index[i]][j] = cost_time_matrix[Olegs_index[i]][j].first;
					}
				}
			}
		}
	}



	//Floyd找最短路

	for (int i = 0; i<Olegs_index.size(); i++)
	{
		for (int j = 0; j < num; j++)
		{
			for (int k = 0; k<num; k++)
			{
				if (dis_[Olegs_index[i]][j] > dis_[Olegs_index[i]][k] + cost_time_matrix[k][j].first)     //是否插入k点
				{
					dis_[Olegs_index[i]][j] = dis_[Olegs_index[i]][k] + cost_time_matrix[k][j].first;
					path_[Olegs_index[i]][j] = path_[k][j];
				}
			}
		}
	}




	//输出路径,存入rea_path
	vector<int> ** rea_path = new vector<int> *[num];
	for (int i = 0; i < num; i++)
	{
		rea_path[i] = new vector<int>[num];
	}

	
	for (int i = 0; i< num; i++)
	{
		for (int j = 0; j < num; j++)
		{

			int q = path_[i][j];
			while (q != i&&q != -1)
			{
				rea_path[i][j].push_back(q);
				q = path_[i][q];
			}
		}
	}

	
	//找最短路
	pair<int, int>SP_index;    //OD最短路是从O的i leg 到D的j leg
	vector<tuple<vector<int>, double, int, int>>ODpaths_;   //OD的path和总的cost
	for (int i = 0; i < Olegs_index.size(); i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (leglist_[j]->dest_airp == D_airp)
			{
				ODpaths_.push_back(make_tuple(rea_path[i][j], dis_[i][j], i, j));
			}
		}
	}
	//给ODpaths排序，然后返回最短路

	sort(ODpaths_.begin(), ODpaths_.end(), cmp);       //ODpath[0]存放了从O到D的cost最小的路径

	//cout << ODpaths_.size() << endl;
	

	//以leg串的形式输出路径，返回
	tuple<vector<int>, double, int, int>opt_path = ODpaths_[0];

	vector<leg*>to_add_path;


	if (rea_path[get<2>(opt_path)][get<3>(opt_path)].size() != 0)    //不是直达
	{
		to_add_path.push_back(leglist_[get<2>(opt_path)]);   //第一个leg节点
		for (int i = 0; i<rea_path[get<2>(opt_path)][get<3>(opt_path)].size(); i++)
		{
			to_add_path.push_back(leglist_[rea_path[get<2>(opt_path)][get<3>(opt_path)][i]]);
		}
		to_add_path.push_back(leglist_[get<3>(opt_path)]);
	}
	else
	{
		if (leglist_[get<2>(opt_path)]->index != leglist_[get<3>(opt_path)]->index)  // 一次中转
		{
			to_add_path.push_back(leglist_[get<2>(opt_path)]);
			to_add_path.push_back(leglist_[get<3>(opt_path)]);
		}
		else
		{
			to_add_path.push_back(leglist_[get<2>(opt_path)]);   //直达
		}
	}

	//cout << "jjjjjjjjjjjjjjjjjjjjjjjj到达时间" << to_add_path.back()->arrival_t << endl;
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
	string filename = PATH + string("flights_data.csv");
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


		leg*leg_ = new leg(index, date, origin_airp, departure_t, dest_airp, arrival_t, firm, v_c, f_c);
		leg_list.push_back(leg_);
		flight_list.push_back(new flight(index, date, leg_, leg_, origin_airp, dest_airp, departure_t, arrival_t, firm));

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
