// Problem: P4390 [BOI2007]Mokia 摩基亚
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4390
// Memory Limit: 125 MB
// Time Limit: 2000 ms
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

const int N = 2e6 + 5;

struct Q {
	int x, y1, y2, op, pos, id;
	Q() {}
	Q(int x0, int y10, int y20, int op0, int pos0, int id0) : x(x0), y1(y10), y2(y20), op(op0), pos(pos0), id(id0) {}
};

int n, qq;

int t[N];

inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int p) { for(int x0 = x; x0 <= n; x0 += lowbit(x0)) t[x0] += p; }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += t[x0]; return res; }
inline int query(int l, int r) { return query(r) - query(l-1); }

Q q[N];
int tt;
int ans[N];
bool qr[N];

inline void cdq(int l, int r) {
	if(l == r) return;
	int mid = l + r >> 1;
	cdq(l, mid);
	cdq(mid+1, r);
	sort(q + l, q + r + 1, [&](const Q& x, const Q& y) { return x.x == y.x ? abs(x.op) < abs(y.op) : x.x < y.x; });
	rep(i, l, r) {
		if(q[i].pos <= mid && q[i].op == 1) {
			add(q[i].y1, q[i].y2);
		}
		if(q[i].pos > mid && abs(q[i].op) == 2) {
			ans[q[i].id] += (q[i].op / 2) * query(q[i].y1, q[i].y2);
		}
	}
	rep(i, l, r) {
		if(q[i].pos <= mid && q[i].op == 1) {
			add(q[i].y1, -q[i].y2);
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	int tmp;
	cin >> tmp >> n;
	while(++qq) {
		int op; cin >> op;
		if(op == 3) break;
		if(op == 1) {
			int x, y, k;
			cin >> x >> y >> k;
			++tt;
			q[tt] = Q(x, y, k, 1, tt, 0);
		} else {
			qr[qq] = 1;
			int x1, x2, y1, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			++tt, q[tt] = Q(x1-1, y1, y2, -2, tt, qq);
			++tt, q[tt] = Q(x2, y1, y2, 2, tt, qq);
		}
	}
	
	cdq(1, tt);
	
	rep(i, 1, qq) {
		if(qr[i]) cout << ans[i] << "\n";
	}
	
	return 0;
}
