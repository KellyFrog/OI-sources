// Problem: CF484E Sign on Fence
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF484E
// Memory Limit: 250 MB
// Time Limit: 4000 ms
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 1e5 + 5;
const int L = 22;

struct T{
	int l, r, len, mx;
	T() : l(0), r(0), mx(0), len(0) {}
	T(int l0, int r0, int mx0, int len0) : l(l0), r(r0), mx(mx0), len(len0) {}
};

int n, q;
int a[N], b[N];
int lson[N*L], rson[N*L], rt[N], tt;
int id[N];
T t[N*L];

T operator + (const T& a, const T& b) {
	return T(
		a.l == a.len ? a.len + b.l : a.l,
		b.r == b.len ? a.r + b.len : b.r,
		max(max(a.mx, b.mx), a.r + b.l),
		a.len + b.len
	);
}

inline void add(int& o, int rt, int p, int l, int r) {
	o = ++tt;
	t[o] = t[rt];
	lson[o] = lson[rt], rson[o] = rson[rt];
	if(l == r) {
		t[o] = T(1, 1, 1, 1);
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) add(lson[o], lson[rt], p, l, mid);
	else add(rson[o], rson[rt], p, mid+1, r);
	t[o] = t[lson[o]] + t[rson[o]];
}

T res;
bool isf;

inline void query(int o, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isf) res = t[o], isf = 0;
		else res = res + t[o];
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) query(lson[o], ql, qr, l, mid);
	if(mid < qr) query(rson[o], ql, qr, mid+1, r);
}

inline int query(int p, int l, int r) {
	isf = 1;
	query(rt[p], l, r, 1, n);
	return res.mx;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) id[i] = i;
	sort(id + 1, id + n + 1, [&](int i, int j) { return a[i] > a[j]; });
	rep(i, 1, n) {
		add(rt[i], rt[i-1], id[i], 1, n);
	}
	cin >> q;
	while(q--) {
		int ql, qr, k;
		cin >> ql >> qr >> k;
		debug("[{}, {}] {}\n", ql, qr, k);
		int L = 1, R = n;
		int res = -1;
		while(L <= R) {
			int mid = L + R >> 1;
			debug("LR = {}, {}  mid = {}\n", L, R, mid);
			if(query(mid, ql, qr) >= k) {
				res = mid;
				R = mid - 1;
			} else {
				L = mid + 1;
			}
		}
		assert(res != -1);
		cout << a[id[res]] << "\n";
	}
	return 0;
}
