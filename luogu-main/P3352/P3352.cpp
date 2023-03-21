// Problem: P3352 [ZJOI2016]线段树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3352
// Memory Limit: 125 MB
// Time Limit: 3000 ms
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

const int N = 405;
const int P = 1e9 + 7;

int n, q;
int a[N], b[N], ans[N], f[2][N][N], d1[N][N], d2[N][N];

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i], b[i] = a[i];
	sort(b + 1, b + n + 1);
	rep(i, 1, n) {
		int p = 0;
		rep(j, 1, n) if(a[j] >= b[i]) f[0][p+1][j-1] += b[i] - b[i-1], p = j;
		f[0][p+1][n] += b[i] - b[i-1];
	}
	rep(t, 0, q-1) {
		memset(f[t+1&1], 0, sizeof f[t+1&1]);
		memset(d1, 0, sizeof d1);
		memset(d2, 0, sizeof d2);

		per(len, 1, n) rep(l, 1, n) {
			int r = l + len - 1;
			if(r > n) break;
			int v = (1ll * l * (l-1) / 2 + 1ll * (n - r) * (n - r + 1) / 2 + 1ll * (r - l + 1) * (r - l + 2) / 2 ) % P;
			f[t+1&1][l][r] = (f[t+1&1][l][r] + 1ll * f[t&1][l][r] * v) % P;
			int s1 = 1ll * f[t&1][l][r] * (n - r) % P;
			int s2 = 1ll * f[t&1][l][r] * (l - 1) % P;
			d1[l][l] = (d1[l][l] + s1) % P;
			d1[l][r] = (d1[l][r] - s1) % P;
			d2[l+1][r] = (d2[l+1][r] + s2) % P;
			d2[r+1][r] = (d2[r+1][r] - s2) % P;

		}
		rep(i, 1, n) rep(j, 1, n) {
			d1[i][j] = (d1[i][j] + d1[i][j-1]) % P;
			f[t+1&1][i][j] = (f[t+1&1][i][j] + d1[i][j]) % P;
		}
		rep(i, 1, n) rep(j, 1, n) {
			d2[i][j] = (d2[i][j] + d2[i-1][j]) % P;
			f[t+1&1][i][j] = (f[t+1&1][i][j] + d2[i][j]) % P;
		}
	}

	int s = 1ll * b[n] * qpow(1ll * n * (n+1) / 2, q) % P;
	rep(i, 1, n) rep(j, i, n) rep(k, i, j) ans[k] = (ans[k] + f[q&1][i][j]) % P;
	rep(i, 1, n) {
		ans[i] = (s - ans[i]) % P;
		cout << (ans[i] + P) % P << " \n"[i == n];
	}

	return 0;
}
