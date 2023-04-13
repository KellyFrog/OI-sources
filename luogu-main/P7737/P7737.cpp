// Problem: P7737 [NOI2021] 庆典
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7737
// Memory Limit: 1 GB
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

const int N = 1e6 + 5;

vector<int> adj[N], dag[N], t[N];
vector<pair<int, bool>> vt[N], rvt[N];
int dfn[N], low[N], dfncnt, ins[N], stk[N], top, scc[N], ssiz[N], scccnt;
int ind[N], que[N], phead = 1, ptail = 0;
int n, m, q, k;
int dep[N], psum[N], tdfn[N], tsiz[N], eul[N<<1], st[21][N<<1], lg2[N<<1], ecnt;
bool vis1[N], vis2[N];

inline void tarjan(int u) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1, stk[++top] = u;
	for(int v : adj[u]) {
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], low[v]);
		}
	}
	if(dfn[u] == low[u]) {
		int x = -1;
		++scccnt;
		do {
			x = stk[top--];
			scc[x] = scccnt;
			++ssiz[scccnt];
			ins[x] = 0;
		} while(x != u);
	}
}

inline void dfs(int u, int fa) {
	debug("t {} -> {}\n", fa, u);
	eul[tdfn[u] = ++ecnt] = u;
	tsiz[u] = 1;
	dep[u] = dep[fa] + 1;
	psum[u] = psum[fa] + ssiz[u];
	for(int v : t[u]) dfs(v, u), eul[++ecnt] = u, tsiz[u] += tsiz[v];
}

inline void buildst() {
	rep(i, 1, ecnt) st[0][i] = eul[i];
	rep(j, 1, 20) rep(i, 1, ecnt) {
		if(i + (1 << j) - 1 > ecnt) break;
		st[j][i] = dep[st[j-1][i]] < dep[st[j-1][i+(1<<j-1)]] ? st[j-1][i] : st[j-1][i+(1<<j-1)];
	}
	lg2[0] = -1;
	rep(i, 1, ecnt) lg2[i] = lg2[i>>1] + 1;
}

inline int LCA(int x, int y) {
	debug("query LCA({}, {}), ", x, y);
	int l = tdfn[x], r = tdfn[y];
	if(l > r) swap(l, r);
	int j = lg2[r-l+1];
	debug("[{}, {}], j = {}\n", l, r, j);
	return dep[st[j][l]] < dep[st[j][r-(1<<j)+1]] ? st[j][l] : st[j][r-(1<<j)+1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> q >> k;
	rep(i, 1, m){
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
	}
	rep(i, 1, n) if(!dfn[i]) tarjan(i);
	// rep(i, 1, n) cerr << scc[i] << " \n"[i == n];
	rep(u, 1, n) {
		for(int v : adj[u]) {
			if(scc[u] != scc[v]) dag[scc[u]].pb(scc[v]), ++ind[scc[v]];
		}
	}
	
	// rep(i, 1, n) cerr << scc[i] <<x` " \n"[i == n];
	
	int rt = 0;
	
	{
		
		rep(i, 1, scccnt) if(!ind[i]) que[++ptail] = i, rt = i;
		while(phead <= ptail) {
			int u = que[phead++];
			for(int v : dag[u]) {
				if(--ind[v] == 0) {
					t[u].pb(v);
					que[++ptail] = v;
				}
			}
		}
	}
	
	dfs(rt, 0);
	buildst();
	
	// rep(i, 1, scccnt) cerr << tdfn[i] << " \n"[i == scccnt];
	
	while(q--) {
		int s, t;
		int a[3], b[3];
		vector<int> nd(2+2*k), vtnd;
		cin >> s >> t;
		s = scc[s], t = scc[t];
		nd[0] = s, nd[1] = t;
		rep(i, 1, k) cin >> a[i] >> b[i], a[i] = scc[a[i]], b[i] = scc[b[i]], nd[i<<1] = a[i], nd[i<<1|1] = b[i];
		sort(nd.begin(), nd.end(), [&](int x, int y) { return tdfn[x] < tdfn[y]; });
		top = 0;
		stk[++top] = rt;
		vtnd.pb(rt);
		debug("solve rt = {}\n", rt);
		
		for(int i = 0; i < nd.size(); i++) {
			int x = nd[i];
			if(i > 0 && nd[i] == nd[i-1]) continue;
			debug("get {} tdfn = {}\n", x, tdfn[x]);
			int lca = LCA(x, stk[top]);
			debug("lca({}, {}) = {}\n", x, stk[top], lca);
			while(dep[stk[top]] > dep[lca]) {
				if(dep[stk[top-1]] <= dep[lca]) {
					vt[lca].pb(mp(stk[top], 0));
					rvt[stk[top]].pb(mp(lca, 0));
					--top;
				} else {
					vt[stk[top-1]].pb(mp(stk[top], 0));
					rvt[stk[top]].pb(mp(stk[top-1], 0));
					--top;
				}
			}
			if(stk[top] != lca) stk[++top] = lca, vtnd.pb(lca);
			if(stk[top] != x) stk[++top] = x, vtnd.pb(x);
		}
		
		rep(i, 1, top-1) vt[stk[i]].pb(mp(stk[i+1], 0)), rvt[stk[i+1]].pb(mp(stk[i], 0));
		rep(i, 1, k) vt[a[i]].pb(mp(b[i], 1)), rvt[b[i]].pb(mp(a[i], 1));
		
		// for(int u : vtnd) for(auto [v, tp] : vt[u]) debug("vt {} -> {} {}\n", u, v, tp);
		
		auto bfs = [&](int s, bool vis[], vector<pair<int, bool>> vt[]) {
			phead = 1, ptail = 0;
			que[++ptail] = s;
			vis[s] = 1;
			while(phead <= ptail) {
				int u = que[phead++];
				for(auto [v, tp] : vt[u]) {
					if(!vis[v]) {
						vis[v] = 1;
						que[++ptail] = v;
					}
				}
			}
		};
		
		
		int ans = 0;
		bfs(s, vis1, vt);
		bfs(t, vis2, rvt);
		for(int u : vtnd) {
			if(vis1[u] && vis2[u]) {
				ans += ssiz[u];
				for(auto [v, tp] : vt[u]) {
					if(vis2[u] && vis2[v] && !tp) {
						ans += psum[v] - psum[u] - ssiz[v];
					}
				}
			}
		}
		
		for(int x : vtnd) rvt[x].clear(), vt[x].clear(), vis1[x] = vis2[x] = 0;
		
		cout << ans << "\n";
	}
	
	return 0;
}
