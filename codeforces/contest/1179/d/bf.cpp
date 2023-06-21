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

const int N = 5e5 + 5;

int n;
vector<int> adj[N];
ll f[N], ans = 1e18;
int siz[N];
int que[N], ph = 1, pt = 0;

inline ll X(int u) { return f[u] + 1ll * siz[u] * siz[u] - 2ll * n * siz[u]; }
inline ll Y(int u) { return 2ll * siz[u]; }

void dfs(int u, int fa) {
	for(int v : adj[u]) if(v != fa) dfs(v, u);
	vector<int> vec;
	vec.pb(u);
	for(int v : adj[u]) if(v != fa) vec.pb(v);
	for(int i = 0; i < vec.size(); ++i) for(int j = 0; j < i; ++j) {
		int u = vec[i], v = vec[j];

		ans = min(ans, f[u] + f[v] + 1ll * (n - siz[u] - siz[v]) * (n - siz[u] - siz[v]));
	}
	siz[u] = 1;
	for(int v : adj[u]) if(v != fa) siz[u] += siz[v];
	f[u] = 1ll * siz[u] * siz[u];
	for(int v : adj[u]) if(v != fa) f[u] = min(f[u], 1ll * (siz[u] - siz[v]) * (siz[u] - siz[v]) + f[v]);
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
	cout << (1ll * n * n - ans) / 2 + 1ll * n * (n-1) / 2 << "\n";
	
	return 0;
}
