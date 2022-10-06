// Problem: P3369 【模板】普通平衡树
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3369
// Memory Limit: 128 MB
// Time Limit: 1000 ms
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

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

int val[N];
int lson[N], rson[N], siz[N], cnt[N], rt, ncnt;
unsigned pri[N];
int trash[N], trashp;

inline int newnode(int v = 0, int c = 1, int lc = 0, int rc = 0) {
	int u = trashp ? trash[trashp--] : ++ncnt;
	val[u] = v;
	lson[u] = lc, rson[u] = rc;
	siz[u] = cnt[u] = c;
	pri[u] = mtrnd();
	return u;
}

inline void pushup(int rt) {
	siz[rt] = cnt[rt] + siz[lson[rt]] + siz[rson[rt]];
}

inline void splitval(int& rt1, int& rt2, int rt, int v) {
	if(!rt) {
		rt1 = 0;
		rt2 = 0;
		return;
	}
	if(val[rt] <= v) {
		rt1 = rt;
		splitval(rson[rt1], rt2, rson[rt], v);
		pushup(rt1);
	} else {
		rt2 = rt;
		splitval(rt1, lson[rt2], lson[rt], v);
		pushup(rt2);
	}
}

inline void splitsize(int& rt1, int& rt2, int rt, int k) {
	if(!rt) {
		rt1 = 0;
		rt2 = 0;
		return;
	}
	if(k <= siz[lson[rt]]) {
		rt2 = rt;
		splitsize(rt1, lson[rt2], lson[rt], k);
		pushup(rt2);
	} else {
		rt1 = rt;
		splitsize(rson[rt1], rt2, rson[rt], k-siz[lson[rt]]-cnt[rt]);
		pushup(rt1);
	}
}

inline void merge(int&rt, int rt1, int rt2) {
	if(!rt1 || !rt2) {
		rt = rt1 + rt2;
		return;
	}
	if(pri[rt1] > pri[rt2]) {
		rt = rt1;
		merge(rson[rt], rson[rt1], rt2);
	} else {
		rt = rt2;
		merge(lson[rt], rt1, lson[rt2]);
	}
	pushup(rt);
}

inline void print(int rt) {
	if(!rt) return;
	debug("node = {}, val = {}, cnt = {}, siz = {}, son = ({}, {})\n", rt, val[rt], cnt[rt], siz[rt], lson[rt], rson[rt]);
	print(lson[rt]);
	print(rson[rt]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int q;
	cin >> q;
	while(q--) {
		int op, x; cin >> op >> x;
		if(op == 1) {
			int a, b;
			splitval(a, b, rt, x);
			
			int o = newnode(x);
			merge(rt, a, o);
			merge(rt, rt, b);
			
		} else if(op == 2) {
			int a, b, c, d;
			splitval(a, b, rt, x);
			splitval(c, d, a, x-1);
			merge(d, lson[d], rson[d]);
			merge(a, c, d);
			merge(rt, a, b);
		} else if(op == 3) {
			int a, b;
			splitval(a, b, rt, x-1);
			cout << siz[a]+1 << "\n";
			merge(rt, a, b);
		} else if(op == 4) {
			int a, b;
			splitsize(a, b, rt, x-1);
			int o = b;
			while(lson[o]) o = lson[o];
			cout << val[o] << "\n";
			merge(rt, a, b);
		} else if(op == 5) {
			int a, b;
			splitval(a, b, rt, x-1);
			int o = a;
			while(rson[o]) o = rson[o];
			cout << val[o] << "\n";
			merge(rt, a, b);
		} else if(op == 6) {
			int a, b;
			splitval(a, b, rt, x+1);
			int o = b;
			while(lson[o]) o = lson[o];
			cout << val[o] << "\n";
			merge(rt, a, b);
		}
	}
	
	return 0;
}