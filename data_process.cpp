#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include"point.h"
using namespace std;
#define TXTPATH1 "D:/data/model3_day1-5/"
#define TXTPATH2 "D:/data/单天单模型紧凑-day1-5/"
int  total = 230708;
static int s = 5;


//bool cmp(point* &a, point* &b);
//void readfile1();
void readfile2();
void readfile3();
void init();
vector<point*> selectpoint(vector<point*>point_list);
bool exist(int x, int y, vector<point*>point_list);
point*getpoint(int x, int y, vector<point*>point_list);
vector<point*> point_list_;
vector<point*>new_point_list;
//typedef vector<double>point_hour_speed;
vector<vector<double>>allpoint_hour_speed;

int main()
{
	//cout << "start" << endl;
	for (int i = 0; i<total; i++)
	{
		allpoint_hour_speed.push_back({ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 });
	}
	//cout << "read_file1!!!" << endl;
	//readfile1();
	//cout << point_list_.size() << endl;
	//cout << point_list_[3]->getX() << "," << point_list_[3]->getY() << "," << point_list_[3]->gethour() << "," << point_list_[3]->getspeed() << "," << point_list_[3]->getloc() << "," << point_list_[3]->getmeasure() << endl;
	cout << "read_file2!!!" << endl;
	readfile2();
	new_point_list = selectpoint(point_list_);
	cout << "read_file3!!!" << endl;
	readfile3();
	cout << "output the picked data" << endl;
	init();
	cout << new_point_list.size() << endl;
	system("pause");
	return 0;
}

//void readfile1()
//{
	//string filename1 = TXTPATH1 + string("day1model3.csv");
	//ifstream infile1(filename1.c_str());

	//string buf;
	//char*token;
	//char*temp;
	//int x;
	//int y;
	//int hour=0;
	//double speed=0;
	//int acc;
	//int loc;
	//double measure = 0;
	//int i = 0;
	//while (getline(infile1,buf))
	//{
		//token = strtok_s((char*)buf.c_str(), ",", &temp);
	//	x = atoi(token);
	//	token = strtok_s(NULL, ",", &temp);
	//	y = atoi(token);
		//token = strtok_s(NULL, ",", &temp);
		//token = strtok_s(NULL, ",", &temp);
	//	token = strtok_s(NULL, ",", &temp);
		//acc= atoi(token);
	//	token = strtok_s(NULL, ",", &temp);
		//loc = atoi(token);
		//token = strtok_s(NULL, ",", &temp);

		//point*newpoint = new point(x, y, hour, speed, loc, measure);
		//if (i > 0)
		//{
			//if (acc == 1 && (x != point_list_[i - 1]->getX() || y != point_list_[i - 1]->getY()))
		//	{
			//	point_list_.push_back(newpoint);
		//	}
		//	else
		//		continue;
		//}
		//else
		//{
		//	point_list_.push_back(newpoint);
	//	}
		//i++;
	//}

	//infile1.close();
	//sort(point_list_.begin(), point_list_.end(), cmp);
	//cout << "finish!!!" << endl;
//}

void readfile2()
{
	string filename2 = TXTPATH2 + string("compress_day1R3.csv");
	ifstream infile2(filename2.c_str());
	string buf;
	char*token;
	char*temp;
	int x;
	int y;
	int date;
	int hour = 0;
	int loc = 0;
	int acc = 0;
	double measure = 0;
	int i = 0;
	while (getline(infile2, buf))
	{
		//point_hour_speed *point_speed;
		token = strtok_s((char*)buf.c_str(), ",", &temp);
		x = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		y = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		date = atoi(token);
		token = strtok_s(NULL, ",", &temp);
	    allpoint_hour_speed[i][0]=atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][1] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][2] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][3] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][4] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][5] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][6] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][7] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][8] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][9] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][10] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][11] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][12] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][13] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][14] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][15] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][16] = atof(token);
		token = strtok_s(NULL, ",", &temp);
		allpoint_hour_speed[i][17] = atof(token);
		i++;
		point*newpoint_ = new point(x, y, hour, 0, acc, loc, measure);
		point_list_.push_back(newpoint_);
	}
		infile2.close();
		cout << "finish" << endl;
}

void readfile3()
{
	string filename1 = TXTPATH1 + string("day1model3.csv");
	ifstream infile1(filename1.c_str());

	string buf;
	char*token;
	char*temp;
	int x;
	int y;
	int hour;
	double speed;
	int acc;
	int loc;
	double measure;
	int i = 0;
	while (getline(infile1,buf))
	{
		token = strtok_s((char*)buf.c_str(), ",", &temp);
		x = atoi(token);
		token = strtok_s(NULL, ",", &temp);
	    y = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		hour = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		speed = atof(token);
		token = strtok_s(NULL, ",", &temp);
		acc = atoi(token);
		token = strtok_s(NULL, ",", &temp);
		loc = atoi(token);
		token = strtok_s(NULL, ",", &temp);
	    measure = atof(token);

		int size = new_point_list.size();
		for (int i=0;i<size;i++)
		{
			if (x == new_point_list[i]->getX() && y == new_point_list[i]->getY() && hour == new_point_list[i]->gethour())
			{
				new_point_list[i]->setmeasure(measure);
				new_point_list[i]->setacc(acc);
				new_point_list[i]->setloc(loc);
			}
		}
	}
	infile1.close();
	cout << "finish" << endl;
}

void init()
{
	ofstream outFile;
	outFile.open("process_day1model3.csv", ios::out);
	cout << "start!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	int size = new_point_list.size();

	for (int i=0;i<size;i++)
	{
		outFile << new_point_list[i]->getX() << "," << new_point_list[i]->getY() << "," << new_point_list[i]->gethour() << "," << new_point_list[i]->getspeed() << "," << new_point_list[i] ->getacc()<<","<< new_point_list[i]->getloc() << "," << new_point_list[i]->getmeasure() << endl;
	}

	cout << "finish" << endl;
	outFile.close();
}

vector<point*> selectpoint(vector<point*>point_list)
{
	cout << "start select points!!!" << endl;
	vector<point*>new_point_list;
	vector<point*>canchoosed_points;

	int size = 421;
	for (int j=0;j<total;j++ )
	{
		point_list[j]->setstate(0);
	}


	for (int z=0;z<273;z++)
	{
		int i = 421+421*2*z;
		while (i <421*2 + 421 * 2 * z)    //每次走一列
		{
			int k = 0;
			canchoosed_points.clear();
			//point_list[i]->setstate(0);
			int b = point_list[i]->getstate();
			canchoosed_points.push_back(getpoint(point_list[i]->getX(), point_list[i]->getY(), point_list));
			bool a = exist(point_list[i]->getX() - 1, point_list[i]->getY(), point_list);
			b += getpoint(point_list[i]->getX() - 1, point_list[i]->getY(), point_list)->getstate();
			if (a)
			{
				k++;
				canchoosed_points.push_back(getpoint(point_list[i]->getX() - 1, point_list[i]->getY(), point_list));
			}
			a = exist(point_list[i]->getX() + 1, point_list[i]->getY(), point_list);
			b += getpoint(point_list[i]->getX() + 1, point_list[i]->getY(), point_list)->getstate();

			if (a)
			{
				k++;
				canchoosed_points.push_back(getpoint(point_list[i]->getX() + 1, point_list[i]->getY(), point_list));
			}
			a = exist(point_list[i]->getX(), point_list[i]->getY() - 1, point_list);
			//b += getpoint(point_list[i]->getX(), point_list[i]->getY()-1, point_list)->getstate();
			//canchoosed_points.push_back(getpoint(point_list[i]->getX(), point_list[i]->getY() - 1, point_list));
			if (a)
			{
				k++;
			}
			a = exist(point_list[i]->getX(), point_list[i]->getY() + 1, point_list);
			b += getpoint(point_list[i]->getX(), point_list[i]->getY() + 1, point_list)->getstate();
			canchoosed_points.push_back(getpoint(point_list[i]->getX(), point_list[i]->getY() + 1, point_list));
			if (a)
			{
				k++;
				canchoosed_points.push_back(getpoint(point_list[i]->getX(), point_list[i]->getY() + 1, point_list));
			}
			if (k == 2 || k == 3)                  //边界点全不选
			{
				i++;
				continue;
			}
			else if (k == 4)
			{
				if (b == 0)        //从canchoosed_points里随机选一个点
				{
					int a = 0; int b = 3;
					srand((unsigned)time(NULL));
					point*choosed_point= canchoosed_points[(rand() % (b - a + 1)) + a];
					choosed_point->setstate(1);
					int c = 0; int d = 17;
					srand((unsigned)time(NULL));
					choosed_point->sethour((rand() % (d - c + 1)) + c + 1);
					int index = choosed_point->getindex();
					choosed_point->setspeed(allpoint_hour_speed[index-1][(rand() % (d - c + 1)) + c]);
					new_point_list.push_back(choosed_point);
					i += 2;
				}
				else
				{
					i += 2;
					//continue;
				}
			}
		}
	}
	return new_point_list;
}
bool exist(int x, int y, vector<point*>point_list)
{
	bool a = false;
	int size = point_list.size();
	for (int i = 0; i<size; i++)
	{
		if (point_list[i]->getX() == x&&point_list[i]->getY() == y)
		{
			a = true;
			break;
		}
	}
	return a;
}

point*getpoint(int x, int y, vector<point*>point_list)
{
	point*point_=point_list[0];
	int size = point_list.size();
	for (int i = 0; i<size; i++)
	{
		if (point_list[i]->getX() == x&&point_list[i]->getY() == y)
		{
			point_ = point_list[i];
			break;
		}
	}
	return point_;
}

bool cmp(point* &a, point* &b) {

	if (a->getX()< b->getX())
		return true;
	else if (a->getX() == b->getX())
	{
		if (a->getY() < b->getY())
			return true;
	}
	return false;
}
