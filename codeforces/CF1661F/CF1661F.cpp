// Problem: F. Teleporters
// Contest: Codeforces - Educational Codeforces Round 126 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1661/problem/F
// Memory Limit: 512 MB
// Time Limit: 7000 ms
// Create Time: 2022-04-12 18:39:37
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

const int N = 2e5 + 5;

int n, a[N];
ll m;

inline ll getans(int len, int k) {
	int x = len / k;
	int y = len % k;
	return 1ll * y * (x + 1) * (x + 1) + 1ll * (k - y) * x * x;
}

pair<ll, int> gett(int i, ll x, int tp) {
	int L = 1, R = a[i] - a[i-1];
	int res = 0;
	ll val = getans(a[i] - a[i-1], 1);
	while(L <= R) {
		int mid = L + R >> 1;
		bool ok;
		if(tp == 0) {
			ok = getans(a[i] - a[i-1], mid + 1) + x < getans(a[i] - a[i-1], mid);
		} else {
			ok = getans(a[i] - a[i-1], mid + 1) + x <= getans(a[i] - a[i-1], mid);
		}
		if(ok) {
			val = getans(a[i] - a[i-1], mid + 1);
			res = mid;
			L = mid + 1;
		} else {
			R = mid - 1;
		}
	}
	return mp(val, res);
}

pair<ll, int> calc(ll x, int tp) {
	pair<ll, int> res = mp(0, 0);
	rep(i, 2, n) {
		auto [val, t] = gett(i, x, tp);
		res.fi += val;
		res.se += t;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	a[1] = 0;
	rep(i, 2, n + 1) cin >> a[i];
	++n;
	cin >> m;

	ll L = 0, R = 1e18;
	ll ans = LONG_LONG_MAX;
	while(L <= R) {
		ll mid = L + R >> 1;
		auto [res1, t1] = calc(mid, 0);
		auto [res2, t2] = calc(mid, 1);
		// debug("[{}, {}], mid = {}, {} {}, {} {}\n", L, R, mid, res1, t1, res2, t2);
		if(m >= res2) {
			ll t = mid == 0 ? t1 : max<ll>(t2 - (m - res2) / mid, t1);
			ans = t;
			L = mid + 1;
		} else {
			R = mid - 1;
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}