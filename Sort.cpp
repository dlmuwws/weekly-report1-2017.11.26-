#include"Sort.h"
#include<iostream>
#include<string>
#define MaxSize 100
#define Nokey -1
typedef int keytype;//above 3 lines are for hashtable, havent finish yet
using namespace std;

void display(string str,const int *arr, int size) {
	cout << str << endl;
	for (int i = 0; i < size; ++i)
		cout << arr[i] << '\t';
	cout << endl;
}

void Insertionsort(int *arr,int size) {
	for (int i = 1; i < size; ++i)
		Insert(arr, i, arr[i]);
}

void Insert(int*arr, int pos, int val) {
	int i(pos - 1);
	while (i >= 0 && arr[i] > val) {
		arr[i + 1] = arr[i];
		i--;
	}
	arr[i + 1] = val;
}

typedef struct {
	keytype key;
	int count;
}HashData;
typedef  HashData HashTable[MaxSize];

void InsertHT(HashTable ha, int &n, keytype k, int p)  
{
	int i, adr;
	adr = k % p;
	if (ha[adr].key == Nokey )    
	{
		ha[adr].key = k;
		ha[adr].count = 1;
	}
	else                  
	{
		i = 1;                
		do
		{
			adr = (adr + 1) % p;  
			i++;
		} while (ha[adr].key != Nokey );
		ha[adr].key = k;
		ha[adr].count = i;
	}
	n++;
}

void CreateHT(HashTable ha, keytype x[], int n, int m, int p)  
{
	int i, n1 = 0;
	for (i = 0; i<m; i++)         
	{
		ha[i].key = Nokey;
		ha[i].count = 0;
	}
	for (i = 0; i<n; i++)
		InsertHT(ha, n1, x[i], p);
}