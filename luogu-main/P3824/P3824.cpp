// Problem: P3824 [NOI2017] 泳池
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3824
// Memory Limit: 125 MB
// Time Limit: 3000 ms
// Create Time: 2022-06-29 15:16:59
// Author: Chen Kaifeng
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

const int N = 1e3 + 5;
const int K = 1e3 + 5;
const int P = 998244353;

int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, k, p, x, y;
int f[K][K], g[K][K], h[N];
int pw[K];

int solve(int m) {
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(h, 0, sizeof h);
	rep(i, 1, m) {
		per(j, 1, m) {
			if(i * j > m) continue;
			rep(k, 1, i) {
				f[i][j] = (f[i][j] + 1ll * (k == 1 ? 1 : g[k-1][j+1]) * (k == i ? 1 : g[i-k][j])) % P;
			}
			f[i][j] = 1ll * f[i][j] * pw[j] % P * (1-p) % P;
			g[i][j] = (f[i][j] + g[i][j+1]) % P;
		}
	}
	assert(1ll * n * m <= 1000000);
	h[0] = 1;
	rep(i, 1, n) {
		h[i] = 1ll * h[i-1] * (1-p) % P;
		rep(j, 1, m) {
			if(j > i) continue;
			if(i == j) {
				h[i] = (h[i] + g[j][1]) % P;
			} else {
				h[i] = (h[i] + 1ll * (1-p) * g[j][1] % P * h[i-j-1]) % P;
			}
		}
	}
	return h[n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k >> x >> y;
	p = 1ll * x * qpow(y, P - 2) % P;
	pw[0] = 1;
	rep(i, 1, k) pw[i] = 1ll * pw[i-1] * p % P;

	int ans = (solve(k) - solve(k-1)) % P;
	cout << (ans + P) % P << "\n";
	
	return 0;
}