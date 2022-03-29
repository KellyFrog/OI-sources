// Problem: P4630 [APIO2018] Duathlon 铁人两项
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4630
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 3e5 + 5;

int n, m;
vector<int> adj[N], t[N];
int dfn[N], low[N], dfncnt;
int stk[N], top, ins[N];
int bcnt;
int tt;

inline void tarjan(int u) {
	low[u] = dfn[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	++tt;
	
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			
			if(low[v] == dfn[u]) {
				++bcnt;
				while(1) {
					int x = stk[top];
					t[x].pb(n+bcnt);
					t[n+bcnt].pb(x);
					ins[x] = 0;
					--top;
					
					if(x == v) break;
				}
				
				t[u].pb(n+bcnt);
				t[n+bcnt].pb(u);
			}
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int siz[N];
ll ans = 0;

inline void dfs(int u, int fa) {
	debug("{} {}\n", u, fa);
	siz[u] = u <= n;
	int sm = 0;
	for(int v : t[u]) {
		if(v != fa) {
			dfs(v, u);
			if(u > n) {
				debug("ans += {} * {} * {}\n", t[u].size(), sm, siz[v]);
				ans += 2ll * t[u].size() * sm * siz[v];
			} else {
				ans -= 2ll * sm * siz[v];
			}
			siz[u] += siz[v];
			sm += siz[v];
		}
	}
	if(u > n) {
		debug("ans += {} * {} * {}\n", t[u].size(), siz[u], tt-siz[u]);
		ans += 2ll * t[u].size() * siz[u] * (tt-siz[u]);
	} else {
		ans -= 2ll * (siz[u]-1) * (tt-siz[u]);
		ans -= 2ll * (tt-1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	rep(i, 1, n) {
		if(!dfn[i]) {
			tt = 0;
			tarjan(i);
			dfs(i, 0);
		}
	}
	
	cout << ans << "\n";
	
	return 0;
}
