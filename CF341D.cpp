
// Problem: CF341D Iahub and Xors
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF341D?contestId=42578
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

/*
a[i][j] 是 i,j 左上的异或和

*/

const int N = 1e3 + 5;

int n, m;
ll tree[N][N][2][2];

inline int lowbit(int x) {
	return x & (-x);
}

inline void Modify(int x, int y, ll p) {
	debug("modified {} {} {} ({}, {})\n", x, y, p, x&1, y&1);
	for(rg int x0 = x; x0 <= n; x0 += lowbit(x0)) {
		for(rg int y0 = y; y0 <= n; y0 += lowbit(y0)) {
			tree[x0][y0][x&1][y&1] ^= p;
		}
	}
}

inline ll Query(int x, int y) {
	debug("query {} {} ({}, {})\n", x, y, x&1, y&1);
	ll res = 0;
	for(rg int x0 = x; x0; x0 -= lowbit(x0)) {
		for(rg int y0 = y; y0; y0 -= lowbit(y0)) {
			res ^= tree[x0][y0][x&1][y&1];
		}
	}
	debug("getres = {}\n", res);
	return res;
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, m) {
		int op, x1, x2, y1, y2, p;
		fastio::qread(op, x1, y1, x2, y2);
		if(op == 1) {
			fastio::qwrite(Query(x1-1, y1-1) ^ Query(x1-1, y2) ^ Query(x2, y1-1) ^ Query(x2, y2), '\n');
		} else {
			fastio::qread(p);
			Modify(x1, y1, p);
			Modify(x1, y2+1, p);
			Modify(x2+1, y1, p);
			Modify(x2+1, y2+1, p);
		}
	}
  fastio::flush();
  return 0;
}