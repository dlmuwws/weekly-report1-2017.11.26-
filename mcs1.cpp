#include<math.h>  
#include<string> 
#include<iostream>
#include<algorithm>  
using namespace std;
int n, m;
int ans = INT_MAX;  
int x[4] = { 1,-1,0,0 }, y[4] = { 0,0,1,-1 }; //方向  
char map[100][100];  
bool check(int s, int t)  
{
	if (s&&t&&s <= n&&t <= m&&map[s][t] != 'S') return 1;
	return 0;
}
void dfs(int r, int c)  
{
	for (int i = 0; i<4; i++)
		if (check(r + x[i], c + y[i]) && map[r + x[i]][c + y[i]] != '.')  
		{
			map[r + x[i]][c + y[i]] = 'S'; 
			dfs(r + x[i], c + y[i]);
		}
}
void f()
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] == 'X')
			{
				dfs(i, j);
				map[i][j] = 'S'; 
				return;
			}
}
int main()
{
	for (int i = 1; i <= n; i++)
		cout << map[i] + 1 << endl;
	bool flag = 1;
	f();   
	for (int i = 1; i <= n; i++)//每个方向都用循环穷搜一次
		for (int j = 1; j <= m; j++)
			for (int k = 1; k <= n; k++)
				for (int h = 1; h <= m; h++)
					if (map[i][j] == 'S'&&map[k][h] == 'X')
						ans = min(ans, abs(i - k) + abs(j - h) - 1);   
	cout << ans << endl;
}