// Problem: P9039 [PA2021] Drzewo czerwono-czarne
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9039
// Memory Limit: 512 MB
// Time Limit: 3000 ms
// Create Time: 2023-06-08 22:10:31
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

const int N = 1e5 + 5;

int n;
int a[N], b[N];
vector<int> adj[N];
int d[N];

inline void dfs(int u, int fa) {
	d[u] = d[fa] ^ 1;
	for(int v : adj[u]) if(v != fa) dfs(v, u);
}

void solve() {
	cin >> n;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, n) {
		char ch; cin >> ch; a[i] = ch - '0';
	}
	rep(i, 1, n) {
		char ch; cin >> ch; b[i] = ch - '0';
	}
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v), adj[v].pb(u);
	}
	bool f = 1;
	rep(i, 2, n) f &= a[i] == a[i-1];
	if(f) {
		bool ok = 1;
		rep(i, 1, n) ok &= b[i] == a[1];
		cout << (ok ? "TAK" : "NIE") << "\n";
		return;
	}
	int mx = 0;
	rep(i, 1, n) mx = max(mx, (int)adj[i].size());
	if(mx <= 2) {
		int p = -1;
		rep(i, 1, n) if(adj[i].size() == 1) p = i;
		int las = p;
		p = adj[p][0];
		int c1 = (a[las] != a[p]) - (a[las] != b[las]), c2 = (b[las] != b[p]);
		while(adj[p].size() > 1) {
			int v = adj[p][0] ^ adj[p][1] ^ las;
			c1 += a[p] != a[v];
			c2 += b[p] != b[v];
			las = p;
			p = v;
		}
		cout << (c1 >= c2 ? "TAK" : "NIE") << "\n";
		return;
	}
	f = 1;
	rep(i, 1, n) f &= a[i] == b[i];
	if(f == 1) {
		cout << "TAK" << "\n";
		return;
	}
	dfs(1, 0);
	f = 1;
	rep(i, 2, n) f &= (b[i] ^ d[i]) == (b[i-1] ^ d[i-1]);
	cout << (f ? "NIE" : "TAK") << "\n";
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

