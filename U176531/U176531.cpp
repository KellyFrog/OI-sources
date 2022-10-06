// Problem: U176531 count
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U176531
// Memory Limit: 128 MB
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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 1e5 + 5;

vector<ll> v = {1, 199981, 199982, 199983, 199984, 199985, 199986, 199987, 199988, 199989, 199990, 200000, 200001, 1599981, 1599982, 1599983, 1599984, 1599985, 1599986, 1599987, 1599988, 1599989, 1599990, 2600000, 2600001, 13199998, 35000000, 35000001, 35199981, 35199982, 35199983, 35199984, 35199985, 35199986, 35199987, 35199988, 35199989, 35199990, 35200000, 35200001, 117463825, 500000000, 500000001, 500199981, 500199982, 500199983, 500199984, 500199985, 500199986, 500199987, 500199988, 500199989, 500199990, 500200000, 500200001, 501599981, 501599982, 501599983, 501599984, 501599985, 501599986, 501599987, 501599988, 501599989, 501599990, 502600000, 502600001, 513199998, 535000000, 535000001, 535199981, 535199982, 535199983, 535199984, 535199985, 535199986, 
535199987, 535199988, 535199989, 535199990, 535200000, 535200001, 1111111110};

char S[N];
int len;
ll n;

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0); cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> S + 1;
	len = strlen(S + 1);
	if(len > 15) {
		n = 1e15;
	} else {
		rep(i, 1, len) n = 10ll * n + S[i]-'0';
	}
	ll ans = 0;
	for(ll x : v) if(x <= n) ans += x;
	cout << ans << "\n";
	
	return 0;
}