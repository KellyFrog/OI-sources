// Problem: E - Rearranging
// Contest: AtCoder - AtCoder Grand Contest 010
// URL: https://atcoder.jp/contests/agc010/tasks/agc010_e
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

const int N = 2e3 + 5;
const int M = N * 10;

int n, a[N], ind[N];
vector<int> adj[N];
bool vis[N];

inline void dfs(int u) {
	vis[u] = 1;
	rep(i, 1, n) if(__gcd(a[u], a[i]) != 1 && !vis[i]) {
		adj[u].pb(i);
		++ind[i];
		dfs(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1);
	rep(i, 1, n) if(!vis[i]) dfs(i);
	priority_queue<int> pq;
	rep(i, 1, n) if(!ind[i]) pq.push(i);
	while(!pq.empty()) {
		int u = pq.top(); pq.pop();
		cout << a[u] << " ";
		for(int v : adj[u]) if(--ind[v] == 0) pq.push(v);
	}
	rep(i, 1, n) assert(ind[i] == 0);
	cout << "\n";

	return 0;
}

