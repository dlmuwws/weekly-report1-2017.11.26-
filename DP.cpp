#include<fstream>
#include<string>
#include<vector>
#include "DP.h"
#include<iostream>
using namespace std;
#define wspeedlimit 15
#define inputpath "D:/气象数据优化大赛/"
#define ftype ".csv"
#define outputpath "D:/气象数据优化大赛/"
#define IMAX 18.5
#define IMIN 12.3


double getMax(double *arr,int count) {
	double max = arr[0];
	for (int i = 1; i < count; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}

double getMin(double*arr, int count) {
	double min = arr[0];
	for (int i = 0; i < count; ++i) {
		if (arr[i] < min)
			min = arr[i];
	}
	return min;
}


void getError() {
	int day(1);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) +"_R10" +ftype);
	ifstream infile(infilename.c_str());
	//output
	string outfileless(outputpath + in + "_day" + to_string(day) + "less" + ftype);
	ofstream outfile1(outfileless.c_str());//输出小于15的真值对应的最大预测值
	string outfilelarger(outputpath + in + "_day" + to_string(day) + "larger" + ftype);
	ofstream outfile2(outfilelarger.c_str());//输出大于15的真值对应的最小预测值

	string outfilefeasible(outputpath + in + "_day" + to_string(day) + "_feasible" + ftype);
	ofstream outfilefea(outfilefeasible.c_str());//输出小于15的真值
	string outfileinfeasible(outputpath + in + "_day" + to_string(day) + "_infeasible" + ftype);
	ofstream outfileinfea(outfileinfeasible.c_str());//输出大于15的真值

	string buf;
	char *token;
	char *tmp;
	int countless=0, countlarger=0;

	int x = 0;
	int y = 0;
	int date = 0;
	int hour = 0;
	double wind = 0.0;
	double rea[10];

	while (getline(infile, buf))
	{

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		//x = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//y = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//date = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//hour = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		wind = atof(token);//真实值

		token = strtok_s(NULL, ",", &tmp);
		rea[0] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[1] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[2] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[3] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[4] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[5] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[6] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[7] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[8] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[9] = atof(token);

		double err;//用于存放预测极值

		if (wind > wspeedlimit) {
			err = getMin(rea, 10);
		    outfile2<<  err << '\n';
			outfileinfea << buf << '\n';
			countlarger++;
		}
		else {
			err = getMax(rea, 10);
			outfile1<<  err << '\n';
			outfilefea << buf << '\n';
			countless++;
		}

	}
	infile.close();
	outfile1.close();
	outfile2.close();
	cout << "The Number of countlarger is " << countlarger << endl;
	cout << "The Number of countless is " << countless << endl;

}

void getMAX() {
	int day(1);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "less" + ftype);
	ifstream infile(infilename.c_str());

	char buf[10];
	double MAX = 0.00;
	while (infile.getline(buf, sizeof(buf)))
		if (atof(buf) > MAX)
			MAX = atof(buf);
	cout << "The MAX Forecast Value for " << day << "  is: " << MAX << endl;
	infile.close();

}

void getMIN() {
	int day(1);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "larger" + ftype);
	ifstream infile(infilename.c_str());

	char buf[10];
	double MIN = 30.00;
	while (infile.getline(buf, sizeof(buf)))
		if (atof(buf) < MIN)
			MIN = atof(buf);
	cout << "The MIN Forecast Value for " << day << "  is: " << MIN << endl;
	infile.close();

}

void getFeasibleInterval() {
	int day(1);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "_feasible" + ftype);
	ifstream infile(infilename.c_str());
	//output
	string outfile1516(outputpath + in + "_day" + to_string(day) + "_15_16" + ftype);
	ofstream outfile15_16(outfile1516.c_str());//输出小于15的真值对应预测值15 到16
	string outfile1617(outputpath + in + "_day" + to_string(day) + "_16_17" + ftype);
	ofstream outfile16_17(outfile1617.c_str());//输出小于15的真值对应预测值16到17
	string outfile17(outputpath + in + "_day" + to_string(day) + "_17_max" + ftype);
	ofstream outfile_17(outfile17.c_str());//17-max

	string buf;
	char *token;
	char *tmp;


	int x = 0;
	int y = 0;
	int date = 0;
	int hour = 0;
	double wind = 0.0;
	double rea[10];

	int countInterval[3] = { 0,0,0 };//统计区间出现的次数
	int countIntervalRealization[3][10] = { {0,0,0,0,0,0,0,0,0,0},{ 0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0 } };//统计各区间模型出现的次数

	while (getline(infile, buf))
	{

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		//x = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//y = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//date = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//hour = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		wind = atof(token);//真实值

		token = strtok_s(NULL, ",", &tmp);
		rea[0] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[1] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[2] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[3] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[4] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[5] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[6] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[7] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[8] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[9] = atof(token);

		for (int i = 0; i < 10; ++i) {
			if (rea[i] > 15.00 && rea[i] <= 16.00) {
				countInterval[0]++;
				countIntervalRealization[0][i]++;
				outfile15_16 << buf << '\n';
			}
			if (rea[i] > 16.00 && rea[i] <= 17.00) {
				countInterval[1]++;
				countIntervalRealization[1][i]++;
				outfile16_17 << buf << '\n';
			}
			if (rea[i] > 17.00 && rea[i] <= IMAX) {
				countInterval[2]++;
				countIntervalRealization[2][i]++;
				outfile_17 << buf << '\n';
			}
		}	
	}

	infile.close();
	outfile15_16.close();
	outfile16_17.close();
	outfile_17.close();
	cout <<'\n'<< "Frequency of 3 intervals are" << '\n';
	for (int i = 0; i < 3; ++i) {
		cout << endl;
		cout <<"Interval  "<<i+1<<":     "<< countInterval[i] << '\n';
		for (int j = 0; j < 10; j++)
			cout << "In this interval realiazation:" << j + 1 << "occurs:  " << countIntervalRealization[i][j] << endl;
	}
}


void getInfeasibleInterval() {
	int day(1);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "_infeasible" + ftype);
	ifstream infile(infilename.c_str());
	//output
	string outfile13(outputpath + in + "_day" + to_string(day) + "_min_13" + ftype);
	ofstream outfile_13(outfile13.c_str());//输出小于15的真值对应预测值15 到16
	string outfile1314(outputpath + in + "_day" + to_string(day) + "_13_14" + ftype);
	ofstream outfile13_14(outfile1314.c_str());//输出小于15的真值对应预测值16到17
	string outfile1415(outputpath + in + "_day" + to_string(day) + "_14_15" + ftype);
	ofstream outfile14_15(outfile1415.c_str());//17-max

	string buf;
	char *token;
	char *tmp;


	int x = 0;
	int y = 0;
	int date = 0;
	int hour = 0;
	double wind = 0.0;
	double rea[10];

	int countInterval[3] = { 0,0,0 };//统计区间出现的次数
	int countIntervalRealization[3][10] = { { 0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0 },{ 0,0,0,0,0,0,0,0,0,0 } };//统计各区间模型出现的次数

	while (getline(infile, buf))
	{

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		//x = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//y = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//date = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		//hour = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		wind = atof(token);//真实值

		token = strtok_s(NULL, ",", &tmp);
		rea[0] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[1] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[2] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[3] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[4] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[5] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[6] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[7] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[8] = atof(token);
		token = strtok_s(NULL, ",", &tmp);
		rea[9] = atof(token);

		for (int i = 0; i < 10; ++i) {
			if (rea[i] >= IMIN && rea[i] <= 13.00) {
				countInterval[0]++;
				countIntervalRealization[0][i]++;
				outfile_13 << buf << '\n';
			}
			if (rea[i] > 13.00 && rea[i] <= 14.00) {
				countInterval[1]++;
				countIntervalRealization[1][i]++;
				outfile13_14 << buf << '\n';
			}
			if (rea[i] > 14.00 && rea[i] <= 15.00) {
				countInterval[2]++;
				countIntervalRealization[2][i]++;
				outfile14_15 << buf << '\n';
			}
		}
	}

	infile.close();
	outfile_13.close();
	outfile13_14.close();
	outfile14_15.close();
	cout << '\n' << "Frequency of 3 intervals are" << '\n';
	for (int i = 0; i < 3; ++i) {
		cout << endl;
		cout << "Interval  " << i + 1 << ":     " << countInterval[i] << '\n';
		for (int j = 0; j < 10; j++)
			cout << "In this interval realiazation:" << j + 1 << "occurs:  " << countIntervalRealization[i][j] << endl;
	}
}