// Problem: P3225 [HNOI2012]矿场搭建
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3225
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

const int N = 2e3 + 5;

int n;
vector<int> adj[N], t[N];
int dfn[N], low[N], dfncnt;
int stk[N], top, ins[N];
int bcnt;
ll ans1 = 0, ans2 = 1;

inline void tarjan(int u) {
	debug("tarjan({})\n", u);
	low[u] = dfn[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
			
			if(low[v] == dfn[u]) {
				++bcnt;
				while(1) {
					int x = stk[top];
					t[x].pb(1e3+bcnt);
					t[(int)1e3+bcnt].pb(x);
					ins[x] = 0;
					--top;
					
					if(x == v) break;
				}
				
				t[u].pb(1e3+bcnt);
				t[(int)1e3+bcnt].pb(u);
			}
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

inline void dfs(int u, int fa) {
	debug("dfs({}, {})\n", u, fa);
	if(u > 1e3) {
		int cnt = t[u].size();
		for(int v : t[u]) {
			if(t[v].size() == 1) --cnt;
		}
		debug("u = {}, cnt = {}\n", u, cnt);
		if(cnt == 1) {
			ans1 += 1;
			ans2 *= t[u].size()-1;
			debug("ans += 1, ans *= {}\n", t[u].size()-1);
		} else if(cnt == 0) {
			ans1 += 2;
			ans2 *= 1ll * t[u].size() * (t[u].size()-1) / 2;
			debug("ans += 2, ans *= {} * {} / 2\n", t[u].size(), t[u].size()-1);
		}
	}
	for(int v : t[u]) if(v != fa) dfs(v, u);
}

void solve(int id) {
	rep(i, 1, 2e3) adj[i].clear(), t[i].clear();
	rep(i, 1, 1e3) dfn[i] = low[i] = 0;
	dfncnt = bcnt = 0;
	ans1 = 0, ans2 = 1;
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rep(i, 1, 1e3) {
		if(adj[i].empty()) continue;
		if(!dfn[i]) {
			tarjan(i);
			debug("tarjan({}) ok\n", i);
			dfs(i, 0);
		}
	}
	cout << "Case " << id << ": " << ans1 << " " << ans2 << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int id = 0;
	while(cin >> n && n) {
		solve(++id);
	}
	
	return 0;
}
