// Problem: F - Yakiniku Restaurants
// Contest: AtCoder - AtCoder Regular Contest 067
// URL: https://atcoder.jp/contests/arc067/tasks/arc067_d
// Memory Limit: 256 MB
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

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 5e3 + 5;
const int M = 2e2 + 5;

ll mx[N<<2], lazy[N<<2];

inline void setlazy(int cur, ll x) {
	mx[cur] += x;
	lazy[cur] += x;
}

inline void pushdown(int cur) {
	if(lazy[cur]) {
		setlazy(cur<<1, lazy[cur]);
		setlazy(cur<<1|1, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void pushup(int cur) {
	mx[cur] = max(mx[cur<<1], mx[cur<<1|1]);
}

inline void add(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur<<1, ql, qr, x, l, mid);
	if(mid < qr) add(cur<<1|1, ql, qr, x, mid+1, r);
	pushup(cur);
}

int a[N], b[N][M], n, m;
int stk[M][N], top[M];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m;
	rep(i, 2, n) cin >> a[i];
	rep(i, 1, n) rep(j, 1, m) cin >> b[i][j];
	
	ll ans = 0;
	
	rep(i, 1, n) {
		if(i>1) add(1, 1, i-1, -a[i], 1, n);
		debug("add [1, {}] = {}, i = {}\n", i, -a[i], i);
		rep(j, 1, m) {
			while(top[j] && b[stk[j][top[j]]][j] < b[i][j]) {
				int l = stk[j][top[j]-1] + 1, r = stk[j][top[j]];
				add(1, l, r, -b[stk[j][top[j]]][j], 1, n);
				debug("add [{}, {}] {}, color = {}\n", l, r, -b[stk[j][top[j]]][j], j);
				--top[j];
			}
			int p = stk[j][top[j]] + 1;
			stk[j][++top[j]] = i;
			add(1, p, i, b[i][j], 1, n);
			debug("add [{}, {}], {}, i = {}, j = {}\n", p, i, b[i][j], i, j);
		}
		debug("ans[{}] = {}\n", i, mx[1]);
		ans = max(ans, mx[1]);
	}
	
	cout << ans << "\n";
	
	return 0;
}
