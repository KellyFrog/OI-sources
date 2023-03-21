// Problem: U77167 【模板】大水题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U77167
// Memory Limit: 500 MB
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

int dep[N], anc[N][21], mx[N][21], mi[N][21], siz[N];
ll dis[N];
vector<pair<int, int>> adj[N];
int n, q, s;

inline void dfs(int u, int fa, int lw) {
	dep[u] = dep[fa] + 1;
	dis[u] = dis[fa] + lw;
	mi[u][0] = mx[u][0] = lw;
	anc[u][0] = fa;
	siz[u] = 1;
	rep(i, 1, 20) {
		anc[u][i] = anc[anc[u][i-1]][i-1];
		mx[u][i] = max(mx[u][i-1], mx[anc[u][i-1]][i-1]);
		mi[u][i] = min(mi[u][i-1], mi[anc[u][i-1]][i-1]);
	}
	for(auto [v, w] : adj[u]) {
		if(v != fa) dfs(v, u, w), siz[u] += siz[v];
	}
}

int solve(int x, int y, bool f) {
	int x0 = x, y0 = y;
	if(dep[x] < dep[y]) swap(x, y);
	int mxans = 0, mians = 1e9;
	per(i, 0, 20) {
		if(dep[anc[x][i]] >= dep[y]) {
			mxans = max(mxans, mx[x][i]);
			mians = min(mians, mi[x][i]);
			x = anc[x][i];
		}
	}
	if(x == y) {
		if(f) cout << x << " " << dis[x0] + dis[y0] - dis[x] * 2 << " " << mxans << " " << mians << "\n";
		return x;
	}
	per(i, 0, 20) {
		if(anc[x][i] != anc[y][i]) {
			mxans = max(mxans, mx[x][i]);
			mxans = max(mxans, mx[y][i]);
			mians = min(mians, mi[x][i]);
			mians = min(mians, mi[y][i]);
			x = anc[x][i];
			y = anc[y][i];
		}
	}
	
	mxans = max(mxans, mx[x][0]); mxans = max(mxans, mx[y][0]);
	mians = min(mians, mi[x][0]); mians = min(mians, mx[y][0]);
	
	x = anc[x][0], y = anc[y][0];
	if(f) cout << x << " " << dis[x0] + dis[y0] - dis[x] * 2 << " " << mxans << " " << mians << "\n";
	return x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q >> s;
	rep(i, 1, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	
	dfs(1, 0, 0);
	
	rep(i, 1, n) {
		int lca = solve(i, s, 0);
		cout << dis[i] + dis[s] - dis[lca] * 2 << " " << dep[i] << " " << (i==1 ? 1 : anc[i][0]) << " " << (i==1 ? adj[i].size() : adj[i].size() - 1) << " " << siz[i] << "\n";
	}
	while(q--) {
		int x, y;
		cin >> x >> y;
		solve(x, y, 1);
	}
	
	return 0;
}
