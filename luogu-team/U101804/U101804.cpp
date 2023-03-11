// Problem: U101804 随机爬树（climb）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U101804
// Memory Limit: 125 MB
// Time Limit: 1000 ms

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

const int N = 1e5 + 5;

int fat[N], a[N], w[N];
int n, q;
vector<int> adj[N];
int dfn[N], siz[N], dfncnt;
int f[N], psum[N], dist[N], sval[N];

inline void dfs(int u, int fa) {
	dfn[u] = ++dfncnt;
	sval[dfn[u]] = 1ll * f[u] * a[u] % mod;
	siz[u] = 1;
	dist[u] = dist[fa] + a[u];
	for(int v : adj[u]) {
		upd(psum[u], w[v]);
	}
	int isum = qpow(psum[u], mod-2);
	for(int v : adj[u]) {
		f[v] = 1ll * f[u] * isum % mod * w[v] % mod;
		dfs(v, u);
		siz[u] += siz[v];
	}
}

int sum[N<<2], mul[N<<2];

inline void setlazy(int cur, int x) {
	sum[cur] = 1ll * sum[cur] * x % mod;
	mul[cur] = 1ll * mul[cur] * x % mod;
}

inline void pushdown(int cur) {
	if(mul[cur] != 1) {
		setlazy(cur<<1, mul[cur]);
		setlazy(cur<<1|1, mul[cur]);
		mul[cur] = 1;
	}
}

inline void pushup(int cur) {
	upd(sum[cur], sum[cur<<1], sum[cur<<1|1]);
}

inline void build(int cur, int l, int r) {
	sum[cur] = 0;
	mul[cur] = 1;
	if(l == r) {
		sum[cur] = sval[l];
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

inline void modify(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) modify(cur<<1, ql, qr, x, l, mid);
	if(mid < qr) modify(cur<<1|1, ql, qr, x, mid+1, r);
	pushup(cur);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 2, n) {
		cin >> fat[i];
		adj[fat[i]].pb(i);
	}
	rep(i, 1, n) cin >> w[i];
	rep(i, 1, n) cin >> a[i];
	
	f[1] = 1;
	dfs(1, 0);
	
	build(1, 1, n);
	cout << sum[1] << "\n";
	
	cin >> q;
	
	while(q--) {
		int u, aa, ww;
		cin >> u >> ww >> aa;
		
		if(u != 1) {
			int osum = psum[fat[u]];
			int nsum = psum[fat[u]] - w[u] + ww;
			if(nsum >= mod) nsum -= mod;
			if(nsum < 0) nsum += mod;
			
			psum[fat[u]] = nsum;
			
			debug("[{}, {}] *= {}\n", dfn[fat[u]]+1, dfn[fat[u]]+siz[fat[u]]-1,double(osum) / nsum);
			modify(1, dfn[fat[u]]+1, dfn[fat[u]]+siz[fat[u]]-1, 1ll*osum*qpow(nsum, mod-2)%mod, 1, n);
			modify(1, dfn[u], dfn[u]+siz[u]-1, 1ll*ww*qpow(w[u], mod-2)%mod, 1, n);
		}
		
		modify(1, dfn[u], dfn[u], 1ll*aa*qpow(a[u],mod-2)%mod, 1, n);
		
		cout << sum[1] << "\n";
		
		a[u] = aa;
		w[u] = ww;
	}
	
	return 0;
}
