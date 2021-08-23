
// Problem: P2403 [SDOI2010]所驼门王的宝藏
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2403?contestId=41163
// Memory Limit: 125 MB
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

const int N = 4e5 + 5;
const int M = 1e6 + 5;
struct Node {
  int x, y, op;
};

map<int, int> a[M];

int n, r, c;
vector<int> adj[N], dag[N];
int rn[M], cn[M], cnt;
int w[N], wei[N], dp[N], ind[N];
int dfn[N], low[N], ins[N], stk[N], scc[N], top, dfncnt, scccnt;
Node nd[N];

inline void Connect(int x, int i, int j) {
  if (a[i][j]) {
    adj[x].pb(a[i][j]);
  }
}

bool ok[M];

inline void Tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt;
  stk[++top] = u;
  ins[u] = 1;
  for (int v : adj[u]) {
    if (!dfn[v])
      Tarjan(v), low[u] = min(low[u], low[v]);
    else if (ins[v])
      low[u] = min(low[u], low[v]);
  }
  if (dfn[u] == low[u]) {
    int x = 0;
    scccnt++;
    debug("scc={} contain=\n", scccnt);
    while ((x = stk[top--]) != u) {
      ins[x] = 0;
      scc[x] = scccnt;
      wei[scc[x]] += w[x];
      debug("{} ", x);
    }
    ins[x] = 0;
    scc[x] = scccnt;
    wei[scc[x]] += w[x];
    debug("{}\n", x);
  }
}

int main() {
  scanf("%d%d%d", &n, &r, &c);
  rep(i, 1, n) {
    scanf("%d%d%d", &nd[i].x, &nd[i].y, &nd[i].op);
    ok[nd[i].x] = 1;
    ok[nd[i].y] = 1;
    if (!a[nd[i].x][nd[i].y]) a[nd[i].x][nd[i].y] = ++cnt, w[cnt] = 1;
  }
  rep(i, 1, r) if(ok[i]) rn[i] = ++cnt;
  rep(i, 1, c) if(ok[i]) cn[i] = ++cnt;
  rep(i, 1, n) {
    int cur = a[nd[i].x][nd[i].y];
    adj[rn[nd[i].x]].pb(cur);
    adj[cn[nd[i].y]].pb(cur);
    
    if (nd[i].op == 1) {
      adj[cur].pb(rn[nd[i].x]);
      //adj[rn[nd[i].x]].pb(cur);
    } else if (nd[i].op == 2) {
      adj[cur].pb(cn[nd[i].y]);
      //adj[cn[nd[i].y]].pb(cur);
    } else {
      int x = nd[i].x, y = nd[i].y;
      Connect(cur, x - 1, y - 1);
      Connect(cur, x - 1, y);
      Connect(cur, x - 1, y + 1);
      Connect(cur, x, y - 1);
      Connect(cur, x, y + 1);
      Connect(cur, x + 1, y - 1);
      Connect(cur, x + 1, y);
      Connect(cur, x + 1, y + 1);
    }
  }
  rep(i, 1, cnt) for(int v : adj[i]) debug("{}\t->{}\n", i, v);
  rep(i, 1, cnt) if(!dfn[i]) Tarjan(i);
  rep(i, 1, cnt) debug("node[{}] : scc={} wei={}\n", i, scc[i], wei[scc[i]]);
  rep(u, 1, cnt) {
    for (int v : adj[u]) {
      if (scc[u] != scc[v]) {
        dag[scc[u]].pb(scc[v]);
        ind[scc[v]]++;
      }
    }
  }
  queue<int> q;
  rep(i, 1, cnt) if (ind[i] == 0) q.push(i);
  int ans = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    dp[u] += wei[u];
    ans = max(ans, dp[u]);
    for (int v : dag[u]) {
      dp[v] = max(dp[v], dp[u]);
      if (--ind[v] == 0) q.push(v);
    }
  }
  cout << ans << "\n";
  return 0;
}