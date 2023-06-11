// Problem: X(or)-mas Tree
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1615/problem/D
// Memory Limit: 256 MB
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

const int N = 4e5 + 5;

vector<pair<int, int>> adj[N];
int n, m;
int uni[N*2];
vector<int> bel[N];
bool vis[N];
int ans[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }
inline void merge(int x, int y) {
	debug("merge = {} {}\n", x, y);
	x = find(x), y = find(y);
	if(uni[x] != uni[y]) uni[x] = y;
}

inline void dfs(int u, int fa, int p) {
	if(p != -1) {
		if(p) merge(u, fa+n), merge(u+n, fa);
		else merge(u, fa), merge(u+n, fa+n);
	}
	for(auto [v, w] : adj[u]) {
		if(v == fa) continue;
		dfs(v, u, w==-1 ? w : (__builtin_popcount(w) & 1));
	}
}

inline void dfsans(int u, int fa) {
	for(auto [v, w] : adj[u]) {
		if(v == fa) continue;
		if(w == -1) cout << u << " " << v << " " << (ans[u] ^ ans[v]) << "\n";
		else cout << u << " " << v << " " << w << "\n";
		dfsans(v, u);
	}
}

void solve() {
	debug("solve\n");
	cin >> n >> m;
	rep(i, 1, n) vis[i] = 0, bel[i].clear(), bel[i+n].clear(), adj[i].clear();
	rep(i, 1, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	rep(i, 1, 2*n) uni[i] = i;
	dfs(1, 0, -1);
	rep(i, 1, m) {
		int x, y, z;
		cin >> x >> y >> z;
		if(z) merge(x+n, y), merge(x, y+n);
		else merge(x, y), merge(x+n, y+n);
	}
	rep(i, 1, n) if(find(i) == find(i+n)) {
		cout << "NO" << "\n";
		return;
	}
	cout << "YES" << "\n";
	rep(i, 1, 2*n) bel[find(i)].pb(i);
	rep(i, 1, n) {
		if(!vis[i]) {
			for(int x : bel[find(i)]) {
				if(x <= n) ans[x] = 0, vis[x] = 1;
				else ans[x-n] = 1, vis[x-n] = 1;
			}
		}
	}
	dfsans(1, 0);
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
