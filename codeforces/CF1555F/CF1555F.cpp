// Problem: F. Good Graph
// Contest: Codeforces - Educational Codeforces Round 112 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1555/problem/F
// Memory Limit: 256 MB
// Time Limit: 2000 ms

/*
 * Author: chenkaifeng @BDFZ
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 5e5 + 5;

vector<pair<int, bool> > adj[N];
int siz[N], fat[N], son[N], dep[N], top[N], sgn[N], sgncnt;
bool dis[N];
bool sum[N<<2], lazy[N<<2];
int n, m;
pair<pair<int, int>, bool> eg[N];

inline void setlazy(int cur) {
	sum[cur] = lazy[cur] = 1;
}

inline void pushdown(int cur) {
	if(lazy[cur]) {
		setlazy(cur << 1);
		setlazy(cur << 1 | 1);
		lazy[cur] = 0;
	}
}

inline void pushup(int cur) {
	sum[cur] = sum[cur << 1] || sum[cur << 1 | 1];
}

inline void modify(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) modify(cur << 1, ql, qr, l, mid);
	if(mid < qr) modify(cur << 1 | 1, ql, qr, mid + 1, r);
	pushup(cur);
	assert(sum[cur]);
}

inline bool query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	pushdown(cur);
	int mid = l + r >> 1;
	bool res = 0;
	if(ql <= mid) res |= query(cur << 1, ql, qr, l, mid);
	if(mid < qr) res |= query(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

inline void dfs1(int u, int fa) {
	siz[u] = 1;
	son[u] = 0;
	dep[u] = dep[fa] + 1;
	fat[u] = fa;
	for(auto [v, w] : adj[u]) {
		if(v != fa) {
			dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

inline void dfs2(int u, int fa, int tp, bool w) {
	sgn[u] = ++sgncnt;
	top[u] = tp;
	dis[u] = dis[fa] ^ w;
	for(auto [v, w] : adj[u]) if(v == son[u]) dfs2(v, u, tp, w);
	for(auto [v, w] : adj[u]) if(v != son[u] && v != fa) dfs2(v, u, v, w);
}

inline void modify(int l, int r, int p) {
	if(l == p) l++;
	if(r == p) r--;
	if(l <= r) modify(1, l, r, 1, n);
}

inline bool query(int l, int r, int p) {
	if(l == p) l++;
	if(r == p) r--;
	if(l > r) return 0;
	return query(1, l, r, 1, n);
}

inline int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fat[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}

inline bool routequery(int x, int y) {
	int lca = LCA(x, y);
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		if(query(sgn[top[x]], sgn[x], sgn[lca])) return 1;
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	return query(sgn[x], sgn[y], sgn[lca]);
}

inline void routemodify(int x, int y) {
	int lca = LCA(x, y);
	while(top[x] !=  top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(sgn[top[x]], sgn[x], sgn[lca]);
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	modify(sgn[x], sgn[y], sgn[lca]);
}

inline bool solve(int x, int y, bool w) {
	if(dis[x] ^ dis[y] ^ w) {
		if(routequery(x, y)) return 0;
		else return routemodify(x, y), 1;
	} else {
		return 0;
	}
}

bool ans[N];
int uni[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) {
		int u, v; bool w;
		cin >> u >> v >> w;
		eg[i] = mp(mp(u, v), w);
		int x = find(u), y = find(v);
		if(x != y) {
			adj[u].pb(mp(v, w));
			adj[v].pb(mp(u, w));
			uni[x] = y;
			ans[i] = 1;
		}
	}
	
	rep(i, 1, n) {
		if(!dep[i]) {
			dfs1(i, 0);
			dfs2(i, 0, i, 0);
		}
	}
	
	
	rep(i, 1, m) {
		if(!ans[i]) {
			ans[i] = solve(eg[i].fi.fi, eg[i].fi.se, eg[i].se);
		}
	}
	
	rep(i, 1, m) cout << (ans[i] ? "Yes" : "No") << "\n";
	
	return 0;
}