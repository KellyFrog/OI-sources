// Problem: P3384 【模板】轻重链剖分/树链剖分
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3384
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Create Time: 2022-04-14 19:35:42
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int n, q, rt, P;
vector<int> adj[N];
int a[N], sgn[N], seg[N], sgncnt, fat[N], dep[N], siz[N], son[N], top[N];
int sum[N<<2], lazy[N<<2];

inline void setlazy(int o, int x, int l, int r) {
	sum[o] = (sum[o] + 1ll * x * (r - l + 1)) % P;
	lazy[o] = (lazy[o] + x) % P;
}

inline void pushdown(int o, int l, int r) {
	if(lazy[o]) {
		int mid = l + r >> 1;
		setlazy(o << 1, lazy[o], l, mid);
		setlazy(o << 1 | 1, lazy[o], mid + 1, r);
		lazy[o] = 0;
	}
}

inline void pushup(int o) {
	sum[o] = (sum[o << 1] + sum[o << 1 | 1]) % P;
}

inline void add(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) {
		setlazy(o, x, l, r);
		return;
	}
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, x, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[o];
	pushdown(o, l, r);
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res = (res + query(o << 1, ql, qr, l, mid)) % P;
	if(mid < qr) res = (res + query(o << 1 | 1, ql, qr, mid + 1, r)) % P;
	return res;
}

inline void dfs1(int u, int fa) {
	siz[u] = 1;
	son[u] = 0;
	fat[u] = fa;
	dep[u] = dep[fa] + 1;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs1(v, u);
			if(siz[v] > siz[son[u]]) son[u] = v;
			siz[u] += siz[v];
		}
	}
}

inline void dfs2(int u, int fa) {
	top[u] = u == son[fa] ? top[fa] : u;
	seg[sgn[u] = ++sgncnt] = u;
	if(son[u]) dfs2(son[u], u);
	for(int v : adj[u]) {
		if(v != fa && v != son[u]) dfs2(v, u);
	}
}

inline void routeadd(int x, int y, int z) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		add(1, sgn[top[x]], sgn[x], z, 1, n);
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	add(1, sgn[x], sgn[y], z, 1, n);
}

inline int routequery(int x, int y) {
	int res = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		res = (res + query(1, sgn[top[x]], sgn[x], 1, n)) % P;
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	res = (res + query(1, sgn[x], sgn[y], 1, n)) % P;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q >> rt >> P;
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs1(rt, 0);
	dfs2(rt, 0);

	rep(i, 1, n) add(1, sgn[i], sgn[i], a[i], 1, n);
	while(q--) {
		int op;
		cin >> op;
		if(op == 1) {
			int x, y, z;
			cin >> x >> y >> z;
			routeadd(x, y, z);
		} else if(op == 2) {
			int x, y;
			cin >> x >> y;
			cout << routequery(x, y) << "\n";
		} else if(op == 3) {
			int x, z;
			cin >> x >> z;
			add(1, sgn[x], sgn[x] + siz[x] - 1, z, 1, n);
		} else {
			int x;
			cin >> x;
			cout << query(1, sgn[x], sgn[x] + siz[x] - 1, 1, n) << "\n";
		}
	}

	return 0;
}