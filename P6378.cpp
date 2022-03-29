
// Problem: P6378 [PA2010] Riddle
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6378?contestId=41164
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

const int N = 5e6 + 5;

int head[N], to[N<<1], nxt[N<<1], siz;
int dfn[N], low[N], scc[N], ins[N], scccnt, dfncnt;
int stk[N], top;
int n, m, k;
int nd[N], nnd[N], tot;
int tmp[N];

inline void Tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt;
  stk[++top] = u;
  ins[u] = 1;
  for(int i = head[u]; i; i = nxt[i]) {
  	int v = to[i];
    if (!dfn[v])
      Tarjan(v), low[u] = min(low[u], low[v]);
    else if (ins[v])
      low[u] = min(low[u], low[v]);
  }
  if (dfn[u] == low[u]) {
    int x = 0;
    scccnt++;
    while ((x = stk[top--]) != u) {
      ins[x] = 0;
      scc[x] = scccnt;
    }
    ins[x] = 0;
    scc[x] = scccnt;
  }
}

//一个点向区间连边 前后缀优化

void Add(int u, int v) {
	nxt[++siz] = head[u];
	to[siz] =v;
	head[u] = siz;
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) {
  	Add(i+3*n, i+n);
  	Add(i+2*n, i+n);
  }
  rep(i, 1, m) {
  	int x, y;
  	scanf("%d%d", &x, &y);
  	Add(x+n, y);
  	Add(y+n, x);
  }
  tot = 4 * n;
  rep(i, 1, k) {
  	int len; scanf("%d", &len);
  	rep(i, 1, len) {
  		scanf("%d", &tmp[i]);
  	}
  	rep(i, 2, len) Add(tmp[i-1]+3*n, tmp[i]+3*n);
  	per(i, 1, len-1) Add(tmp[i+1]+2*n, tmp[i]+2*n);
  	rep(i, 1, len) {
  		if(i != 1) Add(tmp[i], tmp[i-1]+2*n);
  		if(i != len) Add(tmp[i], tmp[i+1]+3*n);
  	}
  }
  rep(i, 1, tot) if(!dfn[i]) Tarjan(i);
  rep(i, 1, n) if(scc[i] == scc[i+n]) return puts("NIE"), 0;
  puts("TAK");
  return 0;
}