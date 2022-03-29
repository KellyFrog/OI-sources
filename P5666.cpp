// Problem: P5666 [CSP-S2019] 树的重心
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5666
// Memory Limit: 250 MB
// Time Limit: 4000 ms

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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 3e5 + 5;

struct Node {
	int t, l, r, op;
	Node(int t0, int l0, int r0, int op0) : t(t0), l(l0), r(r0), op(op0) {}
	Node() {}
};

int n;
vector<int> adj[N];
int dfn[N], siz[N], dfncnt, id[N], fat[N];
int t[N];
int rt;
Node qry[N<<2]; int qryp;
int lowbit(int x) { return x & (-x); }
void add(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += val; }
int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t[x0]; return res; }
int query(int l, int r) { return query(r) - query(l-1); }

inline void addquery1(int t, int l, int r, int op) {
	if(t) {
		qry[++qryp] = Node(t, l, r, op);
		debug("add query, t = {}, [{}, {}], op = {}\n", t, l, r, op);
	}
}
inline void addquery2(int st, int et, int l, int r, int val) { addquery1(st-1, l, r, -val), addquery1(et, l, r, val); }

inline int dfsrt(int u, int fa) {
	siz[u] = 1;
	int ret = -1;
	for(int v : adj[u]) {
		if(v != fa) {
			int x = dfsrt(v, u);
			if(x != -1) ret = x;
			siz[u] += siz[v];
		}	
	}
	int mxsiz = n - siz[u];
	for(int v : adj[u]) if(v != fa) chkmax(mxsiz, siz[v]);
	if(mxsiz <= n / 2) ret = u;
	return ret;
}



inline void dfs(int u, int fa) {
	fat[u] = fa;
	dfn[u] = ++dfncnt;
	id[dfn[u]] = u;
	siz[u] = 1;
	for(int v : adj[u]) if(v != fa) dfs(v, u), siz[u] += siz[v];
	
	int mxsiz = 0;
	for(int v : adj[u]) if(v != fa) chkmax(mxsiz, siz[v]);
	
	if(u == rt) {
		vector<int> pre(adj[u].size()), suf(adj[u].size());
		pre[0] = siz[adj[u][0]];
		for(int i = 1; i < adj[u].size(); i++) chkmax(pre[i], pre[i-1], siz[adj[u][i]]);
		pre[(int)adj[u].size()-1] = siz[(int)adj[u][adj[u].size()-1]];
		for(int i = (int)adj[u].size() - 2; i >= 0; i--) chkmax(suf[i], suf[i+1], siz[adj[u][i]]);
		for(int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i];
			int curmx = max(i?pre[i-1]:0, i+1<adj[u].size()?suf[i+1]:0);
			addquery2(dfn[v], dfn[v] + siz[v] - 1, 1, n - 2 * curmx, rt);
		}
	} else {
		int L = n - 2 * siz[u];
		int R = n - 2 * mxsiz;
		if(L < 1) L = 1;
		if(R == n) R = n-1;
		debug("get L = {}, R = {} for u = {}\n", L, R, u);
		if(L <= R) {
			addquery1(dfn[u] - 1, L, R, u);
			addquery2(dfn[u] + siz[u], n, L, R, u);
		}
	}
}

void solve() {
	debug("--------solve---------\n");
	cin >> n;
	qryp = dfncnt = 0;
	rep(i, 1, n) t[i] = 0;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, n-1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	rt = dfsrt(1, 0);
	dfs(rt, 0);
	OK;
	ll ans = 0;
	int p = 0;
	sort(qry + 1, qry + qryp + 1, [&](const Node& x, const Node& y) { return x.t < y.t; });
	rep(i, 1, n) {
		debug("id[{}] = {}, siz = {}\n", i, id[i], siz[id[i]]);
		add(siz[id[i]], 1);
		// for(int v : adj[id[i]]) if(v != fat[id[i]]) add(n - siz[v], 1);
		while(p+1 <= qryp && qry[p+1].t == i) {
			p++;
			debug("ans += 1ll * {} * query({}, {}) = {}\n", qry[p].op, qry[p].l, qry[p].r, query(qry[p].l, qry[p].r));
			ans += 1ll * qry[p].op * query(qry[p].l, qry[p].r);
		}
	}
	cout << ans << "\n";
	OK;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0); cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	int T; cin >> T;
	while(T--) solve();
	
	return 0;
}