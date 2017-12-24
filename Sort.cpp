#include"Sort.h"
#include<iostream>
#include<string>
#include<vector>
#define MaxSize 100
#define Nokey -1
typedef int keytype;
using namespace std;

inline bool is_size_ok(int num) {
	if (num < 0 || num>1024)
		return false;
	else
		return true;
}

const vector<int> *getElements(int pos) {
	static vector<int> pe;
	if (!is_size_ok(pos)) {
		cerr << "Invalid Size!" << endl;
		return 0;
	}
	int temp = 0;
	if (pe.size() < pos) {
		for (int i = pe.size(); i < pos; ++i) {
			int temp = i*(3 * i - 1) / 2;
			pe.push_back(temp);
			cout << "计算了 " << i << " 次" << endl;
		}
		return &pe;
	}
	else {
		cout << "直接得出" << endl;
		return &pe;
	}
}

template<typename type>
type max(type *v, int size) {
	type max = v[0];
	for (int i = 1; i < size; ++i) {
		if (v[i] > max)
			max = v[i];
	}
	return max;
}


int partition(vector<int>& array, int low, int high)
 {
	    int pivot_value = array[low];
        while (low < high)
	    {
	        while (low<high && array[high] >= pivot_value)
		        --high;
	        swap(array[low], array[high]);
	        while (low<high && array[low] <= pivot_value)
	            ++low;
	         swap(array[low], array[high]);
         }
        return low;
 }

void Qsort(vector<int>& array, int low, int high)
 {
	     int pivot_index;
	     if (low < high)
	    {
		    pivot_index = partition(array, low, high);
	        Qsort(array, low, pivot_index - 1);
	        Qsort(array, pivot_index + 1, high);
	    }
 }



void display(string str,const int *arr, int size) {
	cout << str << endl;
	for (int i = 0; i < size; ++i)
		cout << arr[i] << '\t';
	cout << endl;
}


void ShellInsertSort(int a[], int n, int step)
{
	for (int i = step; i<n; ++i) {
		if (a[i] < a[i - step]) {          
			int j = i - step;
			int x = a[i];          
			a[i] = a[i - step];        
			while (x < a[j]) {   
				a[j + step] = a[j];
				j -= step;            
			}
			a[j + step] = x;        
		}
	}

}

void shellSort(int a[], int n) {

	int step = n / 2;
	while (step >= 1) {
		ShellInsertSort(a, n, step);
		step = step / 2;
	}
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

