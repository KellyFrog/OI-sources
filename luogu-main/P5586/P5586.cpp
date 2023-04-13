// Problem: P5586 [P5350] 序列 (加强版)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5586
// Memory Limit: 256 MB
// Time Limit: 2500 ms
// Create Time: 2022-03-24 17:50:42
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

template<typename T> inline void upd(T& x, const T& y) {	x += y;	if(x >= mod) x -= mod; }
template<typename T> inline void upd(T& x, const T& y, const T& z) { x = y + z; if(x >= mod) x -= mod; }

/* template ends here */

mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());
// mt19937_64 mtrnd(0);

const int N = 3e5 + 5;
const int M = N * 25;

int ls[M], rs[M], siz[M], sum[M], val[M], lazy1[M], lazy2[M], rev[M], tt, rt;
int n, q, a[N];

inline int newnode(int o) {
	int cur = ++tt;
	ls[cur] = ls[o];
	rs[cur] = rs[o];
	siz[cur] = siz[o];
	lazy1[cur] = lazy1[o];
	lazy2[cur] = lazy2[o];
	rev[cur] = rev[o];
	val[cur] = val[o];
	sum[cur] = sum[o];
	return cur;
}

inline void setlazy1(int o, int x) {
	lazy2[o] = 0;
	lazy1[o] = x;
	val[o] = x;
	sum[o] = 1ll * siz[o] * x % mod;
}

inline void setlazy2(int o, int x) {
	if(lazy1[o] != -1) {
		setlazy1(o, (lazy1[o] + x) % mod);
	} else {
		lazy2[o] = (lazy2[o] + x) % mod;
		sum[o] = (sum[o] + 1ll * siz[o] * x) % mod;
		val[o] = (val[o] + x) % mod;
	}
}

inline void setrev(int o) {
	rev[o] ^= 1;
	swap(ls[o], rs[o]);
}

inline void pushdown(int o) {
	if(lazy1[o] != -1 || lazy2[o] || rev[o]) {
		if(ls[o]) ls[o] = newnode(ls[o]);
		if(rs[o]) rs[o] = newnode(rs[o]);
	}
	if(lazy1[o] != -1) {
		setlazy1(ls[o], lazy1[o]);
		setlazy1(rs[o], lazy1[o]);
		lazy1[o] = -1;
	}
	if(lazy2[o]) {
		setlazy2(ls[o], lazy2[o]);
		setlazy2(rs[o], lazy2[o]);
		lazy2[o] = 0;
	}
	if(rev[o]) {
		setrev(ls[o]);
		setrev(rs[o]);
		swap(ls[o], rs[o]);
		rev[o] = 0;
	}
}

inline void pushup(int o) {
	siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
	sum[o] = ((unsigned int)sum[ls[o]] + sum[rs[o]] + val[o]) % mod;
}

inline void split(int& o1, int& o2, int o3, int k) {
	if(o3 == 0) {
		o1 = o2 = 0;
		return;
	}
	int o = newnode(o3);
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
	if(o1 == 0 || o2 == 0) {
		o = o1 + o2 ? newnode(o1 + o2)  : 0;
		return;
	}
	pushdown(o1);
	pushdown(o2);
	if(mtrnd() & 1) {
		o = newnode(o1);
		pushdown(o);
		merge(rs[o], rs[o1], o2);
	} else {
		o = newnode(o2);
		pushdown(o);
		merge(ls[o], o1, ls[o2]);
	}
	pushup(o);
}

inline void splitrange(int& a, int& b, int& c, int l, int r, int rt = ::rt) {
	split(a, c, rt, r);
	split(a, b, a, l-1);
}

inline void mergerange(int a, int b, int c, int& rt) {
	merge(rt, rt, a);
	merge(rt, rt, b);
	merge(rt, rt, c);
}

inline void build(int& o, int l, int r) {
	if(l > r) return o = 0, void();
	o = newnode(0);
	int mid = l + r >> 1;
	val[o] = a[mid];
	build(ls[o], l, mid-1);
	build(rs[o], mid+1, r);
	pushup(o);
}

inline void dfs(int o) {
	if(!o) return;
	pushdown(o);
	dfs(ls[o]);
	cout << val[o] << " ";
	dfs(rs[o]);
}

inline void dfs1(int o) {
	// if(!o) return;
	// pushdown(o);
	// dfs1(ls[o]);
	// debug("o = {}, ls = {}, rs = {}, val = {}, id = {}\n", o, ls[o], rs[o], val[o], id[o]);
	// dfs1(rs[o]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	memset(lazy1, -1, sizeof lazy1);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	
	
	build(rt, 1, n);

	int last = 0;
	while(q--) {
		int op;
		cin >> op;
		debug("query, op = {}\n", op);
		if(op == 1) {
			int l, r;
			cin >> l >> r;
			l ^= last, r ^= last;
			int a, b, c;
			splitrange(a, b, c, l, r);

			
			debug("a\n");dfs1(a);
			debug("b\n");dfs1(b);
			debug("c\n");dfs1(c);

			cout << (last = sum[b]) << "\n";
			rt = 0;
			mergerange(a, b, c, rt);

			debug("rt\n"); dfs1(rt);
		} else if(op == 2) {
			int l, r, x;
			cin >> l >> r >> x;
			l ^= last, r ^= last, x ^= last;
			int a, b, c;
			splitrange(a, b, c, l, r);

			debug("a\n");dfs1(a);
			debug("b\n");dfs1(b);
			debug("c\n");dfs1(c);

			setlazy1(b, x);

			// debug("after b\n");
			// dfs1(b);

			rt = 0;
			mergerange(a, b, c, rt);

			debug("rt\n"); dfs1(rt);
		} else if(op == 3) {
			int l, r, x;
			cin >> l >> r >> x;
			l ^= last, r ^= last, x ^= last;
			int a, b, c;
			splitrange(a, b, c, l, r);
			setlazy2(b, x);
			rt = 0;
			mergerange(a, b, c, rt);
		} else if(op == 4) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1 ^= last, l2 ^= last, r1 ^= last, r2 ^= last;
			if(r1 < l2) {
				int a, b, c, d, e;
				splitrange(c, d, e, l2, r2, rt);
				splitrange(a, b, c, l1, r1, c);
				d = newnode(b);
				rt = 0;
				mergerange(a, b, c, rt);
				mergerange(d, e, 0, rt);
			} else {
				int a, b, c, d, e;
				splitrange(c, d, e, l1, r1, rt);
				splitrange(a, b, c, l2, r2, c);

				debug("split ok, get {} {} {} {} {}\n", a, b, c, d, e);

				b = newnode(d);
				rt = 0;
				mergerange(a, b, c, rt);
				mergerange(d, e, 0, rt);
			}
		} else if(op == 5) {
			int l1, r1, l2, r2;
			cin >> l1 >> r1 >> l2 >> r2;
			l1 ^= last, l2 ^= last, r1 ^= last, r2 ^= last;

			if(l1 > r2) swap(l1, l2), swap(r1, r2);

			int a, b, c, d, e;
			splitrange(c, d, e, l2, r2, rt);
			splitrange(a, b, c, l1, r1, c);
			int b0 = newnode(d);
			int d0 = newnode(b);
			d = d0, b = b0;
			
			rt = 0;
			mergerange(a, b, c, rt);
			mergerange(d, e, 0, rt);
		} else {
			int l, r;
			cin >> l >> r;
			l ^= last, r ^= last;
			int a, b, c;
			splitrange(a, b, c, l, r);
			setrev(b);
			rt = 0;
			mergerange(a, b, c, rt);
		}
		// assert(siz[rt] == n);
	}

	dfs(rt);
	cout << "\n";
	
	return 0;
}