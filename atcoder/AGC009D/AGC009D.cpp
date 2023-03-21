// Problem: D - Uninity
// Contest: AtCoder - AtCoder Grand Contest 009
// URL: https://atcoder.jp/contests/agc009/tasks/agc009_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
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

const int N = 1e5 + 5;

int n;
vector<int> adj[N];
int f[N];

inline void dfs(int u, int fa) {
	int g = 0;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			g |= f[u] & f[v];
			f[u] |= f[v];
		}
	}
	int p = 0;
	rep(i, 0, 25) if(!(g >> i)) {
		f[u] = ((f[u] >> i) + 1) << i;
		break;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	dfs(1, 0);
	int ans = 0;
	while(f[1]) ++ans, f[1] >>= 1;
	cout << ans-1 << "\n";
	
	return 0;
}

