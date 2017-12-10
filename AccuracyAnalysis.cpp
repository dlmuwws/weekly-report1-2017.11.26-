#include<vector>
#include<fstream>
#include<string>
using namespace std;

#define inputpath "D:/BaiduNetdiskDownload/"
#define outputpath  "D:/气象数据优化大赛/"
#define ftype ".csv"

#define countline 18
#define accuracy 1
#define wspeedlimit 15

struct record {
	int x, y,day;
	//double wind;
	//double fval[10];
	double model_accuracy[10];
};

void PlusAccuracy() {
	vector<record>* allpoints;
	
	//input
	int day(5);
	string in = string("reProcess");
	string infilename1(inputpath + in + "_day" + to_string(day) + "_R10" + ftype);
	ifstream infile1(infilename1.c_str());

	string buf;
	char *token;
	char *tmp;
	int countmodel[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int x_temp = 0;
	int y_temp = 0;
	int date = 0;
	int hour = 0;
	double wind_temp = 0.0;
	double fval_temp[10];//forecast value

	int i(0);
	int countmodel[10] = { 0,0,0,0,0,0,0,0,0,0 };
	double arate[10] = { 0,0,0,0,0,0,0,0,0,0 };

	while (getline(infile1, buf)) {
		if(i==(countline-1)){
			string bufCopy = buf;
			token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
			x_temp = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			y_temp = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			date = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			//hour = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			wind_temp = atof(token);//真实值

			token = strtok_s(NULL, ",", &tmp);
			fval_temp[0] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[1] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[2] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[3] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[4] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[5] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[6] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[7] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[8] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[9] = atof(token);

			if ((wind_temp < wspeedlimit&& fval_temp[0] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[0] >= wspeedlimit))
				countmodel[0]++;
			if ((wind_temp < wspeedlimit&& fval_temp[1] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[1] >= wspeedlimit))
				countmodel[1]++;
			if ((wind_temp < wspeedlimit&& fval_temp[2] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[2] >= wspeedlimit))
				countmodel[2]++;
			if ((wind_temp < wspeedlimit&& fval_temp[3] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[3] >= wspeedlimit))
				countmodel[3]++;
			if ((wind_temp < wspeedlimit&& fval_temp[4] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[4] >= wspeedlimit))
				countmodel[4]++;
			if ((wind_temp < wspeedlimit&& fval_temp[5] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[5] >= wspeedlimit))
				countmodel[5]++;
			if ((wind_temp < wspeedlimit&& fval_temp[6] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[6] >= wspeedlimit))
				countmodel[6]++;
			if ((wind_temp < wspeedlimit&& fval_temp[7] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[7] >= wspeedlimit))
				countmodel[7]++;
			if ((wind_temp < wspeedlimit&& fval_temp[8] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[8] >= wspeedlimit))
				countmodel[8]++;
			if ((wind_temp < wspeedlimit&& fval_temp[9] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[9] >= wspeedlimit))
				countmodel[9]++;

			//最后一行数据读完后判断+输出
			for (int i = 0; i < 10; ++i) {
				arate[i] = countmodel[i] / countline;
				countmodel[i] = 0;//初始化
			}

			record cur{ x_temp,y_temp,date,{arate[0],arate[1], arate[2], arate[3], arate[4], arate[5], arate[6], arate[7], arate[8], arate[9]} };
			allpoints->push_back(cur);

			i = 0;

			continue;


		}
		else {
			string bufCopy = buf;
			token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
			x_temp = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			y_temp = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			date = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			hour = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			wind_temp = atof(token);//真实值

			token = strtok_s(NULL, ",", &tmp);
			fval_temp[0] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[1] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[2] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[3] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[4] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[5] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[6] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[7] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[8] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval_temp[9] = atof(token);

			if ((wind_temp < wspeedlimit&& fval_temp[0] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[0] >= wspeedlimit))
				countmodel[0]++;
			if ((wind_temp < wspeedlimit&& fval_temp[1] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[1] >= wspeedlimit))
				countmodel[1]++;
			if ((wind_temp < wspeedlimit&& fval_temp[2] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[2] >= wspeedlimit))
				countmodel[2]++;
			if ((wind_temp < wspeedlimit&& fval_temp[3] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[3] >= wspeedlimit))
				countmodel[3]++;
			if ((wind_temp < wspeedlimit&& fval_temp[4] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[4] >= wspeedlimit))
				countmodel[4]++;
			if ((wind_temp < wspeedlimit&& fval_temp[5] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[5] >= wspeedlimit))
				countmodel[5]++;
			if ((wind_temp < wspeedlimit&& fval_temp[6] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[6] >= wspeedlimit))
				countmodel[6]++;
			if ((wind_temp < wspeedlimit&& fval_temp[7] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[7] >= wspeedlimit))
				countmodel[7]++;
			if ((wind_temp < wspeedlimit&& fval_temp[8] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[8] >= wspeedlimit))
				countmodel[8]++;
			if ((wind_temp < wspeedlimit&& fval_temp[9] < wspeedlimit) || (wind_temp >= wspeedlimit&& fval_temp[9] >= wspeedlimit))
				countmodel[9]++;

			i++;


		}

	}

	infile1.close();

}

/*void quickSort(vector<record>* points) {
	int i = (points.front()->x), j = (points.end()->x);
	int tmp;
	int pivot = arr[(left + right) / 2];

	//partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	//recursion
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}
*/