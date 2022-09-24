// Problem: AT2046 [AGC004F] Namori
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2046
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-09-11 10:26:22
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

const int N = 1e5 + 5;

int n, m;
int uni[N];
vector<int> adj[N];
int dep[N], fat[N], vis[N];
ll ans = 0;

inline void dfs1(int u, int fa) {
	dep[u] = dep[fa] ^ 1;
	fat[u] = fa;
	for(int v : adj[u]) if(v != fa) dfs1(v, u);
}

inline void dfs2(int u, int fa) {
	f[u][dep[u]] = g[u] + 1;
	for(int v : adj[u]) if(v != fa && !vis[v]) {
		dfs2(v, u);
		f[u][0] += f[v][0];
		f[u][1] += f[v][1];
	}
}

inline void dfs3(int u, int fa) {
	ans += abs(f[u][0] - f[u][1]);
	for(int v : adj[u]) if(v != fa && !vis[v]) {
		dfs3(v, u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
		
	cin >> n >> m;

	if(n % 2 == 1) {
		cout << -1 << "\n";
		return 0;
	}

	rep(i, 1, n) uni[i] = i;

	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		int x = find(u), y = find(v);
		if(x != y) {
			uni[x] = y;
			adj[u].pb(v);
			adj[v].pb(u);
		} else {
			eu = x, ev = y;
		}
	}

	if(!eu) eu = ev = 1;

	dfs1(1, 0);

	if(dep[eu] == dep[ev]) {
		dfs2(1, 0);
		bool f = (dep[eu] & 1) ^ (f[u][1] > f[u][0]);
		int x = (f ? -1 : 1) * abs(f[u][0] - f[u][1]) / 2;
		g[eu] = x;
		g[ev] = x;
		ans += x;
		dfs2(1, 0);
		dfs3(1, 0);
	} else {
		vector<int> px, py, v;
		int x = eu, y = ev;
		while(x != y) {
			if(dep[x] < dep[y]) {
				py.pb(y);
				vis[y] = 1, y = fat[y];
			} else {
				px.pb(x);
				vis[x] = 1, x = fat[x];
			}
		}
		vis[x] = 1;
		v.insert(v.end(), px.begin(), px.end());
		reverse(py.begin(), py.end());
		v.pb(x);
		v.insert(v.end(), py.begin(), py.end());

	

		rep(i, 1, n) if(vis[i]) dfs2(i, 0);
	}

	return 0;
}
