#pragma once
#include <string>
using namespace std;

class customer
{
private:
	int cster_age;
	string cster_name;
public:
	customer(string name, int age);
	void print();
};
