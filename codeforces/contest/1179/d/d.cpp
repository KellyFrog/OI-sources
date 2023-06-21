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
const long double eps = 1e-8;

int n;
vector<int> adj[N];
ll f[N], ans = 1e18;
int siz[N];
int que[N], ph = 1, pt = 0;

inline ll X(int u) { return -(f[u] + 1ll * siz[u] * siz[u] - 2ll * n * siz[u]); }
inline ll Y(int u) { return 2ll * siz[u]; }
inline long double slope(int x, int y) {
	if(Y(x) == Y(y)) return X(x) < X(y) ? 1e18 : -1e18;
	return (long double)(X(x) - X(y)) / (Y(x) - Y(y));
}

void dfs(int u, int fa) {
	for(int v : adj[u]) if(v != fa) dfs(v, u);
	vector<pair<int, int>> vec;
	vec.emplace_back(0, u);
	for(int v : adj[u]) if(v != fa) vec.emplace_back(siz[v], v);
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	ph = 1, pt = 0;
	auto calc = [&](int u, int v) {
		return f[u] + f[v] + 1ll * (n - siz[u] - siz[v]) * (n - siz[u] - siz[v]);
	};
	for(auto [sz, nd] : vec) {
		while(ph < pt && calc(nd, que[ph]) >= calc(nd, que[ph+1])) ++ph;
		if(ph <= pt) {
			int v = que[ph];
			ans = min(ans, f[nd] + f[v] + 1ll * (n - sz - siz[v]) * (n - sz - siz[v]));
		}
		while(ph < pt && slope(que[pt], que[pt-1]) < slope(nd, que[pt-1])) --pt;
		que[++pt] = nd;
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
