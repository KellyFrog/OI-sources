
// Problem: P4211 [LNOI2014]LCA
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4211
// Memory Limit: 125 MB
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
#define rg register
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

void debug(const char *s) { cerr << s; }
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

const int N = 5e4 + 5;
const ll mod = 201314;

struct Opt {
	int p, x, tim, op;
};

ll sum[N << 2], lazy[N << 2];
int rt[N], cnt;
int dfn[N], dep[N], fat[N], siz[N], top[N], son[N], sgn[N], dfncnt, sgncnt;
int head[N], nxt[N << 1], to[N << 1], tot;
int ans[N];
Opt qry[N << 1];
int n, m;

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
	sgn[u] = ++sgncnt;
	if(!son[u]) return;
	Dfs2(son[u], u);
	for(rg int i = head[u]; i; i = nxt[i]) {
		rg int v = to[i];
		if(v != fa && v != son[u]) {
			Dfs2(v, u);
		}
	}
}

inline void Lazy(int cur, int x, int l, int r) {
	sum[cur] = (sum[cur] + 1ll * x * (r - l + 1)) % mod;
	lazy[cur] = (lazy[cur] + x) % mod;
}

inline void PushDown(int cur, int l, int r) {
	if(lazy[cur]) {
		rg int mid = l + r >> 1;
		Lazy(cur << 1, lazy[cur], l, mid);
		Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
		lazy[cur] = 0;
	}
}

inline void PushUp(int cur) {
	sum[cur] = (sum[cur << 1] + sum[cur << 1 | 1]) % mod;
}

void Add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x, l, r), void();
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

int Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res = Sum(cur << 1, ql, qr, l, mid);
	if(mid < qr) res = (res + Sum(cur << 1 | 1, ql, qr, mid + 1, r)) % mod;
	return res;
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
	fastio::qread(n, m);
	rep(i, 2, n) {
		int x; fastio::qread(x); x++;
		AddEdge(x, i);
	}
	Dfs1(1, 0);
	Dfs2(1, 0);
	rep(i, 1, n) debug("{} : {} {} {} {} {} {}\n", i, dfn[i], siz[i], sgn[i], top[i], fat[i], son[i]);
	int pt = 0;
	rep(i, 1, m) {
		int l, r, z;
		fastio::qread(l, r, z);
		l++, r++, z++;
		pt++, qry[pt].p = i, qry[pt].x = z, qry[pt].tim = r, qry[pt].op = 1;
		pt++, qry[pt].p = i, qry[pt].x = z, qry[pt].tim = l-1, qry[pt].op = -1;
	}
	sort(qry + 1, qry + 1 + pt, [](Opt x, Opt y) {
		return x.tim < y.tim;
	});
	rep(i, 1, pt) {
		debug("qry[{}]={} {} {} {}\n", i, qry[i].tim, qry[i].p, qry[i].x, qry[i].op);
		if(qry[i].tim == 0) continue;
		if(qry[i].tim != qry[i-1].tim) {
			rep(j, qry[i-1].tim + 1, qry[i].tim) debug("adding={}...\n", j), RouteAdd(1, j, 1);
		}
		debug("got res={}\n", RouteSum(qry[i].x, 1));
		ans[qry[i].p] += qry[i].op * RouteSum(qry[i].x, 1);
	}
	rep(i, 1, m) fastio::qwrite(ans[i] < 0 ? ans[i] + mod : ans[i], '\n');
  fastio::flush();
  return 0;
}