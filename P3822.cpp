// Problem: P3822 [NOI2017] 整数
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3822
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Create Time: 2022-06-07 16:06:41
// Input/Output: stdin/stdout
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
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
const ll B = (1ll << 60) - 1;
const int inf = 0x3f3f3f3f;

int n, q, t1, t2, t3;
ll val[N<<2];
int pos0[N<<2], pos1[N<<2];

inline void setlazy(int o, int x, int l, int r) {
	val[o] = x;
	pos0[o] = x == 0 ? inf : l;
	pos1[o] = x == B ? inf : l;
}

inline void pushdown(int o, int l, int r) {
	if(val[o] != -1) {
		int mid = l + r >> 1;
		setlazy(o << 1, val[o], l, mid);
		setlazy(o << 1 | 1, val[o], mid + 1, r);
		val[o] = -1;
	}
}

inline void pushup(int o) {
	pos0[o] = min(pos0[o << 1], pos0[o << 1 | 1]);
	pos1[o] = min(pos1[o << 1], pos1[o << 1 | 1]);
}

inline int query(int o, int ql, int qr, bool op, int l, int r) {
	if(ql <= l && r <= qr) {
		return op ? pos1[o] : pos0[o];
	}
	pushdown(o, l, r);
	int mid = l + r >> 1;
	int res = inf;
	if(ql <= mid) res = min(res, query(o << 1, ql, qr, op, l, mid));
	if(mid < qr) res = min(res, query(o << 1 | 1, ql, qr, op, mid + 1, r));
	return res;
}

inline bool add(int o, int p, ll x, int l, int r) {
	if(l == r) {
		ll y = val[o] + x;
		bool ret = y < 0 || y > B;
		if(y < 0) y += B;
		if(y > B) y &= B;
		setlazy(o, y, l, r);
		return ret;
	}
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(p <= mid) return add(o << 1, p, x, l, mid);
	else return add(o << 1 | 1, p, x, mid + 1, r);
}

inline void modify(int o, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x, l, r), void();
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) modify(o << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(o << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(o);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> q >> t1 >> t2 >> t3;
	n = 1e6;
	setlazy(1, 0, 0, n);

	while(q--) {
		int op; cin >> op;
		if(op == 1) {
			int x, k; cin >> x >> k;

		}
	}

	return 0;
}