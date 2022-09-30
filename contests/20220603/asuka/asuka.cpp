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

// const int N = 150;
// const int P = 998244353;

// int qpow(int x, ll p) {
// 	int res = 1, base = x;
// 	while(p) {
// 		if(p & 1) res = 1ll * res * base % p;
// 		base = 1ll * base * base % P;
// 		p >>= 1;
// 	}
// 	return res;
// }

// int n;
// vector<int> adj[N];
// int f[N][N][2][2], g[2][N][N][N];
// int fac[N], ifac[N];
// int dep[N];

// inline int cob(int n, int m) {
// 	assert(n >= m);
// 	return 1ll * fac[n] * ifac[m] % P * ifac[n-m] % P;
// }

// inline void dfs(int u, int fa) {
// 	f[u][1][1][1] = 1;
// 	for(int v : adj[u]) if(v != fa) dfs(v, u);
// 	for(int s : adj[u]) if(s != fa) {
// 		memset(g, 0, sizeof g);
// 		int t = 0;
// 		g[0][0][0][0] = 1;
// 		for(int v : adj[s]) {
// 			if(v != u) {

// 			}
// 		}
// 	}
// }

// int main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr), cout.tie(nullptr);
// 	cout << fixed << setprecision(15); 
// 	cerr << fixed << setprecision(15);
	
// 	cin >> n;
// 	rep(i, 2, n) {
// 		int u, v;
// 		cin >> u >> v;
// 		adj[u].pb(v);
// 		adj[v].pb(u);
// 	}

// 	ifac[0] = fac[0] = ifac[1] = fac[1] = 1;
// 	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % P;
// 	ifac[n] = qpow(fac[n], P - 2);
// 	per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % P;

// 	return 0;
// }

const int N = 21;
const int P = 998244353;

int n;
vector<int> adj[N];
int f[1<<N][N], fat[N];

inline void dfs(int u ,int fa) {
	fat[u] = fa;
	for(int v : adj[u]) if(v != fa) dfs(v, u);
}

bool check(int u, int v) {
	if(fat[u] == fat[v]) return 0;
	if(fat[fat[u]] == v || fat[fat[v]] == u) return 0;
	return 1;
}

int main() {
	freopen("asuka.in", "r", stdin);
	freopen("asuka.out", "w", stdout);
	cin >> n;
	rep(i, 2, n) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	rep(i, 1, n) f[1<<i-1][i] = 1;
	int u = (1 << n) - 1;
	rep(s, 1, u) {
		rep(i, 1, n) {
			if((s >> i - 1 & 1) == 0) continue;
			rep(j, 1, n) {
				if(s >> j - 1 & 1) continue;
				if(check(i, j)) f[s|1<<j-1][j] = (f[s|1<<j-1][j] + f[s][i]) % P;
			}
		}
	}
	int ans = 0;
	rep(i, 1, n) ans = (ans + f[u][i]) % P;
	cout << ans << "\n";
	return 0;
}