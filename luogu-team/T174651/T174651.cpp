
// Problem: T174651 擂台挑战
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T174651?contestId=43116
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

const int N = 2e6 + 5;
const int M = 22;

int n, m, q;
int head[N], nxt[N<<1], to[N<<1], tot;
int anc[N][M], qry[N], p;
int a[N];
int win[M][M];

inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

inline void dfs(int u, int fa) {
	rep(i, 1, m) {
		if(win[i][a[u]]) anc[u][i] = anc[fa][i];
		else anc[u][i] = u;
	}
	for(rg int e = head[u]; e; e = nxt[e]) {
		rg int v = to[e];
		if(v != fa) {
			dfs(v, u);
		}
	}
}

int main() {
	fastio::qread(n, q, m);
	rep(i, 1, m) rep(j, 1, m) fastio::qread(win[i][j]);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 2, n) {
		static int u, v;
		fastio::qread(u, v);
		addedge(u, v);
		addedge(v, u);
	}
	dfs(1, 0);
	rep(i, 1, q) {
		static int u, p;
		fastio::qread(p, u);
		rep(i, 1, p) fastio::qread(qry[i]);
		per(i, 1, p) {
			if(u == 0) break;
			u = anc[u][qry[i]];
		}
		puts(u ? "0" : "1");
	}
  fastio::flush();
  return 0;
}