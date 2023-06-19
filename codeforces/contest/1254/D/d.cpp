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

const int N = 1.5e5 + 5;
const int P = 998244353;

inline int qpow(int x, int p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

int n, q;
vector<int> adj[N];
vector<pair<int, int>> qdj[N], mdj[N];
vector<pair<int, int>> son[N];
int dfn[N], siz[N], dfncnt;
int ssiz[N], rt;
bool vis[N];
vector<tuple<int, int, int>> v;
int ans[N], pw[N], op[N];

inline int getsiz(int rt, int u) {
	int ret = 0;
	if(rt == u) ret = n;
	else if(dfn[u] <= dfn[rt] && dfn[rt] < dfn[u] + siz[u]) {
		int v = (upper_bound(son[u].begin(), son[u].end(), mp(dfn[rt], 1000000000)) - 1) -> se;
		ret = n - siz[v];
	}
	else ret = siz[u];
	return ret;
}

inline void dfssiz(int u, int fa) {
	ssiz[u] = 1;
	for(int v : adj[u]) if(v != fa && !vis[v]) dfssiz(v, u), ssiz[u] += ssiz[v];
}

inline void dfsrt(int u, int fa, int tot) {
	int mx = tot - ssiz[u];
	for(int v : adj[u]) if(v != fa && !vis[v]) dfsrt(v, u, tot), mx = max(mx, ssiz[v]);
	if(mx <= tot / 2) rt = u;
}

inline void dfsupd(int u, int fa, int rt) {
	ssiz[u] = getsiz(rt, u);
	for(int v : adj[u]) if(v != fa && !vis[v]) dfsupd(v, u, rt);
}

inline void dfsins(int u, int fa) {
	if(u != rt) for(auto [t, id] : qdj[u]) v.emplace_back(t, u, -id);
	for(auto [t, d] : mdj[u]) v.emplace_back(t, u, d);
	for(int v : adj[u]) if(v != fa && !vis[v]) dfsins(v, u);
}

inline void getans(int rt, int tt) {
	cerr << "getans = " << rt << " " << tt << "\n";
	v.clear();
	dfsins(rt, 0);
	sort(v.begin(), v.end());
	ll sum = 0;
	for(auto [t, u, x] : v) {
		cerr << t << " " << u << " " << x << "\n";
		if(x < 0) {
			ans[-x] = (ans[-x] + tt * sum * ssiz[u]) % P;
			cerr << "q " << -x << " " << sum << " " << ssiz[u] << " " << ans[-x] << "\n";
		} else {
			sum += x;
		}
	}
}

inline void dfsinss(int u, int fa, int rt) {
	for(auto [t, d] : mdj[u]) v.emplace_back(t, d, ssiz[rt]);
	for(int v : adj[u]) if(v != fa && !vis[v]) dfsinss(v, u, rt);
}

inline void solve(int u) {
	dfssiz(u, 0);
	rt = -1;
	dfsrt(u, 0, ssiz[u]);
	assert(rt != -1);
	cerr << "solve = " << rt << "\n";
	dfsupd(rt, 0, rt);
	getans(rt, 1);
	vis[rt] = 1;
	for(int v : adj[rt]) if(!vis[v]) getans(v, -1);
	v.clear();
	for(int v : adj[rt]) if(!vis[v]) dfsinss(v, rt, v);
	for(auto [t, id] : qdj[rt]) v.emplace_back(t, rt, -id);
	for(auto [t, d] : mdj[rt]) v.emplace_back(t, d, 0);
	cerr << "calc throu rt" << "\n";
	sort(v.begin(), v.end());
	ll a = 0, b = 0;
	for(auto [t, u, x] : v) {
		cerr << t << " " << u << " " << x << "\n";
		if(x < 0) {
			ans[-x] = (ans[-x] + n * a - b);
		} else {
			a += u, b += u * x;
		}
	}
	for(int v : adj[rt]) if(!vis[v]) solve(v);
}

inline void dfs0(int u, int fa) {
	siz[u] = 1, dfn[u] = ++dfncnt;
	for(int v : adj[u]) if(v != fa) {
		dfs0(v, u), siz[u] += siz[v];
		son[u].emplace_back(dfn[v], v);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> q;
	int inv = qpow(n, P-2);
	pw[0] = 1;
	rep(i, 1, q) pw[i] = 1ll * pw[i-1] * inv % P;
	rep(i, 1, n-1) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	rep(i, 1, q) {
		int u, d;
		cin >> op[i] >> u;
		if(op[i] == 1) {
			cin >> d;
			mdj[u].emplace_back(i, d);
		} else {
			qdj[u].emplace_back(i, i);
		}
	}
	dfs0(1, 0);
	solve(1);
	int c = 0;
	rep(i, 1, q) {
		if(op[i] == 1) ++c;
		else {
			cerr << ans[i] << "\n";
			cout << 1ll * ans[i] * pw[c] % P << "\n";
		}
	}
	
	return 0;
}
