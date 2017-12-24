#include<iostream>
#include<vector>
using namespace std;

typedef vector<double>row;
int const n = 3;

void temp(row row1, row row2, int n)  //交换两行
{
	double temp1;
	for (int i = 0; i<n; i++)
	{
		temp1 = row1[i];
		row2[i] = row2[i];
		row2[i] = temp1;
	}
}
int main()
{
	typedef vector<double>row;
	vector<row>B;
	vector<row>B_add;
	vector<row>Binverse;

	row row1;  row row2;  row row3;
	row1.push_back(-1);
	row1.push_back(0);
	row1.push_back(-2);
	row2.push_back(2);
	row2.push_back(-1);
	row2.push_back(2);
	row3.push_back(5);
	row3.push_back(-3);
	row3.push_back(3);
	B.push_back(row1);
	B.push_back(row2);
	B.push_back(row3);

	row row4; row row5; row row6;
	for (int i = 0; i<n*2; i++)
	{
		row4.push_back(0);
		row5.push_back(0);
		row6.push_back(0);
	}

	B_add.push_back(row4);
	B_add.push_back(row5);
	B_add.push_back(row6);

	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
		{
			B_add[i][j] = B[i][j];
		}
	}

	for (int i = 0; i<n; i++)
	{
		B_add[i][i+n] =1;
	}


	for (int i = 0; i < n; i++)
	{
		if (B_add[i][i] == 0)
		{
			for (int j = i; j < n; j++)
			{
				if (B_add[j][i] != 0)
					temp(B_add[i], B_add[j], 2 * n);  //交换两行
			}
		}
		else
		{
			double yinzhi;
			for (int k = i + 1; k < n; k++)
			{
				yinzhi = -1 * B_add[k][i] / B_add[i][i];
				for (int u = 0; u < 2 * n; u++)
				{
					B_add[k][u] = B_add[k][u] + B_add[i][u] * yinzhi;
				}
			}
		}
	}

	double k;
	for (int i = 0; i<n; i++)    //左矩阵 的对角线 全部 转化为  1
	{
		 k= B_add[i][i];
		for (int j = 0; j<2 * n; j++)
			B_add[i][j] = B_add[i][j] / k;
	}


	for (int i = n - 1; i>0; i--)
	{
		for (int j= 0; j<i; j++)
		{
			k= B_add[j][i];
			for (int u = 0; u<2 * n; u++)
			B_add[j][u] = B_add[j][u] - k*B_add[i][u];
		}
     }


	row row7; row row8; row row9;
	for (int i = 0; i<n; i++)
	{
		row7.push_back(0);
		row8.push_back(0);
		row9.push_back(0);
	}
	Binverse.push_back(row7);
	Binverse.push_back(row8);
	Binverse.push_back(row9);

	for (int i= 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Binverse[i][j] = B_add[i][j + n];
		}
	}
	cout << "finish!!!" << endl;
	cout << "the inverse matrix is:"<<endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Binverse[i][j] << ",";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
