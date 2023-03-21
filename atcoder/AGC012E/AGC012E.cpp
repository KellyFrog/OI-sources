// Problem: E - Camel and Oases
// Contest: AtCoder - AtCoder Grand Contest 012
// URL: https://atcoder.jp/contests/agc012/tasks/agc012_e
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

const int N = 4e5 + 5;

int n, v, a[N], p[N], bel[N];
int uni[N], rt[N], val[N], f[N][21], g[N][21], h;
int ls[N], rs[N];
bool ans[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

inline void dfs1(int u) {
	if(u <= n) {
		f[u][1] = 1;
		return;
	}
	dfs1(ls[u]), dfs1(rs[u]);
	rep(i, 0, 20) rep(j, 0, 20) {
		if(i+j <= 20 && f[ls[u]][i] && f[rs[u]][j]) {
			int c = 0, d = 0;
			rep(k, 0, 19) {
				c += f[ls[u]][i] >> k & 1;
				c += f[rs[u]][j] >> k & 1;
				d |= (!!c) << k; c -= !!c;
			}
			if(!c) f[u][i+j] = min(f[u][i+j], d);
		}
	}
	if(val[u] <= v) f[u][1] = 1 << bel[val[u]];
}

inline void dfs2(int u) {
	if(val[u] <= v) {
		rep(i, 1, 18) if(g[u][i] <= h) ans[u] = 1;
		return;
	}
	rep(i, 0, 20) rep(j, 0, 20) {
		if(i+j <= 20) {
			int c = 0, d = 0;
			rep(k, 0, 19) {
				c += g[u][i] >> k & 1;
				c += f[rs[u]][j] >> k & 1;
				d |= (!!c) << k; c -= !!c;
			}
			if(!c) g[ls[u]][i+j] = min(g[ls[u]][i+j], d);
		}
	}
	dfs2(ls[u]);
	rep(i, 0, 20) rep(j, 0, 20) {
		if(i+j <= 20) {
			int c = 0, d = 0;
			rep(k, 0, 19) {
				c += g[u][i] >> k & 1;
				c += f[ls[u]][j] >> k & 1;
				d |= (!!c) << k; c -= !!c;
			}
			if(!c) g[rs[u]][i+j] = min(g[rs[u]][i+j], d);
		}
	}
	dfs2(rs[u]);
}

inline void dfs3(int u) {
	if(u <= n) return;
	ans[ls[u]] |= ans[u], ans[rs[u]] |= ans[u];
	dfs3(ls[u]), dfs3(rs[u]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> v;
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) p[i] = i;
	sort(p + 2, p + n + 1, [&](int i, int j) { return a[i]-a[i-1] < a[j]-a[j-1]; });
	rep(i, 1, n) rt[i] = uni[i] = i;
	int t = n;
	rep(i, 2, n) {
		int o = p[i];
		int u = rt[find(o-1)], v = rt[find(o)];
		++t, val[t] = a[o] - a[o-1], ls[t] = u, rs[t] = v;
		uni[find(o-1)] = uni[find(o)], rt[find(o)] = t;
	}
	int v0 = v, c = 0;
	while(v0) ++c, v0 >>= 1;
	h = (1 << c) - 1;
	v0 = v;
	while(v0) {
		rep(i, v0/2+1, v0) bel[i] = c;
		--c;
		v0 >>= 1;
	}
	memset(f, 0x3f, sizeof f);
	memset(g, 0x3f, sizeof g);
	dfs1(t);
	g[t][0] = 0;
	dfs2(t);
	dfs3(t);
	rep(i, 1, n) cout << (ans[i] ? "Possible" : "Impossible") << "\n";
	
	return 0;
}
