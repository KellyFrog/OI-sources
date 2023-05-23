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

int n, q;
vector<pair<int, pair<int, int>>> adj[N];
int ansp, ansi, ansj;
bool vis[N];
ll f[N], g[N], h[N], mx[N], ans[N], tot;
vector<ll> pans;

inline void dfs1(int u, int fa) {
	for(auto [v, e] : adj[u]) if(v != fa) {
		dfs1(v, u);
		f[u] += f[v] + e.se;
		h[u] = max(h[u], h[v] + e.fi);
	}
}

inline void dfs2(int u, int fa) {
	ll s = 0;
	for(auto [v, e] : adj[u]) if(v != fa) s += f[v] + e.se;
	for(auto [v, e] : adj[u]) if(v != fa) {
		g[v] = g[u] + s - (f[v] + e.se) + e.fi;
		dfs2(v, u);
	}
}

inline void dfs3(int u, int fa) {
	int x = -1, y = -1;
	ll ansx = 0, ansy = 0;
	for(auto [v, e] : adj[u]) if(v != fa) {
		if(x == -1 || h[v] + e.fi > ansx) {
			y = x, ansy = ansx;
			x = v, ansx = h[v] + e.fi;
		} else if(y == -1 || h[v] + e.fi > ansy) {
			y = v, ansy = h[v] + e.fi;
		}
		dfs3(v, u);
	}
	ans[2] = max(ans[2], ansx + ansy + f[u] + g[u]);
	if(ans[2] == ansx + ansy + f[u] + g[u]) ansp = u, ansi = x, ansj = y;
}

inline void dfs4(int u, int fa) {
	if(u == -1) return;
	vis[u] = 1;
	for(auto [v, e] : adj[u]) if(v != fa && h[u] == h[v] + e.fi) {
		dfs4(v, u);
		break;
	}
}

inline void dfs5(int u, int fa) {
	vector<ll> val;
	for(auto [v, e] : adj[u]) if(v != fa) {
		dfs5(v, u);
		if(!vis[v]) val.pb(mx[v] + e.fi);
	}
	sort(val.begin(), val.end(), greater<ll>());
	if(!val.empty()) {
		if(vis[u]) pans.insert(pans.end(), val.begin(), val.end());
		else pans.insert(pans.end(), val.begin() + 1, val.end()), mx[u] = val[0];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 2, n) {
		int u, v, a, b; cin >> u >> v >> a >> b;
		adj[u].emplace_back(v, mp(a, b));
		adj[v].emplace_back(u, mp(b, a));
		tot += a;
		tot += b;
	}
	dfs1(1, 0);
	dfs2(1, 0);
	rep(i, 1, n) ans[1] = max(ans[1], f[i] + g[i]);
	dfs3(1, 0);
	dfs4(ansi, ansp);
	dfs4(ansj, ansp);
	vis[ansp] = 1;
	dfs5(ansp, 0);

	while(pans.size() < n) pans.pb(0);
	sort(pans.begin(), pans.end(), greater<ll>());
	for(int i = 0; i < pans.size(); ++i) ans[i+3] = ans[i+2] + pans[i];


	cin >> q;
	while(q--) {
		int x; cin >> x; cout << tot - ans[x] << "\n";
	}
	
	return 0;
}
