// Problem: CF487E Tourists
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF487E
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-12-24 09:26:55
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

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

int n, m, k, q, a[N];
vector<int> adj[N], bdj[N];
int low[N], dfn[N], dfncnt, stk[N], tp;
int siz[N], son[N], seq[N], sgn[N], sgncnt, fat[N], top[N], dep[N];
set<pair<int, int>> s[N];
int t[N<<2];

inline void pushup(int o) {
	t[o] = min(t[o << 1], t[o << 1 | 1]);
}

inline void modify(int o, int p, int x, int l, int r) {
	if(l == r) {
		t[o] = x;
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, x, l, mid);
	else modify(o << 1 | 1, p, x, mid + 1, r);
	pushup(o);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return t[o];
	int mid = l + r >> 1;
	int res = inf;
	if(ql <= mid) res = min(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = min(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	stk[++tp] = u;
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			if(low[v] == dfn[u]) {
				++k;
				while(1) {
					int x = stk[tp--];
					bdj[x].pb(k);
					bdj[k].pb(x);
					if(x == v) break;
				}
				bdj[k].pb(u);
				bdj[u].pb(k);
			}
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

inline void dfs1(int u, int fa) {
	fat[u] = fa;
	dep[u] = dep[fa] + 1;
	siz[u] = 1;
	if(u > n) a[u] = inf;
	for(int v : bdj[u]) if(v != fa) {
		dfs1(v, u);
		if(u > n) {
			a[u] = min(a[u], a[v]);
			s[u].emplace(a[v], v);
		}
		if(siz[v] > siz[son[u]]) son[u] = v;
		siz[u] += siz[v];
	}
}

inline void dfs2(int u, int fa) {
	top[u] = u == son[fa] ? top[fa] : u;
	seq[sgn[u] = ++sgncnt] = u;
	if(son[u]) dfs2(son[u], u);
	for(int v : bdj[u]) if(v != fa && v != son[u]) dfs2(v, u);
}

inline void build(int o, int l, int r) {
	if(l == r) {
		t[o] = seq[l] <= n ? inf : a[seq[l]];
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	
	k = n;
	tarjan(1);
	dfs1(n+1, 0);
	dfs2(n+1, 0);
	build(1, 1, k);
	
	while(q--) {
		char op; cin >> op;
		int x, y; cin >> x >> y;
		if(op == 'C') {
			s[fat[x]].erase(mp(a[x], x));
			s[fat[x]].emplace(a[x] = y, x);
			modify(1, sgn[fat[x]], s[fat[x]].begin()->fi, 1, k);
		} else {
			int res = inf;
			while(top[x] != top[y]) {
				if(dep[top[x]] < dep[top[y]]) swap(x, y);
				res = min(res, query(1, sgn[top[x]], sgn[x], 1, k));
				x = fat[top[x]];
			}
			if(dep[x] < dep[y]) swap(x, y);
			res = min(res, query(1, sgn[y], sgn[x], 1, k));
			if(y <= n) res = min(res, a[y]);
			else if(fat[y]) res = min(res, a[fat[y]]);
			cout << res << "\n";
		}
	}
	
	return 0;
}
