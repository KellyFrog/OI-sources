
// Problem: U112060 星际专列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U112060?contestId=42578
// Memory Limit: 125 MB
// Time Limit: 600 ms
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
const int M = 1e6 + 5;

struct Query {
	int op, x, y;
};

Query op[M];
int tree[N];
vector<int> adj[N];
int dfn[N], siz[N], fa[N][21], dep[N], dfncnt;
int uni[N], a[N];
int n, m;

int lowbit(int x) {
	return x & (-x);
}

void Add(int p, int x) {
	while(p <= n) {
		tree[p] += x;
		p += lowbit(p);
	}
}

void Add(int L, int R, int x) {
	Add(L, x);
	Add(R+1, -x);
}

int Sum(int p) {
	int res = 0;
	while(p) {
		res += tree[p];
		p -= lowbit(p);
	}
	return res;
}

int Find(int x) {
	return x == uni[x] ? x : uni[x] = Find(uni[x]);
}

void Dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	fa[u][0] = f;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int v : adj[u]) {
		if(v != f) Dfs(v, u), siz[u] += siz[v];
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
	rep(i, 1, n) fastio::qread(a[i]), uni[i] = i;
	rep(i, 1, m) {
		fastio::qread(op[i].op, op[i].x, op[i].y);
		if(op[i].op == 1) {
			int fx = Find(op[i].x), fy = Find(op[i].y);
			if(fx == fy) continue;
			adj[op[i].x].pb(op[i].y);
			adj[op[i].y].pb(op[i].x);
			uni[fx] = fy;
		}
	}
	rep(i, 1, n) if(!dep[i]) Dfs(i, 0);
	rep(i, 1, n) Add(dfn[i], dfn[i] + siz[i] - 1, a[i]);
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) {
		if(op[i].op == 1) {
			int fx = Find(op[i].x), fy = Find(op[i].y);
			puts(fx == fy ? "fail" : "success");
			uni[fx] = fy;
		} else if(op[i].op == 2) {
			int fx = Find(op[i].x), fy = Find(op[i].y);
			int x = op[i].x, y = op[i].y;
			if(fx != fy) {
				puts("-1");
				continue;
			}
			int lca = LCA(x, y);
			printf("%d\n", Sum(dfn[x]) + Sum(dfn[y]) - Sum(dfn[lca]) - Sum(dfn[fa[lca][0]]));
		} else {
			int delta = op[i].y - a[op[i].x];
			Add(dfn[op[i].x], dfn[op[i].x] + siz[op[i].x] - 1, delta);
			a[op[i].x] = op[i].y;
		}
	}
  fastio::flush();
  return 0;
}