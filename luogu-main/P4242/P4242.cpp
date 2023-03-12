// Problem: P4242 树上的毒瘤
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4242
// Memory Limit: 125 MB
// Time Limit: 2000 ms

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

#define ONLINE_JUDGE

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

vector<int> adj[N];
int n, q, a[N];

struct TNode {
	int cnt, lc, rc;
	int tag;
	TNode(int cnt0 = 0, int lc0 = -1, int rc0 = -1, int tag0 = -1) : cnt(cnt0), lc(lc0), rc(rc0), tag(tag0) {}
};

TNode t[N<<2];

inline TNode merge(const TNode& x, const TNode& y) { return TNode(x.cnt + y.cnt - (x.rc == y.lc), x.lc, y.rc, -1); }
inline void pushup(int x) { t[x] = merge(t[x<<1], t[x<<1|1]); }
inline void setlazy(int x, int c) { t[x] = TNode(1, c, c, c); }
inline void pushdown(int cur) {
	if(t[cur].tag != -1) {
		setlazy(cur<<1, t[cur].tag);
		setlazy(cur<<1|1, t[cur].tag);
		t[cur].tag = -1;
	}
}

inline void modify(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) modify(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

TNode qres; bool isf;
	
inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isf) qres = t[cur], isf = 0;
		else qres = merge(qres, t[cur]);
		return;;
	}
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);
}

int siz[N], son[N], dep[N], fat[N], sgn[N], sgncnt, sgq[N], top[N];

inline void dfs1(int u, int fa) {
	debug("edge {} -> {}\n", fa, u);
	dep[u] = dep[fa] + 1;
	siz[u] = 1;
	son[u] = 0;
	fat[u] = fa;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs1(v, u);
			siz[u] += siz[v];
			if(siz[v] > siz[son[u]]) son[u] = v;
		}
	}
}

inline void dfs2(int u, int fa) {
	sgq[sgn[u] = ++sgncnt] = u;
	
	if(son[fa] == u) top[u] = top[fa];
	else top[u] = u;
	
	if(son[u]) dfs2(son[u], u);
	
	for(int v : adj[u]) {
		if(v != fa && v != son[u]) {
			dfs2(v, u);
		}
	}
}

inline void build(int cur, int l, int r) {
	if(l == r) {
		t[cur] = TNode(1, a[sgq[l]], a[sgq[l]], -1);
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid+1, r);
	pushup(cur);
}

inline void pmodify(int x, int y, int z) {
	debug("pmodify = {} {} {}\n", x, y, z);
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		modify(1, sgn[top[x]], sgn[x], z, 1, n);
		x = fat[top[x]];
	}
	if(sgn[x] > sgn[y]) swap(x, y);
	modify(1, sgn[x], sgn[y], z, 1, n);
}

vector<pair<int, int>> vt[N];

inline TNode pquery(int x, int y) {
	debug("pquery = {} {}\n", x, y);
	TNode res = TNode(0, 0, 0, -1);
	assert(dep[x] > dep[y]);
	
	while(top[x] != top[y]) {
		isf = 1;
		query(1, sgn[top[x]], sgn[x] ,1, n);
		res = merge(res, qres);
		debug("query sgn range = [{}, {}]\n", sgn[top[x]], sgn[x]);
		debug("get qres = {} {} {}\n", qres.cnt, qres.lc, qres.rc);
		x = fat[top[x]];
	}
	
	isf = 1;
	query(1, sgn[y], sgn[x], 1, n);
	res = merge(res, qres);
	
	debug("ok get res = {}\n", res.cnt);
	
	return res;
}

inline int LCA(int x, int y) {
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		x = fat[top[x]];
	}
	if(dep[x] < dep[y]) return x;
	else return y;
}

int m, vtp;
int nd[N], ndd[N], vtnd[N], stk[N], tp;
ll f[N], g[N], fcnt[N];
bool flag[N];
ll ans;

inline void dfs3(int u, int fa) {
	if(flag[u]) fcnt[u] = 1;
	
	for(auto [v, w] : vt[u]) {
		dfs3(v, u);
		f[u] += 1ll * fcnt[v] * w;
		f[u] += f[v];
		fcnt[u] += fcnt[v];
	}
}

inline void dfs4(int u, int fa, int lastw) {
	if(u == 1) {
		g[u] = f[u];
	} else {
		g[u] = g[fa];
		g[u] -= 1ll * fcnt[u] * lastw;
		g[u] += 1ll * (m - fcnt[u]) * lastw;
	}
	
	if(flag[u]) ans += g[u];
	for(auto [v, w] : vt[u]) {
		dfs4(v, u, w);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n-1) {
		int u, v; cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs1(1, 0);
	dfs2(1, 0);
	build(1, 1, n);
	
	// rep(i, 1, n) cerr << sgn[i] << " \n"[i == n];
	
	while(q--) {
		int op; cin >> op;
		debug("solve op = {}\n", op);
		if(op == 1) {
			int x, y, z;
			cin >> x >> y >> z;
			pmodify(x, y, z);
		} else {
			cin >> m;
			rep(i, 1, m) cin >> nd[i], ndd[i] = nd[i];
			ans = 0;
			vtp = tp = 0;
			
			vtnd[++vtp] = stk[++tp] = 1;
			sort(nd + 1, nd + m + 1, [&](int x, int y) { return sgn[x] < sgn[y]; });
			
			rep(i, 1, m) {
				int lca = LCA(nd[i], stk[tp]);
				while(dep[lca] < dep[stk[tp]]) {
					if(dep[lca] <= dep[stk[tp-1]]) {
						TNode v = pquery(stk[tp], stk[tp-1]);
						vt[stk[tp-1]].pb(mp(stk[tp], v.cnt - 1));
						--tp;
					} else {
						TNode v = pquery(stk[tp], lca);
						vt[lca].pb(mp(stk[tp], v.cnt - 1));
						--tp;
					}
				}
				if(stk[tp] != lca) stk[++tp] = lca, vtnd[++vtp] = lca;
				if(stk[tp] != nd[i]) stk[++tp] = nd[i], vtnd[++vtp] = nd[i];
				
				flag[nd[i]] = 1;
			}
			rep(i, 1, tp-1) {
				TNode v = pquery(stk[i+1], stk[i]);
				vt[stk[i]].pb(mp(stk[i+1], v.cnt - 1));
			}
			
			// rep(i, 1, vtp) cerr << vtnd[i] << " \n"[i == vtp];
			
			debug("build vtree ok\n");
			
			dfs3(1, 0);
			dfs4(1, 0, 0);
			
			// rep(i, 1, m) cerr << f[ndd[i]] << " \n"[i == m];
			// rep(i, 1, m) cerr << g[ndd[i]] << " \n"[i == m];
			
			rep(i, 1, m) cout << g[ndd[i]] + m << " \n"[i == m];
			
			rep(i, 1, vtp) flag[i] = 0, fcnt[i] = f[i] = g[i] = 0, vt[i].clear();
		}
		debug("ok op = {}\n", op);
	}
	
	return 0;
}
