// C++practise.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
using namespace std;
#include"currency.h"

template <class T>
void make2dArray(T **&x, int numberOfRows, int numberOfColumns);


template <class T>
void make2dArray(T **&x, int numberOfRows, int numberOfColumns) {


		x = new T*[numberOfRows];
		for (int i = 0; i < numberOfRows; i++) {
			x[i] = new int[numberOfColumns];
	
		}

}
template <class T>
void make2dArray1(T **&x, int numberOfRows, int rowSize[]) {
	x = new T*[numberOfRows];
	for (int i = 0; i < numberOfRows; i++) {
		x[i] = new int[rowSize[i]];
	}
}
template <class T>
void delete2dArray(T**&x, int numberOfRows) {
	for (int i = 0; i < numberOfRows; i++) {
		delete[]x[i];
	}
	delete[]x;
	x = NULL;
}
int min(int a, int b) {
	if (a > b)
		return b;
	else
	{
		return a;
	}
}
template <class T>
void changeLength1d(T* &arr, int oldLength, int newLength) {

	int *newarr=new int[newLength];
	int num = min(oldLength, newLength);
	for (int i = 0; i < num; i++) {
		newarr[i] = arr[i];
	}
	delete[] arr;
	arr = newarr;
}

int main()
{	
	int **a,**b;
	try {
		int arr[] = { 1,2 };
		make2dArray(a, 2, 2);
		make2dArray1(b, 2, arr);

		a[0][0] = 1;
		a[0][1] = 2;
		a[1][0] = 3;
		a[1][1] = 4;

		b[0][0] = 1;
		b[1][0] = 3;
		b[1][1] = 4;

	}
	catch (bad_alloc)
	{
		cerr << "Could not create x" << endl;
		exit(1);
	}
	cout << a[0][0] << ' ' << a[0][1] << endl;
	cout << a[0][0] << ' ' << a[1][1] << endl;
	cout << b[0][0] << endl;
	cout << b[0][0] << ' ' << b[1][1] << endl;
	delete2dArray(a, 2);
	delete2dArray(b, 2);
	cout << "the array is deleted" << endl;
	
	int *arr;
	arr = new int[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = i + 1;
	}
	for (int i = 0; i < 5; i++) {
		cout << arr[i] << " ";
		
	}
	cout << endl;
	changeLength1d(arr, 5, 8);
	arr[5] = 7;
	for (int i = 0; i < 6; i++) {
		cout << arr[i] << " ";

	}
	cout << endl;

	currency g, h(signType::plus, 3, 50), i, j;
	g.setValue(signType::minus, 2, 25);
	i.setValue(-6.45);
	j = h+g;
	cout << h << "+" << g << "=" << j << endl;
    
	j = i + g + h;
	cout << i << "+" << g << "+" << h << "=" << j << endl;
	cout << "Increment" << i << "by" << g << "and then add " << h << endl;
	j = (i += g) + h;
	cout << "result is " << j << endl;
	cout << "Incremented object is " << i << endl;

	cout << "Attempting to init with cents = 152" << endl;
	try {
		i.setValue(signType::plus, 3, 152);
	}
	catch (illegalParameterValue e) {
		cout << "Cauhght thrown exception" << endl;
		e.outputmessage();
		system("pause"); 
		return 1;
	}
	system("pause");
    return 0;
}
