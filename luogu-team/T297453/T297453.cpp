// Problem: T297453 月亮（moon）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T297453
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-12-05 19:14:08
// Input/Output: stdin/stdout
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

const int N = 120 + 5;

int n, a[N];
char s[N];
int f[N][N][N][2], g[N];

inline void upd(int& x, int y) {
	if(x < y) x = y;
}

void solve() {
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	cin >> (s + 1);
	memset(f, 0xf3, sizeof f);
	rep(i, 1, n) {
		f[i][i][1][1] = 0;
		f[i][i][1][0] = 0;
		if(a[1] != -1) f[i][i][0][0] = a[1];
		f[i+1][i][0][0] = 0;
	}
	rep(len, 2, n) {
		rep(i, 1, n) {
			int j = i + len - 1;
			if(j > n) break;
			rep(k, 1, len) rep(p, i+1, j) upd(f[i][j][k][1], f[i+1][p-1][0][0] + f[p][j][k-1][0]);
			if(s[i] == s[j]) {
				rep(k, 1, len) rep(p, i, j-1) upd(f[i][j][k][0], f[i][p][k-1][1] + f[p+1][j-1][0][0]);
				rep(k, 1, len) if(a[k] != -1) upd(f[i][j][0][0], f[i][j][k][0] + a[k]);
			}
			rep(k, i, j-1) upd(f[i][j][0][0], f[i][k][0][0] + f[k+1][j][0][0]);
		}
	}
	memset(g, 0, sizeof g);
	rep(i, 1, n) {
		g[i] = g[i-1];
		rep(j, 0, i-1) upd(g[i], g[j] + f[j+1][i][0][0]);
	}
	cout << g[n] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}
