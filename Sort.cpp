// Sort.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<algorithm>
#include<iostream>
using namespace std;


template<class T>
void rearrange(T a[], int n, int r[]) {
	T* u = new T[n];
	for (int i = 0; i < n; i++) {
		u[r[i]] = a[i];
	}
	for (int i = 0; i < n; i++) {
		a[i] = u[i];
	}
}

template<class T>
void Ranksort(T a[], int n, int r[]) {
	for (int i = 0; i < n; i++) {
		r[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] <= a[i])
				r[i]++;
			else
				r[j]++;
		}
	}
}
template<class T>
int IndexOfMax(T a[],int n){
	int IndexOfMax = 0;
	for (int i = 0; i < n; i++) {
			if (a[i] > a[IndexOfMax])
				IndexOfMax = i;
	}
	return IndexOfMax;
}
template <class T>
void selectionSort(T a[], int n) {

	for (int size = n;n > 1; n--) {
		int i = IndexOfMax(a, n);
		swap(a[i], a[size - 1]);
	}
}
template<class T>
int bubble(T a[], int n) {
	bool swapped = false;
	for (int i = 0; i < n - 1; i++) {
		if (a[i] > a[i + 1])
			swap(a[i], a[i + 1]);
		swapped = true;
	}
	return swapped;
}
template<class T>
void bubblesort(T a[],int n){
	for (int i = n; i > 1 && bubble(a, i); i--)
		;
}

template <class T>
void insert(T a[],int n,const T & x){
	int i;
	for ( i = n -1; i >= 0 && x<a[i]; i--) {
		a[i + 1] = a[i];
	}
	a[i+1] = x;
	
}
template<class T>
void insertsort(T a[], int n) {
	for (int i = 1; i < n; i++) {
		T t = a[i];
		insert(a, i,t );
	}
}
int main()
{
	int a[6] = { 2, 6, 4, 3, 1, 5 };
	int r[6];

	
	cout << "a[0:5] = ";
	for (int i = 0; i < 6; i++) {
		cout << a[i]<<" ";
	}
	cout << endl;
	int select;
	cin >> select;
	switch (select)
	{
	case 1:
		Ranksort(a, 6, r);
		rearrange(a, 6, r);
	case 2:
		selectionSort(a, 6);
	case 3:
		bubblesort(a, 6);
	case 4:
		insertsort(a, 6);
	}

	cout << "After the sort, a[0:5] = ";
	for (int i = 0; i < 6; i++) {
		cout << a[i]<<" ";
	}
	cout << endl;
	system("pause");
	return 0;
}

