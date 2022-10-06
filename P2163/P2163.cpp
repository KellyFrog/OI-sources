// Problem: P2163 [SHOI2007]园丁的烦恼
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2163
// Memory Limit: 125 MB
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

const int N = 5e5 + 5;
const int L = 100;

int lson[N*L], rson[N*L], sum[N*L], rt[N], ncnt;
int a[N], b[N], c[N], x[N], y[N], id[N];
int n, q;

inline void add(int& o, int rt, int p, int l, int r) {
	o = ++ncnt;
	lson[o] = lson[rt], rson[o] = rson[rt], sum[o] = sum[rt] + 1;
	if(l == r) return;
	int mid = l + r >> 1;
	if(p <= mid) add(lson[o], lson[rt], p, l, mid);
	else add(rson[o], rson[rt], p, mid+1, r);
}

inline int query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[o];
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res += query(lson[o], ql, qr, l, mid);
	if(mid < qr) res += query(rson[o], ql, qr, mid+1, r);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) {
		cin >> x[i] >> y[i];
		c[i] = a[i] = x[i], b[i] = y[i];
	}
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	int ap = unique(a + 1, a + n + 1) - (a + 1);
	int bp = unique(b + 1, b + n + 1) - (b + 1);
	rep(i, 1, n) id[i] = i;
	sort(id + 1, id + n + 1, [&](int i, int j) { return x[i] < x[j]; });
	rep(i, 1, n) {
		x[i] = lower_bound(a + 1, a + ap + 1, x[i]) - a;
		y[i] = lower_bound(b + 1, b + bp + 1, y[i]) - b;
	}
	rep(i, 1, n) {
		int p = id[i];
		debug("i = {}, y = {}\n", i, y[p]);
		add(rt[i], rt[i-1], y[p], 1, bp);
	}
	
	sort(c + 1, c + n + 1);
	
	while(q--) {
		int aa, bb, cc, dd;
		cin >> aa >> bb >> cc >> dd;
		int p1 = lower_bound(c + 1, c + n + 1, aa) - c - 1;
		int p2 = upper_bound(c + 1, c + n + 1, cc) - c - 1;
		int l = lower_bound(b + 1, b + bp + 1, bb) - b;
		int r = upper_bound(b + 1, b + bp + 1, dd) - b - 1;
		
		debug("p = {}, {},  [{}, {}]\n", p1, p2, l, r);
		cout << query(rt[p2], l, r, 1, bp) - query(rt[p1], l, r, 1, bp) << "\n";
	}
	
	return 0;
}
