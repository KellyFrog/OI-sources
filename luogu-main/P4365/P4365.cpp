// Problem: P4365 [九省联考 2018] 秘密袭击 coat
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4365
// Memory Limit: 1000 MB
// Time Limit: 7000 ms
// Create Time: 2022-03-05 22:09:31
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

/*
 * Author: chenkaifeng @BDFZ
 */
 
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

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const int mod = 1e9 + 7;
const int mod = 64123;
std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 1670;

int n, k, w;
int a[N];
vector<int> adj[N];
int id[N], f[N][N], tmp[N], siz[N];
bool vis[N];

inline void dfssiz(int u, int fa) {
	siz[u] = 1;
	for(int v : adj[u]) {
		if(!vis[v] && v != fa) dfssiz(v, u), siz[u] += siz[v];
	}
}

inline void dfs(int u, int fa) {
	rep(i, 0, k) f[u][i] = 0;
	f[u][vis[u] ? 0 : 1] = 1;
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			++f[v][0];
			rep(i, 0, k) tmp[i] = f[u][i], f[u][i] = 0;
			rep(i, 0, min(k, siz[u])) rep(j, 0, min(k, siz[v])) {
				if(i + j > k) break;
				f[u][i+j] = (1ll * tmp[i] * f[v][j] + f[u][i+j]) % mod;
			}
			siz[u] += siz[v];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k >> w;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n-1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rep(i, 1, n) id[i] = i;
	sort(id + 1, id + n + 1, [&](int i, int j) { return a[i] == a[j] ? i < j : a[i] < a[j]; });
	
	int ans = 0;
	rep(i, 1, n) {
		if(n - i + 1 < k) break;
		int rt = id[i];
		dfs(rt, 0);
		ans = (1ll * f[rt][k] * a[rt] + ans) % mod;
	
		vis[rt] = 1;
	}
	
	cout << ans << "\n";
	
	return 0;
}
