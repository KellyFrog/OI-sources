// Problem: P3747 [六省联考 2017] 相逢是问候
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3747
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// Create Time: 2022-03-01 18:05:18
// Input/Output: stdin/stdout
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

std::mt19937_64 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 5e4 + 5;
const int M = 5e4 + 5;

int lw[100][M], hi[100][M];
int n, m, P, c;
int a[N];
int S;
vector<int> phi;
int mi[N<<2], sum[N<<2];

int getphi(int p) {
	int res = p;
	int pp = p;
	for(int i = 2; i * i <= pp; ++i) {
		if(p % i == 0) {
			res /= i;
			res *= i-1;
			while(p % i == 0) p /= i;
		}
	}
	if(p > 1) {
		res /= p;
		res *= p-1;
	}
	return res;
}

inline int emod(const ll& x, int p) {
	return x < p ? x : x % p + p;
}

inline int getpow(int x, int id) {
	// debug("getpow {} {}, {} {}\n", x, id, lw[id][x%S], hi[id][x/S]);
	return emod(1ll * lw[id][x%S] * hi[id][x/S], phi[id]);
}

int calc(int x, int t) {
	
	t = min<int>(t, phi.size());
	// debug("calc {} {}\n", x, t);
	for(int i = t-1; i >= 0; --i) {
		// debug("{}^{} emod {}\n", c, x, phi[i]);
		x = getpow(x, i);
		// debug("i = {}, get x = {}\n", i, x);
	}
	x %= P;
	// debug("get x = {}\n", x);
	return x;
}

inline void pushup(int o) {
	sum[o] = (sum[o<<1] + sum[o<<1|1]) % P;
}

inline void build(int o, int l, int r) {
	mi[o] = 0;
	if(l == r) {
		sum[o] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

inline void dfs(int o, int l, int r) {
	if(mi[o] > phi.size()+1) return;
	++mi[o];
	if(l == r) {
		sum[o] = calc(a[l], mi[o]);
		return;
	}
	int mid = l + r >> 1;
	dfs(o << 1, l, mid);
	dfs(o << 1 | 1, mid + 1, r);
	pushup(o);
}

inline void modify(int o, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) {
		dfs(o, l, r);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) modify(o << 1, l, mid, ql, qr);
	if(mid < qr) modify(o << 1 | 1, mid + 1, r, ql, qr);
	pushup(o);
}

inline int query(int o, int l, int r, int ql, int qr) {
	if(ql <= l && r <= qr) return sum[o];
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res = (res + query(o << 1, l, mid, ql, qr)) % P;
	if(mid < qr) res = (res + query(o << 1 | 1, mid+1, r, ql, qr)) % P;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> P >> c;
	rep(i, 1,n) cin >> a[i];
	int pp = P;
	phi.pb(pp);
	do {
		phi.pb(pp = getphi(pp));
	} while(pp != 1);
	phi.pb(1), phi.pb(1);
	
	
	// for(int p : phi) cerr << p << " "; cerr << "\n";
	
	int PP = 2*P;
	
	S = sqrt(PP);
	for(int i = 0; i < phi.size(); ++i) {
		lw[i][0] = 1;
		rep(j, 1, S) lw[i][j] = emod(1ll * lw[i][j-1] * c, phi[i]);
		hi[i][0] = 1;
		rep(j, 1, S+1) hi[i][j] = emod(1ll * hi[i][j-1] * lw[i][S], phi[i]);
	}
	
	build(1, 1, n);
	
	while(m--) {
		int op, l, r;
		cin >> op >> l >> r;
		if(op == 0) {
			modify(1, 1, n, l, r);
		} else {
			cout << query(1, 1, n, l, r) << "\n";
		}
	}
	
	// for(int x : phi) cerr << x << " "; cerr << "\n";
	return 0;
}
