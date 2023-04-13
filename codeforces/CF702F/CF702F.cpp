// Problem: CF702F T-Shirts
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF702F
// Memory Limit: 1000 MB
// Time Limit: 4000 ms
// Create Time: 2022-03-23 16:45:45
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

mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

int ls[N], rs[N], val1[N], val2[N], lazy1[N], lazy2[N], id[N], tt;
unsigned pri[N];
int rt;
int n;
pair<int, int> a[N];
int k, b[N];
int ans[N];

inline void setlazy1(int o, int t) {
	if(o == 0) return;
	val1[o] += t;
	lazy1[o] += t;
}

inline void setlazy2(int o, int x) {
	if(o == 0) return;
	val2[o] += x;
	lazy2[o] += x;
}

inline void pushdown(int o) {
	if(lazy1[o]) {
		setlazy1(ls[o], lazy1[o]);
		setlazy1(rs[o], lazy1[o]);
		lazy1[o] = 0;
	}
	if(lazy2[o]) {
		setlazy2(ls[o], lazy2[o]);
		setlazy2(rs[o], lazy2[o]);
		lazy2[o] = 0;
	}
}

inline int newnode(int x, int p) {
	int o = ++tt;
	pri[o] = mtrnd();
	ls[o] = rs[o] = 0;
	val2[o] = x;
	val1[o] = lazy1[o] = lazy2[o] = 0;
	id[o] = p;
	return o;
}

inline void merge(int& o, int o1, int o2) {
	if(o1 == 0 || o2 == 0) {
		o = o1 + o2;
		return;
	}
	pushdown(o1);
	pushdown(o2);
	if(pri[o1] > pri[o2]) {
		o = o1;
		merge(rs[o], rs[o1], o2);
	} else {
		o = o2;
		merge(ls[o], o1, ls[o2]);
	}
}

inline void split(int& o1, int& o2, int o, int k) {
	if(o == 0) {
		o1 = o2 = 0;
		return;
	}
	pushdown(o);
	if(val2[o] > k) {
		o2 = o;
		split(o1, ls[o2], ls[o], k);
	} else {
		o1 = o;
		split(rs[o1], o2, rs[o], k);
	}
}

inline void insert(int o) {
	int x = val2[o];
	int a, b;
	split(a, b, rt, x);
	merge(a, a, o);
	merge(rt, a, b);
}

inline void dfs1(int o) {
	if(o == 0) return;
	pushdown(o);
	dfs1(ls[o]);
	dfs1(rs[o]);
	ls[o] = rs[o] = 0;
	insert(o);
}

inline void dfs2(int o) {
	if(o == 0) return;
	pushdown(o);
	ans[id[o]] = val1[o];
	dfs2(ls[o]);
	dfs2(rs[o]);
}

inline void dfs3(int o) {
	if(o == 0) return;
	pushdown(o);
	dfs3(ls[o]);
	debug("o = {}, ls = {}, rs = {}, val1 = {}, val2 = {}\n", o, ls[o], rs[o], val1[o], val2[o]);
	dfs3(rs[o]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n;
	rep(i, 1, n) cin >> a[i].se >> a[i].fi;
	sort(a + 1, a + n + 1, [&](const pair<int, int>& x, const pair<int, int>& y) { return x.fi == y.fi ? x.se < y.se : x.fi > y.fi; });
	
	cin >> k;
	rep(i, 1, k) {
		cin >> b[i];
		insert(newnode(b[i], i));
	}

	rep(i, 1, n) {
		int a, b, c;
		split(a, c, rt, ::a[i].se-1);
		split(b, c, c, 2*::a[i].se - 1);

		setlazy1(b, 1);
		setlazy1(c, 1);
		setlazy2(b, -::a[i].se);
		setlazy2(c, -::a[i].se);

		rt = a;
		dfs1(b);
		merge(rt, rt, c);
	}

	dfs2(rt);

	rep(i, 1, k) cout << ans[i] << " \n"[i == k];

	return 0;
}