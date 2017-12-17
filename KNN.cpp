#include <iostream>  
#include <vector>  
#include <fstream>  
#include <string>  
#include <sstream>  
using namespace std;

typedef vector<float> Tuple;
const int k = 4;
const int dims = 3;
const int categories = 3; // 1,2,3  

int RunKnn(vector<Tuple>& trainData, vector<int>& label, Tuple& testData, int count);
float getDist(Tuple& trainData, Tuple& testData);
void sortDist(Tuple& dists, vector<int>& label, int count);
//void showDist(Tuple& dists, int count);

int main()
{
//已知分类的数据
	cout << "Preparing the Trainning data----" << endl;
	string fileName = "datingTestSet.txt";
	fstream file(fileName);
	if (!file)
	{
		cout << "can not open the file " << endl;
		return 0;
	}
	vector<Tuple> trainData;
	vector<int> label;
	int count = 0;
	while (!file.eof())
	{
		string str;
		getline(file, str);
		stringstream ss(str);
		ss << str;
		Tuple temp(dims, 0);
		for (int i = 0; i < dims; i++)
			ss >> temp[i];
		trainData.push_back(temp);
		int t;
		ss >> t;
		label.push_back(t);
		count++;
	}
 
	Tuple maxnum(dims, 0);
	Tuple minnum(dims, 0);
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < dims; j++)
		{
			if (trainData[i][j] > maxnum[j])
				maxnum[j] = trainData[i][j];
			if (trainData[i][j] < minnum[j])
				minnum[j] = trainData[i][j];
		}
	}
	float chazhi;
	for (int i = 0; i < dims; i++)
	{
		chazhi = maxnum[i] - minnum[i];
		for (int j = 0; j < count; j++)
			trainData[j][i] = (trainData[j][i] - minnum[i]) / chazhi;
	}
	//未知分类数据 
	cout << "Preparing the testing data-----" << endl;
	int ind = 80;
	Tuple testData = trainData[ind];
	int truthLabel = label[ind];

	//knn开始  
	cout << "Running" << endl;
	int testLabel = RunKnn(trainData, label, testData, count);
	cout << "testLabel: " << testLabel << endl;
	cout << "truthLabel: " << truthLabel << endl;
	if (testLabel == truthLabel)
		cout << "Yes!" << endl;
	else
		cout << "No!" << endl;
	system("pause");
	return 0;
}

float getDist(Tuple& trainData, Tuple& testData)
{
	float dist = 0;
	for (int i = 0; i < dims; i++)
		dist += (trainData[i] - testData[i]) * (trainData[i] - testData[i]);
	return dist;

}
//或可以用队列实现
void sortDist(Tuple& dists, vector<int>& label, int count)
{
	for (int i = 1; i < count; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (dists[j] > dists[j + 1])
			{
				float temp1 = dists[j];
				dists[j] = dists[j + 1];
				dists[j + 1] = temp1;
				int temp2 = label[j];
				label[j] = label[j + 1];
				label[j + 1] = temp2;
			}
		}
	}
}

int RunKnn(vector<Tuple>& trainData, vector<int>& label, Tuple& testData, int count)
{
	//计算距离  
	Tuple dists(count, 0);
	for (int i = 0; i < count; i++)
		dists[i] = getDist(trainData[i], testData);
	//showDist(dists, count);
	//距离排序  
	sortDist(dists, label, count);
	//showDist(dists, count);
	//统计前k个;  
	int sumLabels[3] = { 0 };
	for (int i = 0; i < k; i++)
		sumLabels[label[i] - 1] ++;
	//统计最多的那个label  
	int temp = 0;
	int testLabel;
	for (int i = 0; i < k; i++)
	{
		if (sumLabels[i] > temp)
		{
			temp = sumLabels[i];
			testLabel = i + 1;
		}
	}
	return testLabel;
}

//void showDist(Tuple& dists, int count)
//{
//	for (int i = 0; i < count; i++)
//		cout << dists[i] << " ";
//	cout << endl;
//}