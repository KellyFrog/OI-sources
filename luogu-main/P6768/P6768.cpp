// Problem: P6768 [USACO05MAR]Ombrophobic Bovines 发抖的牛
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6768
// Memory Limit: 128 MB
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
const int M = 1e7 + 5;

const int inf = 0x3f3f3f3f;

int n, m, e, s, t;
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
			if(!x) dis[v] = -1;
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

ll d[N][N];
int a[N], b[N];
pair<ll, pair<int, int>> dd[N*N]; int ddp;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i] >> b[i];
	
	int sum = 0;
	
	s = 2*n+1, t = 2*n+2;
	rep(i, 1, n) {
		addedge(s, i, a[i]);
		addedge(i, s, 0);
		addedge(i+n, t, b[i]);
		addedge(t, i+n, 0);
		sum += a[i];
	}
	
	memset(d, 0x3f, sizeof d);
	rep(i, 1, n) d[i][i] = 0;
	rep(i, 1, m) {
		ll u, v, w;
		cin >> u >> v >> w;
		d[u][v] = min(d[u][v], w);
		d[v][u] = min(d[v][u], w);
	}
	rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
	rep(i, 1, n) rep(j, 1, n) dd[++ddp] = mp(d[i][j], mp(i, j));
	
	sort(dd+1, dd+ddp+1);
	
	int flow = 0;
	rep(i, 1, n*n) {
		ll ds = dd[i].fi;
		while(dd[i].fi == ds && i <= n*n) {
			auto [x, y] = dd[i].se;
			if(dd[i].fi == 0x3f3f3f3f3f3f3f3f) {
				cout << -1 << "\n";
				return 0;
			}
			addedge(x, y+n, inf);
			addedge(y+n, x, 0);
			addedge(y, x+n, inf);
			addedge(x+n, y, 0);
			++i;
		}
		--i;
		flow += dinic();
		if(flow == sum) {
			cout << dd[i].fi << "\n";
			return 0;
		}
	}
	cout << -1 << "\n";
	
	return 0;
}
