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

const int N = 25;
const int M = 1 << 20 | 5;
const int K = 2e3 + 5;

mt19937 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

int n, m, k, l;
vector<int> adj[N][N];
ll f[M][N], g[N][N];
int c = 0;
vector<vector<pair<int, int>>> v;
set<
pair<int, vector<pair<int, int>>>
> pq;

inline void dfs1(int s, int i, int l) {
	if(l <= 0) ++c;
	if(c > 2 * k) return;
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		for(int w : adj[i][j]) {
			if(w + f[s^(1<<i-1)][j] >= l) dfs1(s^(1<<i-1), j, l-w);
			else break;
		}
	}
}

inline void dfs2(int s, int i, int l, const vector<pair<int, int>>& pt) {
	if(l <= 0) {
		if(l < 0) v.pb(pt);
		else if(v.size() < 2 * k) v.pb(pt);
	}
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		for(int k = 0; k < adj[i][j].size(); ++k) {
			int w = adj[i][j][k];
			if(w + f[s^(1<<i-1)][j] >= l) {
				vector<pair<int, int>> ptt = pt;
				ptt.emplace_back(j, k);
				dfs2(s^(1<<i-1), j, l-w, ptt);
			}
			else break;
		}
	}
}

int solve(int l) {
	c = 0;
	::l = l;
	int u = (1 << n) - 1;
	rep(i, 1, n) if(f[u][i] >= l) dfs1(u, i, l);
	return c;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("sp.in", "r", stdin);
	freopen("sp.out", "w", stdout);

	cin >> n >> m >> k;
	rep(i, 1, m) {
		int u, v, w; cin >> u >> v >> w;
		adj[u][v].emplace_back(w);
		adj[v][u].emplace_back(w);
	}
	rep(i, 1, n) rep(j, 1 ,n) {
		sort(adj[i][j].begin(), adj[i][j].end(), greater<int>());
		g[i][j] = adj[i][j].empty() ? (ll)-1e18 : adj[i][j][0];
	}
	int u = (1 << n) - 1;
	rep(i, 1, n) f[1<<i-1][i] = 0;
	rep(s, 0, u) {
		if(__builtin_popcount(s) <= 1) continue;
		rep(i, 1, n) {
			f[s][i] = -1e18;
			if(s >> i-1 & 1) rep(j, 1, n) if(i != j && (s >> j-1 & 1)) f[s][i] = max(f[s][i], f[s^(1<<i-1)][j] + g[i][j]);
		}
	}
	rep(i, 1, n) rep(s, 0, u) rep(j, 1, n) f[s|(1<<j-1)][i] = max(f[s|(1<<j-1)][i], f[s][i]);
	ll L = 1, R = 2e9;
	ll res = -1;
	while(L <= R) {
		ll mid = L + R >> 1;
		if(solve(mid) <= 2*k) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	rep(i, 1, n) if(f[u][i] >= res) {
		vector<pair<int, int>> v = {{i, -1}};
		dfs2(u, i, res, v);
	}
	for(auto& vv : v) {
		vv[0].se = mtrnd();
		int res = 0;
		for(int i = 1; i < vv.size(); ++i) res += adj[vv[i-1].fi][vv[i].fi][vv[i].se];
		pq.emplace(res, vv);
	}
	auto merge = [&](vector<pair<int, int>> v1, vector<pair<int, int>> v2) {
	};
	int k0 = k;
	k *= 2;
	vector<int> ans;
	int c = 0;
	while(k--) {
		if(pq.empty()) break;
		while(pq.size() > k+1) pq.erase(pq.begin());
		auto it = --pq.end();
		if(c % 2 == 0) {
			ans.pb(it->fi);
		}
		++c;
		auto cur = it->se; pq.erase(it);
		for(auto it = pq.begin(); it != pq.end(); ++it) {
			if(it->se[0].fi == cur[0].fi && it->se.back().fi == cur.back().fi) {
				merge(it->se, cur);
			}
		}
	}

	while(ans.size() < k0) ans.pb(-1);
	for(int x : ans) cout << x << "\n";
	return 0;
}
