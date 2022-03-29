// Problem: P6773 [NOI2020] 命运
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6773
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const int mod = 1e9 + 7;
const int mod = 998244353;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
	}
	return res;
}

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 5e5 + 5;
const int L = 22;

int lson[N*L], rson[N*L], sum[N*L], lazy[N*L], rt[N], tt;
int n, m;
vector<int> adj[N], lim[N];
int dep[N];

inline void setlazy(int o, int x) {
	lazy[o] = 1ll * lazy[o] * x % mod;
	sum[o] = 1ll * sum[o] * x % mod;
}

inline void pushdown(int o) {
	if(lazy[o] != 1) {
		int x = lazy[o]; lazy[o] = 1;
		setlazy(lson[o], x);
		setlazy(rson[o], x);
	}
}

inline void pushup(int o) {
	sum[o] = (sum[lson[o]] + sum[rson[o]]) % mod;
}

inline void add(int& o, int p, int l, int r) {
	if(!o) o = ++tt, lazy[o] = 1;
	++sum[o];
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) add(lson[o], p, l, mid);
	else add(rson[o], p, mid+1, r);
}

inline void merge(int& o, int o1, int o2, int l, int r, int pu, int pv, int s) {
	if(!o1 && !o2) return o = 0, void();
	if(!o1) {
		o = o2;
		setlazy(o, pu);
		return;
	}
	if(!o2) {
		o = o1;
		setlazy(o, (pv + s) % mod);
		return;
	}
	if(l == r) {
		o = o1;
		sum[o] = (1ll * pu * sum[o2] + 1ll * (pv + s) * sum[o1] + 1ll * sum[o1] * sum[o2]) % mod;
		return;
	}
	pushdown(o1);
	pushdown(o2);
	int mid = l + r >> 1;
	int p1 = sum[lson[o1]], p2 = sum[lson[o2]];
	merge(lson[o], lson[o1], lson[o2], l, mid, pu, pv, s);
	merge(rson[o], rson[o1], rson[o2], mid+1, r, (pu+p1)%mod, (pv+p2)%mod, s);
	pushup(o);
}

inline void mul(int o, int ql, int qr, int x, int l, int r) {
	if(!o) return;
	if(ql <= l && r <= qr) {
		setlazy(o, x);
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) mul(lson[o], ql, qr, x, l, mid);
	if(mid < qr) mul(rson[o], ql, qr, x, mid+1, r);
	pushup(o);
}

inline int query(int o, int p, int l, int r) {
	if(l == r) return sum[o];
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) return query(lson[o], p, l, mid);
	else return query(rson[o], p, mid+1, r);
}

inline void dfsd(int o, int l, int r) {
	if(l == r) {
		cerr << sum[o] << " \n"[r == n];
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	dfsd(lson[o], l, mid);
	dfsd(rson[o], mid+1, r);
}

inline void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	int mx = 0;
	for(int v : lim[u]) mx = max(mx, dep[v]);
	add(rt[u], mx, 0, n);
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			int s = sum[rt[v]];
			mul(rt[v], dep[u], n, 0, 0, n);
			merge(rt[u], rt[u], rt[v], 0, n, 0, 0, s);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 2, n) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	cin >> m;
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		lim[v].pb(u);
	}
	
	dfs(1, 0);
	
	cout << query(rt[1], 0, 0, n);
	
	return 0;
}
