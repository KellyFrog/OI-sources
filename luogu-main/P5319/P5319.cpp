// Problem: P5319 [BJOI2019]奥术神杖
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5319?contestId=45634
// Memory Limit: 125 MB
// Time Limit: 1000 ms
//
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 2e3 + 5;
const double eps = 1e-7;

double dp[N][N];
int from[N][N];
double val[N], val0[N];
int son[N * 10][10], fail[N], rt, tot;
char ans[N];
char S[N], T[N], ch[N][N];
int n, m;
int que[N], head = 1, tail = 0;

inline void insert(double x) {
  int len = strlen(T + 1);
  if (!rt) rt = ++tot;
  int cur = rt;
  rep(i, 1, len) {
    if (!son[cur][T[i] - '0']) son[cur][T[i] - '0'] = ++tot;
    cur = son[cur][T[i] - '0'];
  }
  val0[cur] = val[cur] = x;
}

inline void buildfail() {
  fail[rt] = rt;
  rep(i, 0, 9) son[rt][i]                            ? fail[son[rt][i]] = rt,
                            que[++tail] = son[rt][i] : son[rt][i] = rt;
  while (head <= tail) {
    int cur = que[head++];
    rep(i, 0, 9) son[cur][i] ? fail[son[cur][i]] = son[fail[cur]][i],
                               que[++tail] = son[cur][i]
                             : son[cur][i] = son[fail[cur]][i];
  }
}

inline bool check(double x) {
  rep(i, 1, tot) val[i] = val0[i] / x;
  rep(i, 1, tot) if (val[i] == 0) val[i] = 1;
  rep(i, 2, tot) val[que[i]] *= val[fail[que[i]]];
  memset(dp, 0, sizeof dp);
  dp[0][rt] = 1;
  rep(i, 1, n) {
    if (S[i] == '.') {
      rep(j, 1, tot) {
        static double curval0 = 0;
        curval0 = dp[i - 1][j] * val[son[j][0]];
        if (dp[i][son[j][0]] < curval0) {
          dp[i][son[j][0]] = curval0;
          from[i][son[j][0]] = j;
          ch[i][son[j][0]] = 0 + '0';
        }
        static double curval1 = 0;
        curval1 = dp[i - 1][j] * val[son[j][1]];
        if (dp[i][son[j][1]] < curval1) {
          dp[i][son[j][1]] = curval1;
          from[i][son[j][1]] = j;
          ch[i][son[j][1]] = 1 + '0';
        }
        static double curval2 = 0;
        curval2 = dp[i - 1][j] * val[son[j][2]];
        if (dp[i][son[j][2]] < curval2) {
          dp[i][son[j][2]] = curval2;
          from[i][son[j][2]] = j;
          ch[i][son[j][2]] = 2 + '0';
        }
        static double curval3 = 0;
        curval3 = dp[i - 1][j] * val[son[j][3]];
        if (dp[i][son[j][3]] < curval3) {
          dp[i][son[j][3]] = curval3;
          from[i][son[j][3]] = j;
          ch[i][son[j][3]] = 3 + '0';
        }
        static double curval4 = 0;
        curval4 = dp[i - 1][j] * val[son[j][4]];
        if (dp[i][son[j][4]] < curval4) {
          dp[i][son[j][4]] = curval4;
          from[i][son[j][4]] = j;
          ch[i][son[j][4]] = 4 + '0';
        }
        static double curval5 = 0;
        curval5 = dp[i - 1][j] * val[son[j][5]];
        if (dp[i][son[j][5]] < curval5) {
          dp[i][son[j][5]] = curval5;
          from[i][son[j][5]] = j;
          ch[i][son[j][5]] = 5 + '0';
        }
        static double curval6 = 0;
        curval6 = dp[i - 1][j] * val[son[j][6]];
        if (dp[i][son[j][6]] < curval6) {
          dp[i][son[j][6]] = curval6;
          from[i][son[j][6]] = j;
          ch[i][son[j][6]] = 6 + '0';
        }
        static double curval7 = 0;
        curval7 = dp[i - 1][j] * val[son[j][7]];
        if (dp[i][son[j][7]] < curval7) {
          dp[i][son[j][7]] = curval7;
          from[i][son[j][7]] = j;
          ch[i][son[j][7]] = 7 + '0';
        }
        static double curval8 = 0;
        curval8 = dp[i - 1][j] * val[son[j][8]];
        if (dp[i][son[j][8]] < curval8) {
          dp[i][son[j][8]] = curval8;
          from[i][son[j][8]] = j;
          ch[i][son[j][8]] = 8 + '0';
        }
        static double curval9 = 0;
        curval9 = dp[i - 1][j] * val[son[j][9]];
        if (dp[i][son[j][9]] < curval9) {
          dp[i][son[j][9]] = curval9;
          from[i][son[j][9]] = j;
          ch[i][son[j][9]] = 9 + '0';
        }
      }
    } else {
      rep(j, 1, tot) {
        int p = son[j][S[i] - '0'];
        static double curval = 0;
        curval = dp[i - 1][j] * val[p];
        if (dp[i][p] < curval) {
          dp[i][p] = curval;
          from[i][p] = j;
          ch[i][p] = S[i];
        }
      }
    }
  }
  rep(i, 1, tot) if (dp[n][i] > 1) return 1;
  return 0;
}

inline void record() {
  int mxpos = 0;
  rep(i, 1, tot) if (dp[n][i] > dp[n][mxpos]) mxpos = i;
  per(i, 1, n) ans[i] = ch[i][mxpos], mxpos = from[i][mxpos];
}

int main() {
  scanf("%d%d", &n, &m);
  scanf("%s", S + 1);
  rep(i, 1, m) {
    double x = 0;
    scanf("%s%lf", T + 1, &x);
    insert(x);
  }
  buildfail();
  double L = 1, R = 1e9;
  double res = 1;
  while (R - L > eps) {
    double mid = (L + R) / 2;
    if (check(mid))
      res = mid, L = mid, record();
    else
      R = mid;
  }
  printf("%s", ans + 1);
  fastio::flush();
  return 0;
}
