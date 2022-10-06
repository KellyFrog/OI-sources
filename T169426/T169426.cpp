
// Problem: T169426 删数游戏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T169426?contestId=41458
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

const int N = 1e6 + 5;
const int inf = 1e9;
const int SZ = 547;

struct Query {
  int l, r, bel, p;
};

Query qry[N];
int l, r;
int n, m;
int a[N], b[N], res[N];
int ans, delta[N], delta0, delta1;
map<int, int> s, s1;

void AddBeg(int p) {
	if(a[p] == 0) {
		ans += s1[-1 - delta1];
		delta0++;
		ans++;
		delta1++;
	} else {
		s1[-a[p] - delta1]++;
	}
	delta[-a[p] - delta1] = 0;
}

void AddEnd(int p) {
  debug("addend={} ans={} delta={}\n", a[p], ans, delta0);
	if(a[p] == 0) {
		ans++;
		delta0++;
	} else {
		s1[delta0 - a[p] - delta1]++;
		delta[p] = delta0 - a[p] - delta1;
		if(a[p] <= delta0) {
			delta0++;
			ans++;
		}
	}
}

void DelBeg(int p) {
  debug("delbeg={} ans={} delta={}\n", a[p], ans, delta0);
  if(a[p] == 0) {
  	ans -= s1[-delta1];
  	delta0--;
  	ans--;
  	delta1--;
  } else {
  	s1[delta[p]]--;
  }
}

void DelEnd(int p) {
  debug("delend={}\n", a[p]);
  if(a[p] == 0) {
  	ans--;
  	delta0--;
  } else {
  	s1[delta[p]]--;
  	if(a[p] <= delta0) {
  		delta0--;
  		ans--;
  	}
  }
}

int main() {
  fastio::qread(n);
  rep(i, 1, n) {
    fastio::qread(a[i]);
    a[i] = a[i] > i ? inf : i - a[i];
    debug("a[{}]={}\n", i, a[i]);
  }
  fastio::qread(m);
  rep(i, 1, m) {
    int l, r;
    fastio::qread(l, r);
    qry[i].l = l, qry[i].r = r;
    qry[i].p = i, qry[i].bel = qry[i].l / SZ;
  }
  sort(qry + 1, qry + 1 + m, [](const Query &a, const Query &b) {
    return a.bel == b.bel ? (a.bel & 1) ? a.r < b.r : a.r > b.r : a.l < b.l;
  });
  l = 1;
  rep(i, 1, m) {
    debug("qry={} {}\n", qry[i].l, qry[i].r);
    while (l > qry[i].l) AddBeg(--l);
    while (r < qry[i].r) AddEnd(++r);
    while (l < qry[i].l) DelBeg(l++);
    while (r > qry[i].r) DelEnd(r--);
    res[qry[i].p] = ans;
  }
  rep(i, 1, m) fastio::qwrite(res[i], '\n');
  fastio::flush();
  return 0;
}