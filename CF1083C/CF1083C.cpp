// Problem: CF1083C Max Mex
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1083C
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Create Time: 2022-03-02 13:59:34
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

// #define ONLINE_JUDGE

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

const int N = 2e5 + 5;

struct T {
	int s, t, lca;
	bool ok, ch;
	T() {}
	T(int s, int t, bool ok) : s(s), t(t), ok(ok) {}
} t[N<<2];

int n, q;
vector<int> adj[N];
int dep[N], st[21][N<<1], lg2[N<<1], pos[N], eul[N<<1], eid;
int a[N], b[N];

inline int compare(int x, int y) {
	return dep[x] < dep[y] ? x : y;
}

inline void dfs1(int u, int fa) {
	dep[u] = dep[fa] + 1;
	eul[pos[u] = ++eid] = u;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs1(v, u);
			eul[++eid] = u;
		}
	}
}

void buildst() {
	lg2[0] = -1;
	rep(i, 1, eid) lg2[i] = lg2[i>>1] + 1;
	
	rep(i, 1, eid) st[0][i] = eul[i];
	rep(j, 1, 20) rep(i, 1, eid) {
		if(i + (1 << j) - 1 > eid) break;
		st[j][i] = compare(st[j-1][i], st[j-1][i+(1<<j-1)]);
	}
}

inline int LCA(int x, int y) {
	x = pos[x], y = pos[y];
	if(x > y) swap(x, y);
	int j = lg2[y - x + 1];
	return compare(st[j][x], st[j][y-(1<<j)+1]);
}

inline T merge(const T& o1, const T& o2) {
	if(!o1.ok || !o2.ok) { return T(-1, -1, 0); }
	if(o1.s == o2.s || o1.s == o2.t || o1.t == o2.s || o1.t == o2.t) return T(-1, -1, 0);
	
	debug("merge ({}, {}), ({}, {})\n", o1.s, o1.t, o2.s, o2.t);
	
	static int v[4], res[4];
	int rp = 0;
	v[0] = o1.s;
	v[1] = o1.t;
	v[2] = o2.s;
	v[3] = o2.t;
	
	sort(v, v+4, [&](int i, int j) { return pos[i] < pos[j]; });
	
	int lca = LCA(v[0], v[3]);
	
	auto check = [&](int x, int y) {
		return LCA(x, y) == x;
	};
	
	for(int i = 0; i < 4; ++i) for(int j = 0; j < i; ++j) {
		bool ok = 1;
		if(i == j) continue;
		for(int k = 0; k < 4; ++k) {
			if(i == k || j == k) continue;
			if(!check(v[k], v[i]) && !check(v[k], v[j])) ok = 0;
		}
		if(ok) return T(v[i], v[j], 1);
	}
	
	return T(-1, -1, 0);
}

inline void pushup(int o) {
	t[o] = merge(t[o<<1], t[o<<1|1]);
}

inline void build(int o, int l, int r) {
	if(l == r) {
		t[o] = T(b[l], b[l], 1);
		return;
	}
	int mid = l + r >> 1;
	build(o << 1, l, mid);
	build(o << 1 | 1, mid + 1, r);
	pushup(o);
	debug("o = {}, [{}, {}], node = ({}, {})\n", o, l, r, t[o].s, t[o].t);
}

inline void modify(int o, int p, int x, int l, int r) {
	if(l == r) {
		t[o] = T(x, x, x);
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) modify(o << 1, p, x, l, mid);
	else modify(o << 1 | 1, p, x, mid+1, r);
	pushup(o);
}

T fuck;
bool isfirst;

inline int query(int o, int l, int r) {
	debug("o = {}, [{}, {}], fuck = ({}, {})\n", o, l, r, fuck.s, fuck.t);
	if(l == r) {
		fuck = isfirst ? t[o] : merge(fuck, t[o]);
		return fuck.ok ? l : l-1;
	}
	int mid = l + r >> 1;
	auto fuckfuck = isfirst ? t[o<<1] : merge(fuck, t[o<<1]);
	debug("get left = ({}, {})\n", fuckfuck.s, fuckfuck.t);
	if(fuckfuck.ok) {
		isfirst = 0;
		fuck = fuckfuck;
		return query(o<<1|1, mid+1, r);
	}
	return query(o<<1, l, mid);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i], ++a[i], b[a[i]] = i;
	rep(i, 2, n) {
		int f; cin >> f;
		debug("{} {}\n", i, f);
		adj[f].pb(i);
		adj[i].pb(f);
	}
	
	dfs1(1, 0);
	buildst();
	build(1, 1, n);
	
	cin >> q;
	while(q--) {
		int op, x, y;
		cin >> op;
		if(op == 1) {
			cin >> x >> y;
			int ax = a[x], ay = a[y];
			swap(a[x], a[y]);
			modify(1, ax, y, 1, n);
			modify(1, ay, x, 1, n);
			swap(b[ax], b[ay]);
			// rep(i, 1, n) cout << a[i]-1 << " \n"[i == n];
		} else {
			debug("query\n");
			isfirst = 1;
			cout << query(1, 1, n) << "\n";
		}
	}
	
	return 0;
}
