// Problem: P4364 [九省联考 2018] IIIDX
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4364
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// Create Time: 2022-03-10 16:24:11
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

const int N = 5e5 + 5;

int n;
double k;
vector<int> adj[N], dept[N];
int a[N];
int mi[N<<2], lazy[N<<2], cnt[N<<2];
int pos[N], siz[N], dep[N];
bool vis[N];

inline void pushup(int o) {
	mi[o] = min(mi[o<<1], mi[o<<1|1]);
	cnt[o] = cnt[o<<1] + cnt[o<<1|1];
}

inline void setlazy(int o, int x) {
	mi[o] += x;
	lazy[o] += x;
}

inline void pushdown(int o) {
	if(lazy[o]) {
		setlazy(o << 1, lazy[o]);
		setlazy(o << 1 | 1, lazy[o]);
		lazy[o] = 0;
	}
}

inline void add1(int o, int p, int x, int l, int r) {
	if(l == r) {
		cnt[o] = 1;
		mi[o] += x;
		// debug("add mi[{}] to {}, {}\n", o, mi[o]);
		return;
	}
	pushdown(o);
	int mid = l + r >> 1;
	if(p <= mid) add1(o << 1, p, x, l, mid);
	else add1(o << 1 | 1, p, x, mid + 1, r);
	pushup(o);
}

inline void add2(int o, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(o, x), void();
	pushdown(o);
	int mid = l + r >> 1;
	if(ql <= mid) add2(o << 1, ql, qr, x, l, mid);
	if(mid < qr) add2(o << 1 | 1, ql, qr, x, mid+1, r);
	pushup(o);
}

inline int dfs(int o, int val, int l, int r) {
	if(l == r) return l - (mi[o] < val);
	pushdown(o);
	int mid = l + r >> 1;
	// debug("o = {}, [{}, {}] ls = {}\n", o, l, mid, mi[o << 1]);
	if(mi[o << 1] >= val && cnt[o << 1 | 1] != r - mid) return dfs(o << 1 | 1, val, mid+1, r);
	else return dfs(o << 1, val, l, mid);
}

inline int getf(int i) {
	return int(floor(i/k));
}

inline void dfs0(int u, int fa) {
	// debug("{} -> {}\n", u, fa);
	dep[u] = dep[fa] + 1;
	
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v != fa) dfs0(v, u), siz[u] += siz[v];
	}
}

inline void build(int o, int l, int r) {
	if(l == r) {
		mi[o] = n-l+1;
		// debug("mi[{}] = {}\n", o, mi[o]);
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i];
	sort(a + 1, a + n + 1);
	rep(i, 1, n) {
		int o = getf(i);
		if(o) {
			adj[o].pb(i);
		}
	}
	
	rep(i, 1, n) if(getf(i) == 0) dfs0(i, 0);
	
	build(1, 1, n);
	
	rep(i, 1, n) {
		int o = getf(i);
		if(o && !vis[o]) {
			vis[o] = 1;
			add1(1, pos[o], siz[o], 1, n);
			if(pos[o] > 1) add2(1, 1, pos[o]-1, siz[o], 1, n);
		}
		// debug("i = {}, siz = {}\n", i, siz[i]);
		pos[i] = dfs(1, siz[i], 1, n);
		add1(1, pos[i], -siz[i], 1, n);
		if(pos[i] > 1) add2(1, 1, pos[i] - 1, -siz[i], 1, n);
	}
	
	rep(i, 1, n) cout << a[pos[i]] << " \n"[i == n];
	
	return 0;
}
