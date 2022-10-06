// Problem: P5656 【模板】二元一次不定方程 (exgcd)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5656
// Memory Limit: 16 MB
// Time Limit: 500 ms
// Create Time: 2022-04-14 18:52:18
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

ll exgcd(ll a, ll b, ll& x, ll& y) {
	if(b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll tx, ty;
	ll g = exgcd(b, a%b, tx, ty);
	x = ty;
	y = tx - (a / b) * ty;
	return g;
}

void solve() {
	ll a, b, c;
	cin >> a >> b >> c;
	ll x, y;
	ll g = exgcd(a, b, x, y);
	if(c % g != 0) {
		cout << -1 << "\n";
		return;
	}
	x *= c / g;
	y *= c / g;

	ll xmi = (x % (b / g) + b / g) % (b / g); if(xmi == 0) xmi += b / g;
	ll ymx = (c - a * xmi) / b;
	ll ymi = (y % (a / g) + a / g) % (a / g); if(ymi == 0) ymi += a / g;
	ll xmx = (c - b * ymi) / a;

	if(ymx <= 0) {
		cout << xmi << " " << ymi << "\n";
	} else {
		cout << (xmx - xmi) / (b / g) + 1 << " " << xmi << " " << ymi << " " << xmx << " " << ymx << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}