#include <iostream>  
#include <algorithm>  
#include <vector> 
#include"Util.h"
using namespace std;

int cnt = 0;
void Perm(int list[], int k, int m) {
	if (k == m) {
		cnt++;
		cout << "cnt = " << cnt << endl;
		for (int i = 0; i <= m; i++) {
			cout << list[i] << "  ";
		}
		cout << endl;
	}
	else {
		for (int i = k; i <= m; i++) {
			swap(list[k], list[i]);
			Perm(list, k + 1, m);//递归回溯，调用自己
			swap(list[k], list[i]);
		}
	}

}

void Perm_iterative(int list[], int n) {
	int t = 0;
	vector<int> p = { -1,-1,-1,-1,-1 };

	while (t >= 0) {
		int k = p[t];
		while (find(p.begin(), p.end(), k) != p.end())  k++;

		if (k > n || t > n) {  
			for (int i = t; i <= n; ++i)  p[i] = -1;
			t--;
			continue;
		}
		p[t] = k;
		if (t >= n) {  
			cnt++;
			cout << "cnt = " << cnt << endl;
			for (int i = 0; i <= n; i++) {
				cout << list[p[i]] << "  ";
			}
			cout << endl;
		}
		else {
			 
			t++;
		}
	}
	return;
}

int main() {
	//int x[] = { 1,2,3,4,5 };
	//cout << " test " << endl;
	//Perm(x,0,4);  
	//Perm_iterative(x, 4);
	int li[] = { 1,2,3,4 };
	bool v[] = { false,false,false,false };
	getSubset(li, v, 0, 4);
	getSubset_iterative(li, 3);
}



void getSubset(int list[], bool v[], int a, int b) {
	if (a == b) {
		for (int i = 0; i < b; i++) {
			if (v[i])
				cout << list[i] << "  ";
		}
		cout << endl;
		return;
	}
	v[a] = true;
	getSubset(list, v, a + 1, b);
	v[a] = false;
	getSubset(list, v, a + 1, b);

}


void getSubset_iterative(int list[], int n) {
	int t = 0;
	bool v[n + 1] = { false,false,false,false };
	int init[n + 1] = { 0,0 };
	while (t >= 0) {
		if (2 > init[t]) {
			init[t]++;
			v[t] = !v[t];
			if (t >= n) {
				for (int i = 0; i <= n; i++) {
					if (v[i])  cout << list[i] << "  ";
				}
				cout << endl;
			}
			else {
				++t;//向下一层  
			}
		}
		else {
			  
			init[t] = 0;
			--t;
		}
	}

}
