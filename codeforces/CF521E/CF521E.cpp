// Problem: CF521E Cycling City
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF521E
// Memory Limit: 250 MB
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

const int N = 2e5 + 5;

int n, m;
vector<int> adj[N];
vector<pair<int, int>> e;
int uni[N], pos[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		int x = find(u), y = find(v);
		if(x != y) {
			adj[u].pb(v);
			adj[v].pb(u);
			uni[x] = y;
		} else {
			e.emplace_back(u, v);
		}
	}
	rep(i, 1, n) if(!fat[i]) dfs(i, -1);

	return 0;
}
