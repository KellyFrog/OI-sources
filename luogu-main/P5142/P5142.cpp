
// Problem: P5142 区间方差
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5142?contestId=42241
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

const int N = 1e5 + 5;
const ll mod = 1e9 + 7;

inline int lowbit(int x) {
	return x & (-x);
}

template<typename T1, typename T2>
inline void chkadd(T1& x, T2 y) {
	x = x + y > mod ? x + y - mod : x + y;
}

#define int long long

int n, m, a[N];

struct BIT {
	ll sum[N];
	ll Sum(int p) {
		ll res = 0;
		while(p) {
			chkadd(res, sum[p]);
			p -= lowbit(p);
		}
		return res;
	}
	void Add(int p, ll x) {
		while(p <= n) {
			chkadd(sum[p], x);
			p += lowbit(p);
		}
	}
};

BIT b1, b2;
ll invn;

signed main() {
	fastio::qread(n, m);
	rep(i, 1, n) {
		fastio::qread(a[i]);
		b1.Add(i, a[i]);
		b2.Add(i, 1ll * a[i] * a[i] % mod);
	}
	while(m--) {
		int op, x, y;
		fastio::qread(op, x, y);
		if(op == 1) {
			ll delta1 = (y - a[x] + mod) % mod;
			ll delta2 = ((1ll * y * y - 1ll * a[x] * a[x]) % mod + mod) % mod;
			a[x] = y;
			b1.Add(x, delta1);
			b2.Add(x, delta2);
		} else {
			ll s1 = (b1.Sum(y) - b1.Sum(x-1) + mod) % mod;
			ll s2 = (b2.Sum(y) - b2.Sum(x-1) + mod) % mod;
			ll invn = qpow(y - x + 1, mod-2, mod);
			ll res = (s2 * invn % mod - (((((s1 * s1) % mod) * invn) % mod) * invn) % mod + mod) % mod;
			fastio::qwrite(res, '\n');
		}
	}
  fastio::flush();
  return 0;
}