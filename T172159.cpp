
// Problem: T172159 计算游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T172159?contestId=42210
// Memory Limit: 500 MB
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

const int N = 35;
const ll mod = 1e9 + 7;

ll a[N], b[N], invb[N];
int n;

void Solve(set<ll> &tar, ll x, int s, int t, bool inv) {
  set<ll> last, cur;
  last.insert(x);
  if (s > t) return tar = last, void();
  if (inv) {
    per(i, s, t) {
      cur.clear();
      for (ll x : last) {
      	debug("{} -> {} {} {}\n", x, x-a[i], x*invb[i]%mod, x);
        cur.insert((x - a[i] + mod) % mod);
        cur.insert(x * invb[i] % mod);
        //cur.insert(x);
      }
      last = cur;
    }
  } else {
    rep(i, s, t) {
      cur.clear();
      for (ll x : last) {
      	debug("{} -> {} {} {}\n", x, x+a[i], x*b[i]%mod, x);
        cur.insert((x + a[i]) % mod);
        cur.insert(x * b[i] % mod);
        //cur.insert(x);
      }
      last = cur;
    }
  }
  tar = last;
}

int main() {
  cin >> n;
  rep(i, 1, n) cin >> a[i];
  rep(i, 1, n) cin >> b[i], invb[i] = qpow(b[i], mod - 2, mod);
  int T;
  cin >> T;
  while (T--) {
    ll x, y;
    cin >> x >> y;
    set<ll> s1, s2;
    Solve(s1, x, 1, n / 2, 0);
    OK;
    Solve(s2, y, n / 2+1, n, 1);
    /*
    debug("s1=");
    for (ll x : s1) cerr << x << " ";
    cerr << "\n";
    debug("s2=");
    for (ll x : s2) cerr << x << " ";
    cerr << "\n";
    */
    bool ok = 0;
    for (ll x : s1)
      if (s2.count(x)) {
        ok = 1;
        break;
      }
    puts(ok ? "Yes" : "No");
  }
  fastio::flush();
  return 0;
}