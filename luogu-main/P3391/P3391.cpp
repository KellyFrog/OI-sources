// Problem: P3391 【模板】文艺平衡树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3391
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Create Time: 2022-04-14 19:47:07
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

mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

int n, m, a[N], rt;
int siz[N], val[N], ls[N], rs[N], rev[N], tt;
unsigned pri[N];

inline void setlazy(int o) {
	rev[o] ^= 1;
	swap(ls[o], rs[o]);
}

inline void pushdown(int o) {
	if(rev[o]) {
		setlazy(ls[o]);
		setlazy(rs[o]);
		rev[o] = 0;
	}
}

inline void pushup(int o) {
	siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
}

inline void split(int& o1, int& o2, int o, int k) {
	if(!o) {
		o1 = o2 = 0;
		return;
	}
	pushdown(o);
	if(k <= siz[ls[o]]) {
		o2 = o;
		split(o1, ls[o2], ls[o], k);
	} else {
		o1 = o;
		split(rs[o1], o2, rs[o], k - siz[ls[o]] - 1);
	}
	pushup(o);
}

inline void merge(int& o, int o1, int o2) {
	if(!o1 || !o2) {
		o = o1 + o2;
		return;
	}
	pushdown(o1);
	pushdown(o2);
	if(pri[o1] < pri[o2]) {
		o = o2;
		merge(ls[o], o1, ls[o2]);
	} else {
		o = o1;
		merge(rs[o], rs[o1], o2);
	}
	pushup(o);
}

inline int newnode(int v) {
	int o = ++tt;
	ls[o] = rs[o] = rev[o] = 0;
	siz[o] = 1, val[o] = v;
	pri[o] = mtrnd();
	return o;
}

inline void build(int& o, int l, int r) {
	if(l > r) return;
	int mid = l + r >> 1;
	o = newnode(mid);
	build(ls[o], l, mid - 1);
	build(rs[o], mid + 1, r);
	pushup(o);
}

inline void dfs(int o) {
	if(!o) return;
	pushdown(o);
	dfs(ls[o]);
	cout << val[o] << " ";
	dfs(rs[o]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	build(rt, 1, n);
	while(m--) {
		int l, r;
		cin >> l >> r;
		int a, b, c;
		split(b, c, rt, r);
		split(a, b, b, l-1);
		setlazy(b);
		rt = 0;
		merge(rt, rt, a);
		merge(rt, rt, b);
		merge(rt, rt, c);
		assert(siz[rt] == n);
	}

	dfs(rt);
	cout << "\n";

	return 0;
}