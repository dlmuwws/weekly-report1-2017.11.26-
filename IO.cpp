#include"IO.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#define inpath "C:\Users\wws199633\Desktop"
using namespace std;

IO::IO()
{

}


void IO::input(int order_num, int item_num)
{
	vector<int>orders;
	vector<int>items;
	vector<int>quantity;
	vector<int>EQs;
	vector<int>IQs;
	vector<int>ENs;
	vector<int>IKs;

	string filename="inpath"+ string("EIQ" )+ string(".scv");
	ifstream file(filename.c_str());

	string buf;
	char *temp;
	char *token;

	while (getline(file, buf))
	{

		token = strtok_s((char*)buf.c_str(), ",", &temp);
		items.push_back(atoi(token));


		token = strtok_s(NULL, ",", &temp);
		orders.push_back(atoi(token));

		token = strtok_s(NULL, ",", &temp);
		quantity.push_back(atoi(token));

		//test
	//	cout << items[300]<< endl;
		cout << "finish the data input" << endl;
		//getchar();
	}
	file.close();
	int size = orders.size();
	int k = -1;
	for (int j = 0; j<order_num; j++)
	{
		int m = 0;
		for (int i = k + 1; i<size; i++)
		{
			if (orders[i] = j + 1)
			{
				k++;
				EQs[j] += quantity[i];
				m++;
			}
		}
		ENs[j] = m;
	}
	cout << "get the EQs" << "and" << "get the ENs" << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <size - 1 - i; j++)
		{
			if (items[j + 1] > items[j])
			{
				int c = items[j];
				items[j] = items[j + 1];
				items[j + 1] = c;
			}
		}
	}
	k = -1;
	for (int j = 0; j<item_num; j++)
	{
		int m = 0;
		for (int i = k + 1; i<size; i++)
		{
			if (items[i] = j + 1)
			{
				k++;
				IQs[j] += quantity[i];
				m++;
			}
		}
		IKs[j] = m;
	}

	cout << "get the IQs" << "and" << "get the IKs" << endl;

}


void IO::print()
{
	vector<int>EQs;
	vector<int>IQs;
	vector<int>ENs;
	vector<int>IKs;
	vector<int>::iterator it;
	it = EQs.begin();
	for (it; it != EQs.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	it = IQs.begin();
	for (it; it != IQs.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	it = IKs.begin();
	for (it; it != IKs.end(); it++)
	{
		cout << *it << endl;
	}
	cout << endl;
	it = ENs.begin();
	for (it; it != ENs.end(); it++)
	{
		cout << *it << endl;
	}
}
