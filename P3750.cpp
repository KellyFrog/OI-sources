// Problem: P3750 [六省联考 2017] 分手是祝愿
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3750
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-07 20:40:23
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
const int mod = 1e5 + 3;

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

const int N = 1e5 + 5;

int n, m, k;
int a[N];

struct F {
	int a, b, c, x;
	F(int a, int b, int c, int x) : a(a), b(b), c(c), x(x) {}
	F() {}
};

F f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	per(i, 1, n) {
		for(int j = i + i; j <= n; j += i) a[i] ^= a[j];
		if(a[i]) {
			++m;
		}
	}
	
	int fac = 1;
	rep(i, 1, n) fac = 1ll * fac * i % mod;
	
	if(m <= k) {
		cout << 1ll * m * fac % mod << "\n";
		return 0;
	}
	
	f[k] = F(0, 1, 0, k);
	int invn = qpow(n, mod-2);
	rep(i, k+1, n-1) f[i] = F(-1ll * i * invn % mod, 1, 1ll * (i - n) * invn % mod, 1);
	f[n] = F(-1, 1, 0, 1);
	rep(i, k, n-1) {
		assert(f[i].a == 0);
		
		int t = -1ll * f[i+1].a * qpow(f[i].b, mod-2) % mod;
		f[i+1].a = (f[i+1].a + 1ll * t * f[i].b) % mod;
		f[i+1].b = (f[i+1].b + 1ll * t * f[i].c) % mod;
		f[i+1].x = (f[i+1].x + 1ll * t * f[i].x) % mod;
	}
	
	per(i, k+1, n) {
		assert(f[i].c == 0);
		int t = -1ll * f[i-1].c * qpow(f[i].b, mod-2) % mod;
		f[i-1].c = (f[i-1].c + 1ll * t * f[i].b) % mod;
		f[i-1].x = (f[i-1].x + 1ll * t * f[i].x) % mod;
	}
	
	int ans = 1ll * f[m].x * qpow(f[m].b, mod-2) % mod;
	cout << ((1ll * ans * fac) % mod + mod) % mod << "\n";
	
	return 0;
}
