// Problem: CF1620F Bipartite Array
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1620F
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-02-28 10:49:47
// Author: Chen Kaifeng
// 
// Powered by CP Editor (https://cpeditor.org)

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

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int n, a[N];
int f[N][2];
pair<int, int> g[N][2];

inline void dfs(int i, int t) {
	if(i == 0) return;
	auto [tt, tp] = g[i][t];
	dfs(i-1, tt);
	cout << (t ? -a[i] : a[i]) << " ";
}

void solve() {
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) f[i][0] = f[i][1] = inf, g[i][0] = g[i][1] = mp(0 ,0);
	f[1][0] = f[1][1] = -inf;
	rep(i, 2, n) {
		rep(t1, 0, 1) {
			int x = t1 ? -a[i] : a[i];
			rep(t2, 0, 1) {
				int y = t2 ? -a[i-1] : a[i-1];
				
				auto upd = [&](int pos, int val) {
					debug("update, pos = {}, val = {}\n", pos, val);
					if(f[i][t1] > val) {
						debug("ok val = {}\n", val);
						f[i][t1] = val;
						g[i][t1] = mp(t2, pos);
					}
				};
				
				debug("i = {}, t1 = {}, t2 = {}, xy = {} {}\n", i, t1, t2, x, y);
				
				if(x > y) upd(1, f[i-1][t2]);
				if(f[i-1][t2] < x) upd(0, y);
			}
			debug("f[{}][{}] = {}\n", i, t1, f[i][t1]);
		}
	}
	
	if(f[n][0] != inf) {
		cout << "YES" << "\n";
		dfs(n, 0);
		cout << "\n";
		return;
	}
	if(f[n][1] != inf) {
		cout << "YES" << "\n";
		dfs(n, 1);
		cout << "\n";
		return;
	}
	cout << "NO" << "\n";
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
