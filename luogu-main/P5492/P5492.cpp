// Problem: P5492 [PKUWC2018]随机算法
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5492
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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

const int N = 25;
const int M = 1 << 21 | 5;
const int P = 998244353;

inline int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, m, e[M], f[M], pc[M], inv[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, n) e[1 << i - 1] = 1 << i - 1;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		e[1 << u - 1] |= 1 << v - 1;
		e[1 << v - 1] |= 1 << u - 1;
	}
	int u = (1 << n) - 1;
	rep(s, 1, u) pc[s] = (s & 1) + pc[s >> 1];
	rep(s, 1, u) if(pc[s] > 1) e[s] = e[s & s - 1] | e[s ^ (s & s - 1)];
	rep(i, 1, n) inv[i] = qpow(i, P - 2);
	f[0] = 1;
	rep(s, 0, u) {
		int v = 1ll * f[s] * inv[n - pc[e[s]]] % P;
		rep(i, 1, n) if(!(e[s] >> i-1 & 1)) {
			f[s | (1 << i-1)] = (f[s | (1 << i-1)] + v) % P;
		}
	}
	int mx = 0;
	rep(s, 0, u) if(f[s]) mx = max(mx, pc[s]);
	int ans = 0;
	rep(s, 0, u) if(pc[s] == mx) ans = (ans + f[s]) % P;
	cout << (ans + P) % P << "\n";
		
	return 0;
}
