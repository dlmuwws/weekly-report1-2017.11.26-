#include <iostream>  
#include <queue>  
using namespace std;

#define iMax 0x7fffffff//������

//���ڽ�����
const int Maxn = 100; //����
int pre[Maxn];   
int v[Maxn]; //��  
int g[Maxn][Maxn]; //���  
int f[Maxn][Maxn]; //���� 

				
int min(const int val1, const int val2)
{
	if (val1 < val2)
		return val1;
	else
		return val2;
}



int maxFlow()
{
	int n = 0; //n��ʾ�����  
	//һ���ڴ�ĳ�ʼ������  
	memset(v, 0, sizeof(v));
	memset(f, 0, sizeof(f));
	cin >> n;

	int s = 0, t = n - 1;
	for (int i = 0; i<n; ++i)
		for (int j = 0; j<n; ++j)
			cin >> g[i][j];

	int queTop = 0;  
	while (true)
	{
		memset(pre, int(-1), sizeof(pre));

		queue<int> que;
		pre[s] = s;
		v[s] =iMax;   
		que.push(s);

		while (!que.empty())
		{

			queTop = que.front();
			que.pop();//BFS

			for (int i = 0; i<n; ++i)
			{
				if (pre[i]<0)
				{
					if (g[queTop][i]>f[queTop][i])
					{
						v[i] = min(g[queTop][i] - f[queTop][i], v[queTop]); //delta  
						pre[i] = queTop; 
						que.push(i);

					}

					//if (f[i][queTop]>0)//ָ����㷽��ı�
					//{
					//	v[i] = min(f[i][queTop], v[queTop]);//��ͱߵ���Сֵ
					//	pre[i] = queTop + n; 
					//						
					//	que.push(i);
					//}
				}
			}

			if (pre[t] >= 0) break;
		}

		if (pre[t]<0) break; //û��·��  


		//int p = 0, q = t;
		//int minval = v[t];
		//
		//while (q != s)
		//{
		//	p = pre[q];

		//	if (p >= n)
		//	{
		//		p -= n;
		//		f[q][p] -= minval;  
		//	}
		//	else
		//		f[p][q] += minval;
		//	q = p;
		//}
	}

	
	queTop = 0;
	for (int i = 0; i<n; ++i)
		queTop += f[s][i];
	return queTop;
}

int main()
{
	cout << maxFlow() << endl;
}