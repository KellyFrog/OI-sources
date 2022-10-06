
// Problem: P5025 [SNOI2017]炸弹
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5025
// Memory Limit: 512 MB
// Time Limit: 2500 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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
const ll mod = 1e9 + 7;
const ll inf = 3e18;

vector<int> adj[N], dag[N];
int dfn[N], low[N], scc[N], scccnt, dfncnt, ins[N], stk[N], top;
int lft[N], rgt[N], ind[N];
int id[N];
pair<int, int> range[N];
int mx = -1;
ll x[N], r[N], n;
int que[N], head = 1, tail;

void Build(int cur, int l, int r) {
  mx = max(mx, cur);
  range[cur] = mp(l, r);
  if (l == r) return id[l] = cur, void();
  rg int mid = l + r >> 1;
  Build(cur << 1, l, mid);
  Build(cur << 1 | 1, mid + 1, r);
  adj[cur].pb(cur << 1);
  adj[cur].pb(cur << 1 | 1);
}

void Connect(int cur, int p, int ql, int qr, int l, int r) {
  if (ql <= l && r <= qr) return adj[p].pb(cur), void();
  rg int mid = l + r >> 1;
  if (ql <= mid) Connect(cur << 1, p, ql, qr, l, mid);
  if (mid < qr) Connect(cur << 1 | 1, p, ql, qr, mid + 1, r);
}

void Tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt;
  stk[++top] = u;
  ins[u] = 1;
  for (int v : adj[u]) {
    if (!dfn[v]) {
      Tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (ins[v]) {
      low[u] = min(low[u], low[v]);
    }
  }
  if (dfn[u] == low[u]) {
    scccnt++;
    lft[scccnt] = n + 1;
    rgt[scccnt] = -1;
    rg int v = -1;
    while ((v = stk[top--]) != u) {
      ins[v] = 0;
      scc[v] = scccnt;
      lft[scccnt] = min(lft[scccnt], range[v].fi);
      rgt[scccnt] = max(rgt[scccnt], range[v].se);
    }
    ins[v] = 0;
    scc[v] = scccnt;
    lft[scccnt] = min(lft[scccnt], range[v].fi);
    rgt[scccnt] = max(rgt[scccnt], range[v].se);
  }
}

int main() {
  qread(n);
  Build(1, 1, n);
  x[0] = -inf, x[n + 1] = inf;
  rep(i, 1, n) qread(x[i], r[i]);
  rep(i, 1, n) {
  	if(r[i] == 0) continue;
    rg int L = lower_bound(x + 1, x + 1 + n, x[i] - r[i]) - x;
    rg int R = upper_bound(x + 1, x + 1 + n, x[i] + r[i]) - x - 1;
    Connect(1, id[i], L, R, 1, n);
  }
  Tarjan(1);
  //rep(i, 1, mx) cerr << scc[i] << " \n"[i == mx];
	rep(u, 1, mx) for(int v : adj[u]) if(scc[u] != scc[v]) dag[scc[v]].pb(scc[u]), ind[scc[u]]++;
	rep(i, 1, scccnt) if(ind[i] == 0) que[++tail] = i;
	while(head <= tail) {
		rg int u = que[head++];
		for(int v : dag[u]) {
			lft[v] = min(lft[v], lft[u]), rgt[v] = max(rgt[v], rgt[u]);
			if(--ind[v] == 0) que[++tail] = v;
		}
	}
	ll ans = 0;
	//rep(i, 1, n) cerr << id[i] << " " << scc[id[i]] << " " << rgt[scc[id[i]]] << " " << lft[scc[id[i]]] << endl;
	rep(i, 1, n) ans = (ans + 1ll * (rgt[scc[id[i]]] - lft[scc[id[i]]] + 1) * i) % mod;
	qwrite(ans, '\n');
  return 0;
}