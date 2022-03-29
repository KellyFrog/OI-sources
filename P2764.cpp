// Problem: P2764 最小路径覆盖问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2764
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 405;
const int M = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int s, t;
int cur[N], head[N], nxt[M], to[M], fl[M], tot = 1;
int dis[N];
int que[N], ph=1, pt=0;

inline void addedge(int u, int v, int f) {
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = f;
	head[u] = tot;
}

inline bool bfs() {
	memset(dis, 0, sizeof dis);
	memcpy(cur, head, sizeof cur);
	ph=1, pt=0;
	dis[s] = 1;
	que[++pt] = s;
	while(ph <= pt) {
		int u = que[ph++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			int f = fl[i];
			if(f && !dis[v]) {
				dis[v] = dis[u] + 1;
				que[++pt] = v;
			}
		}
	}
	return dis[t];
}

inline int dfs(int u, int l) {
	if(u == t) return l;
	int res = 0;
	for(int& i = cur[u]; i; i = nxt[i]) {
		int v = to[i];
		int f = fl[i];
		if(f && dis[v] == dis[u] + 1) {
			int x = dfs(v, min(l, f));
			l -= x;
			fl[i] -= x;
			fl[i^1] += x;
			res += x;
		}
		if(!l) break;
	}
	if(l) dis[u] = -1;
	return res;
}

int dinic() {
	int res = 0;
	while(bfs()) res += dfs(s, inf);
	return res;
}

int n, m;
int eu[M], ev[M], eid[M];
vector<int> adj[N], radj[N];
bool vis[N];

inline void dfs1(int u, bool p = 1) {
	vis[u] = 1;
	for(int id : radj[u]) if(!fl[eid[id]]) dfs1(eu[id]);
	if(p) cout << u << " ";
}

inline void dfs2(int u, bool p = 1) {
	if(p) cout << u << " ";
	vis[u] = 1;
	for(int id : adj[u]) if(!fl[eid[id]]) dfs2(ev[id]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	
	s = 2*n+1, t = 2*n+2;
	
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		eu[i] = u, ev[i] = v, eid[i] = tot+1;
		adj[u].pb(i);
		radj[v].pb(i);
		addedge(u+n, v, 1);
		addedge(v, u+n, 0);
	}
	
	rep(i, 1, n) {
		addedge(s, i+n, 1);
		addedge(i+n, s, 0);
		addedge(i, t, 1);
		addedge(t, i, 0);
	}
	
	int res = dinic();
	
	rep(i, 1, n) {
		if(!vis[i]) {
			dfs1(i, 0);
			cout << i << " ";
			dfs2(i, 0);
			cout << "\n";
		}
	}
	
	cout << n - res << "\n";
	
	return 0;
}
