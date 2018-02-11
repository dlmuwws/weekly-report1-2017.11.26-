// Recursive.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include <algorithm>
#include<iterator>
using namespace std;

int factorial(int n) {
	if (n <= 1)
		return 1;
	else
		return n*factorial(n - 1);
}
template<class T>
T rSum(T a[], int n) {
	if (n > 0)
		return rSum(a, n - 1) + a[n-1];
	else
	{
		return 0;
	}
}

template <class T>
void permutations(T list[], int k, int m) {
	if (k == m)
	{
		copy(list, list + m + 1, ostream_iterator<T>(cout, ""));
		cout << endl;
	}
	else {
		for (int i = k; i < m; i++) {
			swap(list[k], list[i]);
			permutations(list, k + 1, m);
			swap(list[k], list[i]);
		}
	}
}
int Fibonacci(int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
	{
		return 1;
	}
	else
		return Fibonacci(n - 1) + Fibonacci(n - 2);
}
int Fibonacci1(int n) {
	int first=0;
	int second =1;
	int fn=0;
	
	while(n>1){
		n = n - 1;
		fn = first + second;
		first = second;
		second = fn;
	}
	return fn;
}
int func1_4(int n) {
	if (n % 2 == 0) {
		return n / 2;
	}
	else
	{
		return func1_4(3 * n + 1);
	}
}
int Ackermann(int i, int j) {
	if (i == 1 && j >= 1)
		return pow(2, j);
	else if (i >= 2) {
		if (j == 1)
		{
			return Ackermann(i - 1, 2);
		}
		else
		{
			int k = Ackermann(i, j - 1);
			return Ackermann(i - 1, k);
		}
	}
}
int main()
{
	cout << "5! =" << factorial(5) << endl;
	int a[4] = { 1,2,3,4 };
	int sum  = rSum(a, 4);
	cout << "the sum of a[4] = " << sum << endl;
	char b[] = { 'a','b','c','d' };
	cout << "The permutations of a are" << endl;
	permutations(b, 0, 0);

	cout << "The permutations of abc are" << endl;
	permutations(b, 0, 2);

	cout << "The permutations of abcd are" << endl;
	permutations(b, 0, 3);

	cout << "The Fibonacci Objcect is" << Fibonacci(10) <<","<< Fibonacci1(10) << endl;

	cout << "The result of practise 1-4 is:" << func1_4(5) << endl;

	cout << "The result of Ackermann is:" << Ackermann(2,2) << endl;
	system("pause");
    return 0;
}

