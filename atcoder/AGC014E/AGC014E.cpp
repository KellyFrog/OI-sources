// Problem: E - Blue and Red Tree
// Contest: AtCoder - AtCoder Grand Contest 014
// URL: https://atcoder.jp/contests/agc014/tasks/agc014_e
// Memory Limit: 256 MB
// Time Limit: 6000 ms
// Creaate Time: 
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

int n;
vector<int> adj[N];
int fat[N], dep[N], siz[N], anc[N][20], d[N];

inline void dfs1(int u, int fa) {
	fat[u] = fa;
	dep[u] = dep[fa] + 1;
	anc[u][0] = fa;
	rep(i, 1, 19) anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int v : adj[u]) if(v != fa) dfs1(v, u);
}

inline int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 19) if(dep[anc[x][i]] >= dep[y]) x = anc[x][i];
	if(x == y) return x;
	per(i, 0, 19) if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}

inline void dfs2(int u, int fa) {
	siz[u] = 1;
	for(int v : adj[u]) if(v != fa) dfs2(v, u), d[u] += d[v], siz[u] += siz[v];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n-1) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs1(1, 0);
	rep(i, 1, n-1) {
		int x, y; cin >> x >> y;
		++d[LCA(x, y)];
	}
	dfs2(1, 0);
	rep(i, 1, n) if(d[i] > siz[i]-1) {
		cout << "NO" << "\n";
		return 0;
	}
	cout << "YES" << "\n";
	
	return 0;
}
