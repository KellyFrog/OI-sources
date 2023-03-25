// Problem: P5642 人造情感（emotion）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5642
// Memory Limit: 500 MB
// Time Limit: 6000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 3e5 + 5;
const int P = 998244353;

int n, m;
vector<int> adj[N];
vector<pair<pair<int, int>, int>> bdj[N];
vector<ll> cdj[N], ddj[N], edj[N];
ll f[N], g[N], h[N], sum[N], t[N], tag[N];
int anc[N][21], dep[N], dfn[N], siz[N], son[N], top[N], fat[N], dfncnt;
int s[N], ans;

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, ll val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += val; }
inline ll query(int x) { ll ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }
inline void add(int l, int r, int val) { add(l, val), add(r+1, -val); }

inline void dfs1(int u, int fa) {
	dep[u] = dep[fa] + 1;
	fat[u] = fa;
	anc[u][0] = fa;
	dfn[u] = ++dfncnt, siz[u] = 1;
	rep(i, 1, 20) anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int v : adj[u]) if(v != fa) {
		dfs1(v, u), siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

inline int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 20) if(dep[anc[x][i]] >= dep[y]) x = anc[x][i];
	if(x == y) return x;
	per(i, 0, 20) if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}

inline void dfs2(int u, int fa) {
	if(son[fa] == u) top[u] = top[fa];
	else top[u] = u;

	for(int v : adj[u]) if(v != fa) dfs2(v, u);
	for(int v : adj[u]) if(v != fa) sum[u] += f[v];
	for(int v : adj[u]) if(v != fa) {
		g[v] = sum[u] - f[v];
		add(dfn[v], dfn[v]+siz[v]-1, g[v]);
	}
	f[u] = sum[u];
	for(auto e : bdj[u]) {
		int x = e.fi.fi, y = e.fi.se, w = e.se;
		ll val = query(dfn[x]) + query(dfn[y]) + sum[x] + sum[y] - sum[u] + w;
		f[u] = max(f[u], val);
	}
}

inline void dfs3(int u, int fa) {
	g[u] += g[fa];
	for(int v : adj[u]) if(v != fa) dfs3(v, u);
}

multiset<ll> st;

inline void dfss(int u, int fa) {
	if(son[u]) {
		dfss(son[u], u);
		tag[u] = max(tag[u], tag[son[u]]);
	}
}

inline void dfs4(int u, int fa) {
	cerr << "dfs4=" << u << " " << fa << "\n";
	if(u == top[u]) dfss(u, fa);
	if(son[fa] != u) h[u] = max(h[u], tag[fa]);
	h[u] -= f[u];
	for(int v : adj[u]) if(v != fa) h[v] = max(h[v], h[u] + sum[u]);
	for(auto e : bdj[u]) {
		int x = e.fi.fi, y = e.fi.se, w = e.se;
		ll val = query(dfn[x]) + query(dfn[y]) + sum[x] + sum[y] - sum[u] + w + h[u];
		while(top[x] != top[u]) {
			tag[x] = max(tag[x], val);
			x = fat[top[x]];
			if(x != u) h[son[x]] = max(h[son[x]], val);
		}
		while(top[y] != top[u]) {
			tag[y] = max(tag[y], val);
			y = fat[top[y]];
			if(y != u) h[son[y]] = max(h[son[y]], val);
		}
		if(x == u) swap(x, y);
		ddj[u].pb(val);
		edj[son[x]].pb(val);
	}
	for(ll v : ddj[u]) st.insert(v);
	for(ll v : edj[u]) st.erase(st.find(v));
	if(!st.empty()) h[u] = max(h[u], *st.rbegin());

	if(son[u]) dfs4(son[u], u);
	else st.clear();

	for(int v : adj[u]) if(v != fa && v != son[u]) dfs4(v, u);
}

inline void dfs5(int u, int fa) {
	siz[u] = 1;
	s[u] = (g[u] + sum[u]) % P;
	ans = (ans + f[1] - h[u] - sum[u]) % P;
	for(int v : adj[u]) if(v != fa) {
		dfs5(v, u);
		ans = (ans 
				+ 2ll * siz[u] * siz[v] % P * ((f[1] - h[u] + 2 * g[u] + sum[u]) % P)
				- 2ll * siz[u] * s[v] - 2ll * siz[v] * s[u]) % P;
		s[u] = (s[u] + s[v]) % P;
		siz[u] += siz[v];
	}
}

int main() {
// 	freopen("emotion.in", "r", stdin);
// 	freopen("emotion.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> m;
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs1(1, 0);
	rep(i, 1, m) {
		int x, y, w; cin >> x >> y >> w;
		int lca = LCA(x, y);
		bdj[lca].emplace_back(mp(x, y), w);
	}
	dfs2(1, 0);
	dfs3(1, 0);
	cerr << "f&g=" << '\n';
	rep(i, 1, n) cerr << f[i] << " \n"[i == n];
	rep(i, 1, n) cerr << g[i] << " \n"[i == n];
	rep(i, 1, n) cerr << siz[i] << " \n"[i == n];
	rep(i, 1, n) cerr << son[i] << " \n"[i == n];
	rep(i, 1, n) cerr << top[i] << " \n"[i == n];
	dfs4(1, 0);
	rep(i, 1, n) cerr << g[i] << " \n"[i == n];
	dfs5(1, 0);
	cout << (ans + P) % P << "\n";

	return 0;
}
