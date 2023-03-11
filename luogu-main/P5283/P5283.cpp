// Problem: P5283 [十二省联考 2019] 异或粽子
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5283
// Memory Limit: 1024 MB
// Time Limit: 3500 ms
// Create Time: 2022-03-15 18:10:28
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

const int N = 5e5 + 5;
const int M = 5e7 + 5;

int ls[M], rs[M], cnt[M], rt[N], tt;
int n, k;
ll a[N], pre[N];

inline void add(int& o1, int o2, ll x, int dep, int val) {
	o1 = ++tt;
	ls[o1] = ls[o2];
	rs[o1] = rs[o2];
	cnt[o1] = cnt[o2] + val;
	if(dep == -1) return;
	if(x >> dep & 1) add(rs[o1], rs[o2], x, dep - 1, val);
	else add(ls[o1], ls[o2], x, dep - 1, val);
	debug("add, o1 = {}, ls = {}, rs = {}\n", o1, ls[o1], rs[o1]);
}

inline ll query(int o, ll x, int dep) {
	debug("query = {} {} {}\n", x, o, dep);
	if(dep == -1) return 0;
	int o1 = ls[o], o2 = rs[o];
	if(x >> dep & 1) swap(o1, o2);
	debug("o2 = {}, rs = {}\n", o2, rs[o]);
	if(cnt[o2]) {
		debug("get {}\n", 1ll << dep);
		return query(o2, x, dep - 1) | 1ll << dep;
	} else {
		return query(o1, x, dep - 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) pre[i] = pre[i-1] ^ a[i];
	add(rt[0], 0, 0, 33, 1);
	rep(i, 1, n) add(rt[i], rt[i-1], pre[i], 33, 1);
	priority_queue<pair<ll, int>> pq;
	rep(i, 1, n) {
		pq.push(mp(query(rt[i], pre[i], 33), i));
	}
	ll ans = 0;
	while(k--) {
		auto [val, id] = pq.top(); pq.pop();
		debug("get id = {}, val = {}\n", id, val);
		ans += val;
		ll x = val ^ pre[id];
		add(rt[id], rt[id], x, 33, -1);
		
		pq.push(mp(query(rt[id], pre[id], 33), id));
	}
	
	cout << ans << "\n";
	
	return 0;
}

