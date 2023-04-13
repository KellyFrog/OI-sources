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

vector<int> adj[N];
int n, k, q;
int a[N];
ll dis[N];
int dfn[N], siz[N], dfncnt, dep[N], st[21][N], lg2[N];
int eul[N], ecnt;
set<pair<int, int>> s;

inline void dfs(int u, int fa) {
	eul[dfn[u] = ++ecnt] = u; 
	siz[u] = 1;
	dep[u] = dep[fa] + 1;
	dis[u] = dis[fa] + a[u];
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			eul[++ecnt] = u;
		}
	}
}

inline void buildst() {
	lg2[0] = -1;
	rep(i, 1, ecnt) lg2[i] = lg2[i>>1] + 1;
	rep(i, 1, ecnt) st[0][i] = eul[i];
	rep(j, 1, 20) rep(i, 1, ecnt) {
		if(i+(1<<j)-1 > ecnt) break;
		st[j][i] = dep[st[j-1][i]] < dep[st[j-1][i+(1<<j-1)]] ? st[j-1][i] : st[j-1][i+(1<<j-1)];
	}
}

inline int LCA(int x, int y) {
	x = dfn[x], y = dfn[y];
	if(x > y) swap(x, y);
	int i = lg2[y-x+1];
	// debug("lca {} {} = {}\n", x, y, dep[st[i][x]] < dep[st[i][y-(1<<i)+1]] ? st[i][x] : st[i][y-(1<<i)+1]);
	return dep[st[i][x]] < dep[st[i][y-(1<<i)+1]] ? st[i][x] : st[i][y-(1<<i)+1];
}

inline ll getdis(int x, int y) {
	int lca = LCA(x, y);
	return dis[x] + dis[y] - dis[lca] * 2;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n-1) {
		int u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	dfs(1, 0);
	buildst();
	
	s.insert(mp(dfn[1], 1));
	cin >> k;
	
	int cnt = k;
	ll ans = 0;
	
	auto insert = [&](int x) {
		if(!s.count(mp(dfn[x], x))) {
			debug("insert = {}\n", x);
			if(s.size() == 1) {
				debug("ans += 2*{}\n", getdis(x, s.begin()->se));
				ans += 2ll*getdis(x, s.begin()->se);
			} else {
				auto it1 = s.lower_bound(mp(dfn[x], x));
				auto it2 = it1;
				if(it1 == s.begin()) it2 = --s.end();
				else if(it1 == s.end()) {
					--it2;
					it1 = s.begin();
				} else {
					--it2;
				}
				debug("ans -= {}\n", getdis(it1->se, it2->se));
				ans -= getdis(it1->se, it2->se);
				debug("ans += {} {}\n", getdis(it1->se, x), getdis(it2->se, x));
				ans += getdis(it1->se, x);
				ans += getdis(it2->se, x);
			}
			s.insert(mp(dfn[x], x));
			debug("ans = {}\n", ans);
		}
	};
	
	auto erase = [&](int x) {
		if(s.count(mp(dfn[x], x))) {
			auto it1 = ++s.find(mp(dfn[x], x));
			s.erase(mp(dfn[x], x));
			if(s.size() == 1) {
				ans = 0;
				return;
			}
			auto it2 = it1;
			if(it2 == s.begin()) it2 = --s.end();
			else --it2;
			if(it1 == s.end()) it1 = s.begin();
			ans -= getdis(it1->se, x);
			ans -= getdis(it2->se, x);
			ans += getdis(it1->se, it2->se);
		}
	};
	
	rep(i, 1, k) {
		int x; cin >> x;
		insert(x);
	}
	
	cout << ans/2 + a[1] << "\n";
	
	cin >> q;
	while(q--) {
		
	}
	
	return 0;
}
