#include<fstream>
#include<string>
#include<vector>
using namespace std;

#define inputpath "D:/BaiduNetdiskDownload/"
#define ftype ".csv"
#define outputpath "D:/气象数据优化大赛/1.17/"
#define wspeedlimit 15 //限制风速


pair<int, double> getMax(const vector<double> &forecast_value) {
	pair<int,double> max(0,0.0);
	for (int i = 0; i < forecast_value.size(); ++i)
	{
		if (forecast_value[i] > max.second) {
			max.second = forecast_value[i];
			max.first = i;
		}	
	}
	return max;
}

pair<int, double> getMin(const vector<double> &forecast_value) {
	pair<int, double> min(0, INT_MAX);
	for (int i = 0; i < forecast_value.size(); ++i)
	{
		if (forecast_value[i] < min.second) {
			min.second = forecast_value[i];
			min.first = i;
		}
	}
	return min;
}

double getAve(const vector<double> &forecast_value) {
	double sum(0.0);
	for (int i = 0; i < forecast_value.size(); ++i)
		sum += forecast_value[i];
	return (double)sum/forecast_value.size();
}

double getRevised_Ave(const vector<double> &forecast_value) {
	vector<double> temp = forecast_value;
	double sum(0.0);
	int min_index(0), max_index(0);
	pair<int, double> min, max;
	
	min = getMin(temp);
	max= getMax(temp);

	min_index = min.first;
	max_index = max.first;

	for (vector<double>::iterator it = temp.begin(); it != temp.end(); )
	{
		if (*it == min.second)
			it = temp.erase(it);
		else if (*it == max.second)
			it = temp.erase(it);
		else
			++it;
	}

	//temp.erase(temp.begin() + min_index );
	//temp.erase(temp.begin() + max_index );

	for (int i = 0; i < temp.size(); ++i)
		sum += temp[i];
	return (double)(sum / temp.size());
}

void Accuracy_Statistic() {
	int day(1);

	string in = string("CountVotes_");
	string i = string("reProcess");
	string explanation = string("_x_y_hour_Max_Min_Ave_RevisedAve");
	string infilename1(inputpath + i + "_day" + to_string(day) + "_R10" + ftype);
	//string infilename1(inputpath + i + ftype);
	ifstream infile1(infilename1.c_str());

	//output
	string outfilePoints1(outputpath +in+ to_string(10) + "_day" + to_string(day) +explanation+ ftype);
	ofstream outfile1(outfilePoints1.c_str(), ios_base::app);

	string outfilePoints2(outputpath + in +  to_string(9) + "_day" + to_string(day) + explanation + ftype);
	ofstream outfile2(outfilePoints2.c_str(), ios_base::app);

	string outfilePoints3(outputpath + in + to_string(8) + "_day" + to_string(day) + explanation + ftype);
	ofstream outfile3(outfilePoints3.c_str(), ios_base::app);

	string outfilePoints4(outputpath + in + to_string(7) + "_day" + to_string(day) + explanation + ftype);
	ofstream outfile4(outfilePoints4.c_str(), ios_base::app);

	string outfilePoints5(outputpath + in  + to_string(6) + "_day" + to_string(day) + explanation + ftype);
	ofstream outfile5(outfilePoints5.c_str(), ios_base::app);

	string outfilePoints6(outputpath + in + to_string(5) + "_day" + to_string(day) + explanation + ftype);
	ofstream outfile6(outfilePoints6.c_str(), ios_base::app);

	

	string buf;
	char *token;
	char *tmp;
	int x = 0;
	int y = 0;
	int date = 0;
	int hour = 0;
	double wind = 0.0;
	double fval[10];//forecast value
	

	

	while ( getline(infile1, buf)) {
		
			string bufCopy = buf;
			int count_votes(0);
			pair<int, double> min, max;
			

			token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
			x = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			y = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			//date = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			hour = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			wind = atof(token);//真实值

			token = strtok_s(NULL, ",", &tmp);
			fval[0] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[1] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[2] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[3] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[4] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[5] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[6] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[7] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[8] = atof(token);
			token = strtok_s(NULL, ",", &tmp);
			fval[9] = atof(token);

			if (wind >wspeedlimit) {
				vector<double> fv;
				for (int i = 0; i < 10; ++i) {
					fv.push_back(fval[i]);
					if (fval[i] < wspeedlimit) {
						count_votes++;
						//fv.push_back(fval[i]);
					}
				}

				min = getMin(fv);
				max = getMax(fv);

				if (count_votes == 10)
					outfile1 <<x << "," << y << "," <<hour<<","<< max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv)<<'\n';
				if (count_votes == 9)
					outfile2 << x << "," << y << "," << hour << "," << max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv) << '\n';
				if (count_votes == 8)
					outfile3 << x << "," << y << "," << hour << "," << max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv) << '\n';
				if (count_votes == 7)
					outfile4 << x << "," << y << "," << hour << "," << max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv) << '\n';
				if (count_votes == 6)
					outfile5 << x << "," << y << "," << hour << "," << max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv) << '\n';
				if (count_votes == 5)
					outfile6 << x << "," << y << "," << hour << "," << max.second << "," << min.second << "," << getAve(fv) << "," << getRevised_Ave(fv) << '\n';
				
			}


			
			/*else
				continue;*/			
		}
	
	infile1.close();
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	outfile6.close();


}