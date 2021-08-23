
// Problem: P1941 [NOIP2014 提高组] 飞扬的小鸟
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1941
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
const int M = 1e3 + 5;
const int inf = 0x3f3f3f3f;

int n, m, k;
int x[N], y[N];
int L[N], R[N];
int dp[2][M * 3][2];

int main() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) scanf("%d%d", &x[i], &y[i]);
  rep(i, 1, n) L[i] = 1, R[i] = 2*m;
  rep(i, 1, k) {
    int p, lw, up;
    scanf("%d%d%d", &p, &lw, &up);
    L[p + 1] = lw;
    R[p + 1] = up;
  }
  int ans = 0;
  rep(i, 1, n + 1) {
    memset(dp[i & 1], 0x3f, sizeof dp[i & 1]);
    rep(j, L[i], min(R[i], 2 * m)) {
      if (i == 2) {
        debug("i={} j={}, [{}, {}] {} {}\n", i, j, (i - 1) & 1, j + y[i],
              dp[(i - 1) & 1][j + y[i]][0], dp[(i - 1) & 1][j + y[i]][1]);
      }
      dp[i & 1][j][0] = min(dp[i & 1][j][0], min(dp[(i - 1) & 1][j + y[i]][0],
                                                 dp[(i - 1) & 1][j + y[i]][1]));
      if (j >= x[i])
        dp[i & 1][j][1] = min(dp[(i - 1) & 1][j - x[i - 1]][0],
                              min(dp[(i - 1) & 1][j - x[i - 1]][1],
                                  dp[i & 1][j - x[i - 1]][1])) +
                          1;
      if (dp[i & 1][j][0] < inf || dp[i & 1][j][1] < inf) ans = i;
      if (dp[i & 1][j][0] < inf)
        debug("dp[{}][{}][{}] = {}\n", i, j, 0, dp[i & 1][j][0]);
      if (dp[i & 1][j][1] < inf)
        debug("dp[{}][{}][{}] = {}\n", i, j, 1, dp[i & 1][j][1]);
    }
    rep(j, m + 1, R[i] + m) {
      dp[i & 1][m][0] = min(dp[i & 1][m][0], dp[i & 1][j][0]);
      dp[i & 1][m][1] = min(dp[i & 1][m][1], dp[i & 1][j][1]);
    }
  }
  if (ans == n + 1) {
    puts("1");
    int res = inf;
    rep(i, 1, m) {
      res = min(res, dp[(n + 1) & 1][i][0]);
      res = min(res, dp[(n + 1) & 1][i][1]);
    }
    printf("%d\n", res);
  }
  fastio::flush();
  return 0;
}