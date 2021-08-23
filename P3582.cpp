
// Problem: P3582 [POI2015]KIN
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3582?contestId=43450
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

const int N = 1e6 + 5;

#define int ll

ll mx[N<<2], lazy[N<<2];
int lastpos[N], last[N];
int a[N], b[N];
int n, m;

inline void Lazy(int cur, ll x) {
	mx[cur] += x;
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
	mx[cur] = max(mx[cur << 1], mx[cur << 1 | 1]);
}

inline void Add(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) return Lazy(cur, x);
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	
	PushUp(cur);
}

signed main() {
	fastio::qread(n, m);
	rep(i, 1, n) {
		fastio::qread(a[i]);
		last[i] = lastpos[a[i]];
		lastpos[a[i]] = i;
	}
	rep(i, 1, m) fastio::qread(b[i]);
	ll ans = 0;
	rep(R, 1, n) {
		Add(1, last[R] + 1, R, b[a[R]], 1, n);
		if(last[R]) Add(1, last[last[R]] + 1, last[R], -b[a[R]], 1, n);
		ans = max(ans, mx[1]);
	}
	cout << ans << "\n";
  fastio::flush();
  return 0;
}