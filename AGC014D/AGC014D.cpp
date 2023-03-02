// Problem: D - Black and White Tree
// Contest: AtCoder - AtCoder Grand Contest 014
// URL: https://atcoder.jp/contests/agc014/tasks/agc014_d
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Creaate Time: 
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

int n;
set<int> adj[N];
int cnt[N];
bool vis[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].insert(v), adj[v].insert(u);
	}
	queue<int> q;
	rep(u, 1, n) if(adj[u].size() == 1) q.push(u), ++cnt[*adj[u].begin()];
	rep(i, 1, n) if(cnt[i] >= 2) {
		cout << "First" << "\n";
		return 0;
	}
	
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(vis[u]) continue;
		int v = *adj[u].begin();
		adj[u].erase(v);
		adj[v].erase(u);
		vis[v] = 1;
		for(int f : adj[v]) {
			adj[f].erase(v);
			if(adj[f].size() == 1) {
				int ff = *adj[f].begin();
				if(++cnt[ff] >= 2) {
					cout << "First" << "\n";
					return 0;
				}
				q.push(f);
			}
		}
		adj[v].clear();
	}

	cout << "Second" << "\n";
	
	return 0;
}
