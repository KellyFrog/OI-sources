// Problem: P3749 [六省联考 2017] 寿司餐厅
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3749
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-08 10:47:01
// Input/Output: stdin/stdout
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

const int N = 100 * 100 + 100;
const int NN = 105;
const int M = 1e7 + 5;

const int inf = 0x3f3f3f3f;

int n, m, e, s, t;
int cur[N], head[N], nxt[M], to[M], fl[M], tot = 1;
int dis[N];
int que[N], ph=1, pt=0;
int val[N], a[NN], id[NN][NN], d[NN][NN];
map<int, int> numid;
int nid;

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) rep(j, i, n) {
		cin >> d[i][j];
		id[i][j] = ++nid;
		if(i == j) d[i][j] -= a[i];
		val[id[i][j]] = d[i][j];
	}
	rep(i, 1, n) {
		if(!numid[a[i]]) {
			int o = numid[a[i]] = ++nid;
			val[o] = -m * a[i] * a[i];
		}
	}
	s = ++nid, t = ++nid;
	rep(i, 1, nid-2) {
		if(val[i] < 0) {
			addedge(i, t, -val[i]);
			addedge(t, i, 0);
		} else {
			addedge(s, i, val[i]);
			addedge(i, s, 0);
		}
	}
	rep(i, 1, n) {
		int o = numid[a[i]];
		addedge(id[i][i], o, inf);
		addedge(o, id[i][i], 0);
	}
	rep(i, 1, n) rep(j, i+1, n) {
		addedge(id[i][j], id[i+1][j], inf);
		addedge(id[i+1][j], id[i][j], 0);
		addedge(id[i][j], id[i][j-1], inf);
		addedge(id[i][j-1], id[i][j], 0);
	}
	
	int ans = 0;
	rep(i, 1, nid) if(val[i] > 0) ans += val[i];
	cout << ans - dinic() << "\n";
	
	return 0;
}
