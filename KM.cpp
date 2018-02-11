#include <iostream>  
#include <algorithm>  
#include <string>  

using namespace std;

#define N 100  

class Solution {
public:
	int S[N];
	int left[N]; 
	//int T[N];
	int lx[N];
	int ly[N];
	int matrix[N][N];
	int n;
	bool dfs(int u) {
		S[u] = 1;
		for (int i = 1; i <= n; i++) {
			//if (!T[i] && lx[u] + ly[i] == matrix[u][i]) {
				T[i] = 1;
				if (left[i] == 0 || dfs(left[i])) {
					left[i] = u;
					return true;
				}
			}
		}
		return false;
	}
	int min(int a, int b) { return a < b ? a : b; }
	void update() {
		int a = (1 << 30);
		for (int i = 1; i <= n; i++) {
			if (S[i] == 0) continue;
			for (int j = 1; j <= n; j++) {
				if (T[j] == 1) continue;
				a = min(a, lx[i] + ly[j] - matrix[i][j]);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (S[i]) lx[i] -= a;
			if (T[i]) ly[i] += a;
		}
	}

	void solve() {
		//memset(S, 0, sizeof(S));
		
		
		for (int i = 1; i <= n; i++) {
			int _max = 0;
			for (int j = 1; j <= n; j++) {
				
				if (matrix[i][j] > _max) _max = matrix[i][j];
			}
			lx[i] = _max;
		}
		for (int i = 1; i <= n; i++) {
			for ( ; ;) {
				  
				memset(S, 0, sizeof(S));
				memset(T, 0, sizeof(T));
				if (dfs(i)) break; else update();
			}
		}
		
	}
};

int main() {
	Solution solution;
	solution.solve();
	return 0;
}