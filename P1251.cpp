// Problem: P1251 餐巾计划问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1251
// Memory Limit: 125 MB
// Time Limit: 4000 ms
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

const int N = 4e3 + 5;
const int M = 1e7 + 5;

const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, s, t;
int head[N], nxt[M<<1], to[M<<1], tot = 1;
ll cost[M<<1], fl[M<<1];
ll dis[N], in[N], from[N];
bool inq[N];

inline void addedge(int u, int v, ll f, ll c) {
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = f;
	cost[tot] = c;
	head[u] = tot;
}

inline bool spfa() {
	memset(dis, 0x3f, sizeof dis);
	memset(from, 0, sizeof from);
	queue<int> q;
	dis[s] = 0;
	in[s] = inf;
	q.push(s);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		inq[u] = 0;
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e];
			ll w = cost[e], f = fl[e];
			if(f && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				in[v] = min(in[u], f);
				from[v] = e;
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[t] != inf;
}

pair<ll, ll> mcmf() {
	ll flow = 0, tcost = 0;
	
	while(spfa()) {
		int cur = t;
		flow += in[t];
		while(cur != s) {
			int e = from[cur];
			tcost += 1ll * cost[e] * in[t];
			fl[e] -= in[t];
			fl[e^1] += in[t];
			cur = to[e^1];
		}
	}
	
	return mp(flow, tcost);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	s = 2*n+1, t = 2*n+2;
	rep(i, 1, n) {
		int r; cin >> r;
		addedge(s, i+n, r, 0);
		addedge(i+n, s, 0, 0);
		addedge(i, t, r, 0);
		addedge(t, i, 0, 0);
	}
	
	rep(i, 1, n-1) {
		addedge(i+n, i+n+1, inf, 0);
		addedge(i+n+1, i+n, 0, 0);
	}
	
	int c; cin >> c;
	rep(i, 1, n) {
		addedge(s, i, inf, c);
		addedge(i, s, 0, -c);
	}
	
	int tf, cf; cin >> tf >> cf;
	rep(i, 1, n) {
		if(i + tf <= n) {
			addedge(i+n, i+tf, inf, cf);
			addedge(i+tf, i+n, 0, -cf);
		}
	}
	int ts, cs; cin >> ts >> cs;
	rep(i, 1, n) {
		if(i + ts <= n) {
			addedge(i+n, i+ts, inf, cs);
			addedge(i+ts, i+n, 0, -cs);
		}
	}
	
	cout << mcmf().se << "\n";
	return 0;
}
