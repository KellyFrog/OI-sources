// Problem: U198447 zjl的树3
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U198447?contestId=62264
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 2e6 + 5;

int n;
int a[N];
pair<int, int> b[N];
int last[N], from[N];
vector<int> adj[N];
int ls[N], rs[N], siz[N], dep[N];
int st[N], ed[N], dfncnt;
int t[N], t2[N];
int tot;

inline void dfs(int u, int fa) {
	if(u == -1) return;
	debug("dfs = {} {}\n", u, fa);
	dep[u] = dep[fa] + 1;
	st[u] = ++dfncnt;
	dfs(ls[u], u);
	dfs(rs[u], u);
	siz[u] = siz[ls[u]] + siz[rs[u]] + 1;
	ed[u] = dfncnt;
}

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int p) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += p; }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t[x0]; return res; }
inline int query(int l, int r) { return query(r) - query(l-1); }

inline void add2(int x, int p) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t2[x0] += p; }
inline void add2(int l, int r, int p) { add2(l, p), add2(r+1, p); }
inline int query2(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t2[x0]; return res; }

void solve() {
	debug("---\n");
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i].fi, b[i].se = i;
	rep(i, 0, n) adj[i].clear();
	rep(i, 0, n) from[i] = 0;
	rep(i, 0, n) last[i] = 0;
	rep(i, 1, n) {
		from[i] = last[a[i]-1];
		if(a[i] > 1 && from[i] == 0) {
			cout << "NO" << "\n";
			return;
		}
		int p = a[i]+1;
		while(last[p]) last[p++] = 0;
		adj[from[i]].pb(i);
		last[a[i]] = i;
	}
	rep(i, 1, n) last[a[i]] = 0;
	rep(i, 1, n) ls[i] = rs[i] = -1;
	rep(i, 1, n) t2[i] = 0;
	rep(i, 0, n) {
		if(adj[i].empty()) continue;
		rs[i] = adj[i][adj[i].size()-1];
		int o = rs[i];
		debug("i = {}\n", i);
		for(int j = (int)adj[i].size()-2; j>=0; --j) {
			ls[o] = adj[i][j];
			o = adj[i][j];
		}
	}
	
	int rt = rs[0];
	
	tot = dfncnt = 0;
	
	dfs(rt, 0);
	
	debug("dfs ok\n");
	
	sort(b + 1, b + n + 1, [&](pair<int, int> x, pair<int, int> y) {
		return x.fi == y.fi ? dep[x.se] > dep[y.se] : x.fi < y.fi;
	});
	
	rep(i, 1, n) t[i] = 0;
	
	rep(i, 1, n) {
		auto [x, p] = b[i];
		int y = siz[p] - query(st[p], ed[p]);
		int t = query2(st[p]);
		debug("p = {}, y = {}, t = {}\n", p, y, t);
		if(y < 0) continue;
		if(t > 0) continue;
		if(tot + y > x) {
			rep(i, 0, n) ls[i] = rs[i] = -1;
			cout << "NO" << "\n";
			return;
		}
		tot += y;
		add(st[p], y);
		add2(st[p], ed[p], 1);
	}
	cout << "YES" << "\n";
	rep(i, 0, n) ls[i] = rs[i] = -1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	return 0;
}
