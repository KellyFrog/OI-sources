
// Problem: P4592 [TJOI2018]异或
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4592
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
const int mod =2017;

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

const int N = 1e5 + 5;

int rt1[N], rt2[N];
int sum[N << 6], lson[N << 6], rson[N << 6], cnt;
int anc[N][21], dep[N];
int dfn[N], siz[N], dfncnt;
int a[N];
int n, q;
vector<int> adj[N];

inline void insert(int& rt, int old, int x, int pos) {
	rt = ++cnt;
	sum[rt] = sum[old] + 1;
	if(pos == -1) return;
	if(!(x & (1 << pos))) {
		rson[rt] = rson[old];
		insert(lson[rt], lson[old], x, pos - 1);
	} else {
		lson[rt] = lson[old];
		insert(rson[rt], rson[old], x, pos - 1);
	}
}

inline int getans(int rt1, int rt2, int rt3, int rt4, int x, int pos) {
	if(pos == -1) return 0;
	bool has0 = sum[lson[rt1]] + sum[lson[rt2]] - sum[lson[rt3]] - sum[lson[rt4]];
	bool has1 = sum[rson[rt1]] + sum[rson[rt2]] - sum[rson[rt3]] - sum[rson[rt4]];
	debug("on x={} digit={} x[d]={} has0={} has1={}\n", x, pos, x & (1 << pos), has0, has1);
	if(x & (1 << pos)) {
		if(has0) return debug("L\n"), getans(lson[rt1], lson[rt2], lson[rt3], lson[rt4], x, pos - 1) + (1 << pos);
		else return getans(rson[rt1], rson[rt2], rson[rt3], rson[rt4], x, pos - 1);
	} else {
		if(has1) return getans(rson[rt1], rson[rt2], rson[rt3], rson[rt4], x, pos - 1) + (1 << pos);
		else return debug("L\n"), getans(lson[rt1], lson[rt2], lson[rt3], lson[rt4], x, pos - 1);
	}
}

inline void dfs(int u, int fa) {
	anc[u][0] = fa;
	dep[u] = dep[fa] + 1;
	rep(i, 1, 20) anc[u][i] = anc[anc[u][i-1]][i-1];
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	insert(rt1[u], rt1[fa], a[u], 30);
	insert(rt2[dfn[u]], rt2[dfn[u]-1], a[u], 30);
	debug("insert {} to rt1[{}]\n", a[u], u);
	debug("insert {} to rt2[{}]\n", a[u], dfn[u]);
	for(int v : adj[u]) {
		if(v != fa) dfs(v, u), siz[u] += siz[v];
	}
}

inline int LCA(int x, int y) {
  if(dep[x] < dep[y]) swap(x, y);
  per(i, 0, 20) if(dep[anc[x][i]] >= dep[y]) x = anc[x][i];
  if(x == y) return x;
  per(i, 0, 20) if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
  return anc[x][0];
}

int main() {
	fastio::qread(n, q);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n-1) {
		int u, v;
		fastio::qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	while(q--) {
		int op, x, y, z;
		fastio::qread(op, x, y);
		if(op == 1) {
			debug("query = {} {}\n", dfn[x] + siz[x] - 1, dfn[x] - 1);
			fastio::qwrite(getans(rt2[dfn[x] + siz[x] - 1], 0, rt2[dfn[x] - 1], 0, y, 30), '\n');
		} else {
			fastio::qread(z);
			int lca = LCA(x, y);
			fastio::qwrite(getans(rt1[x], rt1[y], rt1[lca], rt1[anc[lca][0]], z, 30), '\n');
		}
	}
  fastio::flush();
  return 0;
}
