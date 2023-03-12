// Problem: P2042 [NOI2005] 维护数列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2042
// Memory Limit: 128 MB
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int siz[N], ls[N], rs[N];
unsigned pri[N];
int lazy[N], rev[N], pre[N], suf[N], ans[N], sum[N], val[N], rt;
int trash[N], trp, tt;

inline void pushup(int o) {
	siz[o] = siz[ls[o]] + siz[rs[o]] + 1;
	pre[o] = max(0, max(pre[ls[o]], max(sum[ls[o]] + val[o], sum[ls[o]] + val[o] + pre[rs[o]])));
	suf[o] = max(0, max(suf[rs[o]], max(sum[rs[o]] + val[o], sum[rs[o]] + val[o] + suf[ls[o]])));
	ans[o] = max(max(ans[ls[o]], ans[rs[o]]), val[o] + suf[ls[o]] + pre[rs[o]]);
	sum[o] = sum[ls[o]] + val[o] + sum[rs[o]];
}

inline void setlazy(int o, int x) {
	if(!o) return;
	rev[o] = 0;
	val[o] = x;
	lazy[o] = x;
	sum[o] = siz[o] * x;
	if(x < 0) {
		pre[o] = suf[o] = 0;
		ans[o] = x;
	} else {
		ans[o] = pre[o] = suf[o] = sum[o];
	}
}

inline void setrev(int o) {
	if(!o) return;
	rev[o] ^= 1;
	swap(ls[o], rs[o]);
	swap(pre[o], suf[o]);
}

inline void pushdown(int o) {
	if(lazy[o] != inf) {
		setlazy(ls[o], lazy[o]);
		setlazy(rs[o], lazy[o]);
		lazy[o] = inf;
	}
	if(rev[o]) {
		setrev(ls[o]);
		setrev(rs[o]);
		rev[o] = 0;
	}
}

inline void split(int& o1, int& o2, int o, int k) {
	if(!o) {
		o1 = 0;
		o2 = 0;
		return;
	}
	pushdown(o);
	if(k <= siz[ls[o]]) {
		o2 = o;
		split(o1, ls[o2], ls[o], k);
	} else {
		o1 = o;
		split(rs[o1], o2, rs[o], k-siz[ls[o]]-1);
	}
	pushup(o);
}

inline void merge(int& o, int o1, int o2) {
	if(!o1 || !o2) {
		o = o1 + o2;
		return;
	}
	pushdown(o1);
	pushdown(o2);
	if(pri[o1] < pri[o2]) {
		o = o1;
		merge(rs[o], rs[o1], o2);
	} else {
		o = o2;
		merge(ls[o], o1, ls[o2]);
	}
	pushup(o);
}

inline int newnode(int v) {
	int o = trp ? trash[trp--] : ++tt;
	lazy[o] = inf;
	ls[o] = rs[o] = 0;
	rev[o] = 0;
	val[o] = sum[o] = ans[o] = v;
	pre[o] = suf[o] = max(v, 0);
	pri[o] = mtrnd();
	siz[o] = 1;
	return o;
}

int a[N];

inline int build(int l, int r) {
	if(l > r) return 0;
	if(l == r) {
		return newnode(a[l]);
	}
	int mid = l + r >> 1;
	int o = newnode(a[mid]);
	ls[o] = build(l, mid-1);
	rs[o] = build(mid+1, r);
	pushup(o);
	return o;
}

int n, q;

inline void erase(int o) {
	if(!o) return;
	erase(ls[o]);
	erase(rs[o]);
	trash[++trp] = o;
}

inline void dfs(int o) {
	if(!o) return;
	dfs(ls[o]);
	cerr << val[o] << " ";
	dfs(rs[o]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	ans[0] = -inf;
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	rt = build(1, n);
	
	while(q--) {
		string op; cin >> op;
		if(op == "GET-SUM") {
			int s, len; cin >> s >> len;
			--s;
			int a, b, c, d;
			split(a, b, rt, s);
			split(c, d, b, len);
			cout << sum[c] << "\n";
			merge(b, c, d);
			merge(rt, a, b);
		} else if(op == "MAX-SUM") {
			cout << ans[rt] << "\n";
		} else if(op == "INSERT") {
			int s, len; cin >> s >> len;
			rep(i, 1, len) cin >> a[i];
			int x, y;
			split(x, y, rt, s);
			int o = build(1, len);
			merge(x, x, o);
			merge(rt, x, y);
		} else if(op == "MAKE-SAME") {
			int s, len, x; cin >> s >> len >> x;
			--s;
			int a, b, c, d;
			split(a, b, rt, s);
			split(c, d, b, len);
			setlazy(c, x);
			merge(b, c, d);
			merge(rt, a, b);
		} else if(op == "REVERSE") {
			int s, len; cin >> s >> len;
			--s;
			int a, b, c, d;
			split(a, b, rt, s);
			split(c, d, b, len);
			setrev(c);
			merge(b, c, d);
			merge(rt, a, b);
		} else if(op == "DELETE") {
			int s, len; cin >> s >> len;
			--s;
			int a, b, c, d;
			split(a, b, rt, s);
			split(c, d, b, len);
			erase(c);
			b = d;
			merge(rt, a, b);
			
		}
	}
	
	return 0;
}