#include<algorithm>
#include<iostream>
using namespace std;


pair<int,int> maxmin(int *a,int &max_,int &min_,int low,int high)        //分治求最大最小值.
{

	int mid, x1, y1, x2, y2;
	if ((high-low<=1))             //停止分解条件
	{
		if (a[high]>a[low])
		{
			max_ = a[high];
			min_ = a[low];
		}
		else
		{
			max_ = a[low];
			min_ = a[high];
		}
	}
	else
	{
		mid = (low + high) / 2;           //分成两个子问题分别求最大最小
		maxmin(a, x1, y1, low, mid);
		maxmin(a, x2, y2, mid + 1, high);
		max_ = max(x1, x2);          //从两个子问题的最大值中选最大
		min_ = min(y1, y2);          //从两个子问题的最小值中选最小
	}
	pair<int, int>maxmin;
	maxmin.first = max_;
	maxmin.second = min_;
	return maxmin;
}

//分治法排序

int split(int *a, int low, int high) //找到一个元素把序列分为两部分
{
	int i=low, k = low;
	int x = a[low];
	for (int k = low + 1; k <= high; k++)
	{
		if (a[k] <= x)
		{
			i++;
			if (i != k)
			{
				swap(a[i], a[k]);
			}
		}
	}
	swap(a[low], a[i]);
	return i;
}

int* sort(int *a,int low,int high)
{
	int k;
	if (low<high)
	{
		k = split(a, low, high);
		sort(a, low, k - 1);
		sort(a, k + 1, high);
	}
	return a;
}

int main()
{
	int *A = new int [9]{ 8,3,6,2,1,9,4,5,7 };
	int max_=0, min_=0; int low = 0; int high=8;
	pair<int,int>maxmin_=maxmin(A, max_, min_, low, high);
	cout << "maxvalue:" << maxmin_.first << endl;
	cout << "minvalue:" << maxmin_.second << endl;
	low = 0; high = 8;
	int*a=sort(A,low, high);
	cout << "sort result:" << endl;
	for (int i=low;i<=high;i++)
	{
		cout << a[i] << " ";
	}
	system("pause");
	return 0;
}
