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
		cout << "��" << label+1 << "����" << endl;
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
	//���ݳ�ʼ�����ĸ��ظ�ֵ  
	for (i = 0; i != tuples.size(); ++i) {
		lable = ClusterAssignment(means, tuples[i]);
		clusters[lable].push_back(tuples[i]);
	}
	double oldVar = -1;
	double newVar = GetVariation(clusters, means);
	cout << "��ʼ�ĵ��������ƽ����Ϊ��" << newVar << endl;
	int t = 0;
	while (abs(newVar - oldVar) >= 1) //���¾ɺ���ֵ����1��׼����ֵ���������Ա仯ʱ���㷨��ֹ ,1��ѡ
	{
		cout << "�� " << ++t << " �ε�����ʼ��" << endl;
		for (i = 0; i < k; i++) //����ÿ���ص����ĵ�  
		{
			means[i] = GetMeans(clusters[i]);
		}
		oldVar = newVar;
		newVar = GetVariation(clusters, means); //�����µ�׼����ֵ  
		for (i = 0; i < k; i++) //���ÿ����  
		{
			clusters[i].clear();
		}
		//�����µ����Ļ���µĴ�  
		for (i = 0; i != tuples.size(); ++i) {
			lable = ClusterAssignment(means, tuples[i]);
			clusters[lable].push_back(tuples[i]);
		}
		cout << "�˴ε���֮����������ƽ����Ϊ��" << newVar << endl;
	}

	cout << "The result is:\n";
	print(clusters);
}

int main() {

	/*char fname[256];
	cout << "�����������ݵ��ļ����� ";
	cin >> fname;
	cout << endl << " ����������: ά�� ������Ŀ" << endl;
	cout << endl << " ά��dimNum: ";
	cin >> dim;
	cout << endl << " ������ĿdataNum: ";
	cin >> psize;
	ifstream infile(fname);
	if (!infile) {
		cout << "���ܴ�������ļ�" << fname << endl;
		return 0;
	}*/
	vector<Tuple> tuples;
	//���ļ����ж�������  
	for (int i = 0; i<psize && !infile.eof(); ++i)
	{
		string str;
		getline(infile, str);
		istringstream istr(str);
		Tuple tuple(dim + 1, 0);//��һ��λ�ô�ż�¼��ţ���2��dimNum+1��λ�ô��ʵ��Ԫ��  
		tuple[0] = i + 1;
		for (int j = 1; j <= dim; ++j)
		{
			istr >> tuple[j];	
		}
		tuples.push_back(tuple);
	}

	cout << endl << "��ʼ����" << endl;
	Kmean(tuples);
	system("pause");
	return 0;
}


