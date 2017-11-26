#include <iostream>
#include<stdio.h>
using namespace std;



//用数组练习几种排序方法


int main()
{
	int size = 10;
	int seq[10] = {};
	for (int i=0;i<size;i++)
	{
		seq[i] = rand();
		cout << seq[i]<<" ";
	}
	for (int i = 0; i<size; i++)
	{
		int key =seq[i];
	      int j = i - 1;
		while (j >= 0 && seq[j]>key)
		{
			seq[j + 1] = seq[j];
		    j--;
		}
		seq[j + 1] = key;
	}

	cout <<endl;

	for (int i = 0; i<size; i++)
	{
		cout << seq[i] << " ";
	}


	//冒泡排序
	//int size = 10;
	//int seq[10] = {};
	cout << endl;
	for (int i = 0; i<size; i++)
	{
		seq[i] = rand();
		cout << seq[i] << " ";
	}
	for (int i = 1; i<size; i++)
	{
		for (int j=0;j<size-1-i;j++)
		{
			if (seq[j+1]>seq[j])
			{
				int c = seq[j];
				seq[j] = seq[j +1];
				seq[j + 1] = c;
			}
		}
	}

	cout << endl;

	for (int i = 0; i<size; i++)
	{
		cout << seq[i] << " ";
	}

	//选择排序
	//int size = 10;
	//int seq[10] = {};
	cout << endl;
	for (int i = 0; i<size; i++)
	{
		seq[i] = rand();
		cout << seq[i] << " ";
	}
	for (int i = 0; i<size; i++)
	{
		int min = seq[i];
		for (int j=i+1;j<size;j++)
		{
			if (seq[j]<min)
			{
				min = seq[j];
				seq[j] = seq[i];
				seq[i] = min;
			}
		}
	}

	cout << endl;

	for (int i = 0; i<size; i++)
	{
		cout << seq[i] << " ";
	}



	//希尔排序法(递减增量排序)    先分组，再直接插入排序
	//int size = 10;
	//int seq[10] = {};
	cout << endl;


	int h = 1;
	while (h<size)
	{
		h *= 2;
	}
	//初始增量
	while (h>=1)
	{
		for (int i=h;i<size;i++)
		{
			int j = i - h;
			int key = seq[i];
			while (j >= 0 && seq[j]>key)
			{
				seq[j + 1] = seq[j];
				j=j-h;
			}
			seq[j + h] = key;
		}
		h /= 2;
	}

	cout << endl;

	for (int i = 0; i<size; i++)
	{
		cout << seq[i] << " ";
	}

	getchar();
	return 0;
}
