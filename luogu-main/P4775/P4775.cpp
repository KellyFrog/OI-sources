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
const int M = N * 20;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct D {
	int x, y;
	ll v;
	D() {}
	D(int x, int y, ll v) : x(x), y(y), v(v) {}
};

int n, m;
vector<pair<int, int>> adj[N], son[N];
vector<pair<int, pair<int, int>>> ins[N], era[N];
int dep[N], dfn[N], siz[N], dfncnt, pos[N], eul[N], eulcnt, st[19][N], lg2[N];
ll dis[N], a[N], ans;
pair<D, D> t[M];
int rt[N], ls[M], rs[M], tt;

inline void dfs1(int u, int fa, int lw) {
	dis[u] = dis[fa] + lw;
	dep[u] = dep[fa] + 1;
	siz[u] = 1;
	eul[pos[u] = ++eulcnt] = u;
	dfn[u] = ++dfncnt;
	for(auto [v, w] : adj[u]) if(v != fa) {
		dfs1(v, u, w);
		son[u].emplace_back(dfn[v], v);
		eul[++eulcnt] = u;
		siz[u] += siz[v];
	}
}

inline int compare(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

inline void initst() {
	int m = 2 * n - 1;
	rep(i, 1, m) st[0][i] = eul[i];
	lg2[0] = -1;
	rep(i, 1, m) lg2[i] = lg2[i>>1] + 1;
	rep(j, 1, 18) rep(i, 1, m) {
		if(i + (1 << j) - 1 > m) break;
		st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j-1)]);
	}
}

inline int LCA(int x, int y) {
	x = pos[x], y = pos[y];
	if(x > y) swap(x, y);
	int p = lg2[y-x+1];
	return compare(st[p][x], st[p][y-(1<<p)+1]);
}

inline ll getdis(int x, int y) {
	if(x == 0 && y == 0) return -1.5 * inf;
	if(x == 0 || y == 0) return -inf;
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}

inline pair<D, D> merge(const pair<D, D>& x, const pair<D, D>& y) {
	vector<pair<ll, pair<D, D>>> v;
	v.reserve(6);
	vector<D> d = {x.fi, x.se, y.fi, y.se};
	for(int i = 0; i < 4; ++i) {
		for(int j = 0; j < i; ++j) {
			v.emplace_back(getdis(d[i].y, d[j].y) + d[i].v + d[j].v, mp(d[i], d[j]));
		}
	}
	sort(v.begin(), v.end(), [&](const pair<ll, pair<D, D>>& x, const pair<ll, pair<D, D>>& y) { return x.fi > y.fi; });
	return v[0].se;
}

inline int newnode() {
	int o = ++tt;
	ls[o] = rs[o] = 0;
	return o;
}

inline void pushup(int o) {
	if(!ls[o]) t[o] = t[rs[o]];
	else if(!rs[o]) t[o] = t[ls[o]];
	else t[o] = merge(t[ls[o]], t[rs[o]]);
}

inline void insert(int& o, int p, const D& nd, int l, int r) {
	if(!o) o = newnode();
	if(l == r) {
		t[o] = mp(nd, D(0, 0, 0));
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) insert(ls[o], p, nd, l, mid);
	else insert(rs[o], p, nd, mid + 1, r);
	pushup(o);
}

inline void erase(int o, int p, int l, int r) {
	if(l == r) {
		t[o] = mp(D(0, 0, 0), D(0, 0, 0));
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) erase(ls[o], p, l, mid);
	else erase(rs[o], p, mid + 1, r);
	pushup(o);
}

inline void merge(int& o1, int o2, int l, int r) {
	if(!o1 || !o2) {
		o1 += o2;
		return;
	}
	if(l == r) return;
	int mid = l + r >> 1;
	merge(ls[o1], ls[o2], l, mid);
	merge(rs[o1], rs[o2], mid + 1, r);
	pushup(o1);
}

inline void dfs2(int u, int fa) {
	auto getans = [&](const pair<D, D>& x, const pair<D, D>& y) {
		auto [a, b] = x;
		auto [c, d] = y;
		//cerr << a.y << " " << b.y << " " << c.y << " " << d.y << "\n";
		ans = max(ans, max({
					getdis(a.y, c.y) + a.v + c.v,
					getdis(a.y, d.y) + a.v + d.v,
					getdis(b.y, c.y) + b.v + c.v,
					getdis(b.y, d.y) + b.v + d.v
				}) - 2 * dis[u]);
	};


	for(auto [id, e] : ins[u]) {
		auto [x, y] = e;
		ll d = getdis(x, y);
		D o = {x, y, dis[x] + d - 2 * a[id]};
		getans(t[rt[u]], mp(o, D(0, 0, 0)));
		insert(rt[u], id, o, 1, m);
	}
	
	for(auto [v, w] : adj[u]) if(v != fa) {
		dfs2(v, u);
		getans(t[rt[u]], t[rt[v]]);
		merge(rt[u], rt[v], 1, m);
	}
	for(auto [id, e] : era[u]) {
		erase(rt[u], id, 1, m);
	}
}

void solve() {
	cin >> n;
	ans = -inf;
	tt = 0;
	rep(i, 1, n) adj[i].clear(), ins[i].clear(), era[i].clear(), son[i].clear(), rt[i] = 0;
	dfncnt = eulcnt = 0;
	rep(i, 1, n-1) {
		int u, v, w; cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		adj[v].emplace_back(u, w);
	}
	dfs1(1, 0, 0);
	initst();
	
	auto getpos = [&](int u, int v) {
		return (upper_bound(son[u].begin(), son[u].end(), mp(dfn[v], n+1)) - 1) -> se;
	};

	cin >> m;
	rep(i, 1, m) {
		int x, y;
		cin >> x >> y >> a[i];
		if(x == y) continue;
		if(dfn[x] > dfn[y]) swap(x, y);
		int lca = LCA(x, y);
		if(lca == x) {
			ins[y].emplace_back(i, mp(y, x));
			int yy = getpos(x, y);
			era[yy].emplace_back(i, mp(y, x));
		} else {
			ins[x].emplace_back(i, mp(x, y));
			ins[y].emplace_back(i, mp(y, x));
			int xx = getpos(lca, x);
			int yy = getpos(lca, y);
			era[xx].emplace_back(i, mp(x, y));
			era[yy].emplace_back(i, mp(y, x));
		}
	}
	dfs2(1, 0);
	if(ans < -1e18) {
		cout << "F" << "\n";
	} else {
		cout << ans / 2 << "\n";
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15);
	cerr << fixed << setprecision(15);

	int t;
	cin >> t;
	while(t--) solve();

	return 0;
}
