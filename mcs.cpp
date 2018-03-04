 
#include<string>  
#include<algorithm> 
#include<iomanip>
#include<iostream>
using namespace std;
int n, m;
int pre[10000], a[10000], b[10000];   
int minn, ans =INT_MAX ;  
int x[4] = { 1,-1,0,0 }, y[4] = { 0,0,1,-1 };  //方向 
char map[100][100];  
bool mark[100][100]; 
bool check(int s, int t)  
{
	if (s&&t&&s <= n&&t <= m && !mark[s][t] && map[s][t] != 'S') return 1;
	return 0;
}
void fun(int d)
{
	minn++;
	if (pre[d]) fun(pre[d]);
}
void bfs(int r, int c)  
{
	memset(mark, 0, sizeof(mark));   
	minn = 0;   
	int head = 0, tail = 1;
	int nextr, nextc;
	mark[r][c] = 1;   
	pre[1] = 0;   
	a[1] = r;
	b[1] = c;
	while (head != tail)
	{
		head++;
		for (int i = 0; i<4; i++)
		{
			nextr = a[head] + x[i];
			nextc = b[head] + y[i];
			if (check(nextr, nextc))
			{
				tail++;
				a[tail] = nextr;
				b[tail] = nextc;
				mark[nextr][nextc] = 1;
				pre[tail] = head;
				if (map[nextr][nextc] == 'X')
				{
					fun(tail);
					ans = min(minn, ans);
				}
			}
		}
	}
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
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			if (map[i][j] == 'S')
				bfs(i, j); 
	cout << ans - 2 << endl;//去头去尾
	system("pause");
}
