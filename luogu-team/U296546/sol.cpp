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

//mt19937_64 mtrnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 mtrnd(0x1145);

typedef vector<pair<pair<long double, pair<ull, int>>, int>> vec;

int n, m, k, l;
vector<pair<int, ull>> adj[N][N];
ll f[M][N], g[N][N];
int c = 0;
vector<vec> v;
set<ull> vis;
ull rnd[N];
set<vec> st;

inline void dfs1(int s, int i, int l) {
	if(l <= 0) ++c;
	if(c > 2 * k) return;
	if(s == (1 << i-1)) return;
	rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
		if(c > 2 * k) return;
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
				ptt.emplace_back(mp((long double)w, mp(x, 1 << j-1)), j);
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
			if(v.size() == k) return;
			if(w + f[s^(1<<i-1)][j] >= l) {
				auto ptt = pt;
				ptt.emplace_back(mp((long double)w, mp(x, 1 << j-1)), j);
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

void ins(vec pt) {
	cerr << "ins = " << pt[0].fi.fi << " " << pt[0].fi.se.fi << "\n";
	for(auto x : vis) cerr << x << "\n";
	if(!vis.count(pt[0].fi.se.fi)) {
		cerr << "okkk " << " " << pt[0].fi.se.fi << "\n";
		st.emplace(pt);
		vis.insert(pt[0].fi.se.fi);
		cerr << "after = " << "\n";
		for(auto x : vis) cerr << x << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> k;
	rep(i, 1, m) {
		int u, v, w; cin >> u >> v >> w;
		ull x = mtrnd();
		adj[u][v].emplace_back(w, x);
		adj[v][u].emplace_back(w, x);
	}
	rep(i, 1, n) rnd[i] = mtrnd();
	rep(i, 1, n) rep(j, 1 ,n) {
		sort(adj[i][j].begin(), adj[i][j].end(), greater<pair<int, ull>>());
		g[i][j] = adj[i][j].empty() ? (ll)-1e18 : adj[i][j][0].fi;
	}
	int u = (1 << n) - 1;
	rep(i, 1, n) f[1<<i-1][i] = 0;
	rep(s, 0, u) {
		if(__builtin_popcount(s) <= 1) continue;
		rep(i, 1, n) {
			ll x = -1e18;
			if(s >> i-1 & 1) rep(j, 1, n) if(i != j && (s >> j-1 & 1)) {
				x = max(x, f[s^(1<<i-1)][j] + g[i][j]);
				x = max(x, f[s^(1<<j-1)][i]);
			}
			f[s][i] = x;
		}
	}
	ll L = 1, R = 2e9;
	ll res = -1;
	while(L <= R) {
		ll mid = L + R >> 1;
		if(solve(mid) <= 2*k) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	--res;
	rep(i, 1, n) if(f[u][i] >= res) dfs2(u, i, res, {mp(mp(0.0, mp(0ull, 1 << i-1)), i)});
	rep(i, 1, n) if(f[u][i] >= res) dfs3(u, i, res, {mp(mp(0.0, mp(0ull, 1 << i-1)), i)});
	auto print = [&](const vec& pt) {
		cerr << pt[0].fi.fi << " : ";
		for(int i = 0; i < pt.size(); ++i) cerr << "(" << setprecision(4) << pt[i].fi.fi << "," << pt[i].fi.se.se << ") " << pt[i].se << " \n"[i+1 == pt.size()];
	};
	for(auto& pt : v) {
		for(int i = 1; i < pt.size(); ++i) {
			pt[0].fi.fi += pt[i].fi.fi;
			pt[0].fi.se.fi ^= pt[i].fi.se.fi;
		}
		pt[0].fi.se.fi ^= ::rnd[pt.front().se];
		pt[0].fi.se.fi ^= ::rnd[pt.back().se];
		ins(pt);
	}
	auto merge = [&](const vec& x, const vec& y) {
		cerr << "merge = " << '\n';
		print(x), print(y);
		int p1 = 1, p2 = 0;
		while(p1 < min(x.size(), y.size()) && x[p1].fi.se == y[p1].fi.se && x[p1].se == y[p1].se) ++p1;
		while(p2 < min(x.size(), y.size()) && x[x.size()-p2-1].fi.se == y[y.size()-p2-1].fi.se && x[x.size()-p2-1].se == y[y.size()-p2-1].se) ++p2;
		int s = 0;
		for(int i = 0; i < p1; ++i) s |= x[i].fi.se.se;
		for(int i = x.size() - p2; i < x.size(); ++i) s |= x[i].fi.se.se;
		s |= 1 << x[x.size()-p2-1].se - 1;
		int sx = 0, sy = 0;
		for(int i = p1; i + p2 < x.size(); ++i) sx |= x[i].fi.se.se;
		for(int i = p1; i + p2 < y.size(); ++i) sy |= y[i].fi.se.se;
		cerr << p1 << " " << p2 << " " << sx << " " << sy << "\n";
		if(__builtin_popcount(sx & sy) > 1) return;
		vec pt;
		pt.emplace_back(mp(0.0, mp(0ull, x[0].fi.se.se)), x[0].se);
		for(int i = 1; i < p1; ++i) pt.pb(x[i]);
		long double w1 = 0, w2 = 0;
		ull rnd = 0;
		int s0 = 0;
		for(int i = p1; i + p2 < x.size(); ++i) {
			w1 += x[i].fi.fi;
			rnd ^= x[i].fi.se.fi;
			s0 |= x[i].fi.se.se;
		}
		for(int i = p1; i + p2 < y.size(); ++i) {
			w2 += y[i].fi.fi;
			rnd ^= y[i].fi.se.fi;
			s0 |= y[i].fi.se.se;
		}
		long double w = 1.0 / (1.0 / w1 + 1.0 / w2);
		pt.emplace_back(mp(w, mp(rnd, s0)), x[x.size()-p2-1].se);
		for(int i = x.size() - p2; i < x.size(); ++i) pt.pb(x[i]);
		for(int i = 1; i < pt.size(); ++i) {
			pt[0].fi.fi += pt[i].fi.fi;
			pt[0].fi.se.fi ^= pt[i].fi.se.fi;
		}
		pt[0].fi.se.fi ^= ::rnd[pt.front().se];
		pt[0].fi.se.fi ^= ::rnd[pt.back().se];
		ins(pt);
		cerr << "---" << "\n";
		for(auto x : vis) cerr << x << "\n";
	};
	while(k--) {
		if(st.empty()) {
			cout << -1 << "\n";
			continue;
		}
		auto it = --st.end();
		auto cur = *it;
		st.erase(it);
		cout << cur[0].fi.fi << "\n";
		for(it = st.begin(); it != st.end(); ++it) {
			if((*it).front().se == cur.front().se && (*it).back().se == cur.back().se) {
				merge(*it, cur);
			}
		}
		while(st.size() > k) st.erase(st.begin());
		cerr << "!!! " << vis.count(11251848938040535396ull) << "\n";
		for(auto x : vis) cerr << x << "\n";
	}
	return 0;
}
