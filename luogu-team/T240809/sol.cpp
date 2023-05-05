// Problem: T240809 [PKUSC2021 D2T1] 一棵树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T240809
// Memory Limit: 128 MB
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

const int N = 1e5 + 5;
const int P = 998244353;

int n, k, t;
vector<int> adj[N];
int siz[N], f[N], g[N], h[N], p[N];
int ans;

inline void dfs1(int u, int fa) {
	siz[u] = 1;
	for(int v : adj[u]) {
		dfs1(v, u);
		g[u] = (g[u] + g[v] + 1ll * f[u] * siz[v] + 1ll * (f[v] + siz[v]) * siz[u]) % P;
		f[u] = (f[u] + f[v] + siz[v]) % P;
		siz[u] += siz[v];
	}
}

inline void dfs2(int u, int fa) {
	for(int v : adj[u]) {
		h[v] = (1ll * h[u] + f[u] - (f[v] + siz[v]) + n - siz[v]) % P;
		p[v] = (p[u] 
				+ 1ll * h[u] * (siz[u] - siz[v]) 
				+ 1ll * (f[u] - (f[v] + siz[v])) * (n - siz[u])
				+ g[u] - g[v]
				- 1ll * (f[v] + siz[v]) * (siz[u] - siz[v])
				- 1ll * (f[u] - (f[v] + siz[v])) * siz[v]
			   ) % P;
		dfs2(v, u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> k;
	rep(i, 2, n) {
		int f; cin >> f;
		adj[f].pb(i);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	if(k == 0) {
		cout << g[1] << "\n";
	} else {
		rep(i, 2, n) {
			ans = (ans + 1ll * siz[i] * siz[i] % P * (n - siz[i]) % P * (n - siz[i])) % P;
			ans = (ans + 2ll * g[i] * (n - siz[i]) % P * (n - siz[i])) % P;
			ans = (ans + 1ll * (p[i] + g[i]) * siz[i] % P * (n - siz[i])) % P;
			ans = (ans + 2ll * p[i] * siz[i] % P * siz[i]) % P;
		}
		cout << (ans + P) % P << "\n";
	}
	
	return 0;
}
