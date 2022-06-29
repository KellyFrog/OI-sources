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

const int N = 1e5 + 5;

int n, m, k;
int cnt[N];
vector<pair<int, int>> adj[N];
ll ans;

inline void dfs(int u, int fa, int c) {
	++cnt[c];
	bool ok = 1;
	rep(i, 1, m) {
		ok &= cnt[i] == 0 || cnt[i] == k;
	}
	if(ok) ++ans;
	for(auto [v, c] : adj[u]) {
		if(v != fa) dfs(v, u, c);
	}
	--cnt[c];
}

void solve() {
	cin >> n >> m >> k;
	rep(i, 1, n) adj[i].clear();
	ans = 0;
	rep(i, 2, n) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[u].emplace_back(v, c);
		adj[v].emplace_back(u, c);
	}
	rep(i, 1, n) {
		// cerr << "dfs = " << i << "\n";
		memset(cnt, 0, sizeof cnt);
		dfs(i, 0, 0);
	}
	cout << (ans + n) / 2 << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t; cin >> t;
	while(t--) solve();
	
	return 0;
}