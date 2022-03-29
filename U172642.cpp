// Problem: U172642 PKUWC2019 D1T1
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U172642
// Memory Limit: 128 MB
// Time Limit: 2500 ms
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 21;
const int M = 205;
const int K = 1 << 20 | 5;

int n, m;
int cnt[N][K], lbt[K], f[K];
int eg[N][N];
int pw[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		eg[v][u] = 1;
	}
	int U = (1 << n) - 1;
	rep(S, 1, U) {
		lbt[S] = (S & 1) ? 0 : lbt[S >> 1] + 1;
	}
	rep(i, 1, n) {
		rep(S, 1, U) {
			cnt[i][S] = eg[i][lbt[S]+1] + cnt[i][S^(1<<lbt[S])];
		}
	}
	
	pw[0] = 1;
	rep(i, 1, m) pw[i] = 2 * pw[i-1] % mod;
	f[0] = 1;
	rep(S, 1, U) {
		rep(i, 1, n) {
			if(S >> i - 1 & 1) {
				f[S] = (f[S] + 1ll * f[S ^ (1 << i-1)] * pw[cnt[i][S]]) % mod;
			}
		}
	}
	
	cout << f[U] << "\n";
	
	return 0;
}
