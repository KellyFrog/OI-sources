
// Problem: Phoenix and Computers
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1515/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms
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

ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;

template<typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template<typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template<typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template<typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z; }
template<typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template<typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template<typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y; }
template<typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z; }

const int N = 4e2 + 5;

int n;
ll dp[N][N];
ll fac[N], ifac[N], pw2[N];

inline ll cnm(int n, int m) {
	assert(n >= m);
	return fac[n] * ifac[n - m] % mod * ifac[m] % mod;
}

int main() {
	cin >> n >> mod;
	ifac[0] = fac[0] = fac[1] = pw2[0] = 1;
	rep(i, 2, n) fac[i] = fac[i-1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2, mod);
	per(i, 1, n-1) ifac[i] = ifac[i+1] * (i+1) % mod;
	rep(i, 1, n) pw2[i] = pw2[i-1] * 2 % mod;
	dp[1][1] = 1;
	rep(i, 2, n) rep(j, 1, i) {
		rep(k, 1, min(i-1, j)) {
			chkadd(dp[i][j], dp[i-k-1][j-k] * cnm(j, k) % mod * pw2[k-1] % mod);
		}
		if(i == j) chkadd(dp[i][j], pw2[i-1]);
		//debug("dp[{}][{}]={}\n", i, j, dp[i][j]);
	}
	ll ans = 0;
	rep(i, 1, n) chkadd(ans, dp[n][i]);
	cout << ans << "\n";
  fastio::flush();
  return 0;
}