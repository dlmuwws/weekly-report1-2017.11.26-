#include<stdio.h>
#include<iostream>
using namespace std;


void count(int i, int n)
{
	std::cout << i << " ";
	if (i < n)
	{
		count(i + 1, n);
		std::cout << i << " ";
	}
}

int main()
{
	int n = 9;
	for (int i = 1; i <= n; i++)
	{
		for (int j = n; j > i; j--)
		{
			std::cout << " ";
			count(1, i);
			std::cout << std::endl;
		}
	}
	return 0;
}

//the result is not all right. need to improve.
