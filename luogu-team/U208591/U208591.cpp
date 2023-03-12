// Problem: U208591 【20220319模拟赛t2】小 ds，确信
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U208591
// Memory Limit: 512 MB
// Time Limit: 1500 ms
// Create Time: 2022-03-22 18:44:06
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

const int N = 1e6 + 10;

struct T {
	ll mxc, mxd, mxvc, mxval, mxvd, lazyc, lazyd;
} t[N<<2];;

int n;
tuple<ll, ll, ll, ll> v[N];
ll a[N], b[N], c[N], d[N];
ll valc[N], vald[N];
ll sufmi[N];
int va[N], vb[N], sa, sb;

inline void setlazyc(int o, int x, int l, int r) {
	t[o].lazyc = x;
	t[o].mxc = x;
	t[o].mxvc = x + vb[l];
	t[o].mxval = t[o].mxvd + x;
}

inline void setlazyd(int o, int x, int l, int r) {
	t[o].lazyd = x;
	t[o].mxd = x;
	t[o].mxvd = x + vb[l];
	t[o].mxval = t[o].mxvc + x;
}

inline void pushdown(int o, int l, int r) {
	int mid = l + r >> 1;
	if(t[o].lazyc != -1) {
		setlazyc(o << 1, t[o].lazyc, l, mid);
		setlazyc(o << 1 | 1, t[o].lazyc, mid + 1, r);
		t[o].lazyc = -1;
	}
	if(t[o].lazyd != -1) {
		setlazyd(o << 1, t[o].lazyd, l, mid);
		setlazyd(o << 1 | 1, t[o].lazyd, mid + 1, r);
		t[o].lazyd = -1;
	}
}

inline void pushup(int o) {
	t[o].mxvc = min(t[o << 1].mxvc, t[o << 1 | 1].mxvc);
	t[o].mxvd = min(t[o << 1].mxvd, t[o << 1 | 1].mxvd);
	t[o].mxc = max(t[o << 1].mxc, t[o << 1 | 1].mxc);
	t[o].mxd = max(t[o << 1].mxd, t[o << 1 | 1].mxd);
	t[o].mxval = min(t[o << 1].mxval, t[o << 1 | 1].mxval);
}

inline void build(int o, int l, int r) {
	t[o].lazyc = t[o].lazyd = -1;
	if(l == r) {
		t[o].mxc = valc[l+1];
		t[o].mxd = vald[l+1];
		t[o].mxvc = valc[l+1] + vb[l];
		t[o].mxvd = vald[l+1] + vb[l];
		t[o].mxval = (ll)valc[l+1] + vald[l+1] + vb[l];
		return;
	}

	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

inline void modifyc(int o, int ql, int qr, int val, int l, int r) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) return setlazyc(o, val, l, r);
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) modifyc(o << 1, ql, qr, val, l, mid);
	if(mid < qr) modifyc(o << 1 | 1, ql, qr, val, mid + 1, r);
	pushup(o);
}

inline void modifyd(int o, int ql, int qr, int val, int l, int r) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) return setlazyd(o, val, l, r);
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) modifyd(o << 1, ql, qr, val, l, mid);
	if(mid < qr) modifyd(o << 1 | 1, ql, qr, val, mid + 1, r);
	pushup(o);
}

inline int findc(int o, int val, int l, int r) {
	if(t[o].mxc < val) return 1;
	if(l == r) return l+1;
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(t[o << 1 | 1].mxc > val) return findc(o << 1 | 1, val, mid + 1, r);
	else return findc(o << 1, val, l, mid);
}

inline int findd(int o, int val, int l, int r) {
	if(t[o].mxd < val) return 1;
	if(l == r) return l + 1;
	pushdown(o, l, r);
	int mid = l + r >> 1;
	if(t[o << 1 | 1].mxd > val) return findd(o << 1 | 1, val, mid + 1, r);
	else return findd(o << 1, val, l, mid);
}

inline ll query(int o, int ql, int qr, int l, int r) {
	if(ql > qr) return (ll)1e18;
	if(ql <= l && r <= qr) return t[o].mxval;
	pushdown(o, l, r);
	int mid = l + r >> 1;
	ll res = 1e18;
	if(ql <= mid) res = min(res, query(o << 1, ql, qr, l, mid));
	if(mid < qr) res = min(res, query(o << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

void solve(int T) {
	qio >> n;
	rep(i, 1, n) {
		auto& [a, b, c, d] = v[i];
		qio >> a >> b >> c >> d;
	}
	sort(v + 1, v + n + 1, greater<tuple<int, int, int, int>>());
	rep(i, 1, n) {
		auto& [a0, b0, c0, d0] = v[i];
		a[i] = a0;
		vb[i] = b[i] = b0;
		c[i] = c0;
		d[i] = d0;
	}

	if(n == 1) {
		cout << a[1] + b[1] + c[1] + d[1] << "\n";
		return;
	}

	sort(vb + 1, vb + n + 1);
	sb = unique(vb + 1, vb + n + 1) - vb - 1;
	rep(i, 1, n) b[i] = lower_bound(vb + 1, vb + sb + 1, b[i]) - vb;
	
	rep(i, 0, n+5) valc[i] = vald[i] = 0;
	sufmi[n+1] = (ll)1e18;
	per(i, 1, n) sufmi[i] = min(sufmi[i+1], b[i]);

	rep(i, 1, n) {
		valc[b[i]] = max(valc[b[i]], c[i]);
		vald[b[i]] = max(vald[b[i]], d[i]);
	}

	per(i, 1, sb-1) {
		valc[i] = max(valc[i], valc[i+1]);
		vald[i] = max(vald[i], vald[i+1]);
	}

	build(1, 1, sb);

	int p = 1;
	ll ans = 1e18;

	ll mi = 1e18;
	rep(i, 1, n) mi = min(mi, c[i] + d[i]);
	ans = min(ans, (ll)a[1] + vb[sb] + mi);

	while(p <= n) {

		if(p == 1) {
			ll res = query(1, 1, sb - 1, 1, sb);
			ans = min(ans, a[p] + res);
		} else {
			// int pos = *s.begin();
			int pos = sufmi[p];
			ll res = query(1, pos, sb, 1, sb);
			ans = min(ans, a[p] + res);
		}

		ll val = a[p];
		while(p <= n && a[p] == val) {
			int p1 = findc(1, c[p], 1, sb);
			modifyc(1, p1, sb, c[p], 1, sb);
			int p2 = findd(1, d[p], 1, sb);
			modifyd(1, p2, sb, d[p], 1, sb);
			++p;
		}
	}

	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	int t;
	qio >> t;
	rep(T, 1, t) solve(T);	
	return 0;
}
