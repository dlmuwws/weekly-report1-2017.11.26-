#include<time.h>
#include<random>
#include<math.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<sstream>
using namespace std;

//#define psize 20
#define k 2
int psize;


int dim(0);

typedef vector<double> Tuple;

double GetDistance(const Tuple &t1, const Tuple &t2) {
	double sum(0);
	for (int i = 0; i < dim; i++)
		sum = sum + (t1[i] - t2[i])*(t1[i] - t2[i]);

	return sqrt(sum);
}

int ClusterAssignment(Tuple means[], const Tuple &tuple) {
	double dist = GetDistance(means[0], tuple);
	double temp(0.0);
	int label(0);
	for (int i = 1; i < k; ++i) {
		temp = GetDistance(means[i], tuple);
		if (temp < dist) {
			dist = temp;
			label = i;
		}
	}
	return label;
}

double GetVariation(vector<Tuple> clusters[],Tuple means[]) {
	double var(0.0);
	for (int i = 0; i < k; ++i) {
		vector<Tuple> t = clusters[i];
		for (int j = 0; j < t.size(); ++j)
			var += GetDistance(t[j], means[i]);
	}
	return var;
}

Tuple GetMeans(const vector<Tuple> & cluster) {
	int num = cluster.size();
	Tuple t(dim + 1, 0);
	for (int i = 0; i < num; ++i) {
		for (int j = 0; j <= dim; ++j)
			t[j] += cluster[i][j];
	}
	for (int j = 1; j <= dim;++j)
		t[j] /= num;

	return t;
}
void print(const vector<Tuple> clusters[]) {
	for (int label = 0; label < k; ++label) {
		cout << "第" << label+1 << "个簇" << endl;
		vector<Tuple> t = clusters[label];
		for (int i = 0; i < t.size(); ++i) {
			cout << i + 1 << ".( ";
			for (int j = 0; j <dim; ++j)
				cout << t[i][j] << ", ";
			cout << ")\n";
		}
	}
}

void Kmean(vector<Tuple> & tuples) {
	vector<Tuple> clusters[k];
	Tuple means[k];
	int i(0);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < k; ) {
		int iToSelect = rand() % tuples.size();
		if (means[iToSelect].size() == 0) {
			for (int j = 0; j <= dim; ++j)
				means[i].push_back(tuples[iToSelect][j]);
			++i;
		}
	}

	int lable = 0;
	//根据初始的质心给簇赋值  
	for (i = 0; i != tuples.size(); ++i) {
		lable = ClusterAssignment(means, tuples[i]);
		clusters[lable].push_back(tuples[i]);
	}
	double oldVar = -1;
	double newVar = GetVariation(clusters, means);
	cout << "初始的的整体误差平方和为：" << newVar << endl;
	int t = 0;
	while (abs(newVar - oldVar) >= 1) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止 ,1可选
	{
		cout << "第 " << ++t << " 次迭代开始：" << endl;
		for (i = 0; i < k; i++) //更新每个簇的中心点  
		{
			means[i] = GetMeans(clusters[i]);
		}
		oldVar = newVar;
		newVar = GetVariation(clusters, means); //计算新的准则函数值  
		for (i = 0; i < k; i++) //清空每个簇  
		{
			clusters[i].clear();
		}
		//根据新的质心获得新的簇  
		for (i = 0; i != tuples.size(); ++i) {
			lable = ClusterAssignment(means, tuples[i]);
			clusters[lable].push_back(tuples[i]);
		}
		cout << "此次迭代之后的整体误差平方和为：" << newVar << endl;
	}

	cout << "The result is:\n";
	print(clusters);
}

int main() {

	/*char fname[256];
	cout << "请输入存放数据的文件名： ";
	cin >> fname;
	cout << endl << " 请依次输入: 维数 样本数目" << endl;
	cout << endl << " 维数dimNum: ";
	cin >> dim;
	cout << endl << " 样本数目dataNum: ";
	cin >> psize;
	ifstream infile(fname);
	if (!infile) {
		cout << "不能打开输入的文件" << fname << endl;
		return 0;
	}*/
	vector<Tuple> tuples;
	//从文件流中读入数据  
	for (int i = 0; i<psize && !infile.eof(); ++i)
	{
		string str;
		getline(infile, str);
		istringstream istr(str);
		Tuple tuple(dim + 1, 0);//第一个位置存放记录编号，第2到dimNum+1个位置存放实际元素  
		tuple[0] = i + 1;
		for (int j = 1; j <= dim; ++j)
		{
			istr >> tuple[j];	
		}
		tuples.push_back(tuple);
	}

	cout << endl << "开始聚类" << endl;
	Kmean(tuples);
	system("pause");
	return 0;
}


