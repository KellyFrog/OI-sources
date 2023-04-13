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

const int N = 1e6 + 5;

int n, k, q;
vector<int> adj[N];
int a[N], dfn[N], dfncnt, siz[N], anc[N][21];
int t1[N];
ll t2[N];

inline int lowbit(int x) { return x & (-x); }
inline void add1(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t1[x0] += val; }
inline int query1(int x) { int res= 0 ; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t1[x0]; return res; }
inline int query1(int l, int r) { return query1(r) - query1(l-1); }
inline void add2(int x, int val) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t2[x0] += val; }
inline void add2(int l, int r, int val) { add2(l, val), add2(r+1, -val); }
inline ll query2(int x) { ll res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t2[x0]; return res; }

inline void dfs(int u, int fa) {
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	anc[u][0] = fa;
	rep(i, 1, 20) anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			siz[u] += siz[v];
		}
	}
}

inline int getpos(int x) {
	per(i, 0, 20) {
		int p = anc[x][i];
		if(p) {
			if(query1(dfn[p], dfn[p]+siz[p]-1) == 0) x = p;
		}
	}
	return x;
}

int main() {
	freopen("esport.in", "r", stdin);
	freopen("esport.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 2, n) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	dfs(1, 0);
	
	rep(i, 1, n) add2(dfn[i], dfn[i]+siz[i]-1, a[i]);
	
	ll ans = 0;
	
	auto insert = [&](int x) {
		if(query1(dfn[x], dfn[x]+siz[x]-1)) {
			add1(dfn[x], 1);
			return;
			
		}
		int p = getpos(x);
		if(query1(dfn[x], dfn[x]+siz[x]-1)==0) ans += query2(dfn[x]) - query2(dfn[anc[p][0]]);
		add1(dfn[x], 1);
	};
	
	auto erase = [&](int x) {
		if(!query1(dfn[x], dfn[x]+siz[x]-1)) return;
		add1(dfn[x], -1);
		if(query1(dfn[x], dfn[x]+siz[x]-1)==0) {
			int p = getpos(x);
			ans -= query2(dfn[x]) - query2(dfn[anc[p][0]]);
		}
	};
	
	cin >> k;
	rep(i, 1, k) {
		int x; cin >> x;
		insert(x);
	}
	
	cout << ans << "\n";
	
	cin >> q;
	while(q--) {
		int op, x, y;
		cin >> op >> x;
		if(op == 1) {
			insert(x);
		} else if(op == 2) {
			erase(x);
		} else if(op == 3) {
			cin >> y;
			int delt = y - a[x];
			if(query1(dfn[x], dfn[x]+siz[x]-1)) ans += delt;
			add2(dfn[x], dfn[x]+siz[x]-1, delt);
			a[x] = y;
		}
		cout << ans << "\n";
	}
	
	return 0;
}
