io.h
#pragma once
#include<iostream>
#include<vector>
using namespace std;

class stock
{
public:
	double indicator1;   //13个指标
	double indicator2;
	double indicator3;
	double indicator4;
	double indicator5;
	double indicator6;
	double indicator7;
	double indicator8;
	double indicator9;
	double indicator10;
	double indicator11;
	double indicator12;
	double indicator13;
	stock(double ind1, double ind2, double ind3, double ind4, double ind5, double ind6, double ind7, double ind8, double ind9, double ind10, double ind11, double ind12, double ind13) :
	indicator1(ind1), indicator2(ind2), indicator3(ind3), indicator4(ind4), indicator5(ind5), indicator6(ind6), indicator7(ind7), indicator8(ind8), indicator9(ind9), indicator10(ind10), indicator11(ind11), indicator12(ind12), indicator13(ind13)
	{
	}
	void print() 
	{
		cout <<indicator1 << "  " <<indicator2 << "  " << indicator3 << "  " << indicator4 << "  " << indicator5 << "  " << indicator6 << "  " << indicator7 << "  " << indicator8 << "  " <<indicator9 << "  " <<indicator10 << "  " << indicator11 << "  " <<indicator12 << "  " <<indicator13  << endl;
	}
	bool operator=(const stock *stock_)
	{
		int k = 0;
		if (this->indicator1 == stock_->indicator1) { k++; }
		if (this->indicator2 == stock_->indicator2) { k++; }
		if (this->indicator3 == stock_->indicator3) { k++; }
		if (this->indicator4 == stock_->indicator4) { k++; }
		if (this->indicator5 == stock_->indicator5) { k++; }
		if (this->indicator6 == stock_->indicator6) { k++; }
		if (this->indicator7 == stock_->indicator7) { k++; }
		if (this->indicator8 == stock_->indicator8) { k++; }
		if (this->indicator9 == stock_->indicator9) { k++; }
		if (this->indicator10 == stock_->indicator10) { k++; }
		if (this->indicator11 == stock_->indicator11) { k++; }
		if (this->indicator12 == stock_->indicator12) { k++; }
		if (this->indicator13 == stock_->indicator13) { k++; }
		if (k == 13)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class io
{
public:
	io() {};
	void input(vector<stock*>&sample_sets);
};






io.cpp

#include<iostream>
#include<vector>
#include"io.h"
#include <fstream>
#include <string>
using namespace std;
#define PATH "C:/Users/wws199633/Desktop/"

void io::input(vector<stock*>&sample_sets)
{
	string filename = PATH + string("data.csv");
	ifstream infile;
	infile.open(filename.c_str());
	cout << "#Read stock data from " << filename << "\n";
	string buff;
	char* token;
	char* temp;
	double idc1;
	double idc2;
	double idc3;
	double idc4;
	double idc5;
	double idc6;
	double idc7;
	double idc8;
	double idc9;
	double idc10;
	double idc11;
	double idc12;
	double idc13;
	while (getline(infile,buff))
	{
		token = strtok_s((char*)buff.c_str(), ",", &temp);
		idc1 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc2 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc3 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc4 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc5 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc6 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc7 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc8 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc9 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc10 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc11 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc12 = atof(token);
		token = strtok_s(NULL, ",", &temp);
		idc13 = atof(token);
		stock*stock_ = new stock(idc1,idc2,idc3, idc4, idc5, idc6, idc7, idc8, idc9,idc10, idc11, idc12, idc13);
		sample_sets.push_back(stock_);
	}
	infile.close();
	cout << "test:" << endl;
	sample_sets[1]->print();
	cout << "finish read stock datas" << endl;
}









GA.h
#pragma once
#include"io.h"
#include<vector>
using namespace std;

typedef vector<stock*>chros;   //染色体
class GA
{
private:
	int iter;   //停止迭代次数
	double cross_p; //交叉概率
	double mutate_p; //变异概率
	int N; //种群个体数
	vector<chros>population;   //种群
	vector<double>fitness;   //适应度
public:
	GA();
	void set_cp(double cp_) { cross_p = cp_; };
	void set_mp(double mp_) { mutate_p = mp_; };
	void set_N(int N_) { N = N_; };
	void set_iter(int iter_) { iter = iter_; };
	int getN() { return N; };
	int get_iter() { return iter; };
	void init() { fitness.push_back(0); };
	vector<chros>get_population() { return population; };
	vector<double>get_fitness() { return fitness; };
	double getcp() { return cross_p; };
	double getmp() { return mutate_p; };
	vector<chros> creat_population(GA &GA, int n_, vector<stock*>sample_sets);   
	vector<double>cacu_fitness(GA &GA, vector<stock*>sample_sets);
	vector<chros> choose(GA &GA);
	vector<chros>cross(GA &GA,double p);
	vector<chros>mutate(GA &GA,double q, vector<stock*>sample_sets);
};







GA.cpp
#include "GA.h"
#include"io.h"
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include<math.h>
#include<algorithm>
#include<tuple>
using namespace std;

//定义常量
#define   MAX   999999    
#define julei  3    //聚类数
#define yb 64     //样本数


GA::GA()
{
};
vector<chros> GA::creat_population(GA &GA,int n_, vector<stock*>sample_sets)
{
	cout << "start!!!" << endl;
	//每次从样本集中随机选n_个，组成一个染色体，然后生成N个染色体的种群
	int k = 0;
	while (k<GA.N)
	{
		chros chros_;
		int a = 0; int b = sample_sets.size();  //生成[a,b)的整数
		srand((int)time(NULL)+k);
		for (int i=0;i<n_;i++)
		{
			cout << (rand() % (b - a)) + a << " ";
			chros_.push_back(sample_sets[(rand() % (b - a)) + a]);
		}
		cout << endl;
		bool repeat = false;
		for (int i = 0; i < k; i++)
		{
			if (chros_==GA.population[i])   //有重复，重新生成
			{
				repeat = true;
				break;
			}
		}
		if (repeat) { continue; }
		GA.population.push_back(chros_);
		k++;
	}
	return population;
 }

double squa(double a, double b)  
{
	double t = (b - a)*(b - a);
	return t;
}
double CalcDist(stock* a, stock *b)                //计算两点之间的距离的平方（欧氏距离的平方）
{                                                     
	double t = 0;
	t = squa(a->indicator1, b->indicator1) + squa(a->indicator2, b->indicator2) + squa(a->indicator3, b->indicator3) + squa(a->indicator4, b->indicator4) + squa(a->indicator5, b->indicator5) + squa(a->indicator6, b->indicator6) + squa(a->indicator7, b->indicator7) + squa(a->indicator8, b->indicator8) + squa(a->indicator9, b->indicator9) + squa(a->indicator10, b->indicator10);
	return t;
}

int getMin_index(vector<double>&tempdist)//返回与某聚类中心距离最小值所在的下标
{
	int sign = 0;
	for (int i = 1; i<tempdist.size(); i++) 
	{
		if (tempdist[i] < tempdist[sign])
		{
			sign = i;
		}
	}
	return sign;
}

double getMin_Value(vector<double>tempdist)  //返回距离最小值
{
	double temp = tempdist[0];
	for (int i = 1; i<tempdist.size(); i++) {
		if (tempdist[i]<temp)
			temp = tempdist[i];
	}
	return temp;
}

bool cmp(vector<stock*>&oldcenter_, vector<stock*>&newcenter_)  //比较两次的聚类中心是否一样
{
	bool same = false;
	int k = 0;
	for (int i=0;i<julei;i++)
	{
		if (oldcenter_[i]->operator=(newcenter_[i]))
		{
			k++;
		}
	}
	if (k == oldcenter_.size()) { same = true; }
	return same;
}
vector<double>GA::cacu_fitness(GA &GA, vector<stock*>sample_sets)
{
	//用每一个初始聚类中心，计算一遍k-means,用聚类结果求适应度值
	cout << "start!!!" << endl;
	for (int i=0;i<GA.N;i++)   //每个染色体计算一次适应度
	{
		cout << "第" << i <<"个染色体适应度计算："<< endl;
		vector<stock*>initcenter;     
		vector<stock*>newcenter;       
		vector<vector<double>>tempdists(yb, {0,0,0});       //存储各点到各聚类中心的距离的矩阵
		vector<tuple<stock*, int,double>>cluster_soln;            //聚类结果矩阵
		vector<vector<stock*>>cluster_soln2(julei);     //每一类中有哪些股票
		vector<tuple<stock*, int, double>>cluster_soln_re;           
		vector<vector<stock*>>cluster_soln2_re(julei);
		for (int j=0;j<julei;j++)
		{
			initcenter.push_back(&stock(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0));
		}
		newcenter= GA.population[i];  //选定初始聚类中心
		int s = 1;
		double oldobj = -1;
		double newobj=MAX;
		while (oldobj==-1||abs(newobj-oldobj)>=oldobj*0.01)    //停止聚类条件
		{
			vector<tuple<stock*, int, double>>cluster_soln;            //聚类结果矩阵
			vector<vector<stock*>>cluster_soln2(julei);     //每一类中有哪些股票
			cout << "oldobj" << oldobj << endl;
			cout << "newobj" << newobj << endl;
			s++;
			initcenter = newcenter;
			oldobj = newobj;
			//对每个点计算到各聚类中心的距离,欧式距离,并确定离哪个聚类中心的距离最近
			for (int j=0;j<yb;j++)
			{
				for (int k= 0; k<julei; k++)
				{
					tempdists[j][k] = CalcDist(sample_sets[j], initcenter[k]);
				}
			}
			//为每个点确定属于哪一类
			for (int j = 0; j<yb; j++)
			{
				cluster_soln.push_back(make_tuple(sample_sets[j],getMin_index(tempdists[j]), getMin_Value(tempdists[j])));
			}
			//确定每一类中有哪些
			for (int k = 0; k<julei; k++)
			{
				for (int j = 0; j<yb; j++)
				{
					if (get<1>(cluster_soln[j])== k)
					{
						cluster_soln2[k].push_back(get<0>(cluster_soln[j])); 
					}
				}
			}
			//更新各类的聚类中心,计算平均值
			for (int k=0;k<newcenter.size();k++)
			{
				double sum_inc1=0; double sum_inc2=0; double sum_inc3=0; double sum_inc4=0; double sum_inc5=0;
				double sum_inc6=0; double sum_inc7=0; double sum_inc8=0; double sum_inc9=0; double sum_inc10=0;
				double sum_inc11 = 0; double sum_inc12 = 0; double sum_inc13= 0;
				for (int j=0;j<cluster_soln2[k].size();j++)
				{
					sum_inc1 += cluster_soln2[k][j]->indicator1;
					sum_inc2 += cluster_soln2[k][j]->indicator2;
					sum_inc3 += cluster_soln2[k][j]->indicator3;
					sum_inc4 += cluster_soln2[k][j]->indicator4;
					sum_inc5 += cluster_soln2[k][j]->indicator5;
					sum_inc6 += cluster_soln2[k][j]->indicator6;
					sum_inc7 += cluster_soln2[k][j]->indicator7;
					sum_inc8 += cluster_soln2[k][j]->indicator8;
					sum_inc9 += cluster_soln2[k][j]->indicator9;
					sum_inc10 += cluster_soln2[k][j]->indicator10;
					sum_inc11 += cluster_soln2[k][j]->indicator11;
					sum_inc12 += cluster_soln2[k][j]->indicator12;
					sum_inc13 += cluster_soln2[k][j]->indicator13;
				}
				int size= cluster_soln2[k].size();
				if (size!=0)
				{
					stock *stock_ = new stock(sum_inc1 / size, sum_inc2 / size, sum_inc3 / size, sum_inc4 / size, sum_inc5 / size, sum_inc6 / size, sum_inc7 / size, sum_inc8 / size, sum_inc9 / size, sum_inc10 / size, sum_inc11 / size, sum_inc12 / size, sum_inc13 / size);
					newcenter[k] = stock_;
				}
			}
			newobj = 0;
			for (int j = 0; j<cluster_soln.size(); j++)
			{
				newobj+= get<2>(cluster_soln[j]);
			}
			cluster_soln_re = cluster_soln; cluster_soln2_re = cluster_soln2;
			cluster_soln.clear();            
			cluster_soln2.clear();
			vector<vector<stock*>>cluster_soln2_(julei);
		}
		cout << "聚类迭代" << s-1<<"次" << endl;    
		//知道聚类结果后，计算该聚类结果下的适应度值
		//适应度等于类间差异度/类内离散度。 适应度越大，则聚类效果越好
		//类间差异：计算各聚类中心之间的距离之和
		//类内离散：各点到其对应的聚类中心的距离之和
		double sum1 = 0; //类间
		double sum2= 0; //类内

		for (int j=0;j<julei;j++)
		{
			for (int k=j+1;k<julei;k++)
			{
				sum1 += CalcDist(initcenter[j], initcenter[k]);
			}
		}
		for (int j=0;j<cluster_soln_re.size();j++)
		{
			sum2 += get<2>(cluster_soln_re[j]);
		}
		double f = sum1 / sum2;
		GA.fitness[i]=f;
	}
	return GA.get_fitness();
}

//选择(轮盘赌)下代种群
vector<chros> GA::choose(GA &GA)
{
	vector<double>prob;
	vector<double>sum_prob;  //每个个体有一个累计概率
	int size_ = GA.get_population().size();
	double sum=0; //所有个体适应度之和
	
	for (int i=0;i<size_;i++)
	{
		sum += GA.get_fitness()[i];
	}
	for (int i = 0; i<size_; i++)
	{
		prob.push_back(GA.get_fitness()[i] / sum);
	}

	sum_prob.push_back(prob[0]);
	for (int i = 1; i<size_; i++)
	{
		sum_prob.push_back(sum_prob[i - 1] + prob[i]);
	}

	vector<chros>population_re; population_re = GA.population;

	srand((unsigned)time(NULL));
	for (int i = 0; i < GA.N;i++)          //生成子代种群
	{
		double r = rand() % (N + 1) / (float)(N + 1);
		if (r<sum_prob[0])
		{
			GA.population[i] = population_re[0];
			break;
		}
		for (int j = 1; j< GA.N; j++)
		{
			if (sum_prob[j-1]<r&&r<sum_prob[j])
			{
				GA.population[i] = population_re[j];
				break;
			}
		}
		cout << endl;
	}
	prob.clear(); sum_prob.clear();
	return GA.population;
}

//交叉(单点交叉)
vector<chros>GA::cross(GA &GA,double p)
{
	srand((int)time(NULL));
	for (int i = 0; i < GA.N; i = i + 2)
	{
		double pp = rand() % 1000 / (float)1000;   //0-1之间的随机数
		if (pp < p)
		{
			int a = 0; int  b = julei - 1;
			int  s = (rand() % (b - a+1)) + a;    
			for (int j = s; j < julei; j++)
			{
				stock*c;
				c = GA.population[i][j];
				GA.population[i][j] = GA.population[i + 1][j];
				GA.population[i + 1][j] = c;
			}
		}
		else
		{
			continue;
		}
	}
		return GA.population;
}

//变异
vector<chros>GA::mutate(GA &GA, double q, vector<stock*>sample_sets)
{
	srand((int)time(NULL));
	for (int i = 0; i < GA.N; i++)
	{
		double pp = rand() % 1000 / (float)1000;
		if (pp < q)
		{
			int a = 0; int  b = julei - 1;
			int  s = (rand() % (b - a+1)) + a;    //变异点
			for (int j=0;j<yb;j++)
			{
				if (!sample_sets[j]->operator=(GA.population[i][s]))
				{
					GA.population[i][s] = sample_sets[j];
					break;
				}
				else
					continue;
			}
		}
		else
			continue;
	}
	return GA.population;
}
//主程序
int main()
{
	io io;
	vector<stock*>sample_sets; 
    io.input(sample_sets);
	//读取数据
	    cout << "sample:" << sample_sets.size() << endl;
		GA GA;
		GA.set_iter(100);
		GA.set_N(30);  //染色体数
		GA.set_cp(0.6);
		GA.set_mp(0.05);
		GA.creat_population(GA, julei, sample_sets);
		for (int j = 0; j < GA.getN(); j++) { GA.init(); };
		int i = 0;
		while (i<=GA.get_iter())  //迭代
		{
			cout << "第" << i << "次迭代:" << endl;
			GA.cacu_fitness(GA, sample_sets);
			for (int j = 0; j < GA.getN(); j++){ cout << GA.get_fitness()[j] << "  "; }
			GA.choose(GA);
			GA.cross(GA, GA.getcp());
			GA.mutate(GA, GA.getmp(), sample_sets);
			i++;
		}
		cout << "finish!!!" << endl;
		system("pause");
	return 0;
}
