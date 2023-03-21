// Problem: U224436 树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U224436
// Memory Limit:  MB
// Time Limit:  ms
// Create Time: 2022-06-27 10:25:34
// Author: Chen Kaifeng
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int N = 3e5 + 5;

mt19937_64 mtrnd(chrono::system_clock().now().time_since_epoch().count());

int n, m, k;
vector<pair<int, int>> adj[N];
vector<ull> val[N];
int siz[N], rt, cnt1[N], cnt2[N];
bool vis[N];
ll ans;
map<ull, int> cnt;
ull pre[N], qry[N];

inline void dfssiz(int u, int fa) {
	siz[u] = 1;
	for(auto [v, c] : adj[u]) {
		if(v != fa && !vis[v]) dfssiz(v, u), siz[u] += siz[v];
	}
}

inline void dfsrt(int u, int fa, int tot) {
	int mx = tot - siz[u];
	for(auto [v, c] : adj[u]) {
		if(v != fa && !vis[v]) dfsrt(v, u, tot), mx = max(mx, siz[v]);
	}
	if(mx <= tot / 2) rt = u;
}

inline void dfscalc(int u, int fa, int c) {
	if(cnt2[c] == k || cnt1[c] < k) return;
	pre[u] = pre[fa] ^ val[c][cnt2[c]] ^ val[c][cnt2[c]+1];
	qry[u] = qry[fa] ^ (cnt2[c] ? val[c][k-cnt2[c]] : val[c][0]) ^ val[c][k-cnt2[c]-1];
	// cerr << "get " << u << " " << fa << " " << c << " " << pre[u] << " " << qry[u] << "\n";
	++cnt2[c];
	ans += cnt[qry[u]];
	for(auto [v, c] : adj[u]) {
		if(v != fa && !vis[v]) dfscalc(v, u, c);
	}
	--cnt2[c];
}

inline void dfsadd(int u, int fa, int c) {
	if(cnt2[c] == k || cnt1[c] < k) return;
	++cnt[pre[u]];
	// cerr << "add = " << pre[u] << "\n";
	++cnt2[c];
	for(auto [v, c] : adj[u]) {
		if(v != fa && !vis[v]) dfsadd(v, u, c);
	}
	--cnt2[c];
}

inline void solve(int u) {
	dfssiz(u, 0);
	rt = -1;
	dfsrt(u, 0, siz[u]);
	assert(rt != -1);
	vis[rt] = 1;
	// cerr << "solve = " << rt << "\n";
	cnt.clear();
	++cnt[pre[0]];
	for(auto [v, c] : adj[rt]) {
		if(!vis[v]) {
			dfscalc(v, 0, c);
			dfsadd(v, 0, c);
		}
	}
	ans += cnt[qry[0]];
	// cerr << "-------- get ans = " << ans << " ----------" << "\n";
	for(auto [v, c] : adj[rt]) {
		if(!vis[v]) solve(v);
	}
}

void solve() {
	cin >> n >> m >> k;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, m) cnt1[i] = 0;
	rep(i, 1, n) vis[i] = 0;
	rep(i, 2, n) {
		int u, v, c; cin >> u >> v >> c;
		adj[u].emplace_back(v, c);
		adj[u].emplace_back(u, v);
		++cnt1[c];
	}
	rep(i, 1, m) {
		val[i].clear();
		if(cnt1[i] < k) continue;
		val[i].resize(k+1);
		for(auto& x : val[i]) x = mtrnd();
	}
	rep(i, 1, m) if(val[i].size() >= k) pre[0] ^= val[i][0], qry[0] ^= val[i][0];


	ans = 0;
	solve(1);
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t;
	cin >> t;
	while(t--) solve();

	
	return 0;
}