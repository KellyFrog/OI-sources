
// Problem: CF555E Case of Computer Network
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF555E?contestId=41164
// Memory Limit: 250 MB
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

const int N = 2e5 + 5;

int n, m, q;
int head[N], to[N << 1], nxt[N << 1], tot;
int dfn[N], low[N], dfncnt;
bool iseg[N];
int stk[N], top, ins[N];
int edcc[N], edcccnt;
vector<int> tree[N];

void AddEdge(int u, int v) {
  nxt[++tot] = head[u];
  to[tot] = v;
  head[u] = tot;
}

void Tarjan(int u, int e) {
  dfn[u] = low[u] = ++dfncnt;
  for (int i = head[u]; i; i = nxt[i]) {
    if ((i + 1) / 2 == (e + 1) / 2) continue;
    int v = to[i];
    debug("edge {} -> {}\n", u, v);
    if (!dfn[v]) {
      Tarjan(v, i);
      low[u] = min(low[u], low[v]);
      if (low[v] > dfn[u]) {
      	debug("got {} => {}\n", u, v);
        iseg[(i + 1) / 2] = 1;
      }
    } else low[u] = min(low[u], dfn[v]);
  }
}

void Get(int u) {
  edcc[u] = edcccnt;
  for (int i = head[u]; i; i = nxt[i]) {
    if (iseg[(i + 1) / 2]) continue;
    int v = to[i];
    if (!edcc[v]) Get(v);
  }
}

int anc[N][20], dep[N];

void Dfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  anc[u][0] = fa;
  rep(i, 1, 19) anc[u][i] = anc[anc[u][i - 1]][i - 1];
  for (int v : tree[u]) {
    if (!dep[v]) Dfs(v, u);
  }
}

int LCA(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  per(i, 0, 19) if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
  if (x == y) return x;
  per(i, 0, 19) if (anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
  return anc[x][0];
}

bool vis[N];
int delta1[N], delta2[N];

void Dfs2(int u, int fa) {
  vis[u] = 1;
  for (int v : tree[u]) {
    if (!vis[v]) {
      Dfs2(v, u);
      delta1[u] += delta1[v];
      delta2[u] += delta2[v];
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  rep(i, 1, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    AddEdge(u, v);
    AddEdge(v, u);
  }
  rep(i, 1, n) if (!dfn[i]) Tarjan(i, 0);
  rep(i, 1, n) if (!edcc[i]) edcccnt++, Get(i);
  rep(u, 1, n) {
    for (int i = head[u]; i; i = nxt[i]) {
      int v = to[i];
      if (edcc[u] != edcc[v]) {
      	tree[edcc[u]].pb(edcc[v]);
      	tree[edcc[v]].pb(edcc[u]);
      }
    }
  }
  rep(i, 1, edcccnt) if(!dep[i]) Dfs(i, 0);
  rep(i, 1, n) debug("[{}] edcc={} dfn={} low={}\n", i, edcc[i], dfn[i], low[i]);
  while(q--) {
  	int x, y;
  	scanf("%d%d", &x, &y);
  	x = edcc[x];
  	y = edcc[y];
  	debug("query={} -> {}\n", x, y);
  	int lca = LCA(x, y);
  	if(lca == 0) return puts("No"), 0;
  	delta1[x]++; delta1[lca]--;
  	delta2[y]++; delta2[lca]--;
  }
  rep(i, 1, edcccnt) if(!anc[i][0]) Dfs2(1, 0);
  rep(i, 1, edcccnt) if(delta1[i] && delta2[i] && anc[i][0]) return puts("No"), 0;
  puts("Yes");
  fastio::flush();
  return 0;
}