#include<vector>
#include<fstream>
#include<string>
#include"Util.h"
using namespace std;

#define inputpath "D:/BaiduNetdiskDownload/"
#define ftype ".csv"


vector<WareHouse>* InputWH() {
	vector<WareHouse>* allwh;


	//input
	string in = string("WareHouse");
	string infilename1(inputpath + in + ftype);
	ifstream infile1(infilename1.c_str());

	string buf;
	char *token;
	char *tmp;
	int x_temp = 0;
	int y_temp = 0;
	int dem = 0;
	int n = 0;
	bool ne(false);
	double sf = 0.0;
	double mf = 0.0;
	double lof = 0.0;

	while (getline(infile1, buf)) {

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		x_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		y_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		dem = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		n = atoi(token);
		if (n == 1)
			ne = true;
		else
			ne = false;


		token = strtok_s(NULL, ",", &tmp);
		sf = atof(token);

		token = strtok_s(NULL, ",", &tmp);
		mf = atof(token);

		token = strtok_s(NULL, ",", &tmp);
		lof = atof(token);



		WareHouse cur{ x_temp,y_temp };
		cur.setD(dem);
		cur.setMf(mf);
		cur.setSf(sf);
		cur.setlocalf(lof);
		cur.setnew(ne);
		allwh->push_back(cur);

		infile1.close();

	}
	return allwh;
}

vector<Factory>* InputFac() {
	vector<Factory>*allfc;


	//input
	string in = string("Factory");
	string infilename1(inputpath + in + ftype);
	ifstream infile1(infilename1.c_str());

	string buf;
	char *token;
	char *tmp;
	int x_temp = 0;
	int y_temp = 0;
	int pro = 0, dem = 0;
	int n = 0;
	bool ne(false);
	double sf = 0.0, prof = 0.0;
	double mf = 0.0, slim = 0.0;

	while (getline(infile1, buf)) {

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		x_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		y_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		dem = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		pro = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		n = atoi(token);
		if (n == 1)
			ne = true;
		else
			ne = false;

		token = strtok_s(NULL, ",", &tmp);
		prof = atof(token);

		token = strtok_s(NULL, ",", &tmp);
		sf = atof(token);

		token = strtok_s(NULL, ",", &tmp);
		mf = atof(token);

		token = strtok_s(NULL, ",", &tmp);
		slim = atof(token);



		Factory cur{ x_temp,y_temp };
		cur.setP(pro);
		cur.setD(dem);
		cur.setPf(prof);
		cur.setMf(mf);
		cur.setSf(sf);
		cur.setnew(ne);
		cur.setlim(slim);
		allfc->push_back(cur);

		infile1.close();

	}
	return allfc;
}

vector<Customer>* InputCus() {
	vector<Customer>* allcus;


	//input
	string in = string("Cutomer");
	string infilename1(inputpath + in + ftype);
	ifstream infile1(infilename1.c_str());

	string buf;
	char *token;
	char *tmp;
	int x_temp = 0;
	int y_temp = 0;
	int dem = 0;

	while (getline(infile1, buf)) {

		string bufCopy = buf;
		token = strtok_s((char *)bufCopy.c_str(), ",", &tmp);
		x_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		y_temp = atoi(token);

		token = strtok_s(NULL, ",", &tmp);
		dem = atoi(token);



		Customer cur{ x_temp,y_temp };
		cur.setD(dem);
		allcus->push_back(cur);

		infile1.close();

	}
	return allcus;
}

		