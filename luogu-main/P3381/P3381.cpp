// Problem: P3381 【模板】最小费用最大流
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3381
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Create Time: 2022-04-14 19:12:27
// Input/Output: stdin/stdout
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

const int N = 5e3 + 5;
const int M = 5e4 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t;
int cur[N], head[N], nxt[M<<1], to[M<<1], tot = 1;
ll fl[M<<1], cost[M<<1];
ll dis[N], from[N];
bool inq[N];

inline void addedge(int u, int v, int f, int w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = f;
	cost[tot] = w;
	head[u] = tot;
}

inline bool spfa() {
	memset(dis, 0x3f, sizeof dis);
	queue<int> q;
	dis[s] = 0;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e], f = fl[e], w = cost[e];
			if(f && dis[u] + w < dis[v]) {
				from[v] = e;
				dis[v] = dis[u] + w;
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[t] != inf;
}

inline pair<ll, ll> mcmf() {
	ll flow = 0, cst = 0;
	while(spfa()) {
		ll f = inf;
		ll c = 0;
		int x = t;
		while(x != s) {
			f = min(f, fl[from[x]]);
			c += cost[from[x]];
			x = to[from[x]^1];
		}
		x = t;
		while(x != s) {
			fl[from[x]] -= f;
			fl[from[x]^1] += f;
			x = to[from[x]^1];
		}
		flow += f;
		cst += f * c;
	}
	return mp(flow, cst);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m >> s >> t;
	rep(i, 1, m) {
		int u, v, f, w;
		cin >> u >> v >> f >> w;
		addedge(u, v, f, w);
		addedge(v, u, 0, -w);
	}

	auto [flow, cst] = mcmf();
	cout << flow << " " << cst << "\n";
	
	return 0;
}