// Problem: U172641 【PKUWC2019】递增序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U172641
// Memory Limit: 128 MB
// Time Limit: 500 ms
// Create Time: 2022-02-22 10:37:47
<<<<<<< HEAD
// Input/Output: {"type":"stdin"}/{"type":"stdout"}
=======
// Input/Output:stdin/stdout
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
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

const int N = 100 + 5;

int f[N][N][N][2][2];
int n;
ll a[N], l[N], r[N];

inline int dfs(int k, int l, int r, int lmax, int lmin) {
<<<<<<< HEAD
	
	string pre = "";
	rep(i, 1, 3-k) pre += "  ";
	
	if(k == -1) return 1;
	if(f[k][l][r][lmax][lmin] != -1) {
		debug("{}return f[{}][{}][{}] = {}\n", pre, k, l, r, f[k][l][r][lmax][lmin]);
		return f[k][l][r][lmax][lmin];
	}
	if(l > r) return 1;
	if(k == 0 && r-l+1 > 2) return f[k][l][r][lmax][lmin] = 0;
	
	
	debug("{}dfs(k = {}, [{}, {}], lmax = {}, lmin = {}\n", pre, k, l, r, lmax, lmin);
=======
	if(k == -1) return 1;
	if(f[k][l][r][lmax][lmin] != -1) return f[k][l][r][lmax][lmin];
	if(l > r) return 1;
	if(k == 0 && r-l+1 > 2) return f[k][l][r][lmax][lmin] = 0;
	
	// debug("{}dfs(k = {}, [{}, {}], lmax = {}, lmin = {}\n", pre, k, l, r, lmax, lmin);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	
	
	int res = 0;
	
	auto check = [&](int p, int& lmx, int& lmi, int& rmx, int& rmi) {
<<<<<<< HEAD
		debug("{}check = {}, k = {}, [{}, {}]\n", pre, p, k, l, r);
		ll val = -1;
		if(lmax) {
			val = (::r[l] >> k) << k;
		}
		if(lmin) {
			val = (::l[r] >> k) << k;
=======
		// debug("{}check = {}, k = {}, [{}, {}]\n", pre, p, k, l, r);
		ll val = -1;
		if(lmax) {
			val = (::r[l] >> k+1) << k+1;
		}
		if(lmin) {
			val = (::l[r] >> k+1) << k+1;
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		}
		
		
		rep(i, l, p) if(a[i] >> k & 1) return 0;
		
		
		if(val == -1) {
			lmx = rmx = lmi = rmi = 0;
			return  1;
		}
		
<<<<<<< HEAD
=======
		// debug("{}get val = {}\n", pre, val);
		
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		if(p+1 <= r && (val | 1ll << k) > (::r[p+1] >> k << k)) return 0;
		if(l <= p && val < (::l[p] >> k << k)) return 0;
		
		if(k == 0) {
			lmx = val == ::r[l];
			lmi = val == ::l[p];
			val |= 1;
			rmx = val == ::r[p+1];
			rmi = val == ::l[r];
			
<<<<<<< HEAD
			return 1;
		}
		
		debug("{}get val = {}\n", pre, val);
		
		lmx = val == (::r[l] >> k << k);
		lmi = val == (::l[p] >> k-1 << k-1);
		
		
		debug("{}val = {}, llim = {}\n", pre, val, ::l[p] >> k-1 << k-1);
		
=======
			// debug("{}ok k = 0\n", pre);
			
			return 1;
		}
		
		lmx = val == (::r[l] >> k << k);
		lmi = val == (::l[p] >> k << k);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		
		val |= 1ll << k;
		
		rmx = val == (::r[p+1] >> k << k);
<<<<<<< HEAD
		rmi = val == (::l[r] >> k-1 << k-1);
=======
		rmi = val == (::l[r] >> k << k);
		
		// debug("{}ok\n", pre);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
		
		return 1;
	};
	
	if(k == 0 && r-l+1 > 2) return f[k][l][r][lmax][lmin] = 0;
	
	int sl = k == 0 && r-l+1 == 2 ? l : l-1;
	int sr = k == 0 && r-l+1 == 2? r-1 : r;
	
	rep(i, sl, sr) {
		int lmx = -1, lmi = - 1, rmx = -1, rmi = -1;
		if(check(i, lmx, lmi, rmx, rmi)) {
<<<<<<< HEAD
			debug("{}OK! k = {}, [{}, {}] i = {} check = ok, {}, {}, {}, {}\n", pre, k, l, r, i, lmi, lmx, rmi, rmx);
			int cur = 1ll * dfs(k-1, l, i, lmx, lmi) * dfs(k-1, i+1, r, rmx, rmi) % mod;
			res = (res + cur) % mod;
			debug("{}k = {}, [{}, {}] i = {}, get res = {}\n", pre, k, l, r, i, cur);
		}
	}
	
	debug("{}get f[{}][{}][{}][{}][{}] = {}\n", pre, k, l, r, lmax, lmin, res);
=======
			// debug("{}OK! k = {}, [{}, {}] i = {} check = ok, {}, {}, {}, {}\n", pre, k, l, r, i, lmi, lmx, rmi, rmx);
			int cur = 1ll * dfs(k-1, l, i, lmx, lmi) * dfs(k-1, i+1, r, rmx, rmi) % mod;
			res = (res + cur) % mod;
			// debug("{}k = {}, [{}, {}] i = {}, get res = {}\n", pre, k, l, r, i, cur);
		}
	}
	
	// debug("{}get f[{}][{}][{}][{}][{}] = {}\n", pre, k, l, r, lmax, lmin, res);
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
	
	return f[k][l][r][lmax][lmin] = res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> l[i];
	rep(i, 1, n) cin >> r[i];
	rep(i, 1, n) cin >> a[i];
	
	rep(i, 2, n) l[i] = max(l[i], l[i-1] + 1);
	per(i, 1, n-1) r[i] = min(r[i], r[i+1] - 1);
	
	rep(i, 1, n) if(l[i] > r[i]) {
		cout << 0 << "\n";
		return 0;
	}
	
	memset(f, -1, sizeof f);
	
<<<<<<< HEAD
	cout << dfs(2, 1, n, 1, 1) << "\n";
	
	return 0;
}
=======
	cout << dfs(61, 1, n, 1, 1) << "\n";
	
	return 0;
}
>>>>>>> 07e8fc721cf87637ca1e4d43005e936688912e6e
