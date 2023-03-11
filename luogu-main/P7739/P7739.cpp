// Problem: P7739 [NOI2021] 密码箱
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7739
// Memory Limit: 1024 MB
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

struct M {
	int a[2][2];
	M() {
		a[0][0] = 0;
		a[0][1] = 0;
		a[1][0] = 0;
		a[1][1] = 0; 
	}
	M(int b, int c, int d, int e) {
		a[0][0] = b;
		a[0][1] = c;
		a[1][0] = d;
		a[1][1] = e;
	}
};

M operator * (const M& a, const M& b) {
	return M(
	(1ll*a.a[0][0]*b.a[0][0] + 1ll*a.a[0][1]*b.a[1][0])%mod,
	(1ll*a.a[0][0]*b.a[0][1] + 1ll*a.a[0][1]*b.a[1][1])%mod,
	(1ll*a.a[1][0]*b.a[0][0] + 1ll*a.a[1][1]*b.a[1][0])%mod,
	(1ll*a.a[1][0]*b.a[0][1] + 1ll*a.a[1][1]*b.a[1][1])%mod
	);
}

const M W = M(1, 1, 1, 0) * M(0, 1, 1, 0);
const M E = M(1, 1, 1, 0) * M(1, 1, 1, 0) * M(0, 1, 1, 0) * M(0, 1, 1, mod-1);

void print(const M& x) {
	cerr << x.a[0][0] << " " << x.a[0][1] << "\n";
	cerr << x.a[1][0] << " " << x.a[1][1] << "\n";
}

const int N = 2e5 + 5;

int n, q;
char s[N];

int rt, lson[N], rson[N], siz[N], ncnt;
bool rev[N], flip[N];
M v[N][2][2];
int tp[N];
unsigned pri[N];

inline void setlazy(int rt, bool r, bool f) {
	if(!rt) return;
	if(r) {
		rev[rt] ^= 1;
		swap(v[rt][0][0], v[rt][1][0]);
		swap(v[rt][0][1], v[rt][1][1]);
	}
	if(f) {
		flip[rt] ^= 1;
		tp[rt] ^= 1;
		swap(v[rt][0][0], v[rt][0][1]);
		swap(v[rt][1][0], v[rt][1][1]);
	}
}

inline void pushdown(int rt) {
	if(!rt) return;
	if(rev[rt]) swap(lson[rt], rson[rt]);
	setlazy(lson[rt], rev[rt], flip[rt]);
	setlazy(rson[rt], rev[rt], flip[rt]);
	rev[rt] = flip[rt] = 0;
}

inline void pushup(int rt) {
	M o = tp[rt] ? E : W;
	M ro = tp[rt] ? W : E;
	v[rt][0][0] = v[rson[rt]][0][0] * o * v[lson[rt]][0][0];
	v[rt][0][1] = v[rson[rt]][0][1] * ro * v[lson[rt]][0][1];
	v[rt][1][0] = v[lson[rt]][1][0] * o * v[rson[rt]][1][0];
	v[rt][1][1] = v[lson[rt]][1][1] * ro * v[rson[rt]][1][1];
	siz[rt] = siz[lson[rt]] + siz[rson[rt]] + 1;
}

inline int newnode(int t) {
	int u = ++ncnt;
	lson[u] = rson[u] = 0;
	siz[u] = 1;
	tp[u] = t;
	M o = tp[u] ? E : W;
	M ro = tp[u] ? W : E;
	pri[u] = mtrnd();
	// pri[u] = u;
	v[u][0][0] = v[u][1][0] = o;
	v[u][0][1] = v[u][1][1] = ro;
	return u;
}

inline void split(int& rt1, int& rt2, int rt, int k) {
	if(!rt) {
		rt1 = rt2 = 0;
		return;
	}
	pushdown(rt);
	if(k <= siz[lson[rt]]) {
		rt2 = rt;
		split(rt1, lson[rt2], lson[rt], k);
		pushup(rt2);
	} else {
		rt1 = rt;
		split(rson[rt1], rt2, rson[rt], k-siz[lson[rt]]-1);
		pushup(rt1);
	}
}

inline void merge(int& rt, int rt1, int rt2) {
	if(!rt1 || !rt2) {
		rt = rt1 + rt2;
		return;
	}
	pushdown(rt1);
	pushdown(rt2);
	if(pri[rt1] > pri[rt2]) {
		rt = rt1;
		merge(rson[rt], rson[rt1], rt2);
		pushup(rt1);
	} else {
		rt = rt2;
		merge(lson[rt], rt1, lson[rt2]);
		pushup(rt2);
	}
}

inline void dfs(int rt) {
	if(!rt) return;
	debug("node = {}, siz = {}, lson = {}, rson = {}, c = {}\n", rt, siz[rt], lson[rt], rson[rt], "WE"[tp[rt]]);
	rep(i, 0, 1) rep(j, 0, 1) {
		debug("rev = {}, flip = {}:\n", rev[rt], flip[rt]);
		print(v[rt][i][j]);
	}
	dfs(lson[rt]);
	dfs(rson[rt]);
}

inline void insert(char c) {
	int t = c == 'E';
	int o = newnode(t);
	merge(rt, rt, o);
}

inline void qflip(int l, int r) {
	int a, b, c, d;
	split(a, b, rt, r);
	split(c, d, a, l-1);
	setlazy(d, 0, 1);
	merge(a, c, d);
	merge(rt, a, b);
}

inline void qreverse(int l, int r) {
	int a, b, c, d;
	split(a, b, rt, r);
	split(c, d, a, l-1);
	setlazy(d, 1, 0);
	merge(a, c, d);
	merge(rt, a, b);
}

inline void getans() {
	cout << v[rt][0][0].a[0][0] << " " << (v[rt][0][0].a[0][0] + v[rt][0][0].a[0][1]) % mod << "\n";
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	v[0][0][0] = v[0][0][1] = v[0][1][0] = v[0][1][1] = M(1, 0, 0, 1);
	
	cin >> n >> q;
	cin >> (s+1);
	rep(i, 1, n) insert(s[i]);
	
	getans();
	
	while(q--) {
		string o; cin >> o;
		if(o == "APPEND") {
			char ch; cin >> ch;
			insert(ch);
		} else if(o == "FLIP") {
			int l, r;
			cin >> l >> r;
			qflip(l, r);
		} else {
			int l, r;
			cin >> l >> r;
			qreverse(l, r);
		}
		
		getans();
	}
	
	return 0;
}
