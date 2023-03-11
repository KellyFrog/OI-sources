// Problem: P3748 [六省联考 2017] 摧毁“树状图”
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3748
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Create Time: 2022-03-08 11:03:03
// Input/Output: stdin/stdout
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 5e5 + 5;

int n;
vector<int> adj[N];
int f[N][4];
int ans;
int tp;

inline void upd(int& x, int y) {
	if(x < y) x = y;
}

inline void dfs(int u, int fa) {
	f[u][0] = 0;
	f[u][1] = f[u][2] = f[u][3] = adj[u].size();
	vector<int> ff[4];
	vector<int> mx;
	for(int v : adj[u]) {
		if(v == fa) continue;
		dfs(v, u);
		ff[0].pb(f[v][0]);
		ff[1].pb(f[v][1]);
		ff[2].pb(f[v][2]);
		ff[3].pb(f[v][3]);
		mx.pb(max(f[v][0], f[v][1]));
	}
	sort(mx.begin(), mx.end(), greater<int>());
	if(mx.size() > 1) upd(ans, mx[0] + mx[1] - 1);
	if(ff[0].empty()) return;
	sort(ff[0].begin(), ff[0].end(), greater<int>());
	sort(ff[1].begin(), ff[1].end(), greater<int>());
	sort(ff[2].begin(), ff[2].end(), greater<int>());
	sort(ff[3].begin(), ff[3].end(), greater<int>());
	upd(f[u][0], ff[0][0]);
	upd(f[u][0], ff[1][0]);
	if(ff[0].size() > 1) upd(f[u][1], ff[2][0] + ff[2][1] + (int)adj[u].size() - 4);
	
	upd(f[u][2], ff[2][0] + (int)adj[u].size() - 2);
	upd(f[u][1], f[u][2]);
	upd(f[u][3], ff[3][0] + (int)adj[u].size() - 2);
	// debug("f[u][3] = {} {} {}\n", f[u][3], ff[3][0], adj[u].size());
	if(ff[0].size() > 2) upd(f[u][3], ff[2][0] + ff[2][1] + ff[2][2] + (int)adj[u].size() - 6);
	multiset<int> s;
	
	
		
	auto get = [&](int k) {
		if(k > s.size()) return (int)-1e9;
		int ret = 0;
		auto it = s.rbegin();
		while(k--) {
			ret += *it;
			++it;
		}
		return ret;
	};
	
	for(int x : ff[2]) s.insert(x);
	for(int v : adj[u]) {
		if(v == fa) continue;
		s.erase(s.find(f[v][2]));
		
		upd(f[u][3], f[v][0] + get(1) + (int)adj[u].size() - 3);
		upd(f[u][3], f[v][0] + (int)adj[u].size() - 1);
		upd(f[u][3], f[v][1] + get(1) + (int)adj[u].size() - 4);
		// debug("{} -> {}, get {} + {} + {} and {} + {} + {}\n", u, v, f[v][0], get(1), (int)adj[u].size()-3, f[v][1], get(1), (int)adj[u].size()-4);
		// debug("fuck {} {}\n", f[v][0], (int)adj[u].size()-1);
		// debug("f[3] = {}\n", f[u][3]);
		
		upd(ans, f[v][3] + get(1) + (int)adj[u].size() - 4);
		upd(ans, f[v][0] + get(2) + adj[u].size() - 5);
		upd(ans, f[v][1] + get(2) + adj[u].size() - 6);
		
		s.insert(f[v][2]);
	}
	
	
	upd(ans, get(4) + (int)adj[u].size() - 8);
	
	upd(ans, f[u][0]);
	upd(ans, f[u][1]);
	upd(ans, f[u][2]);
	upd(ans, f[u][3]);
	
	// debug("get f[{}] = {} {} {} {}\n", u, f[u][0], f[u][1], f[u][2], f[u][3]);
}

void solve(int T) {
	cin >> n;
	int tt = tp;
	while(tt--) {
		int x, y;
		cin >> x >> y;
	}
	if(n == 1) {
		cout << 0 << "\n";
		return;
	}
	ans = 0;
	rep(i, 1, n) f[i][0] = f[i][1] = f[i][2] = f[i][3] = 0;
	rep(i, 1, n) adj[i].clear();
	rep(i, 2, n) {
		int  u, v;
		cin >> u >> v;
		adj[u].pb(v);
		adj[v].pb(u);
	}
	dfs(1, 0);
	cout << ans << "\n";
	
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t >> tp;
	rep(T, 1, t) {
		solve(T);
	}
	
	return 0;
}
