// Problem: F - Tree Game
// Contest: AtCoder - AtCoder Grand Contest 010
// URL: https://atcoder.jp/contests/agc010/tasks/agc010_f
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

const int N = 3e3 + 5;

int n;
vector<int> adj[N];
int a[N];

inline bool dfs(int u, int fa) {
	int mi = INT_MAX;
	for(int v : adj[u]) if(v != fa) mi = min(mi, a[v]);
	if(a[u] <= mi) return 0;
	for(int v : adj[u]) if(v != fa && a[v] < a[u] && !dfs(v, u)) return 1;
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	rep(i, 1, n) if(dfs(i, 0)) cout << i << " ";
	cout << "\n";
	
	return 0;
}

