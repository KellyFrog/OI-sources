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
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m;
vector<pair<int, int>> adj[N];
vector<tuple<int, int, int>> nd[N];
int rt[N], ls[N*20], rs[N*20], na[N*20], nb[N*20], tt;
ll va[N*20], vb[N*20], ans[N*20];
int px[N], py[N];
ll dis[N], w[N], res;
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
	if(!x || !y) return -inf;
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}

inline void pushup(int o) {
	ll val[4], pos[4];
	val[0] = va[ls[o]], pos[0] = na[ls[o]];
	val[1] = vb[ls[o]], pos[1] = nb[ls[o]];
	val[2] = va[rs[o]], pos[2] = na[rs[o]];
	val[3] = vb[rs[o]], pos[3] = nb[rs[o]];
	ans[o] = -inf;
	rep(i, 0, 3) rep(j, 0, i-1) {
		ll curans = val[i] + val[j] + getdis(pos[i], pos[j]);
		if(curans > ans[o]) {
			ans[o] = curans;
			na[o] = pos[i], va[o] = val[i];
			nb[o] = pos[j], vb[o] = val[j];
		}
	}
}

inline void insert(int& o, int p, int u, ll val, int l, int r) {
	if(!o) {
		o = ++tt;
		ls[o] = rs[o] = va[o] = vb[o] = na[o] = nb[o] = 0;
		ans[o] = -inf;
		return;
	}
	if(l == r) {
		assert(na[o] == 0);
		na[o] = nb[o] = u;
		va[o] = vb[o] = val;
		ans[o] = -inf;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) insert(ls[o], p, u, val, l, mid);
	else insert(rs[o], p, u, val, mid+1, r);
	pushup(o);
}

inline void merge(int& o1, int o2, int l, int r) {
	if(!o1 || !o2) return o1 += o2, void();
	if(l == r) return o1 = 0, void();
	int mid = l + r >> 1;
	merge(ls[o1], ls[o2], l, mid);
	merge(rs[o1], rs[o2], mid + 1, r);
	pushup(o1);
}

inline void dfs2(int u, int fa) {
	for(auto [i, a, b] : nd[u]) {
		ll v = getdis(a, b) + dis[a] - w[i];
		insert(rt[u], i, b, v, 1, m);
	}
	for(auto [v, w] : adj[u]) {
		if(v == fa) continue;
		dfs2(v, u);
		merge(rt[u], rt[v], 1, m);
	}
	res = max(res, (ans[rt[u]] - 2 * dis[u]) / 2);
}

void solve() {
	cin >> n >> m;
	ecnt = tt = 0;
	rep(i, 1, n) rt[i] = 0, adj[i].clear(), nd[i].clear();
	res = -inf;

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
		nd[px[i]].emplace_back(i, px[i], py[i]);
		nd[py[i]].emplace_back(i, py[i], px[i]);
	}

	dfs2(1, 0);

	if(res < -1e18) cout << "F" << "\n";
	else cout << res << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}