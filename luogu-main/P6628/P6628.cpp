// Problem: P6628 [省选联考 2020 B 卷] 丁香之路
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6628
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-03-14 17:17:46
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

#define ONLINE_JUDGE

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

const int N = 2.5e3 + 5;

int n, m, s;
int uni0[N], uni[N];
ll ans, ans0;
int d0[N], d[N];
bool ok0[N], ok[N];

inline int find(int x, int uni[]) { return x == uni[x] ? x : uni[x] = find(uni[x], uni); }

ll solve(int t) {
	debug("solve = {}, ans0 = {}\n", t, ans0);
	ans = ans0;
	memcpy(d, d0, sizeof d);
	memcpy(uni, uni0, sizeof uni);
	memcpy(ok, ok0, sizeof ok);
	
	d[s] ^= 1;
	d[t] ^= 1;
	
	ok[s] = ok[t] = 1;
	
	auto merge = [&](int x, int y) {
		x = find(x, uni);
		y = find(y, uni);
		if(x != y) {
			uni[x] = y;
			return 1;
		}
		return 0;
	};
	
	merge(s, t);
	
	int last = -1;
	rep(i, 1, n) {
		if(d[i] == 1) {
			if(last == -1) last = i;
			else {
				ans += abs(i - last);
				rep(j, last, i) merge(j, i), ok[j] = 1;
				debug("[{}, {}]\n", last, i);
				last = -1;
			}
		}
	}
	
	vector<pair<int, pair<int, int>>> e;
	
	
	last = -1;
	rep(i, 1, n) {
		if(ok[i]) {
			if(last == -1) last = i;
			else {
				e.pb(mp(i-last, mp(i, last)));
				last = i;
			}
		}
	}
	
	sort(e.begin(), e.end());
	for(auto [w, ee] : e) {
		auto [u, v] = ee;
		debug("get edge {} {} {}\n", u, v, w);
		if(merge(u, v)) {
			ans += 2ll * w;
			debug("merge = {} {} {}\n", u, v, w);
		}
	}
	
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> s;
	rep(i, 1, n) uni0[i] = i;
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		debug("{} {} {}\n", u, v, abs(u-v));
		ans0 += abs(u-v);
		d0[u] ^= 1;
		d0[v] ^= 1;
		u = find(u, uni0);
		v = find(v, uni0);
		ok0[u] = ok0[v] = 1;
		if(u != v) {
			uni0[u] = v;
		}
	}
	
	rep(i, 1, n) {
		cout << solve(i) << " \n"[i == n];
	}
	
	return 0;
}

