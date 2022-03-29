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
const int S = 150;

ll dis[S][N], dis0[N];
bool vis[N];
int bel[N], bl[N], br[N];
int s, t, n, q;
vector<pair<int, int>> adj[N];
int pos[N], dep[N], eul[N<<1], eid, lg2[N<<1], st[21][N<<1];
ll dist[N];
int tp;

void dij(int id) {
    memset(dis0, 0x3f, sizeof dis0);
    memset(vis, 0, sizeof vis);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    rep(i, bl[id], br[id]) pq.push(mp(dis0[i] = 0, i));
    while(!pq.empty()) {
	int u = pq.top().se; pq.pop();
	if(vis[u]) continue;
	for(auto e : adj[u]) {
	    int v = e.fi, w = e.se;
	    if(dis0[u] + w < dis0[v]) {
		dis0[v] = dis0[u] + w;
		pq.push(mp(dis0[v], v));
	    }
	}
    }
    memcpy(dis[id], dis0, sizeof dis0);
}

inline void dfs(int u, int fa, int lw) {
    eul[pos[u] = ++eid] = u;
    dep[u] = dep[fa] + 1;
    dist[u] = dist[fa] + lw;
    for(auto e : adj[u]) {
	int v = e.fi, w = e.se;
	if(v != fa) {
	    dfs(v, u, w);
	    eul[++eid] = u;
	}
    }
}

inline int compare(int x, int y) {
    return dep[x] < dep[y] ? x : y;
}

void buildst() {
    lg2[0] = -1;
    rep(i, 1, eid) lg2[i] = lg2[i>>1] + 1;
    rep(i, 1, eid) st[0][i] = eul[i];
    rep(j, 1, 20) rep(i, 1, eid) {
	if(i + (1 << j) - 1 > eid) break;
	st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j-1)]);
    }
}

inline int LCA(int x, int y) {
    x = pos[x], y = pos[y];
    if(x > y) swap(x, y);
    int j = lg2[y-x+1];
    return compare(st[j][x], st[j][y-(1<<j)+1]);
}

inline ll getdist(int x, int y) {
    return dist[x] + dist[y] - 2ll * dist[LCA(x, y)];
}

int main() {
    freopen("seg.in", "r", stdin);
    freopen("seg.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> tp;
    rep(i, 2, n) {
	int u, v, w;
	cin >> u >> v >> w;
	adj[u].pb(mp(v, w));
	adj[v].pb(mp(u, w));
    }
    s = sqrt(16*n);
    t = (n + s - 1) / s;
    rep(i, 1, t) {
	bl[i] = (i-1) * s + 1;
	br[i] = i * s;
	br[i] = min(br[i], n);
	rep(j, bl[i], br[i]) bel[j] = i;
    }
    rep(i, 1, t) dij(i);
    dfs(1, 0, 0);
    buildst();

    return 0;

    cin >> q;
    
    ll lastans = 0;

    while(q--) {
	int l, r, x;
	cin >> l >> r >> x;
	if(tp) {
	    x = (lastans + x + 1) % n + 1;
	}
	ll ans = 1e18;
	if(bel[l] == bel[r]) {
	    rep(i, l, r) ans = min(ans, getdist(i, x));
	} else {
	    int id1 = bel[l], id2 = bel[r];
	    rep(i, l, br[id1]) ans = min(ans, getdist(i, x));
	    rep(i, bl[id2], r) ans = min(ans, getdist(i, x));
	    rep(i, id1+1, id2-1) ans = min(ans, dis[i][x]);
	}
	cout << (lastans = ans) << "\n";
    }

    return 0;
}
