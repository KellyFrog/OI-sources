// Problem: Sanae and Giant Robot
// Contest: Codeforces
// URL: https://m1.codeforces.com/contest/1687/problem/C
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// Create Time: 2022-06-03 23:13:57
// Input/Output: stdin/stdout
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

const int N = 2e5 + 5;

int n, m;
int a[N], b[N];
int mxr[N], mil[N];
ll s1[N], s2[N];
pair<int, int> c[N];
tuple<int, int, int> cur[N];
vector<int> adj[N];

void solve(int T) {
	cin >> n >> m;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) cin >> b[i];
	rep(i, 1, n) {
		s1[i] = s1[i-1] + a[i];
		s2[i] = s2[i-1] + b[i];
	}
	rep(i, 1, n+1) mxr[i] = 0, mil[i] = n+1;
	rep(i, 1, n) adj[i].clear();
	rep(i, 1, m) {
		cin >> c[i].fi >> c[i].se;
		mxr[c[i].fi] = max(mxr[c[i].fi], c[i].se);
		mil[c[i].se] = min(mil[c[i].se], c[i].fi);
	}
	rep(i, 1, m) adj[c[i].fi].pb(i), adj[c[i].se].pb(i);
	rep(i, 1, n) mxr[i] = max(mxr[i], mxr[i-1]);
	per(i, 1, n-1) mil[i] = min(mil[i], mil[i+1]);
	set<tuple<int, int, int>> s;
	set<int> neq;
	rep(i, 1, n) neq.insert(i);
	rep(i, 1, m) cur[i] = {0, 0, 0};
	
	auto update = [&](int i) {
		auto [l, r] = c[i];
		// rep(i, 1, n) cerr << a[i] << " \n"[i == n];
		// rep(i, 1, n) cerr << b[i] << " \n"[i == n];
		s.erase(cur[i]);
		if(s1[r] - s1[l-1] == s2[r] - s2[l-1]) {
			if(mxr[l] == r && mil[r] >= l) {
				cur[i] = {-1, l, i};
			} else {
				cur[i] = {0, l, i};
			}
		} else {
			cur[i] = {1, l, i};
		}
		s.insert(cur[i]);
	};
	
	rep(i, 1, m) {
		update(i);
	}
	while(!s.empty()) {
		auto [tp, lll, id] = *s.begin();
		s.erase(s.begin());
		if(tp == 1) break;
		auto [l, r] = c[id];
		cerr << l << " " << r << "\n";
		for(auto it = neq.lower_bound(l); it != neq.end() && *it <= r; ++it) {
			int p = *it;
			a[p] = b[p];
			s1[p] = s1[p-1] + a[p];
		}
		for(auto it = neq.lower_bound(l); it != neq.end() && *it <= r; ++it) {
			int p = *it;
			for(int o : adj[p]) update(o);
		}
		for(auto it = neq.lower_bound(l); it != neq.end() && *it <= r; it = neq.erase(it));
	}
	rep(i, 1, n) if(a[i] != b[i]) {
		cout << "NO" << "\n";
		return;
	}
	cout << "YES" << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int t;
	cin >> t;
	rep(T, 1, t) solve(T);
	
	return 0;
}