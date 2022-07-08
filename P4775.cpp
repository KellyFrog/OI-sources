// Problem: P4775 [NOI2018] 情报中心
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4775
// Memory Limit: 500 MB
// Time Limit: 8000 ms
// Create Time: 2022-07-08 10:20:54
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

const int N = 1e5 + 5;

int n, m;
vector<pair<int, int>> adj[N];
vector<tuple<int, int, int>> nd[N];
int rt[N], ls[N*20], rs[N*20], na[N*20], nb[N*20], tt;
int px[N], py[N];
ll dis[N], w[N], d[N], ans;
int lg2[N], dep[N], dfn[N], eul[N], st[20][N], ecnt;

inline void dfs1(int u, int fa, int lw) {
	dis[u] = dis[fa] + lw;
	dep[u] = dep[fa] + 1;
	eul[dfn[u]=++ecnt] = u;
	for(auto [v, w] : adj[u]) {
		if(v == fa) continue;
		dfs1(v, u, w);
		eul[++ecnt] = u;
	}
}

inline int compare(int x, int y) { return dep[x] < dep[y] ? x : y; }

void buildst() {
	lg2[0] = -1;
	rep(i, 1, 2*n-1) lg2[i] = lg2[i>>1] + 1;
	rep(i, 1, 2*n-1) st[0][i] = eul[i];
	rep(j, 1, 18) rep(i, 1, 2*n-1) {
		if(i + (1<<j) - 1 > 2*n-1) break;
		st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j>>1)]);
	}
}

inline int LCA(int x, int y) {
	x = dfn[x], y = dfn[y];
	if(x > y) swap(x, y);
	int k = lg2[y-x+1];
	return compare(st[k][x], st[k][y-(1<<k)+1]);
}

inline ll getdis(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}

inline void insert(int& o, int )

inline void dfs2(int u, int fa) {
	for(auto [i, a, b] : nd[u]) {

	}
}

void solve() {
	cin >> n >> m;
	ecnt = tt = 0;
	rep(i, 1, n) rt[i] = 0, adj[i].clear(), nd[i].clear();
	ans = 1e18;

	rep(i, 2, n) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}

	dfs1(1, 0, 0);
	buildst();

	rep(i, 1, m) {
		cin >> px[i] >> py[i] >> w[i];
		d[i] = getdis(px[i], py[i]);
		nd[px[i]].emplace_back(i, px[i], py[i]);
		nd[py[i]].emplace_back(i, py[i], px[i]);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	return 0;
}