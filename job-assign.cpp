//指派问题匈牙利法
#include <stdio.h>
#include<iostream>
using namespace std;

#define N 5            //工人数/工作数
typedef struct matrix
{
	int cost[N][N];          //效率矩阵
	int zeroelem[N][N];  
	int costforout[N][N];
	int matrixsize;
}MATRIX;
MATRIX matrix;
int result[N][2];								                    //用来储存解的结果,第一列表示工人第二列表示工件 
void getzero(MATRIX &matrix);						//减去行列的最小值得到零元素 
void circlezero(MATRIX &matrix);					//圈出单行列零元素 
void twozero(MATRIX &matrix);						//圈出行列存在两个以上的零元素 
void judge(MATRIX &matrix, int result[N][2]);	//判断是否符合匈牙利算法条件 
void refresh(MATRIX &matrix);							//不符合条件，继续对矩阵进行变形 
void output(int result[N][2], MATRIX matrix);	//结果输出 
//MATRIX input();										//初始输入 
int main()
{
	result[0][0] = 0;
	matrix.matrixsize = N - 1;
	matrix.cost[1][1] = 3; matrix.cost[1][2] = 5; matrix.cost[1][3] = 4; matrix.cost[1][4] = 2;
	matrix.cost[2][1] = 5; matrix.cost[2][2] = 3; matrix.cost[2][3] = 1; matrix.cost[2][4] = 4;
	matrix.cost[3][1] = 6; matrix.cost[3][2] = 4; matrix.cost[3][3] = 2; matrix.cost[3][4] = 3;
	matrix.cost[4][1] = 3; matrix.cost[4][2] = 2; matrix.cost[4][3] = 5; matrix.cost[4][4] = 6;
	for (int i=0;i<=matrix.matrixsize;i++)
	{
		for (int j = 0; j<=matrix.matrixsize; j++)
		{
			matrix.costforout[i][j] = matrix.cost[i][j];
		}
	}
	getzero(matrix);
	circlezero(matrix);
	output(result, matrix);
}
void getzero(MATRIX &matrix)
{
	int i, j;
	int temp;	//表示同行的最大元素或同列的最大元素 
	for (i = 1; i <= matrix.matrixsize; i++)             //减去同行最小元素
	{
		temp = matrix.cost[i][1];
		for (j = 2; j <= matrix.matrixsize; j++)
		{
			if (matrix.cost[i][j] < temp)
				temp = matrix.cost[i][j];
		}
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			matrix.cost[i][j] = matrix.cost[i][j] - temp;
		}
	}
	for (j = 1; j <= matrix.matrixsize; j++)            //减去同列最小元素
	{
		temp = matrix.cost[1][j];
		for (i = 2; i <= matrix.matrixsize; i++)
		{
			if (matrix.cost[i][j] < temp)
				temp = matrix.cost[i][j];
		}
		for (i = 1; i <= matrix.matrixsize; i++)
		{
			matrix.cost[i][j] = matrix.cost[i][j] - temp;
		}
	}
}
void circlezero(MATRIX &matrix)
{
	int i, j, p;
	int flag;
	for (i = 0; i <= matrix.matrixsize; i++)                         //在矩阵外面构建半圈矩阵标记0的个数；
		matrix.cost[i][0] = 0;
	for (j = 1; j <= matrix.matrixsize; j++)
		matrix.cost[0][j] = 0;
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			if (matrix.cost[i][j] == 0)
			{
				matrix.cost[i][0]++;
				matrix.cost[0][j]++;
				matrix.cost[0][0]++;
			}

		}
	}
	for (i = 0; i <= matrix.matrixsize; i++)               //新建一个矩阵
	{
		for (j = 0; j <= matrix.matrixsize; j++)
		{
			matrix.zeroelem[i][j] = 0;
		}
	}
	flag = matrix.cost[0][0] + 1;
	while (matrix.cost[0][0]<flag)
	{
		flag = matrix.cost[0][0];                                       //找行列只有一个0的情况，
		for (i = 1; i <= matrix.matrixsize; i++)                             //第一遍从行开始找独立0元素
		{
			if (matrix.cost[i][0] == 1)
			{
				for (j = 1; j <= matrix.matrixsize; j++)
				{
					if (matrix.cost[i][j] == 0 && matrix.zeroelem[i][j] == 0)  //原来该行有两个0，划去一个现在只有一个0了，划去的那个标为2，此时圈住另一个0
						break;
				}
				matrix.zeroelem[i][j] = 1;
				matrix.cost[i][0]--;
				matrix.cost[0][j]--;
				matrix.cost[0][0]--;
				if (matrix.cost[0][j] > 0)         //这列有多于一个0，划掉
				{
					for (p = 1; p <= matrix.matrixsize; p++)
					{
						if (matrix.cost[p][j] == 0 && matrix.zeroelem[p][j] == 0)
						{
							matrix.zeroelem[p][j] = 2;
							matrix.cost[p][0]--;
							matrix.cost[0][j]--;
							matrix.cost[0][0]--;
						}
					}
				}
			}
		}

		for (j = 1; j <= matrix.matrixsize; j++)                            //   第二遍从列找独立0
		{
			if (matrix.cost[0][j] == 1)
			{
				for (i = 1; i <= matrix.matrixsize; i++)
				{
					if (matrix.cost[i][j] == 0 && matrix.zeroelem[i][j] == 0)
						break;
				}
				matrix.zeroelem[i][j] = 1;
				matrix.cost[i][0]--;
				matrix.cost[0][j]--;
				matrix.cost[0][0]--;
				if (matrix.cost[i][0] > 0)
				{
					for (p = 1; p <= matrix.matrixsize; p++)
					{
						if (matrix.cost[i][p] == 0 && matrix.zeroelem[i][p] == 0)
						{
							matrix.zeroelem[i][p] = 2;
							matrix.cost[i][0]--;
							matrix.cost[0][p]--;
							matrix.cost[0][0]--;
						}
					}
				}
			}
		}
	}

	if (matrix.cost[0][0]>0)      //多重最优解的情况
		twozero(matrix);
	else
		judge(matrix, result);   // 所有独立0都找完了，需要看独立0的个数是否等于工人数
}
void judge(MATRIX &matrix, int result[N][2])
{
	int i, j;
	int num = 0;	 //圈出的0个数 
	int start;	//解的储存开始位置 
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			if (matrix.zeroelem[i][j] == 1)
				num++;
		}
	}
	if (num == matrix.matrixsize)                        //得到最优解
	{
		start = result[0][0] * matrix.matrixsize + 1;
		for (i = 1; i <= matrix.matrixsize; i++)
		{
			for (j = 1; j <= matrix.matrixsize; j++)
			{
				if (matrix.zeroelem[i][j] == 1)             //i工人做j工作
				{
					result[start][0] = i;
					result[start][1] = j;
					start++;
				}
			}
		}
		//result[0][0]++;
	}
	else
		refresh(matrix);
}
void twozero(MATRIX &matrix)
{
	int i, j;
	int p, q;
	int m, n;
	int flag;
	MATRIX backup;
	for (i = 1; i <= matrix.matrixsize; i++)
		if (matrix.cost[i][0]>0)
			break;
	if (i <= matrix.matrixsize)
	{
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			backup = matrix;//备份以寻找多解 
			if (matrix.cost[i][j] == 0 && matrix.zeroelem[i][j] == 0)
			{
				matrix.zeroelem[i][j] = 1;
				matrix.cost[i][0]--;
				matrix.cost[0][j]--;
				matrix.cost[0][0]--;
				for (q = 1; q <= matrix.matrixsize; q++)
					if (matrix.cost[i][q] == 0 && matrix.zeroelem[i][q] == 0)
					{
						matrix.zeroelem[i][q] = 2;
						matrix.cost[i][0]--;
						matrix.cost[0][q]--;
						matrix.cost[0][0]--;
					}
				for (p = 1; p <= matrix.matrixsize; p++)
					if (matrix.cost[p][j] == 0 && matrix.zeroelem[p][j] == 0)
					{
						matrix.zeroelem[p][j] = 2;
						matrix.cost[p][0]--;
						matrix.cost[0][j]--;
						matrix.cost[0][0]--;
					}
				flag = matrix.cost[0][0] + 1;
				while (matrix.cost[0][0]<flag)
				{
					flag = matrix.cost[0][0];
					for (p = i + 1; p <= matrix.matrixsize; p++)
					{
						if (matrix.cost[p][0] == 1)
						{
							for (q = 1; q <= matrix.matrixsize; q++)
								if (matrix.cost[p][q] == 0 && matrix.zeroelem[p][q] == 0)
									break;
							matrix.zeroelem[p][q] = 1;
							matrix.cost[p][0]--;
							matrix.cost[0][q]--;
							matrix.cost[0][0]--;
							for (m = 1; m <= matrix.matrixsize; m++)
								if (matrix.cost[m][q] == 0 && matrix.zeroelem[m][q] == 0)
								{
									matrix.zeroelem[m][q] = 2;
									matrix.cost[m][0]--;
									matrix.cost[0][q]--;
									matrix.cost[0][0]--;
								}
						}
					}
					for (q = 1; q <= matrix.matrixsize; q++)
					{
						if (matrix.cost[0][q] == 1)
						{
							for (p = 1; p <= matrix.matrixsize; p++)
								if (matrix.cost[p][q] == 0 && matrix.zeroelem[p][q] == 0)
									break;
							matrix.zeroelem[p][q] = 1;
							matrix.cost[p][q]--;
							matrix.cost[0][q]--;
							matrix.cost[0][0]--;
							for (n = 1; n <= matrix.matrixsize; n++)
								if (matrix.cost[p][n] == 0 && matrix.zeroelem[p][n] == 0)
								{
									matrix.zeroelem[p][n] = 2;
									matrix.cost[p][0]--;
									matrix.cost[0][n]--;
									matrix.cost[0][0]--;
								}
						}
					}
				}
				if (matrix.cost[0][0]>0)                   //确保matrix.cost[][]中的0元素都在zeroelem[][]中被完全标记出来。
					twozero(matrix);
				else
					judge(matrix, result);
			}
			matrix = backup;
		}
	}
}
void refresh(MATRIX &matrix)
{
	int i, j, min = 0;
	int flag1 = 0, flag2 = 0;
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			if (matrix.zeroelem[i][j] == 1)
			{
				matrix.zeroelem[i][0] = 1;     //覆盖行，记为1 
				break;
			}
		}
	}
	while (flag1 == 0)
	{
		flag1 = 1;
		for (i = 1; i <= matrix.matrixsize; i++)
		{
			if (matrix.zeroelem[i][0] == 0)
			{
				matrix.zeroelem[i][0] = 2;    //未覆盖行，记为2
				for (j = 1; j <= matrix.matrixsize; j++)
				{
					if (matrix.zeroelem[i][j] == 2)   //未覆盖行中有划去的0，则对应的列为覆盖列
					{
						matrix.zeroelem[0][j] = 1;    //覆盖列记为1
					}
				}
			}
		}
		for (j = 1; j <= matrix.matrixsize; j++)
		{
			if (matrix.zeroelem[0][j] == 1)
			{
				matrix.zeroelem[0][j] = 2;          //把覆盖列，记为2
				for (i = 1; i <= matrix.matrixsize; i++)
					if (matrix.zeroelem[i][j] == 1)
					{
						matrix.zeroelem[i][0] = 0;
						flag1 = 0;
					}
			}
		}
	}
	// 从未划去的里面找最小值
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		if (matrix.zeroelem[i][0] == 2)             //未覆盖行
		{
			for (j = 1; j <= matrix.matrixsize; j++)
			{
				if (matrix.zeroelem[0][j] != 2)    //未覆盖列
				{
					if (flag2 == 0)
					{
						min = matrix.cost[i][j];
						flag2 = 1;
					}
					else
					{
						if (matrix.cost[i][j] < min)
							min = matrix.cost[i][j];
					}
				}
			}
		}
	}

	//未覆盖行减去最小值，覆盖列加上最小值
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		if (matrix.zeroelem[i][0] == 2)
			for (j = 1; j <= matrix.matrixsize; j++)
				matrix.cost[i][j] = matrix.cost[i][j] - min;
	}
	for (j = 1; j <= matrix.matrixsize; j++)
	{
		if (matrix.zeroelem[0][j] == 2)
			for (i = 1; i <= matrix.matrixsize; i++)
				matrix.cost[i][j] = matrix.cost[i][j] + min;
	}
	for (i = 0; i <= matrix.matrixsize; i++)
	{
		for (j = 0; j <= matrix.matrixsize; j++)
		{
			matrix.zeroelem[i][j] = 0;              //矩阵清0
		}
	}
	circlezero(matrix);
}
void output(int result[N][2], MATRIX matrix)
{
	int minsum;	//最小的工作成本 
	int i, j;
	int start=1;  //每个解的储存开始位置 
	minsum = 0;
	for (i = 1; i <= matrix.matrixsize; i++)
	{
		minsum = minsum + matrix.costforout[i][result[i][1]];
	}
	cout << "minsum:" << minsum << endl;
	for (j = start; j < start + matrix.matrixsize; j++)
	{
		cout << " 第" << result[j][0] << "个人做" << "第" << result[j][1] << "件工作" << endl;
	}
	getchar();
}
