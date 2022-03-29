// Problem: Purple Crayon
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1615/problem/E
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

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e6 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int lcnt;
vector<int> adj[N];
int n, k, fat[N], dfn[N], dfncnt, seq[N], siz[N];
bool lf[N];
ll mx[N<<2], mxpos[N<<2], lazy[N<<2];
bool vis[N];

inline void setlazy(int cur, ll x) {
	mx[cur] += x;
	lazy[cur] += x;
}

inline void pushdown(int cur) {
	if(lazy[cur]) {
		setlazy(cur<<1, lazy[cur]);
		setlazy(cur<<1|1, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void pushup(int cur) {
	if(mx[cur<<1] > mx[cur<<1|1]) {
		mx[cur] = mx[cur<<1];
		mxpos[cur] = mxpos[cur<<1];
	} else {
		mx[cur] = mx[cur<<1|1];
		mxpos[cur] = mxpos[cur<<1|1];
	}
	debug("mx[{}] = {} {}\n", cur, mx[cur], mxpos[cur]);
}

inline void build(int cur, int l, int r) {
	mx[cur] = -inf;
	if(l == r) {
		int u = seq[l];
		if(lf[u]) mx[cur] = 0, mxpos[cur] = u;
		return;
	}
	int mid = l + r >> 1;
	build(cur<<1, l, mid);
	build(cur<<1|1, mid+1, r);
	pushup(cur);
}

inline void add(int cur, int ql, int qr, ll x, int l, int r) {
	if(l==1 && r==n) debug("[{}, {}] {}\n", ql, qr, x);
	assert(l <= r && ql <= qr);
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur<<1, ql, qr, x, l, mid);
	if(mid < qr) add(cur<<1|1, ql, qr, x, mid+1, r);
	debug("cur={}, l={}, r={}\n", cur, l, r);
	pushup(cur);
}

inline void dfs(int u, int fa) {
	fat[u] = fa;
	dfn[u] = ++dfncnt;
	seq[dfn[u]] = u;
	lf[u] = 1;
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			siz[u] += siz[v];
			lf[u] = 0;
		}
	}
	if(lf[u]) {
		debug("lf = {}\n", u);
		++lcnt;
	}
}

int ans = 0;

inline void dfsans(int u, int fa) {
	if(!vis[u]) {
		ans += siz[u];
		return;
	}
	for(int v : adj[u]) {
		if(v != fa) dfsans(v, u);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n-1) {
		int u ,v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	build(1, 1, n);
	
	if(lcnt <= k) {
		ll ans = 0;
		rep(i, lcnt, k) {
			ans = max(ans, 1ll*i*(n-i));
		}
		cout << ans << "\n";
		return 0;
	}
	
	rep(i, 1, n) cerr << dfn[i] << " \n"[i == n];
	
	rep(u, 1, n) add(1, dfn[u], dfn[u]+siz[u]-1, 1, 1, n);
	
	int cnt = n;
	ll ans = -1e18;
	
	rep(i, 1, k) {
		int u = mxpos[1];
		add(1, dfn[u], dfn[u], -inf, 1, n);
		while(u && !vis[u]) {
			--cnt;
			add(1, dfn[u], dfn[u]+siz[u]-1, -1, 1, n);
			vis[u] =1 ;
			u = fat[u];
		}
		int p = min(cnt, n/2);
		ans = max(ans, 1ll * (n - i - p) * (i - p));
	}
	
	
	cout << ans << "\n";
	
	return 0;
}
