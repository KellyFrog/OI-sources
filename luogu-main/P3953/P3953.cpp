// Problem: P3953 [NOIP2017 提高组] 逛公园
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3953
// Memory Limit: 500 MB
// Time Limit: 3000 ms
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
inline void qread(T1& x, T2&... ls) {
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

void debug(const char* s) { cerr << s; }
template <typename T1, typename... T2>
void debug(const char* s, const T1 x, T2... ls) {
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

ll mod = 1e9 + 7;
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

const int N = 1e5 + 5;
const int M = 2e5 + 5;
const int K = 55;

int head[N], nxt[M], to[M], tot;
ll wgt[M];
ll dis[N];
ll f[N][K]; bool solved[N][K];
int ind[N], vis[N], ord[N];
int n, m, k;

inline void addedge(int u, int v, ll w) {
  nxt[++tot] = head[u];
  to[tot] = v;
  wgt[tot] = w;
  head[u] = tot;
}

inline bool topo() {
  rep(u, 1, n) {
    for (int e = head[u]; e; e = nxt[e]) {
      if (wgt[e] == 0) ind[to[e]]++;
    }
  }
  int cnt = 0;
  bool ret = 1;
  queue<int> q;
  rep(i, 1, n) if (!ind[i]) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    if (u == n) ret = 0;
    ord[u] = ++cnt;
    for (int e = head[u]; e; e = nxt[e]) {
      if (wgt[e] == 0)
        if (--ind[to[e]] == 0) q.push(to[e]);
    }
  }
  return ret;
}

inline void dij() {
  priority_queue<pair<ll, int>, vector<pair<ll, int> >,
                 greater<pair<ll, int> > >
      q;
  q.push(mp(dis[1] = 0, 1));
  while (!q.empty()) {
    int u = q.top().se;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int e = head[u]; e; e = nxt[e]) {
      if (dis[to[e]] > dis[u] + wgt[e]) {
        q.push(mp(dis[to[e]] = dis[u] + wgt[e], to[e]));
      }
    }
  }
}

inline void solve() {
  memset(head, 0, sizeof head);
  memset(solved, 0, sizeof solved);
  memset(dis, 0x3f, sizeof dis);
  memset(f, 0, sizeof f);
  memset(ind, 0, sizeof ind);
  memset(vis, 0, sizeof vis);
  memset(ord, -1, sizeof ord);
  fastio::qread(n, m, k, mod);
  rep(i, 1, m) {
    int u, v;
    ll w;
    fastio::qread(u, v, w);
    addedge(u, v, w);
  }
  if (topo()) return puts("-1"), void();
  dij();
  ll ans = 0;
  f[1][0] = 1;
  priority_queue<
  pair<pair<int, int>, int>, vector<pair<pair<int, int>, int> >, greater<pair<pair<int, int>, int> > > q;
  q.push(mp(mp(0, ord[1]), 1));
  while (!q.empty()) {
    int u = q.top().se;
    int x = q.top().fi.fi;
    q.pop();
    if(solved[u][x]) continue;
    solved[u][x] = 1;
    for(int e = head[u]; e; e = nxt[e]) {
    	int v = to[e];
    	if(ord[v] == -1) continue;
    	ll w = wgt[e];
    	ll dis0 = dis[u] + x + w - dis[v];
    	if(dis0 > k) continue;
    	chkadd(f[v][dis0], f[u][x]);
    	q.push(mp(mp(dis0, ord[v]), v));
    }
  }
  rep(i, 0, k) chkadd(ans, f[n][i]);
  printf("%lld\n", ans);
}

int main() {
  int t;
  fastio::qread(t);
  while (t--) solve();
  fastio::flush();
  return 0;
}
