// Problem: P6846 [CEOI2019] Amusement Park
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6846
// Memory Limit: 1 MB
// Time Limit: 3000 ms
// Create Time: 2023-06-19 13:12:05
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

const int N = 20;
const int M = 1 << 18 | 5;
const int P = 998244353;
const int inv = (P + 1) / 2;

int n, m;
int f[M], g[M];
int adj[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[u] |= 1 << v-1;
		adj[v] |= 1 << u-1;
	}
	int u = (1 << n) - 1;
	rep(s, 1, u) {
		bool ok = 1;
		rep(i, 1, n) if(s >> i-1 & 1) if(adj[i] & s) ok = 0;
		if(ok) g[s] = __builtin_popcount(s) % 2 ? 1 : -1;
	}
	f[0] = 1;
	rep(s, 1, u) {
		for(int s0 = s; s0; s0 = s & (s0 - 1)) f[s] = (f[s] + f[s^s0] * g[s0]) % P;
	}
	int ans = 1ll * f[u] * m % P * inv % P;
	cout << (ans + P) % P << "\n";
	
	return 0;
}

