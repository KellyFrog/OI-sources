// Problem: CF1266F Almost Same Distance
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1266F
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// Create Time: 2022-07-20 15:32:47
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

const int N = 2e6 + 5;
const int inf = 0x3f3f3f3f;

int n;
vector<int> adj[N];
int f[N], g[N];
int ans[N<<1], cnt[N];

inline void dfs1(int u, int fa) {
	for(int v : adj[u]) {
		if(v != fa) {
			dfs1(v, u);
			f[u] = max(f[u], f[v] + 1);
		}
	}
}

inline void dfs2(int u, int fa) {
	vector<int> premx(adj[u].size()), sufmx(adj[u].size());
	for(int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if(v != fa) premx[i] = sufmx[i] = f[v];
		else premx[i] = sufmx[i] = -inf;
	}
	for(int i = 1; i < premx.size(); ++i) premx[i] = max(premx[i], premx[i-1]);
	for(int i = sufmx.size()-2; i >= 0; --i) sufmx[i] = max(sufmx[i], sufmx[i+1]);
	for(int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if(v != fa) {
			g[v] = max(g[u], max((i > 0 ? premx[i-1] : -inf), (i < adj[u].size()-1 ? sufmx[i+1] : -inf)) + 1) + 1;
			dfs2(v, u);
		}
	}
}

inline void dfs3(int u, int fa) {
	vector<int> d(adj[u].size());
	for(int i = 0; i < adj[u].size(); ++i) {
		int v = adj[u][i];
		if(v == fa) d[i] = g[u];
		else {
			d[i] = f[v] + 1;
			dfs3(v, u);
		}
	}

	// cerr << "-----" << u << " " << fa << "-----" << "\n";

	sort(d.begin(), d.end(), greater<int>());
	for(int i = 0; i < d.size(); ++i) {

		ans[2*d[i]] = max(ans[2*d[i]], i+1);

		if(i && d[i-1] != d[i]) {
			// cerr << "t1 " << d[i] << " " << 2*d[i]+1 << " " << i+1 << "\n";
			ans[2*d[i]+1] = max(ans[2*d[i]+1], i+1);
		} else {
			// cerr << "t2 " << d[i] << " " << 2*d[i]-1 << " " << i+1 << "\n";
			ans[2*d[i]-1] = max(ans[2*d[i]-1], i+1);
		}
	}
}

inline void dfs4(int u, int fa) {
	vector<pair<int, int>> d;
	if(u != 1) d.emplace_back(g[u], -u);
	for(int v : adj[u]) {
		if(v == fa) continue;
		d.emplace_back(f[v] + 1, -v);
		for(int vv : adj[v]) if(vv != u) {
			d.emplace_back(f[vv] + 1, v);
		}
	}
	sort(d.begin(), d.end(), greater<pair<int, int>>());
	int cnt1 = 0, cnt2 = 0;

	for(int i = 0; i < d.size(); ++i) {
		int dd = d[i].fi, bel = d[i].se;
		if(bel > 0) ++cnt[bel];
		if(bel < 0) {
			++cnt1;
			int x = cnt1 + max(0, cnt2 - 1);
			ans[2*dd] = max(ans[2*dd], x);
		} else {
			cnt2 = max(cnt2, cnt[bel]);
			int x = cnt1 + cnt[bel] - 1;
			ans[2*dd] = max(ans[2*dd], x);
		}
	}
	cnt[u] = 0;
	for(int v : adj[u]) cnt[v] = 0;
	for(int v : adj[u]) if(v != fa) dfs4(v, u);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) ans[i] = 1;

	rep(i, 1, n-1) {
		int u, v; cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rep(i, 1, n) ans[1] = max(ans[1], (int)adj[i].size() + 1);
	dfs1(1, 0);

	f[0] = g[0] = -inf;
	dfs2(1, 0);
	dfs3(1, 0);
	dfs4(1, 0);

	// rep(i, 1, n) cerr << f[i] << " \n"[i == n];
	// rep(i, 1, n) cerr << g[i] << " \n"[i == n];
	// rep(i, 1, n) cerr << ans[i] << " \n"[i == n];

	per(i, 1, n) ans[i] = max(ans[i], ans[i+2]);
	rep(i, 1, n) cout << ans[i] << " \n"[i == n];

	return 0;
}
