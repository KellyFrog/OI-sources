
// Problem: CF1477B Nezzar and Binary String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1477B?contestId=43450
// Memory Limit: 500 MB
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

const int N = 2e5 + 5;

int qL[N], qR[N];
char S[N], T[N];
int lazy[N << 2], sum[N << 2];
int n, m;

inline void Lazy(int cur, int x, int l, int r) {
  lazy[cur] = x;
  sum[cur] = (r - l + 1) * x;
}

inline void PushDown(int cur, int l, int r) {
  if (lazy[cur] != -1) {
    rg int mid = l + r >> 1;
    Lazy(cur << 1, lazy[cur], l, mid);
    Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
    lazy[cur] = -1;
  }
}

inline void PushUp(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}

inline void Build(int cur, int l, int r) {
  lazy[cur] = -1;
  if (l == r) return sum[cur] = T[l] - '0', void();
  rg int mid = l + r >> 1;
  Build(cur << 1, l, mid);
  Build(cur << 1 | 1, mid + 1, r);
  PushUp(cur);
}

inline void Modify(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x, l, r);
	rg int mid = l + r >> 1;
	PushDown(cur, l, r);
	if(ql <= mid) Modify(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

inline int Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res += Sum(cur << 1, ql, qr, l, mid);
	if(mid < qr) res += Sum(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

void Solve() {
	scanf("%d%d", &n, &m);
	scanf("%s%s", S+1, T+1);
	rep(i, 1, m) scanf("%d%d", &qL[i], &qR[i]);
	debug("--\n");
	Build(1, 1, n);
	per(i, 1, m) {
		int l = qL[i], r = qR[i];
		int ones = Sum(1, l, r, 1, n);
		debug("one = {} [{},{}]\n", ones, l, r);
		if(ones * 2 == r - l + 1) return puts("NO"), void();
		if(ones * 2 < r - l + 1) Modify(1, l, r, 0, 1, n);
		else Modify(1, l, r, 1, 1, n);
	}
	rep(i, 1, n) if(S[i] - '0' != Sum(1, i, i, 1, n)) return puts("NO"), void();
	puts("YES");
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) Solve();
  fastio::flush();
  return 0;
}