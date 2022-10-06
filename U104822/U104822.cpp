
// Problem: U104822 导弹拦截2(mis)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U104822
// Memory Limit: 125 MB
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

const int N = 2005;

int tree[N][N << 1];
int a[N], b[N], c[N << 1];
int dp[N][N];
int n, m, p, op;

int lowbit(int x) { return x & (-x); }

int query(int x, int y) {
  int ans = 0;
  for (rg int x0 = x; x0 > 0; x0 -= lowbit(x0)) {
    for (rg int y0 = y; y0 > 0; y0 -= lowbit(y0)) {
      ans = max(ans, tree[x0][y0]);
    }
  }
  return ans;
}

void modify(int x, int y, int p0) {
  for (rg int x0 = x; x0 <= m + 2; x0 += lowbit(x0)) {
    for (rg int y0 = y; y0 <= p + 2; y0 += lowbit(y0)) {
      tree[x0][y0] = max(tree[x0][y0], p0);
    }
  }
}

int main() {
  fastio::qread(n, m, op);
  per(i, 1, n) fastio::qread(a[i]), c[i] = a[i];
  per(i, 1, m) fastio::qread(b[i]), c[i + n] = b[i];
  sort(c + 1, c + 1 + n + m);
  p = unique(c + 1, c + 1 + n + m) - (c + 1);
  rep(i, 1, n) a[i] = lower_bound(c + 1, c + 1 + p, a[i]) - c;
  rep(i, 1, m) b[i] = lower_bound(c + 1, c + 1 + p, b[i]) - c;
  int ans = 0;
  rep(i, 1, n) {
    rep(j, 1, m) {
      if (a[i] == b[j]) {
        dp[i][j] = query(j - 1, a[i]) + 1;
        ans = max(ans, dp[i][j]);
        modify(j, a[i] + 1, dp[i][j]);
      }
    }
  }
  fastio::qwrite(ans, '\n');
  if (op == 1) {
    vector<int> ans;
    int ansi = 0, ansj = 0;
    per(i, 1, m) per(j, 1, n) if (dp[ansi][ansj] < dp[j][i]) ansj = i, ansi = j;
    if(ansi == 0) return cout << "FUCKYOU!" << endl, 0;
    while (dp[ansi][ansj]) {
      ans.pb(c[a[ansi]]);
    	bool ok = 0;
      per(i, 1, ansj - 1) {
      	if(ok) break;
        per(j, 1, ansi - 1) if (dp[ansi][ansj] == dp[j][i] + 1 && a[j] < a[ansi]) {
          ansj = i;
          ansi = j;
          ok = 1;
          break;
        }
      }
      if(!ok) break;
    }
    for(int x : ans) fastio::qwrite(x, ' ');
  }
  fastio::flush();
  return 0;
}