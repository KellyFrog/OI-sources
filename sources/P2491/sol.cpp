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

const int N = 3e5 + 5;
const int inf = 0x3f3f3f3f;

vector<pair<int, int>> adj[N];
int dis1[N], dis2[N], dist[N], f[N], ff[N];
int px, py;
bool vis[N];
vector<pair<int, int>> dia;
vector<int> pre, suf, val, presum, g;
int n, s;

inline void dfsdis(int u, int fa, int lw, int dis[]) {
    dis[u] = dis[fa] + lw;
    for(auto [v, w] : adj[u]) if(v != fa) dfsdis(v, u, w, dis);
}

inline void dfs1(int u, int fa) {
    if(u == py) {
	vis[u] = 1;
    }

    ff[u] = dis2[u];
    
    for(auto [v, w] : adj[u]) {
	if(v != fa) {
	    dfs1(v, u);
	    if(vis[v]) {
		dia.pb(mp(v, w));
		vis[u] = 1;
	    } else {
		dist[u] = max(dist[u], dist[v] + w);
	    }
	    ff[u] = max(ff[u], ff[v]);
	}
    }
}

inline void dfs2(int u, int fa) {
    f[u] = dis1[u];
    
    for(auto [v, w] : adj[u]) {
	if(v != fa) {
	    dfs2(v, u);
	    f[u] = max(f[u], f[v]);
	}
    }
}

inline void getdiameter() {
    dfsdis(1, 0, 0, dis1);
    int mxpos = 1;
    rep(i, 1, n) if(dis1[i] > dis1[mxpos]) mxpos = i;
    px = mxpos;
    dfsdis(px, 0, 0, dis2);
//    dfsdis(py, 0, 0, dis1);
    mxpos = 1;
    rep(i, 1, n) if(dis2[i] > dis2[mxpos]) mxpos = i;
    py = mxpos;
    dfsdis(py, 0, 0, dis1);
    dfs1(px, 0);
    dfs2(py, 0);
    dia.pb(mp(px, 0));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    
    cin >> n >> s;
    rep(i, 1, n-1) {
	int u, v, w;
	cin >> u >> v >> w;
	adj[u].pb(mp(v, w));
	adj[v].pb(mp(u, w));
    }

    getdiameter();

    int m = dia.size();
    pre.resize(m);
    presum.resize(m);
    suf.resize(m);
    val.resize(m);
    g.resize(m);

    for(int i = 0; i < m; ++i) pre[i] = ff[dia[i].fi], suf[i] = f[dia[i].fi], g[i] = dist[dia[i].fi];
    for(int i = 1; i < m; ++i) pre[i] = max(pre[i], pre[i-1]);
    for(int i = m-2; i >= 0; --i) suf[i] = max(suf[i+1], suf[i]);
    for(int i = 1; i < m; ++i) presum[i] = presum[i-1] + dia[i-1].se;

    
    deque<int> dq;
    int p = 0;
    int ans = inf;
    for(int i = 0; i < m; ++i) {
	while(presum[i] - presum[p] > s) ++p;
	while(!dq.empty() && g[i] > g[dq.back()]) dq.pop_back();
	dq.push_back(i);
	while(!dq.empty() && dq.front() < p) dq.pop_front();
	debug("i = {}, p = {}, g = {}, front = {}, ans = {} {} {} {}\n", i, p, dia[i].fi, g[dq.front()], pre[p], dis2[dia[p].fi], suf[i], dis1[dia[i].fi]
		  );
	debug("ans = p={} {} {}\n", dia[p].fi, pre[p] - dis2[dia[p].fi], suf[i] - dis1[dia[i].fi]);
	ans = min(ans, max(g[dq.front()], max(pre[p] - dis2[dia[p].fi], suf[i] - dis1[dia[i].fi])));
    }

    cout << ans << "\n";
    
    return 0;
}
    
