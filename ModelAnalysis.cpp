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

void ALLModelAnalysis() {

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_ALLdays"+ ftype);
	ifstream infile(infilename.c_str());

	//output

	string outfilelarger1(outputpath + in + "_ALLday" + "_Model" + to_string(1) + "larger" + ftype);
	ofstream outfile1(outfilelarger1.c_str(),ios_base::app);

	string outfilelarger2(outputpath + in + "_ALLday" + "_Model" + to_string(2) + "larger" + ftype);
	ofstream outfile2(outfilelarger2.c_str(), ios_base::app);

	string outfilelarger3(outputpath + in + "_ALLday" + "_Model" + to_string(3) + "larger" + ftype);
	ofstream outfile3(outfilelarger3.c_str(), ios_base::app);

	string outfilelarger4(outputpath + in + "_ALLday" + "_Model" + to_string(4) + "larger" + ftype);
	ofstream outfile4(outfilelarger4.c_str(), ios_base::app);

	string outfilelarger5(outputpath + in + "_ALLday" + "_Model" + to_string(5) + "larger" + ftype);
	ofstream outfile5(outfilelarger5.c_str(), ios_base::app);

	string outfilelarger6(outputpath + in + "_ALLday" + "_Model" + to_string(6) + "larger" + ftype);
	ofstream outfile6(outfilelarger6.c_str(), ios_base::app);

	string outfilelarger7(outputpath + in + "_ALLday" + "_Model" + to_string(7) + "larger" + ftype);
	ofstream outfile7(outfilelarger7.c_str(), ios_base::app);

	string outfilelarger8(outputpath + in + "_ALLday" + "_Model" + to_string(8) + "larger" + ftype);
	ofstream outfile8(outfilelarger8.c_str(), ios_base::app);

	string outfilelarger9(outputpath + in + "_ALLday" + "_Model" + to_string(9) + "larger" + ftype);
	ofstream outfile9(outfilelarger9.c_str(), ios_base::app);

	string outfilelarger10(outputpath + in + "_ALLday" + "_Model" + to_string(10) + "larger" + ftype);
	ofstream outfile10(outfilelarger10.c_str(), ios_base::app);



	string buf;
	char *token;
	char *tmp;
	int countlarger[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int countmodelless[10] = { 0,0,0,0,0,0,0,0,0,0 };

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

		if (rea[0] < wspeedlimit) {
			countmodelless[0]++;
			if (wind > wspeedlimit) {
				outfile1 << rea[0] << '\n';
				countlarger[0]++;
			}
		}
		if (rea[1] < wspeedlimit) {
			countmodelless[1]++;
			if (wind > wspeedlimit) {
				outfile2 << rea[1] << '\n';
				countlarger[1]++;
			}
		}
		if (rea[2] < wspeedlimit) {
			countmodelless[2]++;
			if (wind > wspeedlimit) {
				outfile3 << rea[2] << '\n';
				countlarger[2]++;
			}
		}
		if (rea[3] < wspeedlimit) {
			countmodelless[3]++;
			if (wind > wspeedlimit) {
				outfile4 << rea[3] << '\n';
				countlarger[3]++;
			}
		}
		if (rea[4] < wspeedlimit) {
			countmodelless[4]++;
			if (wind > wspeedlimit) {
				outfile5 << rea[4] << '\n';
				countlarger[4]++;
			}
		}
		if (rea[5] < wspeedlimit) {
			countmodelless[5]++;
			if (wind > wspeedlimit) {
				outfile6 << rea[5] << '\n';
				countlarger[5]++;
			}
		}
		if (rea[6] < wspeedlimit) {
			countmodelless[6]++;
			if (wind > wspeedlimit) {
				outfile7 << rea[6] << '\n';
				countlarger[6]++;
			}
		}
		if (rea[7] < wspeedlimit) {
			countmodelless[7]++;
			if (wind > wspeedlimit) {
				outfile8 << rea[7] << '\n';
				countlarger[7]++;
			}
		}
		if (rea[8] < wspeedlimit) {
			countmodelless[8]++;
			if (wind > wspeedlimit) {
				outfile9<< rea[8] << '\n';
				countlarger[8]++;
			}
		}
		if (rea[9] < wspeedlimit) {
			countmodelless[9]++;
			if (wind > wspeedlimit) {
				outfile10 << rea[9] << '\n';
				countlarger[9]++;
			}
		}
		
	}
	infile.close();
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	outfile6.close();
	outfile7.close();
	outfile8.close();
	outfile9.close();
	outfile10.close();

	for (int i = 0; i < 10; ++i)
		cout << "Model  :  " << i << "   count feasible  " << countmodelless[i] << "but actually infeasible  " << countlarger[i] << '\n';
}



void ModelAnalysis() {
	int day(5);
	int model(2);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "_R10" + ftype);
	ifstream infile(infilename.c_str());
	//output
	//string outfileless(outputpath + in + "_day" + to_string(day) + "less" + ftype);
	//ofstream outfile1(outfileless.c_str());//输出小于15的真值对应的最大预测值
	string outfilelarger(outputpath + in + "_ALLday"  +"_Model"+to_string(model)+ "larger" + ftype);
	ofstream outfile2(outfilelarger.c_str(), ios_base::app);//输出大于15的真值对应的最小预测值


	string buf;
	char *token;
	char *tmp;
	int countless = 0, countlarger = 0, countmodelless = 0;

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

		if (rea[model - 1] < wspeedlimit) {
			countmodelless++;
			if (wind > wspeedlimit) {
				outfile2 << rea[model - 1] << '\n';
               countlarger++;
			}
				
		}

	/*	if (wind > wspeedlimit) {	
			if (rea[model - 1] < wspeedlimit) { 
				outfile2 << wind << "," << rea[model - 1] << '\n'; 
				countless++;
			}
			else if (rea[model-1] > wspeedlimit)
				countlarger++;
		}
		*/
		

	}
	infile.close();
	//outfile2.close();
	//cout << "The Number of countlarger is " << countlarger << endl;
	//cout << "The Number of countless is " << countless << endl;
	cout << "Model " << model << " count feasible as : " << countmodelless << endl;
	cout << "Model" << model << "  where real value greater than limit occurs:  " << countlarger << endl;
}

void mergeFileDays() {

	int day(5);

	//input
	string in = string("reProcess");
	string infilename(inputpath + in + "_day" + to_string(day) + "_R10" + ftype);
	ifstream infile(infilename.c_str());
	//output
	string outfilealldays(outputpath + in + "_ALLdays"+ ftype);
	ofstream outfile2(outfilealldays.c_str(), ios_base::app);


	string buf;
	
	while (getline(infile, buf))
	{
		outfile2 << buf << '\n';
	}
	infile.close();
	outfile2.close();

}