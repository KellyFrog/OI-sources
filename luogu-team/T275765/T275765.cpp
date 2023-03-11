// Problem: T275765 pars/ey
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T275765?contestId=85210
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-10-03 14:02:57
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

const int N = 5e3 + 5;
const int inf = 0x3f3f3f3f;

int n;
vector<int> adj[N];
int a[N];
int f[N][N], siz[N], tmp[N];

inline void dfs(int u, int fa) {
	siz[u] = 1;
	f[u][1] = 0;
	for(int v : adj[u]) if(v != fa) {
		dfs(v, u);
		memset(tmp, 0x3f, sizeof tmp);
		rep(i, 1, siz[u]) rep(j, 1, siz[v]) tmp[i+j] = min(tmp[i+j], f[u][i] + f[v][j]);
		memcpy(f[u], tmp, sizeof tmp);
		siz[u] += siz[v];
	}
	rep(i, 2, siz[u]) f[u][1] = min(f[u][1], f[u][i] + a[i]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 2, n) cin >> a[i];
	rep(i, 2, n) {
		int u, v; cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	memset(f, 0x3f, sizeof f);
	dfs(1, 0);
	cout << f[1][1] << "\n";
	
	return 0;
}
