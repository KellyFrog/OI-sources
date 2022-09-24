// Problem: AT2045 [AGC004E] Salvage Robots
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2045
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 101;

int n, m;
short f[N][N][N][N];
char s[N][N];
int pre1[N][N], pre2[N][N];
int sx = 0, sy = 0;

inline int dfs(int a, int b, int c, int d) {
	if(a < 0 || b < 0 || c < 0 || d < 0) return INT_MIN;
	if(f[a][b][c][d] != -1) return f[a][b][c][d];
	if(a) f[a][b][c][d] = max<int>(f[a][b][c][d], 
			dfs(a-1, b, c, d) + 
			(sx-a <= b ? 0 : max<int>(0, pre1[sx-a][min(m-c, sy+d)] - pre1[sx-a][max(d, sy-c-1)])));
	if(b) f[a][b][c][d] = max<int>(f[a][b][c][d], 
			dfs(a, b-1, c, d) + 
			(n-sx-b < a ? 0 : max<int>(0, pre1[sx+b][min(m-c, sy+d)] - pre1[sx+b][max(d, sy-c-1)])));
	if(c) f[a][b][c][d] = max<int>(f[a][b][c][d], 
			dfs(a, b, c-1, d) + 
			(sy-c <= d ? 0 : max<int>(0, pre2[min(n-a, sx+b)][sy-c] - pre2[max(b, sx-a-1)][sy-c])));
	if(d) f[a][b][c][d] = max<int>(f[a][b][c][d], 
			dfs(a, b, c, d-1) + 
			(m-sy-d < c ? 0 : max<int>(0, pre2[min(n-a, sx+b)][sy+d] - pre2[max(b, sx-a-1)][sy+d])));
	return f[a][b][c][d];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) rep(j, 1, m) cin >> s[i][j];
	rep(i, 1, n) rep(j, 1, m) pre1[i][j] = pre1[i][j-1] + (s[i][j] == 'o');
	rep(i, 1, n) rep(j, 1, m) pre2[i][j] = pre2[i-1][j] + (s[i][j] == 'o');
	rep(i, 1, n) rep(j, 1, m) if(s[i][j] == 'E') sx = i, sy = j;
	memset(f, -1, sizeof f);
	f[0][0][0][0] = 0;
	cout << dfs(sx - 1, n - sx, sy - 1, m - sy) << "\n";
	
	return 0;
}
