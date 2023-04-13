
// Problem: P4116 Qtree3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4116
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// Author: Chenkaifeng

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

const int N = 1e5 + 5;

vector<int> adj[N];
int dep[N], son[N], siz[N], top[N], fa[N], clr[N];
int n, q;

struct Cmp {
  bool operator()(const int& x, const int& y) { return dep[x] < dep[y]; }
};

set<int, Cmp> seg[N];

void Dfs1(int u, int f) {
	dep[u] = dep[f] + 1;
	siz[u] = 1;
	fa[u] = f;
	for(int v : adj[u]) {
		if(v != f) {
			Dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

void Dfs2(int u, int f) {
	if(u == 0) return;
	top[u] = u == son[f] ? top[f] : u;
	Dfs2(son[u], u);
	for(int v : adj[u]) if(v != f && v != son[u]) Dfs2(v, u);
}

int Solve(int x) {
	int res = -1;
	while(x) {
		if(!seg[top[x]].empty()) res = dep[*seg[top[x]].begin()] <= dep[x] ? *seg[top[x]].begin() : res;
		x = fa[top[x]];
	}
	return res;
}

int main() {
	qread(n, q);
	rep(i, 1, n-1) {
		int u, v;
		qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	Dfs1(1, 0);
	Dfs2(1, 0);
	rep(i, 1, q) {
		int op, x;
		qread(op, x);
		if(op == 0) {
			if(clr[x] == 0) seg[top[x]].insert(x), clr[x] = 1;
			else seg[top[x]].erase(x), clr[x] = 0;
		} else {
			qwrite(Solve(x), '\n');
		}
	}
	return 0;
}

