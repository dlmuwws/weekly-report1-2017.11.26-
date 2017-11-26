#include<stdio.h>
#include<iostream>
using namespace std;

//递归求阶乘

int factorial(int n)
{
	if (n > 0)
	{
		if (n == 0 || n == 1)
			return 1;
		else
			return n*factorial(n - 1);
	}
}
