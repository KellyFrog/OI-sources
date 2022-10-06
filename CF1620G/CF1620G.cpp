// Problem: CF1620G Subsequences Galore
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1620G
// Memory Limit: 1000 MB
// Time Limit: 10000 ms
// Create Time: 2022-03-20 15:16:59
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

const int N = 23;
const int M = 1e5 + 5;

int g[1<<N|5];
int cnt[N+5][27];
int n;
char s[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) {
		cin >> (s + 1);
		int m = strlen(s + 1);
		rep(j, 1, m) ++cnt[i][s[j]-'a'];
	}

	int u = (1 << n) - 1;
	rep(s, 1, u) {
		g[s] = 1;
		rep(c, 0, 25) {
			int mi = 1e9;
			rep(i, 1, n) {
				if(s >> i-1 & 1) {
					mi = min(mi, cnt[i][c]);
				}
			}
			g[s] = 1ll * g[s] * (mi + 1) % mod;
		}
		if(__builtin_popcount(s) % 2 == 0) g[s] = mod-g[s];
	}

	rep(i, 0, n-1) {
		rep(j, 0, u) {
			if(!(j >> i & 1)) upd(g[j | 1 << i], g[j]);
		}
	}

	ll ans = 0;
	rep(s, 0, u) {
		int res = 0;
		rep(i, 1, n) if(s >> i-1 & 1) res += i;
		ans ^= 1ll * res * __builtin_popcount(s) * g[s];
	}

	cout << ans << "\n";
	
	return 0;
}

