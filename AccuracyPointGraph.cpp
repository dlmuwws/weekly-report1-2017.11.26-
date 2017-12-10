#include<fstream>
#include<string>
using namespace std;

#define inputpath "D:/BaiduNetdiskDownload/"
#define ftype ".csv"
#define outputpath "D:/气象数据优化大赛/"
#define accuracy 1        //要求准确率
#define wspeedlimit 15 //限制风速
#define countline 18     //每天的十八小时预测或五天共九十次

void Mergefile() {
	    //把一个点5*18=90次的预测数据放在一个文件里
		//input
		string in = string("reProcess");
		string infilename1(inputpath + in + "_day" + to_string(1) + "_R10" + ftype);
		ifstream infile1(infilename1.c_str());
		
		string infilename2(inputpath + in + "_day" + to_string(2) + "_R10" + ftype);
		ifstream infile2(infilename2.c_str());

		string infilename3(inputpath + in + "_day" + to_string(3) + "_R10" + ftype);
		ifstream infile3(infilename3.c_str());

		string infilename4(inputpath + in + "_day" + to_string(4) + "_R10" + ftype);
		ifstream infile4(infilename4.c_str());
		
		string infilename5(inputpath + in + "_day" + to_string(5) + "_R10" + ftype);
		ifstream infile5(infilename5.c_str());
		
		//output
		string outfilealldays(outputpath + in + "_PointsCluster" + ftype);
		ofstream outfile2(outfilealldays.c_str(), ios_base::app);


		string buf1,buf2,buf3,buf4,buf5;

		while (getline(infile5, buf5))
		{
			if (getline(infile1, buf1))
				outfile2 << buf1 << '\n';
			if (getline(infile2, buf2))
				outfile2 << buf2<< '\n';
			if (getline(infile3, buf3))
				outfile2 << buf3 << '\n';
			if (getline(infile4, buf4))
				outfile2 << buf4 << '\n';
			outfile2 << buf5<< '\n';
		}
		infile1.close();
		infile2.close();
		infile3.close();
		infile4.close();
		infile5.close();
		outfile2.close();

	}


void GraphforAllModel() {
	//input
	//string in = string("reProcess");
	//string infilename(inputpath + in + "_day1_R10" + ftype);
	//ifstream infile(infilename.c_str());
	int day(5);

	string in = string("reProcess");
	string infilename1(inputpath + in + "_day" + to_string(day) + "_R10" + ftype);
	ifstream infile1(infilename1.c_str());

	//output
	string outfilePoints1(outputpath + in + "_Model" + to_string(1) +"_day" +to_string(day)+"_AccuratePoints" + ftype);
	ofstream outfile1(outfilePoints1.c_str(), ios_base::app);

	string outfilePoints2(outputpath + in + "_Model" + to_string(2) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile2(outfilePoints2.c_str(), ios_base::app);

	string outfilePoints3(outputpath + in + "_Model" + to_string(3) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile3(outfilePoints3.c_str(), ios_base::app);

	string outfilePoints4(outputpath + in + "_Model" + to_string(4) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile4(outfilePoints4.c_str(), ios_base::app);

	string outfilePoints5(outputpath + in + "_Model" + to_string(5) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile5(outfilePoints5.c_str(), ios_base::app);

	string outfilePoints6(outputpath + in + "_Model" + to_string(6) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile6(outfilePoints6.c_str(), ios_base::app);

	string outfilePoints7(outputpath + in + "_Model" + to_string(7) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile7(outfilePoints7.c_str(), ios_base::app);

	string outfilePoints8(outputpath + in + "_Model" + to_string(8) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile8(outfilePoints8.c_str(), ios_base::app);

	string outfilePoints9(outputpath + in + "_Model" + to_string(9) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile9(outfilePoints9.c_str(), ios_base::app);

	string outfilePoints10(outputpath + in + "_Model" + to_string(10) + "_day" + to_string(day) + "AccuratePoints" + ftype);
	ofstream outfile10(outfilePoints10.c_str(), ios_base::app);

	string buf;
	char *token;
	char *tmp;
	int countmodel[10] = { 0,0,0,0,0,0,0,0,0,0 };
	int x = 0;
	int y = 0;
	int date = 0;
	int hour = 0;
	double wind = 0.0;
	double fval[10];//forecast value

	int i(0);//控制循环
    
	while (i <= (countline-1) && getline(infile1,buf)) {
		if (i == (countline-1))
		{
			string bufCopy = buf;
			token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
			x = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			y = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			//date = atoi(token);

			token = strtok_s(NULL, ",", &tmp);
			//hour = atoi(token);

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

			if ((wind < wspeedlimit&& fval[0] < wspeedlimit) || (wind >= wspeedlimit&& fval[0] >= wspeedlimit))
				countmodel[0]++;
			if ((wind < wspeedlimit&& fval[1] < wspeedlimit) || (wind >= wspeedlimit&& fval[1] >= wspeedlimit))
				countmodel[1]++;
			if ((wind < wspeedlimit&& fval[2] < wspeedlimit) || (wind >= wspeedlimit&& fval[2] >= wspeedlimit))
				countmodel[2]++;
			if ((wind < wspeedlimit&& fval[3] < wspeedlimit) || (wind >= wspeedlimit&& fval[3] >= wspeedlimit))
				countmodel[3]++;
			if ((wind < wspeedlimit&& fval[4] < wspeedlimit) || (wind >= wspeedlimit&& fval[4] >= wspeedlimit))
				countmodel[4]++;
			if ((wind < wspeedlimit&& fval[5] < wspeedlimit) || (wind >= wspeedlimit&& fval[5] >= wspeedlimit))
				countmodel[5]++;
			if ((wind < wspeedlimit&& fval[6] < wspeedlimit) || (wind >= wspeedlimit&& fval[6] >= wspeedlimit))
				countmodel[6]++;
			if ((wind < wspeedlimit&& fval[7] < wspeedlimit) || (wind >= wspeedlimit&& fval[7] >= wspeedlimit))
				countmodel[7]++;
			if ((wind < wspeedlimit&& fval[8] < wspeedlimit) || (wind >= wspeedlimit&& fval[8] >= wspeedlimit))
				countmodel[8]++;
			if ((wind < wspeedlimit&& fval[9] < wspeedlimit) || (wind >= wspeedlimit&& fval[9] >= wspeedlimit))
				countmodel[9]++;

			if (countmodel[0]>= round(countline* accuracy))
				outfile1 << x << "," << y << '\n';
			if (countmodel[1] >= round(countline* accuracy))
				outfile2 << x << "," << y << '\n';
			if (countmodel[2] >= round(countline* accuracy))
				outfile3 << x << "," << y << '\n';
			if (countmodel[3] >= round(countline* accuracy))
				outfile4 << x << "," << y << '\n';
			if (countmodel[4] >= round(countline* accuracy))
				outfile5 << x << "," << y << '\n';
			if (countmodel[5] >= round(countline* accuracy))
				outfile6 << x << "," << y << '\n';
			if (countmodel[6] >= round(countline* accuracy))
				outfile7 << x << "," << y << '\n';
			if (countmodel[7] >= round(countline* accuracy))
				outfile8 << x << "," << y << '\n';
			if (countmodel[8] >= round(countline* accuracy))
				outfile9 << x << "," << y << '\n';
			if (countmodel[9] >= round(countline* accuracy))
				outfile10 << x << "," << y << '\n';
				

			for (int j = 0; j < 10; ++j)
				countmodel[j] = 0;
		

			i = 0;
			continue;
		}

		else {
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

			if ((wind < wspeedlimit&& fval[0] < wspeedlimit) || (wind >= wspeedlimit&& fval[0] >= wspeedlimit))
				countmodel[0]++;
			if ((wind < wspeedlimit&& fval[1] < wspeedlimit) || (wind >= wspeedlimit&& fval[1] >= wspeedlimit))
				countmodel[1]++;
			if ((wind < wspeedlimit&& fval[2] < wspeedlimit) || (wind >= wspeedlimit&& fval[2] >= wspeedlimit))
				countmodel[2]++;
			if ((wind < wspeedlimit&& fval[3] < wspeedlimit) || (wind >= wspeedlimit&& fval[3] >= wspeedlimit))
				countmodel[3]++;
			if ((wind < wspeedlimit&& fval[4] < wspeedlimit) || (wind >= wspeedlimit&& fval[4] >= wspeedlimit))
				countmodel[4]++;
			if ((wind < wspeedlimit&& fval[5] < wspeedlimit) || (wind >= wspeedlimit&& fval[5] >= wspeedlimit))
				countmodel[5]++;
			if ((wind < wspeedlimit&& fval[6] < wspeedlimit) || (wind >= wspeedlimit&& fval[6] >= wspeedlimit))
				countmodel[6]++;
			if ((wind < wspeedlimit&& fval[7] < wspeedlimit) || (wind >= wspeedlimit&& fval[7] >= wspeedlimit))
				countmodel[7]++;
			if ((wind < wspeedlimit&& fval[8] < wspeedlimit) || (wind >= wspeedlimit&& fval[8] >= wspeedlimit))
				countmodel[8]++;
			if ((wind < wspeedlimit&& fval[9] < wspeedlimit) || (wind >= wspeedlimit&& fval[9] >= wspeedlimit))
				countmodel[9]++;

			i++;
		}
	}
	infile1.close();
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

}

