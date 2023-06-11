#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e5 + 5;
const int M = 1e7 + 5;
const int P = 1e9 + 7;

int fac[M];
int n, q;
int a[N], dfn[N], did, siz[N], fat[N], dep[N], pos[N], eul[N<<1], eid, st[21][N<<1], lg2[N<<1];
int qx[N], qy[N], qv[N], ans[N];
vector<int> adj[N];
vector<pair<int, int>> mt[M];
vector<int> pfac;

int t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += val; }
inline void add(int l, int r, int val) { add(l, val), add(r+1, -val); }
inline int query(int x) { int ret = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) ret += t[x0]; return ret; }
inline void clear(int x) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] = 0; }

inline void dfs(int u, int fa) {
    dfn[u] = ++did;
    siz[u] = 1;
    eul[pos[u] = ++eid] = u;
    dep[u] = dep[fa] + 1;
    fat[u] = fa;
    for(int v : adj[u]) {
	if(v != fa) {
	    dfs(v, u);
	    siz[u] += siz[v];
	    eul[++eid] = u;
	}
    }
}

inline int compare(int x, int y) {
    return dep[x] < dep[y] ? x : y ;
}

inline void buildst() {
    lg2[0] = -1;
    rep(i, 1, eid) lg2[i] = lg2[i>>1] + 1;
    rep(i, 1, eid) st[0][i] = eul[i];
    rep(j, 1, 20) rep(i, 1, eid) {
	if(i + (1 << j) - 1 > eid) break;
	st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j-1)]);
    }
}

inline int LCA(int x, int y) {
    if(x == y) return x;
    x = pos[x], y = pos[y];
    if(x > y) swap(x, y);
    int j = lg2[y - x + 1];
    //cerr << "LCA(" << x << ", " << y << ") = " << compare(st[j][x], st[j][y-(1<<j)+1]) << "\n";
    return compare(st[j][x], st[j][y-(1<<j)+1]);
}

inline int queryr(int x, int y) {
    int lca = LCA(x, y);
    return query(dfn[x]) + query(dfn[y]) - query(dfn[lca]) - query(dfn[fat[lca]]);
}

int pw[30 * N];

void solve(int d) {
    if(mt[d].empty()) return;
    sort(mt[d].begin(), mt[d].end(), [&](pair<int, int>& x, pair<int, int>& y) {
					 return x.se == y.se ? x.fi > y.fi : x.se < y.se;
				     });
    //cerr << "solve = " << d << "\n";
    //for(auto [id, val] : mt[d]) cerr << val << " " << id << "\n";
    int p = 0, t = 0;
    pw[0] = 1;
    int mx = 0;
    for(int i = 0; i < mt[d].size(); ++i) {
	if(mt[d][i].fi > 0) mx += mt[d][i].se;
    }
    rep(i, 1, mx) pw[i] = 1ll * pw[i-1] * d % P;
    while(p < mt[d].size()) {
	for(int i = p; i < mt[d].size(); ++i) {
	    if(mt[d][i].fi > 0) {
		int u = mt[d][i].fi;
		add(dfn[u], dfn[u] + siz[u] - 1, 1);
	    }
	}
	for(int i = p; i < mt[d].size(); ++i) {
	    if(mt[d][i].fi < 0) {
		int qid = -mt[d][i].fi;
		int x = queryr(qx[qid], qy[qid]);
		ans[qid] = 1ll * ans[qid] * pw[x] % P;
	    }
	}
	for(int i = p; i < mt[d].size(); ++i) {
	    if(mt[d][i].fi > 0) {
		int u = mt[d][i].fi;
		add(dfn[u], dfn[u] + siz[u] - 1, -1);
	    }
	}
	++t;
	while(p < mt[d].size() && mt[d][p].se == t) ++p;
    }
}

int main() {
    freopen("gcd.in", "r", stdin);
    freopen("gcd.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 2, n) {
	int u, v;
	cin >> u >> v;
	adj[u].pb(v);
	adj[v].pb(u);
    }

    rep(i, 1, n) cin >> a[i];
    cin >> q;
    rep(i, 1, q) cin >> qx[i] >> qy[i] >> qv[i];

    int m = 1e7;
    rep(i, 2, m) {
	if(!fac[i]) {
	    for(int j = i; j <= m; j += i) fac[j] = i;
	}
    }

    auto insert = [&](int x, int id) {
		      while(x != 1) {
			  int f = fac[x];
			  int cnt = 0;
			  while(x % f == 0) x /= f, ++cnt;
			  mt[f].pb(mp(id, cnt));
		      }
		  };
    
    rep(i, 1, n) insert(a[i], i);
    rep(i, 1, q) insert(qv[i], -i);

    rep(i, 1, q) ans[i] = 1;

    dfs(1, 0);
    buildst();
    
    rep(i, 2, m) {
	solve(i);
    }

    rep(i, 1, q) cout << ans[i] << "\n";
    cout.flush();
    
    return 0;
}
