
// Problem: P5305 [GXOI/GZOI2019]旧词
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5305
// Memory Limit: 500 MB
// Time Limit: 1000 ms
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

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
const ll mod = 998244353;
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

const int N = 5e4 + 5;

struct Opt {
	int x, y, p;
};

ll sum1[N << 2], sum2[N << 2], lazy[N << 2];
int rt[N], cnt;
int dfn[N], dep[N], fat[N], siz[N], top[N], son[N], sgn[N], dfncnt, sgncnt;
int head[N], nxt[N << 1], to[N << 1], tot;
ll ans[N];
Opt qry[N << 1];
int n, m, k;
ll delta[N], seg[N];

void AddEdge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

void Dfs1(int u, int fa) {
	fat[u] = fa;
	dep[u] = dep[fa] + 1;
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	chkmns(delta[u], qpow(dep[u], k), qpow(dep[u] - 1, k));
	debug("delta[{}] = {}\n", u, delta[u]);
	for(rg int i = head[u]; i; i = nxt[i]) {
		rg int v = to[i];
		if(v != fa) {
			Dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

void Dfs2(int u, int fa) {
	if(u != son[fa]) top[u] = u;
	else top[u] = top[fa];
	seg[sgn[u] = ++sgncnt] = delta[u];
	if(!son[u]) return;
	Dfs2(son[u], u);
	for(rg int i = head[u]; i; i = nxt[i]) {
		rg int v = to[i];
		if(v != fa && v != son[u]) {
			Dfs2(v, u);
		}
	}
}

inline void Lazy(int cur, int x) {
	chkadd(sum1[cur], 1ll * x * sum2[cur] % mod);
	lazy[cur] += x;
}

inline void PushDown(int cur) {
	if(lazy[cur]) {
		Lazy(cur << 1, lazy[cur]);
		Lazy(cur << 1 | 1, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void PushUp(int cur) {
	chkadd(sum1[cur], sum1[cur << 1], sum1[cur << 1 | 1]);
}

inline void Add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

inline ll Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum1[cur];
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg ll res = 0;
	if(ql <= mid) chkadd(res, Sum(cur << 1, ql, qr, l, mid));
	if(mid < qr) chkadd(res, Sum(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

inline void build(int cur, int l, int r) {
	if(l == r) return sum2[cur] = seg[l], void();
	rg int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	chkadd(sum2[cur], sum2[cur << 1], sum2[cur << 1 | 1]);
	debug("sum2[{}] [{},{}] = {}\n", cur, l, r, sum2[cur]);
}

void RouteAdd(int x, int y, int z) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		debug("adding [{},{}]\n", sgn[top[x]], sgn[x]);
		Add(1, sgn[top[x]], sgn[x], z, 1, n);
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	debug("adding [{},{}]\n", sgn[x], sgn[y]);
	Add(1, sgn[x], sgn[y], z, 1, n);
}

int RouteSum(int x, int y) {
	rg int res = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		debug("qry [{},{}]={}\n", sgn[top[x]], sgn[x], Sum(1, sgn[top[x]], sgn[x], 1, n));
		res = (res + Sum(1, sgn[top[x]], sgn[x], 1, n)) % mod;
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
		debug("qry [{},{}]={}\n", sgn[x], sgn[y], Sum(1, sgn[x], sgn[y], 1, n));
	res = (res + Sum(1, sgn[x], sgn[y], 1, n)) % mod;
	return res;
}

int main() {
	fastio::qread(n, m, k);
	rep(i, 2, n) {
		int fa; fastio::qread(fa);
		AddEdge(fa, i);
	}
	Dfs1(1, 0);
	Dfs2(1, 0);
	build(1, 1, n);
	rep(i, 1, m) {
		fastio::qread(qry[i].x, qry[i].y);
		qry[i].p = i;
	}
	sort(qry + 1, qry + 1 + m, [](const Opt& x, const Opt& y) {
		return x.x < y.x;
	});
	rep(i, 1, m) {
		rep(x, qry[i-1].x + 1, qry[i].x) RouteAdd(1, x, 1);
		ans[qry[i].p] = RouteSum(1, qry[i].y);
	}
	rep(i, 1, m) fastio::qwrite(ans[i], '\n');
  fastio::flush();
  return 0;
}
