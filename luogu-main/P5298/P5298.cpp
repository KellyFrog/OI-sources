// Problem: P5298 [PKUWC2018]Minimax
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5298
// Memory Limit: 500 MB
// Time Limit: 1000 ms
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

const int N = 3e5 + 5;
const int L = 40;

int sum[N*L], lson[N*L], rson[N*L], lazy[N*L], rt[N], tt;
int n;
vector<int> adj[N];
vector<int> d;
int a[N];

inline void setlazy(int o, int x) {
	sum[o] = 1ll * sum[o] * x % mod;
	lazy[o] = 1ll * lazy[o] * x % mod;
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

inline void merge(int& o, int o1, int o2, int l, int r, int p1, int p2, int s1, int s2, int p) {
	if(!o1 && !o2) {
		o = 0;
		return;
	}
	if(!o1) {
		o = o2;
		setlazy(o, (1ll * p * p1 + 1ll * (mod+1 - p) * s1) % mod);
		return;
	}
	if(!o2) {
		o = o1;
		setlazy(o, (1ll * p * p2 + 1ll * (mod+1 - p) * s2) % mod);
		return;
	}
	assert(l != r);
	pushdown(o1);
	pushdown(o2);
	int mid = l + r >> 1;
	int v1 = sum[lson[o1]], v2 = sum[rson[o1]];
	int v3 = sum[lson[o2]], v4 = sum[rson[o2]];
	o = o1;
	merge(lson[o], lson[o1], lson[o2], l, mid, p1, p2, (s1 + v2) % mod, (s2 + v4) % mod, p);
	merge(rson[o], rson[o1], rson[o2], mid+1, r, (p1 + v1) % mod, (p2 + v3) % mod, s1, s2, p);
	pushup(o);
}

inline void dfs(int u, int fa) {
	if(adj[u].empty()) {
		add(rt[u], a[u], 1, n);
	} else {
		int p = 1ll * a[u] * qpow(10000, mod-2) % mod;
		int ls = adj[u][0], rs = adj[u][1];
		dfs(ls, u);
		dfs(rs, u);
		merge(rt[u], rt[ls], rt[rs], 1, n, 0, 0, 0, 0, p);
	}
}

int ans = 0;

inline void dfsans(int o, int l, int r) {
	if(l == r) {
		ans = (ans + 1ll * l * sum[o] % mod * sum[o] % mod * d[l-1]) % mod;
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	dfsans(lson[o], l, mid);
	dfsans(rson[o], mid+1, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) {
		int f; cin >> f;
		if(f) adj[f].pb(i);
	}
	
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) if(adj[i].empty()) d.pb(a[i]);
	sort(d.begin(), d.end());
	auto ed = unique(d.begin(), d.end());
	rep(i, 1, n) if(adj[i].empty()) a[i] = lower_bound(d.begin(), ed, a[i]) - d.begin() + 1;
	
	dfs(1, 0);
	
	dfsans(rt[1], 1, n);
	
	cout << ans << "\n";
	
	
	return 0;
}
