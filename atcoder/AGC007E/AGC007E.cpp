// Problem: AT2172 [AGC007E] Shik and Travel
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT2172
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long int;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 2e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, a[N], ls[N], rs[N];
vector<pair<ll, ll>> f[N];

inline void dfs(int u, int fa, ll mid) {
	if(!ls[u]) {
		f[u].emplace_back(a[u], a[u]);
		return;
	}
	dfs(ls[u], u, mid);
	dfs(rs[u], u, mid);
	if(f[ls[u]].empty() || f[rs[u]].empty()) return;

	vector<pair<ll, ll>> v;
	auto solve = [&]() {
		int p = -1;
		for(auto [i, j] : f[ls[u]]) {
			while(p+1 < f[rs[u]].size() && j + f[rs[u]][p+1].fi <= mid) ++p;
			if(p == -1) continue;
			v.emplace_back(i + a[u], f[rs[u]][p].se + a[u]);
		}
	};
	solve();
	swap(ls[u], rs[u]);
	solve();
	sort(v.begin(), v.end());
	if(v.empty()) return;
	ll mi = inf;
	for(int i = 0; i < v.size(); ++i) {
		if(v[i].se >= mi) continue;
		mi = v[i].se;
		f[u].pb(v[i]);
	}
	sort(f[u].begin(), f[u].end());
}

bool check(ll mid) {
	rep(i, 1, n) f[i].clear();
	dfs(1, 0, mid);
	return !f[1].empty();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 2, n) {
		int f; cin >> f >> a[i];
		if(ls[f]) rs[f] = i;
		else ls[f] = i;
	}

	ll L = 0, R = 1e18;
	ll res = -1;

	while(L <= R) {
		ll mid = L + R >> 1;
		if(check(mid)) res = mid, R = mid - 1;
		else L = mid + 1;
	}

	cout << res << "\n";

	return 0;
}
