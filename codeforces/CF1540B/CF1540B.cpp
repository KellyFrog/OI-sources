// Problem: CF1540B Tree Array
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1540B
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second

#if __cplusplus < 201703L
#define rg register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 200 + 5;
const ll inv2 = (mod + 1) >> 1;

vector<int> adj[N], son[N];
int LCA[N][N], dep[N], fat[N];
int n;
ll dp[N][N], sum[N][N];
ll ans;

inline void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	fat[u] = fa;
	son[u].pb(u);
	LCA[u][u] = u;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			for(int uu : son[u]) for(int vv : son[v]) LCA[uu][vv] = LCA[vv][uu] = u;
			for(int vv : son[v]) son[u].pb(vv);
		}
	}
}

int main() {
	fastio::qread(n);
	rep(i, 1, n-1) {
		int u, v;
		fastio::qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	dp[0][0] = 1;
	rep(i, 0, n) rep(j, 0, n) chkadd(dp[i+1][j], dp[i][j] * inv2 % mod), chkadd(dp[i][j+1], dp[i][j] * inv2 % mod);
	rep(i, 0, n) {
		if(i) sum[i][0] = dp[i][0];
		ll inv2k = 1;
		rep(j, 1, n) {
			inv2k = inv2k * inv2 % mod;
			chkadd(sum[i][j], sum[i][j-1], dp[i][j] * inv2k % mod);
		}
	}
	rep(u, 1, n) rep(v, 1, u-1) {
		rep(x, 1, n) {
			int lca1 = LCA[u][v], lca2 = LCA[u][x], lca3 = LCA[v][x];
			int st = -1;
			if(lca2 != lca1 && lca3 != lca1) st = lca1;
			else if(lca3 == lca1) st = lca2;
			else if(lca2 == lca1) st = lca3;
			int dist1 = dep[u] + dep[st] - 2 * dep[LCA[u][st]];
			int dist2 = dep[v] + dep[st] - 2 * dep[LCA[v][st]];
			debug("solve: [u={}, v={}, x={}] st={} dist=[{},{}] ans={} ", u, v, x, st, dist1, dist2, ans);
			if(dist1 == 0) chkadd(ans, 1ll);
			else if(dist2 == 0);
			else chkadd(ans, sum[dist1][dist2-1]);
			debug("ans'={}\n", ans);
		}
	}
	debug("original ans = {}\n", ans);
	ans = ans * qpow(n, mod-2) % mod;
	cout << ans << "\n";
  fastio::flush();
  return 0;
}
