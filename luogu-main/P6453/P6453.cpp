// Problem: P6453 [COCI2008-2009#4] PERIODNI
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6453
// Memory Limit: 31 MB
// Time Limit: 5000 ms
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

const int mod = 1e9 + 7;
// const int mod = 998244353;

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

const int N = 505;
const int M = 1e6 + 5;

int f[N][N], g[N][N];
int fac[M], ifac[M];
int n, k;
int a[N], ls[N], rs[N], siz[N], stk[N], top;

inline int cob(int n, int m) {
	return 1ll * fac[n] * ifac[m] % mod * ifac[n-m] % mod;
}

inline void dfs(int u, int fa) {
	if(!u) return;
	dfs(ls[u], u);
	dfs(rs[u], u);
	siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	rep(s, 0, siz[u]) {
		rep(j, 0, siz[ls[u]]) {
			g[u][s] = (g[u][s] + 1ll * f[ls[u]][j] * f[rs[u]][s-j]) % mod;
		}
	}
	int d = a[u] - a[fa];
	rep(i, 0, min(k, siz[u])) {
		rep(s, 0, siz[u]) {
			if(i - s > d || i - s < 0) continue;
			f[u][i] = (f[u][i] + 1ll * g[u][s] * cob(siz[u] - s, i - s) % mod * cob(d, i - s) % mod * fac[i - s]) % mod;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	stk[++top] = 1, rs[0] = 1;
	rep(i, 2, n) {
		bool ok = 0;
		while(top && a[stk[top]] > a[i]) --top, ok = 1;
		if(ok) ls[i] = stk[top+1];
		rs[stk[top]] = i;
		stk[++top] = i;
	}
	int rt = rs[0];
	
	f[0][0] = 1;
	
	int m = 1e6;
	ifac[0] = fac[0] = ifac[1] = fac[1] = 1;
	rep(i, 2, m) fac[i] = 1ll * fac[i-1] * i % mod;
	ifac[m] = qpow(fac[m], mod-2);
	per(i, 2, m-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;
	
	dfs(rt, 0);
	
	cout << f[rt][k] << "\n";
	
	return 0;
}
