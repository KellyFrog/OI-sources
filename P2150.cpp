// Problem: P2150 [NOI2015] 寿司晚宴
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2150
// Memory Limit: 125 MB
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

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 505;
const int H = 1 << 8 | 5;

vector<int> prime = {2, 3, 5, 7, 11, 13, 17, 19};
// vector<int> prime = {2, 3};
int n, P;
int f[N][H][H], tmp[H], tmp2[H][H];
int fac[N];
vector<int> adj[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> P;
	
	rep(i, 2, n) {
		int x = i;
		for(int j = 0; j < prime.size(); ++j) {
			if(x % prime[j] == 0) {
				fac[i] |= 1 << j;
				while(x % prime[j] == 0) x /= prime[j];
			}
		}
		adj[x].pb(i);
	}
	
	int u = (1 << 8) - 1;
	
	f[1][0][0] = 1;
	
	int last = 1;
	
	for(int x : adj[1]) {
		memcpy(tmp2, f[1], sizeof f[1]);
		rep(s1, 0, u) rep(s2, 0, u) {
			if(s1 & s2) continue;
			if(!(s1 & fac[x])) f[1][s1][s2|fac[x]] = (f[1][s1][s2|fac[x]] + tmp2[s1][s2]) % P;
			if(!(s2 & fac[x])) f[1][s1|fac[x]][s2] = (f[1][s1|fac[x]][s2] + tmp2[s1][s2]) % P;
		}
	}
	
	rep(i, 23, 500) {
		if(adj[i].empty()) continue;
		memset(tmp, 0, sizeof tmp);
		memcpy(f[i], f[last], sizeof f[i]);
		tmp[0] = 1;
		for(int x : adj[i]) {
			per(s, 0, u) tmp[s|fac[x]] = (tmp[s|fac[x]] + tmp[s]) % P;
		}
		--tmp[0];
		rep(s1, 0, u) rep(s2, 0, u) {
			if(s1 & s2) continue;
			rep(s, 0, u) {
				if(!(s1 & s)) f[i][s1][s2|s] = (f[i][s1][s2|s] + 1ll * f[last][s1][s2] * tmp[s]) % P;
				if(!(s2 & s)) f[i][s1|s][s2] = (f[i][s1|s][s2] + 1ll * f[last][s1][s2] * tmp[s]) % P;
			}
		}
		last = i;
	}
	
	int ans = 0;
	rep(s1, 0, u) rep(s2, 0, u) ans = (ans + f[last][s1][s2]) % P;
	cout << ans << "\n";
	
	return 0;
}
