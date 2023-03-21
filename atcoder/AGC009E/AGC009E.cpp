// Problem: E - Eternal Average
// Contest: AtCoder - AtCoder Grand Contest 009
// URL: https://atcoder.jp/contests/agc009/tasks/agc009_e
// Memory Limit: 256 MB
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

const int N = 4e3 + 5;
const int P = 1e9 + 7;

int n, m, k;
int f[N][N], g[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k;
	
	int ans = 0;
	rep(i, 1, k-1) f[1][i] = 1;
	rep(i, 1, m) g[1][i] = (g[1][i-1] + f[1][i]) % P;
	rep(i, 2, (n+m-1) / (k-1)+3) {
		rep(j, 1, m) f[i][j] = (g[i-1][j] - g[i-1][j-k]) % P;
		rep(j, 1, m) g[i][j] = (g[i][j-1] + f[i][j]) % P;
	}
	rep(i, 1,  (n+m-1) / (k-1)+3) rep(j, 1, m) if(j % (k-1) == m % (k-1) && i*(k-1)-j+1 <= n) ans = (ans + f[i][j]) % P;
	cout << (ans + P) % P << "\n";
	
	return 0;
}

