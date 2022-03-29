
// Problem: P4197 Peaks
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4197
// Memory Limit: 125 MB
// Time Limit: 2000 ms
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
const int M = 1e6 + 5;

struct Node {
  int op, w, x, y, pos;
} qry[M << 1];

int n, m, q;
int rt[N], lson[N << 5], rson[N << 5], sum[N << 5], tot;
int h[N], a[M << 1], siz;
int fa[N];

inline void add(int& rt, int p, int x, int l, int r) {
  if (rt == 0) rt = ++tot;
  sum[rt] += x;
  if (l == r) return;
  rg int mid = l + r >> 1;
  if (p <= mid)
    add(lson[rt], p, x, l, mid);
  else
    add(rson[rt], p, x, mid + 1, r);
}

inline int kth(int rt, int k, int l, int r) {
	if(sum[rt] < k) return 0;
  if (l == r) return l;
  rg int mid = l + r >> 1;
  if (k <= sum[rson[rt]])
    return kth(rson[rt], k, mid+1, r);
  else
    return kth(lson[rt], k - sum[rson[rt]], l, mid);
}

inline void merge(int& cur, int rt, int l, int r) {
  if (cur == 0 || rt == 0) return cur += rt, void();
  rg int mid = l + r >> 1;
  sum[cur] += sum[rt];
  merge(lson[cur], lson[rt], l, mid);
  merge(rson[cur], rson[rt], mid + 1, r);
}

inline int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int ans[N];

int main() {
  fastio::qread(n, m, q);
  rep(i, 1, n) fastio::qread(h[i]);
  rep(i, 1, n) a[++siz] = h[i];
  rep(i, 1, m) qry[i].op = 1, fastio::qread(qry[i].x, qry[i].y, qry[i].w),
               a[++siz] = qry[i].w;
  rep(i, m + 1, m + q) qry[i].pos = i - m, qry[i].op = 2,
                       fastio::qread(qry[i].x, qry[i].w, qry[i].y),
                       a[++siz] = qry[i].w;
  sort(a + 1, a + 1 + siz);
  int s = unique(a + 1, a + 1 + siz) - (a + 1);
#define getpos(x) x = lower_bound(a + 1, a + 1 + s, x) - a
  rep(i, 1, n) getpos(h[i]);
  rep(i, 1, m) getpos(qry[i].w);
  rep(i, m + 1, m + q) getpos(qry[i].w);
  sort(qry + 1, qry + 1 + m + q, [](const Node& x, const Node& y) {
    return x.w == y.w ? x.op < y.op : x.w < y.w;
  });
  a[0] = -1;
  rep(i, 1, n) fa[i] = i, add(rt[i], h[i], 1, 1, s);
  rep(i, 1, m + q) {
    if (qry[i].op == 1) {
      int x = find(qry[i].x);
      int y = find(qry[i].y);
      if (x == y) continue;
      fa[y] = x;
      merge(rt[x], rt[y], 1, s);
      debug("merged x={} y={} with fa[x]={} fa[y]={}, weight={}\n", qry[i].x, qry[i].y, x, y, qry[i].w);
    } else {
    	int x = find(qry[i].x), k = qry[i].y;
    	ans[qry[i].pos] = a[kth(rt[x], k, 1, s)];
    	debug("queried ans[{}] x={} k={} with fa[x]={}, ans={}, weight={}\n", qry[i].pos, qry[i].x, k, x, ans[qry[i].pos], qry[i].w);
    }
  }
  rep(i, 1, q) fastio::qwrite(ans[i], '\n');
  fastio::flush();
  return 0;
}