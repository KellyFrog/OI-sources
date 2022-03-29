
// Problem: P3657 [USACO17FEB]Why Did the Cow Cross the Road II P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3657?contestId=42241
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

/*
dp[i][j] 表示左边前 i 个，右边前 j 个选了第 j 个的最大方案
dp[i][j] = max(dp[i-1/2/3/4][j']) O(n^2) - O(n^2)
dp[i][j] -> dp[i+1][j+1/2/3/4] + [a[i]==b[j+1/2/3/4]]
dp[j] 表示当前的 i，选了 j 的最大值
dp[j] -> dp[j±1/2/3/4] + [a[i]==b[j±1/2/3/4]
 */
 
template<typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}

const int N = 1e5 + 5;

int tree[N];
int n, a[N], b[N];
int last[N], tmp[N];
 
inline int lowbit(int x) {
	return x & (-x);
}

inline int getmax(int p) {
	int res = 0;
	while(p) {
		chkmax(res, tree[p]);
		p -= lowbit(p);
	}
	return res;
}

inline void modify(int p, int x) {
	while(p <= n) {
		chkmax(tree[p], x);
		p += lowbit(p);
	}
}

inline int getL(int i, int x) {
	return max(1, i - x);
}

inline int getR(int i, int x) {
	return min(n, i + x);
}

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n) fastio::qread(b[i]), last[b[i]] = i;
	rep(i, 1, n) {
		int L = getL(a[i], 4);
		int R = getR(a[i], 4);
		rep(j, L, R) tmp[j] = getmax(last[j]-1);
		rep(j, L, R) modify(last[j], tmp[j]+1);
	}
	cout << getmax(n) << "\n";
  fastio::flush();
  return 0;
}