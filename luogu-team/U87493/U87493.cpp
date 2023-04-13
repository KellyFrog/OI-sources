
// Problem: U87493 移动服务(service)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U87493
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// Author: Chenkaifeng

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
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
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

ll qpow(ll x, ll p, ll mod) {
  rg ll base = x, res = 1;
  while (p) {
    if (p & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    p >>= 1;
  }
  return res;
}

const int N = 2e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct Segtree {
  ll mi[N << 2], lazy[N << 2];
  Segtree() { memset(mi, 0x3f, sizeof mi); }
  inline void Lazy(int cur, ll x) {
  	lazy[cur] += x;
  	mi[cur] += x;
  }
  inline void PushDown(int cur) {
  	if(lazy[cur]) {
  		Lazy(cur << 1, lazy[cur]);
  		Lazy(cur << 1 | 1, lazy[cur]);
  		lazy[cur] = 0;
  	}
  }
  inline void PushUp(int cur) {
  	mi[cur] = min(mi[cur << 1], mi[cur << 1 | 1]);
  }
  ll query(int cur, int ql, int qr, int l, int r) {
  	if(ql <= l && r <= qr) return mi[cur];
  	PushDown(cur);
  	rg int mid = l + r >> 1;
  	rg ll res = inf;
  	if(ql <= mid) res = min(res, query(cur << 1, ql, qr, l, mid));
  	if(mid < qr) res = min(res, query(cur << 1 | 1, ql, qr, mid + 1, r));
  	return res;
  }
  void add(int cur, int ql, int qr, ll x, int l, int r) {
  	if(ql <= l && r <= qr) return Lazy(cur, x), void();
  	PushDown(cur);
  	rg int mid = l + r >> 1;
  	if(ql <= mid) add(cur << 1, ql, qr, x, l, mid);
  	if(mid < qr) add(cur << 1 | 1, ql, qr, x, mid + 1, r);
  	PushUp(cur);
  }
  void modify(int cur, int p, ll x, int l, int r) {
  	if(l == r) return mi[cur] = min(mi[cur], x), void();
  	PushDown(cur);
  	rg int mid = l + r >> 1;
  	if(p <= mid) modify(cur << 1, p, x, l, mid);
  	else modify(cur << 1 | 1, p, x, mid + 1, r);
  	PushUp(cur);
  }
};

Segtree t1, t2;

int n, q, a, b;
int qr[N];

//dp[i] = dp[i] + abs(qr[i] - qr[i-1])
//dp[qr[i]] = min{dp[j] + abs(j - qr[i])}

int main() {
  fastio::qread(n, q, a, b);
  rep(i, 1, q) fastio::qread(qr[i]);
  rep(i, 1, n) {
  	t1.modify(1, i, min(abs(qr[1] - a) + abs(b - i), abs(qr[1] - b) + abs(a - i)) - i, 1, n);
  	t2.modify(1, i, min(abs(qr[1] - a) + abs(b - i), abs(qr[1] - b) + abs(a - i)) + i, 1, n);
  }
  rep(i, 2, q) {
  	ll x = min(
  		t1.query(1, 1, qr[i], 1, n) + qr[i],
  		t2.query(1, qr[i], n, 1, n) - qr[i]
  	);
  	t1.add(1, 1, n, abs(qr[i] - qr[i-1]), 1, n);
  	t2.add(1, 1, n, abs(qr[i] - qr[i-1]), 1, n);
  	t1.modify(1, qr[i-1], x - qr[i-1], 1, n);
  	t2.modify(1, qr[i-1], x + qr[i-1], 1, n);
  }
  ll ans = inf;
  rep(i, 1, n) ans = min({ans, t1.query(1, i, i, 1, n) + i, t2.query(1, i, i, 1, n) - i});
  fastio::qwrite(ans, '\n');
  fastio::flush();
  return 0;
}