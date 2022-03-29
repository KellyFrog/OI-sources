// Problem: CF1257F Make Them Similar
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1257F
// Memory Limit: 1000 MB
// Time Limit: 4000 ms

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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const int N = 105;
const int base = 1333331;
const int S = 1<<15;
const int mod1 = 1234567891;
const int mod2 = 1e9 + 7;

int a[N], b[N], c[N], d[N];
int n;
map<pair<int, int>, int> vmap;

int gethash1() {
	int ret = 0;
	rep(i, 1, n) ret = (1ll * base * ret + c[i] + S) % mod1;
	return ret;
}

int gethash2() {
	int ret = 0;
	rep(i, 1, n) ret = (1ll * ret * base + c[i] + S) % mod2;
	return ret;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	int lim = (1 << 16) - 1;
	rep(i, 1, n) b[i] = (a[i] & lim);
	rep(s, 0, lim) {
		rep(i, 1, n) d[i] = __builtin_popcount(b[i] ^ s);
		rep(i, 2, n) c[i] = d[i] - d[i-1];
		int hs1 = gethash1();
		int hs2 = gethash2();
		vmap[mp(hs1, hs2)] = s;
	}
	
	rep(i, 1, n) b[i] = a[i] >> 15;
	rep(s, 0, lim) {
		rep(i, 1, n) d[i] = __builtin_popcount(b[i] ^ s);
		rep(i, 2, n) c[i] = d[i] - d[i-1];
		rep(i, 2, n) c[i] = -c[i];
		int hs1 = gethash1();
		int hs2 = gethash2();
		if(vmap.count(mp(hs1, hs2))) {
			int low = vmap[mp(hs1, hs2)];
			int high = s;
			cout << (low | high << 15) << "\n";
			return 0;
		}
	}
	cout << -1 << "\n";
	
	return 0;
}