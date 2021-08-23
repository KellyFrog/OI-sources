
// Problem: P4146 序列终结者
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4146?contestId=44762
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

const int N = 1e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

#define int long long

struct TreeNode {
  int pri, siz, rev;
  ll max, lazy, val;
  int son[2];
  TreeNode(int pri0 = rand(), int siz0 = 0, int lson = 0, int rson = 0,
           int max0 = 0, int lazy0 = 0)
      : pri(pri0), siz(siz0), max(max0), lazy(lazy0) {
    son[0] = lson;
    son[1] = rson;
    lazy = 0, rev = 0;
  }
};

TreeNode tree[N];
int n, m;

#define pri(x) tree[x].pri
#define siz(x) tree[x].siz
#define lazy(x) tree[x].lazy
#define max(x) tree[x].max
#define rev(x) tree[x].rev
#define son(x, p) tree[x].son[p]
#define lson(x) son(x, 0)
#define rson(x) son(x, 1)
#define val(x) tree[x].val

inline void setrev(int cur) {
  if (cur == 0) return;
  rev(cur) ^= 1;
  swap(lson(cur), rson(cur));
}

inline void setlazy(int cur, ll x) {
  if (cur == 0) return;
  lazy(cur) += x;
  val(cur) += x;
  max(cur) += x;
}

inline void pushdown(int cur) {
  if (cur == 0) return;
  if (rev(cur)) {
    setrev(lson(cur));
    setrev(rson(cur));
    rev(cur) = 0;
  }
  if (lazy(cur)) {
    setlazy(lson(cur), lazy(cur));
    setlazy(rson(cur), lazy(cur));
    lazy(cur) = 0;
  }
}

template<typename T>
T Max(T x, T y) {
	return x > y ? x : y;
}

inline void pushup(int cur) {
	if(cur == 0) return;
  siz(cur) = siz(lson(cur)) + siz(rson(cur)) + 1;
  max(cur) = val(cur);
  if(lson(cur)) chkmax(max(cur), max(lson(cur)));
  if(rson(cur)) chkmax(max(cur), max(rson(cur)));
}

inline void merge(int& rt, int x, int y) {
  if (x == 0 || y == 0) return rt = x + y, void();
  if (pri(x) < pri(y)) {
    pushdown(x);
    rt = x;
    merge(rson(rt), rson(x), y);
    pushup(x);
  } else {
    pushdown(y);
    rt = y;
    merge(lson(rt), x, lson(y));
    pushup(y);
  }
}

inline void split(int rt, int k, int& x, int& y) {
  if (rt == 0) return x = 0, y = 0, void();
  pushdown(rt);
  if (siz(lson(rt)) + 1 <= k) {
    x = rt;
    split(rson(rt), k - siz(lson(rt)) - 1, rson(x), y);
  } else {
    y = rt;
    split(lson(rt), k, x, lson(y));
  }
  pushup(rt);
}

int tot;
int rt;

inline int newnode() {
  tot++;
  tree[tot] = TreeNode();
  lazy(tot) = rev(tot) = 0;
  siz(tot) = 1;
  max(tot) = 0;
  return tot;
}

inline void insert() {
  int cur = newnode();
  merge(rt, rt, cur);
}

void dfs(int cur) {
	if(cur == 0) return;
	pushdown(cur);
	debug("[{}] lson={} rson={} siz={} val={} max={}\n", cur, lson(cur), rson(cur), siz(cur), val(cur), max(cur));
	dfs(lson(cur));
	dfs(rson(cur));
}

//调不动了，哪错了啊

signed main() {
  srand(time(0));
  // max(0) = -inf;
  siz(0) = 0;
  fastio::qread(n, m);
  rep(i, 1, n) insert();
  rep(i, 1, m) {
    int op, l, r;
    fastio::qread(op, l, r);
    if (op == 1) {
      ll val;
      fastio::qread(val);
      int x = 0, y = 0, z = 0;
      split(rt, r, x, y);
      split(x, l - 1, x, z);
      setlazy(z, val);
      merge(rt, x, z);
      merge(rt, rt, y);
    } else if (op == 2) {
      int x = 0, y = 0, z = 0;
      split(rt, r, x, y);
      split(x, l - 1, x, z);
      cerr << "--\n"; dfs(x); cerr << "\n";
      cerr << "--\n"; dfs(y); cerr << "\n";
      cerr << "--\n"; dfs(z); cerr << "\n";
      setrev(z);
      merge(rt, x, z);
      merge(rt, rt, y);
    } else {
      int x = 0, y = 0, z = 0;
      split(rt, r, x, y);
      split(x, l - 1, x, z);
      fastio::qwrite(max(z), '\n');
      merge(rt, x, z);
      merge(rt, rt, y);
    }
  }
  fastio::flush();
  return 0;
}