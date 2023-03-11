
// Problem: T172866 组队问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T172866?contestId=42491
// Memory Limit: 500 MB
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
const double eps = 1e-7;

ll a[N], b[N];
int fa[N];
bool vis[N];
int n, m, k;
double d[N];
vector<int> c;

namespace Solve1 {

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }

int main() {
  sort(c.begin(), c.end(), [](const int &x, const int &y) {
    if ((double)a[x] / b[x] != (double)a[y] / b[y])
      return (double)a[x] / b[x] < (double)a[y] / b[y];
    if (a[x] > b[x]) {
      return a[x] < a[y];
    } else {
      return b[x] > b[y];
    }
  });
  ll ansa = 0, ansb = 0;
  per(i, (int)c.size() - k, (int)c.size() - 1) {
    ansa += a[c[i]];
    ansb += b[c[i]];
  }
  return 1000ll * ansa / ansb;
}
};  // namespace Solve1

int Find(int x) { return x == fa[x] ? x : fa[x] = Find(fa[x]); }

bool Check(double x) {
  rep(i, 0, c.size() - 1) d[i] = (double)a[c[i]] - x * b[c[i]];
  sort(d, d + c.size());
  double res = 0;
  per(i, (int)c.size() - k, (int)c.size() - 1) { res += d[i]; }
  return res >= 0;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) fa[i] = i;
  rep(i, 1, n) scanf("%lld", &a[i]);
  rep(i, 1, n) scanf("%lld", &b[i]);
  rep(i, 1, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    u = Find(u);
    v = Find(v);
    a[u] += a[v];
    b[u] += b[v];
    fa[v] = u;
  }
  rep(i, 1, n) {
    int x = Find(i);
    if (!vis[x]) {
      vis[x] = 1;
      c.pb(x);
    }
  }
  double L = 0.0, R = 1e9;
  double res = -1;
  while (R - L > eps) {
    double mid = (L + R) / 2;
    if (Check(mid)) {
      res = mid;
      L = mid;
    } else {
      R = mid;
    }
  }
  //double solve2res = Solve1::main();
  //printf("%.1lf\n", res * 1000);
  cout << (ll)(res * 1000 + 0.01) << "\n";
  fastio::flush();
  return 0;
}