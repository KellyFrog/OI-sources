// Problem: P4383 [八省联考 2018] 林克卡特树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4383
// Memory Limit: 1000 MB
// Time Limit: 10000 ms
// Create Time: 2022-03-05 21:43:17
// Input/Output: stdin/stdout
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 3e5 + 5;

struct P {
	ll val;
	int t;
	P(ll val, int t) : val(val), t(t) {}
	P() {}
};

P operator + (const P& x, const P& y) {
	return P(x.val + y.val, x.t + y.t);
}

bool operator < (const P& x, const P& y) {
	return x.val == y.val ? x.t > y.t : x.val < y.val;
}

int n, k;
vector<pair<int, int>> adj[N];
P f[N][2];
ll p;

inline void dfs(int u, int fa) {
	P tmp[3];
	tmp[0] = tmp[1] = tmp[2] = P(0, 0);
	for(auto [v, w] : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			P mx = max(P(0, 0), f[v][0]);
			tmp[2] = max(tmp[2] + mx, tmp[1] + f[v][1] + P(w, 0));
			tmp[1] = max(tmp[1] + mx, tmp[0] + f[v][1] + P(w, 0));
			tmp[0] = tmp[0] + mx;
		}
	}
	f[u][0] = max(tmp[0], tmp[2] + P(-p, 1));
	f[u][1] = tmp[1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	++k;
	rep(i, 1, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	
	ll ans = 0;
	ll l = -3e11, r = 3e11;
	// ll l = 1, r = 10;
	while(l <= r) {
		p = l + r >> 1;
		dfs(1, 0);
		int t = f[1][0].t;
		
		// debug("p = {}, get dp = {}, {}\n", p, f[1][0].val, f[1][0].t);
		// rep(i, 1, n) debug("f[{}] = [({}, {}), ({}, {})]\n", i, f[i][0].val, f[i][0].t, f[i][1].val, f[i][1].t);
		
		if(t <= k) {
			ans = f[1][0].val + 1ll * k * p;
			r = p - 1;
		} else {
			l = p + 1;
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}
