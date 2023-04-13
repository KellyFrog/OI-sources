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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 2e5 + 5;
const int M = 1e7 + 5;

const int inf = 0x3f3f3f3f;

int n, m, e, s, t;
int cur[N], head[N], nxt[M], to[M], fl[M], tot = 1;
int dis[N];
int que[N], ph=1, pt=0;
int a[N], b[N];
int eu[N], ev[N], ew[N];



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

int id[N];

void solve1() {
	
	s = 2 * n + 1;
	t = 2 * n + 2;
	
	rep(i, 1, n) {
		int x; qio >> x;
		a[i] = a[i-1] + x;
		addedge(s, i, x);
		addedge(i, s, 0);
	}
	
	rep(i, 1, n) {
		int x; qio  >> x;
		b[i] = b[i-1] + x;
		addedge(i + n, t, x);
		addedge(t, i + n, 0);
	}
	
	rep(i, 2, n) {
		addedge(i - 1, i, inf);
		addedge(i, i - 1, 0);
		addedge(i + n, i + n - 1, inf);
		addedge(i + n - 1, i + n, 0);
	}
	
	rep(i, 1, m) {
		qio >> eu[i] >> ev[i] >> ew[i];
		eu[i] += eu[i-1];
		id[i] = tot+1;
		addedge(eu[i], ev[i] + n, ew[i]);
		addedge(ev[i] + n, eu[i], 0);
	}
	
	cout << dinic() << "\n";
}

int c[N];

void solve2() {
	rep(i, 1, n) {
		int x; qio >> x;
		a[i] = a[i-1] + x;
	}
	rep(i, 1, n) {
		int x; qio >> x;
		b[i] = b[i-1] + x;
	}
	ll ans = 0;
	rep(i, 1, n) {
		int u, v, w;
		qio >> u >> v >> c[i];
	}
	int cura = a[n], curb = b[n];
	per(i, 1, n) {
		cura = min(cura, a[i]);
		curb = min(curb, b[i]);
		int x = min(c[i], min(cura, curb));
		ans += x;
		cura -= x;
		curb -= x;
	}
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	qio >> n >> m;
	
	if(n < (int)1e5) solve1();
	else solve2();
	
	return 0;
}
