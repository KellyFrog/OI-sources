// Problem: P2515 [HAOI2010]软件安装
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2515
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

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x += y; if(x >= mod) x -= mod; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z; if(x >= mod) x -= mod; }
template <typename T> inline void chkmns(T& x, T y) { x -= y; if(x < 0) x += mod; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z; if(x < 0) x += mod; }
template <typename T> inline void chkmax(T& x, T y) { if(y > x) x = y; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { if(y < x) x = y; }
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e2 + 5;
const int M = 5e2 + 5;

int w[N], v[N], d[N], sval[N];
// int smv[N], smw[N];
int sw[N], sv[N];
int dfn[N], low[N], dfncnt, scc[N], scccnt;

bool ins[N];
int ind[N], stk[N], top;
vector<int> adj[N], tadj[N];
int f[N][M];
int n, m;

inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	
	if(dfn[u] == low[u]) {
		++scccnt;
		int curv = 0, curw = 0;
				
		int x = -1;
		while((x = stk[top--]) != u) {
			curv += v[x];
			curw += w[x];
			scc[x] = scccnt;
			ins[x] = 0;
		}
		
		curv += v[x];
		curw += w[x];
		scc[x] = scccnt;
		ins[x] = 0;
		
		sv[scccnt] = curv;
		sw[scccnt] = curw;
	}
}

inline void dfs(int u, int fa) {
	f[u][0] = 0;
	
	if(sv[u] > m) return;
	
	int tmp[M];
	
	for(int v : tadj[u]) {
		// debug("t {} -> {}\n", u, v);
		dfs(v, u);
		memcpy(tmp, f[u], sizeof tmp);
		rep(j, 0, m) {
			per(i, j, m) {
				f[u][i] = max(f[u][i], tmp[i-j] + f[v][j]);
			}
		}
	}
	
	per(i, sv[u], m) {
		f[u][i] = f[u][i-sv[u]] + sw[u];
	}
	
	rep(i, 0, sv[u]-1) f[u][i] = 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> v[i];
	rep(i, 1, n) cin >> w[i];
	rep(i, 1, n) {
		cin >> d[i];
		if(d[i]) adj[d[i]].pb(i);
	}
	
	rep(i, 1, n) if(!dfn[i]) tarjan(i);
	
	rep(u, 1, n) for(int v : adj[u]) if(scc[u] != scc[v]) tadj[scc[u]].pb(scc[v]), ++ind[scc[v]];
	
	rep(i, 1, scccnt) {
		if(!ind[i]) tadj[scccnt+1].pb(i), ++ind[i];
	}
	
	dfs(scccnt+1, 0);
	
	int ans = 0;
	rep(i, 1, m) ans = max(ans, f[scccnt+1][i]);
	cout << ans << "\n";
	
	return 0;
}
