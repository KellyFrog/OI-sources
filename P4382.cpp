// Problem: P4382 [八省联考 2018] 劈配
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4382
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-07 11:13:19
// Author: Chen Kaifeng
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

const int N = 405;
const int inf = 0x3f3f3f3f;
const int M = 1e6 + 5;

int c, n, m;
int a[N], b[N];
vector<int> v[N][N];
bool vis[N];
int ans1[N], ans2[N];
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
	dis[t] = 1;
	que[++pt] = t;
	while(ph <= pt) {
		int u = que[ph++];
		for(int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			int f = fl[i^1];
			if(f && !dis[v]) {
				dis[v] = dis[u] + 1;
				que[++pt] = v;
			}
		}
	}
	return dis[s];
}

inline int dfs(int u, int l) {
	if(u == t) return l;
	int res = 0;
	for(int& i = cur[u]; i; i = nxt[i]) {
		int v = to[i];
		int f = fl[i];
		if(f && dis[v] == dis[u] - 1) {
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

void solve() {
	memset(head, 0, sizeof head);
	tot = 1;
	memset(ans2, 0, sizeof ans2);
	
	cin >> n >> m;
	rep(i, 1, m) cin >> b[i];
	rep(i, 1, n) {
		rep(j, 1, m) v[i][j].clear();
		rep(j, 1, m) {
			int x; cin >> x;
			v[i][x].pb(j);
		}
	}
	rep(i, 1, n) cin >> a[i];
	
	s = n + m + 1;
	t = n + m + 2;
	rep(i, 1, m) {
		addedge(i, t, b[i]);
		addedge(t, i, 0);
	}
	
	assert(dinic() == 0);
	
	rep(i, 1, n) {
		ans1[i] = m+1;
		
		rep(j, i, n) {
			bool ok = 0;
			rep(k, 1, a[j]) {
				for(int o : v[j][k]) {
					if(dis[o]) ok = 1;
				}
			}
			if(ok) ans2[j] = i;
		}
		
		rep(j, 1, m) {
			bool ok = 0;
			for(int o : v[i][j]) {
				if(dis[o]) ok = 1;
			}
			if(ok) {
				addedge(s, i + m, 1);
				addedge(i + m, s, 0);
				for(int o : v[i][j]) {
					addedge(i + m, o, 1);
					addedge(o, i + m, 0);
				}
				assert(dinic() == 1);
				ans1[i] = j;
				break;
			}
		}
	}
	rep(i, 1, n) cout << ans1[i] << " \n"[i == n];
	rep(i, 1, n) cout << i-ans2[i] << " \n"[i == n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t >> c;
	while(t--) solve();
	
	return 0;
}

