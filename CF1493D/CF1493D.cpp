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

#define OK cerr << "OK!\n"

#else

#define debug(...) void(0)
#define OK void(0)

#endif

const ll mod = 1e9 + 7;

ll qpow(ll x, ll p) {
  rg ll base = x, res = 1;
  while (p) {
    if (p & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    p >>= 1;
  }
  return res;
}

const int N = 2e5 + 5;

map<int, int> cnt[N], prm[N];

int n, m;
int a[N], mi[N];
ll ans0 = -1;
int hasz[N];
bool zero = 0;

void Update(int& x, int y, int i) {
	debug("update = {} {} {}\n", x, y, i);
	assert(x!=1);
  int cur = 0;
  while (x % y == 0) {
    cur++;
    x /= y;
  }
  prm[y][cnt[i][y] = cur]++;
  hasz[y]--;
  mi[y] = mi[y] == -1 ? cur : min(cur, mi[y]);
  debug("mi[{}] -> {} {}\n", y, cur, mi[y]);
}

void Solve(int p, int x) {
  int curcnt = cnt[p][x]++;
  debug("solve= {} {} {} mi={}\n", p, x, curcnt, mi[x]);
  if (curcnt == 0) {
    if (mi[x] == curcnt && hasz[x] == 1) ans0 = ans0 * x % mod, mi[x]++;

    hasz[x]--;
  } else {
    if (prm[x][curcnt] == 1 && mi[x] == curcnt) {
      debug("updated {} {}\n", x, curcnt);
      ans0 = ans0 * x % mod;
      mi[x]++;
    }
  }
  // if(mi[x] == curcnt && ((curcnt == 0 && hasz[x] == 0) || (curcnt &&
  // prm[x][curcnt] == 1))) ans0 = ans0 * x % mod;
  prm[x][curcnt]--;
  prm[x][curcnt + 1]++;
}

int main() {
  fastio::qread(n, m);
  rep(i, 1, (int)2e5) mi[i] = -1;
  rep(i, 1, n) {
    fastio::qread(a[i]);
    if (a[i] == 1) {
      ans0 = 1;
      zero = 1;
      continue;
    }
    ans0 = ans0 == -1 ? a[i] : __gcd(ans0, (ll)a[i]);
    int x0 = a[i];
    for (rg int j = 2; j * j <= a[i]; j++) {
      if (x0 % j == 0) Update(x0, j, i);
    }
    if (x0 != 1) Update(x0, x0, i);
  }
  
  rep(i, 1, (int)2e5) hasz[i] += n;
  rep(i, 1, (int)2e5) if (zero || mi[i] == -1 || hasz[i] != 0) mi[i] = 0;
  
  debug("mi[2]={}\n", mi[2]);
  rep(i, 1, m) {
    int p, x, x0;
    fastio::qread(p, x);
    debug("query= {} {} {}\n", i, p, x);
    x0 = x;
    for (rg int j = 2; j * j <= x0; j++) {
      while (x % j == 0) {
        Solve(p, j);
        x /= j;
      }
    }
    if (x != 1) Solve(p, x);
    fastio::qwrite(ans0, '\n');
  }
  fastio::flush();
  return 0;
}