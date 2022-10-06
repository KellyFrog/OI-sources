// Problem: P5787 二分图 /【模板】线段树分治
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5787
// Memory Limit: 256 MB
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
#define ep emplace_back
#define pf push_front
#define ef emplace_front
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

const int N = 2e5 + 5;

vector<pair<int, int>> op[N<<2];
int n, m, k;
bool ans[N];
int uni[N], siz[N];
int top;
int lastu[N], lastv[N];

inline int find(int x) { return x == uni[x] ? x : find(uni[x]); }
inline void merge(int x, int y) {
	x = find(x), y = find(y);
	if(x == y) return;
	if(siz[x] > siz[y]) swap(x, y);
	++top;
	lastu[top] = x;
	lastv[top] = y;
	uni[x] = y;
	siz[y] += siz[x];
}

inline void erase() {
	int x = lastu[top], y = lastv[top]; --top;
	uni[x] = x;
	siz[y] -= siz[x];
}

inline void add(int o, int ql, int qr, int u, int v, int l, int r) {
	if(ql <= l && r <= qr) {
		op[o].ep(u, v);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) add(o << 1, ql, qr, u, v, l, mid);
	if(mid < qr) add(o << 1 | 1, ql, qr, u, v, mid+1, r);
}

inline void dfs(int o, int l, int r, bool ok) {
	debug("dfs = {} {} {} {}\n", o, l, r, ok);
	int t0 = top;
	for(auto [u, v] : op[o]) {
		debug("u = {}, v = {}\n", u, v);
		int u1 = find(u), v1 = find(v);
		int u2 = find(u+n), v2 = find(v+n);
		if(u1 == v1 || u2 == v2) ok = 0;
		merge(u1, v2);
		merge(u2, v1);
	}
	debug("ok = {}\n", ok);
	if(l == r) {
		ans[l] = ok;
	} else {
		int mid = l + r >> 1;
		dfs(o << 1, l, mid, ok);
		dfs(o << 1 | 1, mid + 1, r, ok);
	}
	while(top > t0) erase();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> m >> k;
	rep(i, 1, m) {
		int u, v, l, r;
		cin >> u >> v >> l >> r;
		++l;
		add(1, l, r, u, v, 1, k);
	}
	rep(i, 1, 2*n) uni[i] = i, siz[i] = 1;
	
	debug("ae ok\n");
	
	dfs(1, 1, k, 1);
	rep(i, 1, k) cout << (ans[i] ? "Yes" : "No") << "\n";
	
	return 0;
}
