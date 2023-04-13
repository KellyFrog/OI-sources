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

const int N = 1e5 + 5;

vi adj[N], ins[N], del[N];
int fa[N][21], dep[N];
pii maxi[N << 5], res[N];
int lson[N << 5], rson[N << 5], rt[N], cnt;
int n, m, s = 1e5;

void Dfs1(int u, int f) {
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
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

void PushUp(int cur) {
	maxi[cur] = maxi[lson[cur]].fi == maxi[rson[cur]].fi ? maxi[lson[cur]] : max(maxi[lson[cur]], maxi[rson[cur]]);
}

void Add(int& cur, int p, int x, int l, int r) {
	if(cur == 0) cur = ++cnt, maxi[cur] = mp(0, l);
	if(l == r) return maxi[cur].fi += x, void();
	rg int mid = l + r >> 1;
	if(p <= mid) Add(lson[cur], p, x, l, mid);
	else Add(rson[cur], p, x, mid + 1, r);
	PushUp(cur);
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	if(l == r) return maxi[cur].fi += maxi[old].fi, void();
	int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
	PushUp(cur);
}

void Dfs2(int u, int f) {
	for(int v : adj[u]) if(v != f) Dfs2(v, u), Merge(rt[u], rt[v], 1, s);
	for(int x : ins[u]) Add(rt[u], x, 1, 1, s);
	for(int x : del[u]) Add(rt[u], x, -1, 1, s);
	res[u] = maxi[rt[u]];
}

int main() {
	qread(n, m);
	rep(i, 1, n-1) {
		int u, v;
		qread(u, v);
		adj[u].pb(v), adj[v].pb(u);
	}
	Dfs1(1, 0);
	rep(i, 1, m) {
		int u, v, x;
		qread(u, v, x);
		rg int lca = LCA(u, v);
		ins[u].pb(x), ins[v].pb(x);
		del[lca].pb(x), del[fa[lca][0]].pb(x);
	}
	Dfs2(1, 0);
	rep(i, 1, n) qwrite(res[i].fi == 0 ? 0 : res[i].se, '\n');
	return 0;
}
