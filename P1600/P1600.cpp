//Author: Chenkaifeng

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

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"

inline void qread() {}
template<typename T1, typename ...T2>
inline void qread(T1 &x, T2&... ls) {
	x = 0;
	rg char ch = ' ';
	rg int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
	qread(ls...);
}

template<typename T>
inline void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) return putchar('0' + x), void();
	qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
inline void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
}

template<typename T>
inline void chkmax(T& x, T y) {
	if(x < y) x = y;
}

template<typename T>
inline void chkmin(T& x, T y) {
	if(x > y) x = y;
}

template<typename T>
inline void chkmod(T& x, ll mod) {
	x = x > mod ? x - mod : x;
}

template<typename T>
inline void chkadd(T& x, T y, ll mod) {
	x = x + y > mod ? x + y - mod : x + y;
}

template<typename T>
inline void chkmns(T& x, T y, ll mod) {
	x = x - y < 0 ? x - y + mod : x - y;
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 3e5 + 5;

vi adj[N], ins1[N], ins2[N], del1[N], del2[N];
int sum[N << 5], lson[N << 5], rson[N << 5], rt[N], cnt;
int fa[N][21], dep[N], tim[N], ans[N];
int n, m;

void Dfs1(int u, int f) {
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int v : adj[u]) if(v != f) Dfs1(v, u);
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 20) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	per(i, 0, 20) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

void Add(int& cur, int p, int x, int l, int r) {
	if(cur == 0) cur = ++cnt;
	sum[cur] += x;
	if(l == r) return;
	rg int mid = l + r >> 1;
	if(p <= mid) Add(lson[cur], p, x, l, mid);
	else Add(rson[cur], p, x, mid + 1, r);
}

int Query(int cur, int p, int l, int r) {
	if(cur == 0) return 0;
	if(l == r) return sum[cur];
	rg int mid = l + r >> 1;
	if(p <= mid) return Query(lson[cur], p, l, mid);
	else return Query(rson[cur], p, mid + 1, r);
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	sum[cur] += sum[old];
	if(l == r) return;
	rg int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
}

void Dfs2(int u, int f) {
	for(int v : adj[u]) if(v != f) Dfs2(v, u), Merge(rt[u], rt[v], 1, 2 * n);
	for(int x : ins1[u]) Add(rt[u], x, 1, 1, 2 * n);
	for(int x : del1[u]) Add(rt[u], x, -1, 1, 2 * n);
	ans[u] += Query(rt[u], dep[u] + tim[u], 1, 2 * n);
}

void Dfs3(int u, int f) {
	for(int v : adj[u]) if(v != f) Dfs3(v, u), Merge(rt[u], rt[v], 1, 2 * n);
	for(int x : ins2[u]) Add(rt[u], x, 1, 1, 2 * n);
	for(int x : del2[u]) Add(rt[u], x, -1, 1, 2 * n);
	ans[u] += Query(rt[u], tim[u] - dep[u] + n, 1, 2 * n);
	//tim[u] = dis(s, lca) + dis(u, lca)
	//tim[u] = dep[s] - dep[fa[lca][0]] + dep[u] - dep[fa[lca][0]]
	//tim[u] - dep[u] = dep[s] - 2 * dep[fa[lca][0]]
}

int main() {
	qread(n, m);
	rep(i, 1, n-1) {
		rg int u, v;
		qread(u, v);
		adj[u].pb(v), adj[v].pb(u);
	}
	Dfs1(1, 0);
	rep(i, 1, n) qread(tim[i]);
	rep(i, 1, m) {
		rg int s, t;
		qread(s, t);
		rg int lca = LCA(s, t);
		ins1[s].pb(dep[s]);
		ins2[t].pb(dep[s] - 2 * dep[lca] + n);
		del1[fa[lca][0]].pb(dep[s]);
		del2[fa[lca][0]].pb(dep[s] - 2 * dep[lca] + n);
		if(dep[lca] + tim[lca] == dep[s]) ans[lca]--;
	}
	Dfs2(1, 0);
	memset(rt, 0, sizeof rt), memset(lson, 0, sizeof lson), memset(rson, 0, sizeof rson), memset(sum, 0, sizeof sum), cnt = 0;
	Dfs3(1, 0);
	rep(i, 1, n) qwrite(ans[i], " \n"[i == n]);
	return 0;
}
