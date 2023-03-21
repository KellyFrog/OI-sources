// Problem: P3714 [BJOI2017]树的难题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3714
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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
#define ep emplace_back
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const int mod = 1e9 + 7;
// const int mod = 998244353;

int qpow(int x, ll p) {
    int res = 1, base = x;
    while(p) {
		if(p & 1) res = 1ll * res * base % mod;
		base = 1ll * base * base % mod;
		p >>= 1;
    }
    return res;
}

template<typename T> inline void upd(T& x, const T& y) { x += y; if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod;}

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;

int n, m, l, r;
vector<pair<int, int>> adj[N];
int c[N];
int siz[N], msiz[N], vis[N], mxd[N], mxc[N], dep[N];
int dseq[N], ncnt;
ll dis[N], val1[N], val2[N], val3[N], ans = -inf;

inline void dfssiz(int u, int fa) {
	siz[u] = 1;
	msiz[u] = 0;
	dseq[++ncnt] = u;
	for(auto [v, c] : adj[u]) {
		if(v == fa || vis[v]) continue;
		dfssiz(v, u);
		msiz[u] = max(msiz[u], siz[v]);
		siz[u] += siz[v];
	}
}

inline void dfsdis(int u, int fa, int lc = 0) {
	// debug("dfsdis = {} {}\n", u, fa);
	mxd[u] = 0;
	if(l <= dep[u] && dep[u] <= r) ans = max(ans, dis[u]);
	for(auto [v, cl] : adj[u]) {
		if(v == fa || vis[v]) continue;
		dis[v] = dis[u] + (lc == cl ? 0 : c[cl]);
		dep[v] = dep[u] + 1;
		dfsdis(v, u, cl);
		mxd[u] = max(mxd[u], mxd[v]);
	}
	++mxd[u];
}

inline void dfsupd(int u, int fa, ll* val) {
	val[dep[u]] = max(val[dep[u]], dis[u]);
	for(auto [v, cl] : adj[u]) {
		if(vis[v] || v == fa) continue;
		dfsupd(v, u, val);
	}
}

inline void getans(ll* val1, ll* val2, int len, int det, bool upd) {
	// return;
	// debug("getans, len = {}, det = {}\n", len, det);
	// rep(i, 1, len) cerr << val1[i] << " \n"[i == len];
	// rep(i, 1, len) cerr << val2[i] << " \n"[i == len];
	
	int n = len;
	int l0 = l, r0 = min(r, 2*len);
	// debug("l = {}, r = {}\n", l, r0);
	if(l0 <= r0) {
		len = min(len, r);
		deque<int> dq;
		rep(i, 0, r0-len) {
			int p = i;
			while(!dq.empty() && val1[dq.back()] < val1[p]) dq.pop_back();
			dq.push_back(p);
		}
		per(i, 1, len) {
			int p = r0-i;
			while(!dq.empty() && val1[dq.back()] < val1[p]) dq.pop_back();
			while(!dq.empty() && dq.front() < l-i) dq.pop_front();
			dq.push_back(p);
			ans = max(ans, val1[dq.front()] + val2[i] + det);
		}
	}
	if(upd) rep(i, 1, n) val1[i] = max(val1[i], val2[i]);
	// debug("get ans = {}\n", ans);
}

ll cnt;

inline void dfswork(int u) {
	ncnt = 0;
	dfssiz(u, 0);
	int rt = -1;
	rep(i, 1, ncnt) if(msiz[dseq[i]] <= ncnt / 2 && ncnt - siz[dseq[i]] <= ncnt / 2) rt = dseq[i];
	
	assert(rt != -1);
	dis[rt] = dep[rt] = 0;
	
	dfsdis(rt, 0);
	
	// debug("path with rt, ans = {}\n", ans);
	
	for(auto [v, cl] : adj[rt]) mxc[cl] = 0;
	
	for(auto [v, cl] : adj[rt]) {
		if(!vis[v]) mxc[cl] = max(mxc[cl], mxd[v]);
	}
	
	// for(auto [v, cl] : adj[rt]) debug("cl = {}, mx = {}\n", cl, mxc[cl]);
	
	sort(adj[rt].begin(), adj[rt].end(), [&](const pair<int, int>& x, const pair<int, int>& y) {
		if(x.se == y.se) return mxd[x.fi] < mxd[y.fi];
		else if(mxc[x.se] == mxc[y.se]) return x.se < y.se;
		else return mxc[x.se] < mxc[y.se];
		// return x.se == y.se ? mxd[x.fi] < mxd[y.fi] : mxc[x.se] == mxc[y.se] ? x.se < y.se : mxc[x.se] < mxc[y.se];
	});
	
	int p = 0;
	for(int i = 0; i < adj[rt].size();) {
		while(p < adj[rt].size() && adj[rt][i].se == adj[rt][p].se) {
			++p;
		}
		
		int mx = 0;
		
		// debug("---------calc range = [{}, {}], cl = {}\n", i, p-1, adj[rt][i].se);
		
		for(int j = i; j < p; ++j) {
			if(vis[adj[rt][j].fi]) continue;
			// debug("merge same color = {}, mxd = {}\n", adj[rt][j].fi, mxd[adj[rt][j].fi]);
			dfsupd(adj[rt][j].fi, rt, val3);
			getans(val2, val3, mxd[adj[rt][j].fi], -c[adj[rt][j].se], 1);
			rep(k, 1, mxd[adj[rt][j].fi]) val3[k] = -inf;
			mx = max(mx, mxd[adj[rt][j].fi]);
		}
		
		// debug("merge to diff color\n");
		getans(val1, val2, mx, 0, 1);
		rep(j, 1, mx) val2[j] = val3[j] = -inf;
		
		i = p;
	}
	
	rep(i, 0, ncnt) val1[i] = -inf;
	
	// debug("dfswork({}) ok, ans = {}\n", u, ans);
	
	vis[rt] = 1;
	for(auto [v, cl] : adj[rt]) {
		if(!vis[v]) dfswork(v);
	}
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    cin >> n >> m >> l >> r;
    rep(i, 1, m) cin >> c[i];
    rep(i, 1, n-1) {
    	int u, v, cl;
    	cin >> u >> v >> cl;
    	adj[u].ep(v, cl);
    	adj[v].ep(u, cl);
    	
    	// cerr << u << " " << v << " " << c[cl] << "\n";
    }
    
    rep(i, 0, n) {
    	val1[i] = val2[i] = val3[i] = -inf;
    }
    
    dfswork(1);
    
    cout << ans << "\n";
    
    return 0;
}