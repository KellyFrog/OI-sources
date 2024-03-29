// Problem: U198434 zjl的树2
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U198434?contestId=62264
// Memory Limit: 256 MB
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

const int N = 2e6 + 5;

int n;
int a[N];
int fac[N], ifac[N];
int stk[N], top;
int last[N], from[N];
vector<int> adj[N];
int ls[N], rs[N], siz[N];

inline int cob(int n, int m) {
	return 1ll * fac[n] * ifac[m] % mod * ifac[n-m] % mod;
}

inline int dfs(int u) {
	if(u == -1) return 1;
	
	int res = 1ll * dfs(ls[u]) * dfs(rs[u]) % mod;
	
	siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	
	res = 1ll * res * cob(siz[u]-1, siz[ls[u]]) % mod;
	
	debug("dfs({}) = {}\n", u, res);
	
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	rep(i, 1, n) {
		from[i] = last[a[i]-1];
		if(a[i] > 1 && from[i] == 0) {
			cout << 0 << "\n";
			return 0;
		}
		adj[from[i]].pb(i);
		last[a[i]] = i;
	}
	memset(ls, -1, sizeof ls);
	memset(rs, -1, sizeof rs);
	rep(i, 0, n) {
		if(adj[i].empty()) continue;
		rs[i] = adj[i][adj[i].size()-1];
		int o = rs[i];
		for(int j = (int)adj[i].size()-2; j>=0; --j) {
			ls[o] = adj[i][j];
			o = adj[i][j];
		}
	}
	
	ifac[0] = fac[0] = ifac[1] = fac[1] = 1;
	rep(i, 2, n) fac[i] = 1ll * fac[i-1] * i % mod;
	ifac[n] = qpow(fac[n], mod-2);
	per(i, 2, n-1) ifac[i] = 1ll * ifac[i+1] * (i+1) % mod;
	
	int rt = rs[0];
	
	cout << dfs(rt) << "\n";;
	
	
	
	return 0;
}
