// Problem: CF1580D Subsequence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1580D
// Memory Limit: 250 MB
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 4e3 + 5;

int n, k;
int a[N], ls[N], rs[N], stk[N], top;
int siz[N];
ll f[N][N], tmp[N];

inline void dfs(int u) {
	if(!u) return;
	vector<int> adj = {ls[u], rs[u]};
	f[u][0] = 0;
	f[u][1] = 1ll * a[u] * k - a[u];
	siz[u] = 1;
	for(int v : adj) {
		dfs(v);
		memcpy(tmp, f[u], sizeof tmp);
		memset(f[u], 0xf3, sizeof f[u]);
		rep(i, 0, siz[u]) rep(j, 0, siz[v]) {
			f[u][i+j] = max(f[u][i+j], tmp[i] + f[v][j] - 2ll * i * j * a[u]);
		}
		siz[u] += siz[v];
	}
	// debug("dp[siz = {}] = {}\n", siz[u], f[u][siz[u]]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	stk[++top] = 1;
	rs[0] = 1;
	rep(i, 2, n) {
		bool ok = 0;
		while(top && a[stk[top]] > a[i]) --top, ok = 1;
		if(ok) ls[i] = stk[top+1];
		rs[stk[top]] = i;
		stk[++top] = i;
	}
	
	memset(f, 0xf3, sizeof f);
	
	f[0][0] = 0;
	
	int rt = rs[0];
	dfs(rt);
	
	cout << f[rt][k] << "\n";
	
	return 0;
}
