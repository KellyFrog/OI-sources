#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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

mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());

typedef vector<pair<pair<long double, ull>, int>>> vec;

int n, m, k, l;
vector<pair<int, ull>> adj[N][N];
ll f[M][N], g[N][N];
int c = 0;
vector<vec> v;
set<vec> st;

inline void dfs1(int s, int i, int l) {
	if(l <= 0) ++c;
	if(c > 2 * k) return;
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		for(auto [w, x] : adj[i][j]) {
			if(w + f[s^(1<<i-1)][j] >= l) dfs1(s^(1<<i-1), j, l-w);
			else break;
		}
	}
}

inline void dfs2(int s, int i, int l, const vec& pt) {
	if(l < 0) {
		if(pt.front().se < pt.back().se) v.pb(pt);
	}
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		for(auto [w, x] : adj[i][j]) {
			if(w + f[s^(1<<i-1)][j] >= l) {
				auto ptt = pt;
				ptt.emplace_back(mp((long double)w, x), j);
				dfs2(s^(1<<i-1), j, l-w, ptt);
			}
			else break;
		}
	}
}

inline void dfs3(int s, int i, int l, const vec& pt) {
	if(v.size() == k) return;
	if(l == 0) {
		if(pt.front().se < pt.back().se) v.pb(pt);
	}
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		for(auto [w, x] : adj[i][j]) {
			if(w + f[s^(1<<i-1)][j] >= l) {
				auto ptt = pt;
				ptt.emplace_back(mp((long double)w, x), j);
				dfs3(s^(1<<i-1), j, l-w, ptt);
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

bool vis[N];

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
		ull x = mtrnd();
		adj[u][v].emplace_back(w, x);
		adj[v][u].emplace_back(w, x);
	}
	rep(i, 1, n) rep(j, 1 ,n) {
		sort(adj[i][j].begin(), adj[i][j].end(), greater<pair<int, ull>>());
		g[i][j] = adj[i][j].empty() ? (ll)-1e18 : adj[i][j][0].fi;
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
	rep(i, 1, n) if(f[u][i] >= res) dfs2(u, i, res, {mp(mp(0.0, 0ull), i)});
	rep(i, 1, n) if(f[u][i] >= res) dfs3(u, i, res, {mp(mp(0.0, 0ull), i)});
	for(auto& pt : v) {
		for(int i = 1; i < pt.size(); ++i) {
			pt[0].fi.fi += pt[i].fi.fi;
			pt[0].fi.se ^= pt[i].fi.se;
		}
		st.emplace(pt);
	}
	auto merge = [&](vec v1, vec v2) {
		if(v1.front() != v2.front() || v1.back() != v2.back()) return;
		vec res;
		int t1 = 0, t2 = 0;
		while(t1 < v1.size() && t1 < v2.size() && v1[t1] == v2[t1]) ++t1;
		while(t2 < v1.size() && t2 < v2.size() && v1[v1.size()-t2-1] == v2[v1.size()-t2-1]) ++t2;
		memset(vis, 0, sizeof vis);
		for(int i = t1; i + t2 < v1.size(); ++i) ++vis[v1[i]];
		for(int i = t1; i + t2 < v2.size(); ++i) ++vis[v2[i]];
		rep(i, 1, n) if(vis[i] > 1) return;

	};
	while(k--) {
		if(st.empty()) cout << -1 << "\n";
		else {
			auto it = --st.end();
			auto pt = *it; st.erase(it);
			cout << pt.fi.fi << "\n";
			for(it = st.begin(); it != st.end(); ++it) {
				if(*it.front().se == pt.front().se && *it.back().se == pt.back().se) {
					merge(pt. *it);
				}
			}
		}
		while(st.size() > k) st.erase(st.begin());
	}
	return 0;
}
