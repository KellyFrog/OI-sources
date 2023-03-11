
// Problem: T171289 吃小孩
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T171289?contestId=41960
// Memory Limit: 128 MB
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
const ll mod = 1e9 + 7;

vector<int> adj[N];
int dep[N], fa[N][21];
ll mul[N], imul[N], a[N], tot = 1;
int n, m;

void Dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	mul[u] = mul[f] * a[u] % mod;
	imul[u] = qpow(mul[u], mod-2, mod);
	fa[u][0] = f;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int v : adj[u]) {
		if(v != f) Dfs(v, u);
	}
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 20) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	per(i, 0, 20) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0]; 
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(a[i]), tot = tot * a[i] % mod;
	rep(i, 1, n-1) {
		int u, v; fastio::qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	mul[0] = 1;
	imul[0] = 1;
	Dfs(1, 0);
	while(m--) {
		int x, y;
		fastio::qread(x, y);
		int lca = LCA(x, y);
		if(dep[x] + dep[y] - 2 * dep[lca] + 1 == n) {
			fastio::qwrite(0, '\n');
			continue;
		}
		debug("{} {} lca={}\n", x, y, lca);
		debug("{} {} {} {} {}\n", tot, mul[lca], mul[fa[lca][0]], imul[x], imul[y]);
		fastio::qwrite(tot * mul[lca] % mod * mul[fa[lca][0]] % mod * imul[x] % mod * imul[y] % mod, '\n');
  }
  fastio::flush();
  return 0;
}