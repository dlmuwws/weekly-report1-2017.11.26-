io.h

#pragma once
#include<iostream>
#include<vector>
using namespace std;

class stock
{
public:
	double indicator1;   //10个指标
	double indicator2;
	double indicator3;
	double indicator4;
	double indicator5;
	double indicator6;
	double indicator7;
	double indicator8;
	double indicator9;
	double indicator10;
	double return_rate;   //股票回报率
	stock(double ind1, double ind2, double ind3, double ind4, double ind5, double ind6, double ind7, double ind8, double ind9, double ind10, double r_r) :
	indicator1(ind1), indicator2(ind2), indicator3(ind3), indicator4(ind4), indicator5(ind5), indicator6(ind6), indicator7(ind7), indicator8(ind8), indicator9(ind9), indicator10(ind10), return_rate(r_r)
	{
	}
	void print() 
	{
		cout <<indicator1 << "  " <<indicator2 << "  " << indicator3 << "  " << indicator4 << "  " << indicator5 << "  " << indicator6 << "  " << indicator7 << "  " << indicator8 << "  " <<indicator9 << "  " <<indicator10 << "  " << return_rate << endl;
	}
	bool operator=(const stock *stock_)
	{
		cout << "test" << endl;
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
		if (k == 10)
		{
			cout << 1<<endl;
			return true;
		}
		else
		{
			cout << 0<<endl;
			return false;
		}
	}
};

class io
{
public:
	io() {};
	void input(vector<stock*>&sample_sets, vector<double>&indicators_1, vector<double>&indicators_2,
		vector<double>&indicators_3,
		vector<double>&indicators_4,
		vector<double>&indicators_5,
		vector<double>&indicators_6,
		vector<double>&indicators_7,
		vector<double>&indicators_8,
		vector<double>&indicators_9,
		vector<double>&indicators_10,
		vector<double>&return_rates);
	
	
};


io.cpp

#include<iostream>
#include<vector>
#include"io.h"
#include <fstream>
#include <string>
using namespace std;
#define PATH "C:/Users/wws199633/Desktop/"



void io::input(vector<stock*>&sample_sets, vector<double>&indicators_1, vector<double>&indicators_2,
vector<double>&indicators_3,
vector<double>&indicators_4,
vector<double>&indicators_5,
vector<double>&indicators_6,
vector<double>&indicators_7,
vector<double>&indicators_8,
vector<double>&indicators_9,
vector<double>&indicators_10,
vector<double>&return_rates)
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
	double rr;
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
		rr = atof(token);

		indicators_1.push_back(idc1); indicators_2.push_back(idc2); indicators_3.push_back(idc3);
		indicators_4.push_back(idc4); indicators_5.push_back(idc5); indicators_6.push_back(idc6); 
		indicators_7.push_back(idc7); indicators_8.push_back(idc8); indicators_9.push_back(idc9);
		indicators_10.push_back(idc10); return_rates.push_back(rr);
		stock*stock_ = new stock(idc1,idc2,idc3, idc4, idc5, idc6, idc7, idc8, idc9,idc10,rr);
		sample_sets.push_back(stock_);
	}

	infile.close();
	sample_sets[7]->print();
	cout << "finish read stock datas" << endl;
}

/*
int main()
{
	cout << "start!!!" << endl;
	io io;
	io.input();
	system("pause");
	return 0;
}

//void io::output()
//{


//}
*/





GA.h
#pragma once
#include"io.h"
#include<vector>
using namespace std;

const int n = 3;   //聚类个数
typedef vector<stock*>chros;   //染色体
class GA
{
private:
	int iter;   //停止迭代次数
	double cross_p; //交叉概率
	double mutate_p; //变异概率
	int N; //种群个体数
	vector<chros>population;   //种群
	vector<double>fitness;
public:
	GA();
	void set_cp(double cp_) { cross_p = cp_; };
	void set_mp(double mp_) { mutate_p = mp_; };
	void set_N(int N_) { N = N_; };
	void set_iter(int iter_) { iter = iter_; };
	vector<chros>get_population() { return population; };
	vector<double>get_fitness() { return fitness; };
	vector<chros> creat_population(GA &GA, int n_, vector<stock*>sample_sets);   //生成初始种群
	vector<double>cacu_fitness(GA &GA, vector<stock*>sample_sets);
	vector<chros> choose(GA &GA);
	vector<chros>cross(GA &GA,double p);
	vector<chros>mutate(GA &GA,double q);
};


GA.cpp

#include "GA.h"
#include"io.h"
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include<algorithm>
#include<tuple>
using namespace std;

//定义常量
#define max_iter //最大迭代次数
#define MAX 9999
#define julei  3
#define yb 60


GA::GA()
{
};
vector<chros> GA::creat_population(GA &GA,int n_, vector<stock*>sample_sets)
{
	cout << "start!!!" << endl;
	//每次从样本集中随机选n_个，组成一个染色体，然后生成N个染色体的种群
	int k = 0;
	cout << "N" << GA.N << endl;
	while (k<GA.N)
	{
		chros chros_;
		int a = 0; int b = sample_sets.size();  //生成[a,b)的整数
		srand((int)time(NULL)+k);
		for (int i=0;i<n_;i++)
		{
			cout << (rand() % (b - a)) + a << endl;
			chros_.push_back(sample_sets[(rand() % (b - a)) + a]);
		}
		
		bool repeat = false;
		for (int i = 0; i < k; i++)
		{
			if (chros_==GA.population[i])   //有重复
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


double squa(double a, double b)  //计算每个指标的欧式距离
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

bool cmp(vector<stock*>&oldcenter_, vector<stock*>&newcenter_)
{
	bool same = false;
	int k = 0;
	for (int i=0;i<julei;i++)
	{
		oldcenter_[i]->print();
		newcenter_[i]->print();
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
		cout << "i" << i << endl;
		vector<stock*>initcenter;     
		vector<stock*>newcenter;       
		vector<vector<double>>tempdists(yb, {0,0,0});       //存储各点到各聚类中心的距离的矩阵
		vector<tuple<stock*, int,double>>cluster_soln;            //聚类结果矩阵
		vector<vector<stock*>>cluster_soln2;     //每一类中有哪些股票
		for (int j=0;j<julei;j++)
		{
			initcenter.push_back(&stock(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
		}
		newcenter= GA.population[i];  //选定初始聚类中心
		newcenter[1]->print();
		initcenter[1]->print();
		int s = 0;
		while (!cmp(initcenter,newcenter))    //新旧聚类中心一样时停止聚类
		{
			s++;
			initcenter = newcenter;
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
			cout << "ok" << endl;
			//确定每一类中有哪些
			for (int k = 0; k<julei; k++)
			{
				for (int j = 0; j<yb; j++)
				{
					int g = 0;
					if (get<1>(cluster_soln[j])== k)
					{
						
						get<0>(cluster_soln[j])->print();
						cluster_soln2[k][g]=get<0>(cluster_soln[j]);
						g++;
						
					}
				}
				cout << endl;
			}
			
			//更新各类的聚类中心,计算平均值
			for (int k=0;k<newcenter.size();k++)
			{
				double sum_inc1=0; double sum_inc2=0; double sum_inc3=0; double sum_inc4=0; double sum_inc5=0;
				double sum_inc6=0; double sum_inc7=0; double sum_inc8=0; double sum_inc9=0; double sum_inc10=0;
				double sum_rr=0;
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
					sum_rr += cluster_soln2[k][j]->return_rate;
				}
				int size= cluster_soln2[k].size();
				stock*stock_ = new stock(sum_inc1/size,sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size, sum_inc1 / size,sum_rr/size);
			    newcenter.push_back(stock_);
			}
			//更新新的聚类中心
			initcenter.clear();
			newcenter.clear();
			tempdists.clear();       //将上一次的聚类结果清除
			cluster_soln.clear();            
			cluster_soln2.clear();
		}
		cout << "s" << s << endl;    
		//知道聚类结果后，计算该聚类结果下的适应度值
		//适应度等于类间差异度/类内离散度。 适应度越大，则聚类效果越好
		//类间差异：计算各聚类中心之间的距离之和
		//类内离散：各点到其对应的聚类中心的距离之和
		double sum1 = 0; //类间
		double sum2= 0; //类内
		for (int j=0;j<newcenter.size();j++)
		{
			for (int k=j+1;k<newcenter.size();k++)
			{
				sum1 += CalcDist(newcenter[j], newcenter[k]);
			}
		}
		for (int j=0;j<cluster_soln.size();j++)
		{
			sum2 += get<2>(cluster_soln[j]);
		}
		double f = sum1 / sum2;
		GA.fitness.push_back(f);
	}
	return GA.get_fitness();
}

//选择(轮盘赌)下代种群
vector<chros> GA::choose(GA &GA)
{
	cout << "start!!!" << endl;
	vector<double>prob;
	vector<double>sum_prob;  //每个个体有一个累计概率
	int size_ = GA.get_population().size();
	double sum=0; //所有个体适应度之和
	//给原来种群排序
	for (int i=0;i<size_;i++)
	{
		for (int j= i; j<size_;j++)
		{
			if (GA.get_fitness()[i]>GA.get_fitness()[j])
			{
				chros c; double d; 
				c = GA.population[i];                           d = GA.get_fitness()[i];
				GA.population[i] = GA.population[j];  GA.get_fitness()[i] = GA.get_fitness()[j];
				GA.population[j] = c;                           GA.get_fitness()[j] = d;
			}
		}
	}
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

	srand((unsigned)time(NULL));
	for (int i = 0; i < GA.N;i++)          //生成子代种群
	{
		for (int j = 0; j< GA.N; j++)
		{
			if (rand() % (N + 1) / (float)(N + 1)<sum_prob[j])
			{
				GA.population[i] = GA.population[j];
				break;
			}
		}
	}
	return GA.population;
}

////交叉(单点交叉)
vector<chros>GA::cross(GA &GA,double p)
{
	for (int i=1;i<GA.N;i=i+2)
	{ 
		double pp = rand() % 1000 / (float)1000;   //0-1之间的随机数
		if (pp < p)
		{
			int a = 0; int  b = julei - 1;
			int  s = (rand() % (b - a)) + a;    //交叉点
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

int main()
{
	io io;
	vector<stock*>sample_sets; 
	vector<double>indicators_1; 
	vector<double>indicators_2;
	vector<double>indicators_3;
	vector<double>indicators_4;
	vector<double>indicators_5;
	vector<double>indicators_6;
	vector<double>indicators_7;
	vector<double>indicators_8;
	vector<double>indicators_9;
	vector<double>indicators_10;
	vector<double>return_rates;
    io.input(sample_sets, indicators_1, indicators_2, indicators_3, indicators_4, indicators_5, indicators_6, indicators_7, indicators_8, indicators_9, indicators_10, return_rates);
	//读取数据
	    cout << "sample:" << sample_sets.size() << endl;
		GA GA;
		GA.set_N(30);  //染色体数
		int g = 3;  //聚类数
		GA.creat_population(GA, g, sample_sets);
		cout << GA.get_population().size()<<endl;
		GA.get_population()[0][0]->print();
		GA.cacu_fitness(GA,sample_sets);
		GA.choose(GA);
		GA.get_population()[0][0]->print();
		cout << "finish!!!" << endl;
		system("pause");
	return 0;
}




