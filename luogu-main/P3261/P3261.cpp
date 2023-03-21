
// Problem: P3261 [JLOI2015]城池攻占
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3261?contestId=41933
// Memory Limit: 250 MB
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

const int N = 1e6 + 5;
const ll inf = 1e18 + 5;

int head[N], nxt[N], to[N], tot;
vector<int> adj[N], atk[N];
ll a[N], c[N], h[N], v[N];
int rt[N<<1];
int lson[N<<1], rson[N<<1], dist[N<<1];
int st[N], ed[N], dep[N];
ll val[N<<1], add[N<<1], mul[N<<1];
//先乘后加
int n, m;
int cnt;
int ans[N];

inline void AddEdge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

inline void LazyAdd(int cur, ll x) {
	add[cur] += x;
	val[cur] += x;
}

inline void LazyMul(int cur, ll x) {
	add[cur] *= x;
	mul[cur] *= x;
	val[cur] *= x;
}

inline void PushDown(int cur) {
	if(mul[cur] != 1) {
		if(lson[cur]) LazyMul(lson[cur], mul[cur]);
		if(rson[cur]) LazyMul(rson[cur], mul[cur]);
		mul[cur] = 1;
	}
	if(add[cur]) {
		if(lson[cur]) LazyAdd(lson[cur], add[cur]);
		if(rson[cur]) LazyAdd(rson[cur], add[cur]);
		add[cur] = 0;
	}
}

void Merge(int& rt, int x, int y) {
	//debug("merging = {} {}\n", x, y);
	if(x == 0 || y == 0) return rt = x + y, void();
	if(val[x] > val[y]) swap(x, y);
	PushDown(x);
	rt = x;
	Merge(rson[x], rson[x], y);
	PushDown(lson[x]);
	PushDown(rson[x]);
	if(dist[lson[x]] < dist[rson[x]]) swap(lson[x], rson[x]);
	dist[x] = dist[rson[x]] + 1;
}

void Dfs(int u, int f) {
	//debug("dfs={} {}\n", u, f);
	dep[u] = dep[f] + 1;
	rt[u+m] = ++cnt;
	val[rt[u+m]] = inf;
	mul[rt[u+m]] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == f) continue;
		Dfs(v, u);
		Merge(rt[u+m], rt[u+m], rt[v+m]);
	}
	for(int x : atk[u]) {
		Merge(rt[u+m], rt[u+m], x);
	}
	while(rt[u+m] && val[rt[u+m]] < h[u]) {
		ed[rt[u+m]] = u;
		ans[u]++;
		PushDown(rt[u+m]);
		Merge(rt[u+m], lson[rt[u+m]], rson[rt[u+m]]);
	}
	if(a[u] == 0) {
		LazyAdd(rt[u+m], v[u]);
	} else {
		LazyMul(rt[u+m], v[u]);
	}
}

int main() {
	fastio::qread(n, m);
	cnt = m;
	rep(i, 1, n) fastio::qread(h[i]);
	rep(i, 2, n) {
		int fa; fastio::qread(fa, a[i], v[i]);
		AddEdge(fa, i);
	}
	rep(i, 1, m) {
		fastio::qread(val[i], st[i]);
		atk[st[i]].pb(i);
		rt[i] = i;
		mul[i] = 1;
	}
	Dfs(1, 0);
	rep(i, 1, n) fastio::qwrite(ans[i], '\n');
	rep(i, 1, m) fastio::qwrite(dep[st[i]] - dep[ed[i]], '\n');
  fastio::flush();
  return 0;
}