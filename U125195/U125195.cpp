// Problem: U125195 大战杀马特(smart)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U125195
// Memory Limit: 128 MB
// Time Limit: 3000 ms

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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n")
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

/* template ends here */

const int N = 1e5 + 5;
const ll inf = 0x3f3f3f3f;

struct Node {
	ll mival; int mipos;
	ll mxval; int mxpos;
	ll ans; int ansi, ansj;
	ll lazy;
};

struct Query {
	int l1, r1;
	int l2, r2;
	int type;
	Node ans;
	Query() {}
	Query(int l1, int r1, int l2, int r2, int type, Node ans) : l1(l1), l2(l2), r1(r1), r2(r2), type(type), ans(ans) {}
};

bool operator < (const Query& x, const Query& y) { return x.ans.ans < y.ans.ans; }

Node tree[N<<2];
int n, q;
int a[N];
priority_queue<Query> pq;

inline void setlazy(int cur, ll x) {
	tree[cur].lazy += x;
	tree[cur].mival += x;
	tree[cur].mxval += x;
}

inline void pushdown(int cur) {
	if(tree[cur].lazy) {
		setlazy(cur << 1, tree[cur].lazy);
		setlazy(cur << 1 | 1, tree[cur].lazy);
		tree[cur].lazy = 0;
	}
}

inline Node mergenode(const Node& x, const Node& y, bool flag = 0) {
	// debug("[merge] x = {mi = [{}] {}, mx = [{}], {}, ans = [{}, {}], {}}\n", x.mipos, x.mival, x.mipos, x.mival, x.ansi, x.ansj, x.ans);
	// debug("[merge] y = {mi = [{}] {}, mx = [{}], {}, ans = [{}, {}], {}}\n", y.mipos, y.mival, y.mipos, y.mival, y.ansi, y.ansj, y.ans);
	
	Node ret;
	if(x.mxval > y.mxval) {
		ret.mxval = x.mxval;
		ret.mxpos = x.mxpos;
	} else {
		ret.mxval = y.mxval;
		ret.mxpos = y.mxpos;
	}
	
	if(x.mival < y.mival) {
		ret.mival = x.mival;
		ret.mipos = x.mipos;
	} else {
		ret.mival = y.mival;
		ret.mipos = y.mipos;
	}
	
	ret.ans = -inf;
	if(!flag && x.ans > ret.ans) ret.ans = x.ans, ret.ansi = x.ansi, ret.ansj = x.ansj;
	if(!flag && y.ans > ret.ans) ret.ans = y.ans, ret.ansi = y.ansi, ret.ansj = y.ansj;
	if(x.mxval - y.mival > ret.ans) ret.ans = x.mxval - y.mival, ret.ansi = x.mxpos, ret.ansj = y.mipos;
	
	ret.lazy = 0;
	
	// debug("[merge] ret = {mi = [{}] {}, mx = [{}], {}, ans = [{}, {}], {}}\n", ret.mipos, ret.mival, ret.mipos, ret.mival, ret.ansi, ret.ansj, ret.ans);
	
	return ret;
}

inline void pushup(int cur) {
	tree[cur] = mergenode(tree[cur << 1], tree[cur << 1 | 1]);
}

inline void build(int cur, int l, int r) {
	debug("node {} for [{}, {}]\n", cur, l, r);
	if(l == r) {
		tree[cur].mxval = tree[cur].mival = a[l];
		tree[cur].mxpos = tree[cur].mipos = l;
		tree[cur].ans = 0, tree[cur].ansi = tree[cur].ansj = l;
		return;
	}
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

inline void add(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

Node qres; bool qfirst;

inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		// debug("get node {} [{}, {}]\n", cur, l, r);
		if(qfirst) qres = tree[cur], qfirst = 0;
		else qres = mergenode(qres, tree[cur]);
		return;
	}
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);
}

inline void qinsert(int l1, int r1, int l2, int r2) {
	if(l1 > r1 || l2 > r2) return;
	if(l1 == l2 && r1 == r2) {
		debug("case 1, insert = {} {}\n", l1, r1);
		qfirst = 1;
		query(1, l1, r1, 1, n);
		pq.push(Query(l1, r1, l2, r2, 1, qres));
	} else {
		if(l1 == l2) {
			if(r1 > r2) {
				qinsert(l2, r2, l2, r2);
				qinsert(r2+1, r1, l2, r2);
				// qinsert(l1, r1, l1, r1);
				// qinsert(l1, r1, r1+1, r2);
			} else {
				qinsert(l1, r1, l1, r1);
			}
		} else if(r1 == r2) {
			if(l1 < l2) {
				qinsert(l1, l2-1, l2, r2);
				qinsert(l2, r2, l2, r2);
			} else {
				qinsert(l1, r1, l1, r1);
			}
		} else {
			if(r1 < l2) {
				debug("case 2, insert = [{}, {}], [{}, {}]\n", l1, r1, l2, r2);
				qfirst = 1; query(1, l1, r1, 1, n); Node res1 = qres;
				qfirst = 1; query(1, l2, r2, 1, n); Node res2 = qres;
				pq.push(Query(l1, r1, l2, r2, 2, mergenode(res1, res2, 1)));
			}
		}
	}
}

ll solve(int l, int r, int k) {
	debug("solve = [{}, {}], t = {}\n", l, r, k);
	while(!pq.empty()) pq.pop();
	qinsert(l, r, l, r);
	ll res = 0;
	while(k--) {
		assert(!pq.empty());
		auto e = pq.top(); pq.pop();
		int x = e.ans.ansi;
		int y = e.ans.ansj;
		res += e.ans.ans;
		
		debug("get ans = {}\n", e.ans.ans);
		
		if(e.type == 1) {
			debug("type == 1, get ansi = {}, ansj = {}\n", x, y);
			int l = e.l1, r = e.r1;
			debug("call insert = [{}, {}], [{}, {}]\n", l, r, l, y-1);
			qinsert(l, r, l, y-1);
			debug("call insert = [{}, {}], [{}, {}]\n", l, r, y+1, r);
			qinsert(l, r, y+1, r);
			debug("call insert = [{}, {}], [{}, {}]\n", l, x-1, y, y);
			qinsert(l, x-1, y, y);
			debug("call insert = [{}, {}], [{}, {}]\n", x+1, min(r, y), y, y);
			qinsert(x+1, min(r, y), y, y);
		} else {
			debug("type == 2, get ansi = {}, ansj = {}\n", x, y);
			int l1 = e.l1, r1 = e.r1;
			int l2 = e.l2, r2 = e.r2;
			qinsert(l1, r1, l2, y-1);
			qinsert(l1, x-1, y, y);
			qinsert(x+1, r1, y, y);
			qinsert(l1, r1, y+1, r2);
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	build(1, 1, n);
	while(q--) {
		int op, l, r, x;
		cin >> op >> l >> r >> x;
		if(op == 1) {
			add(1, l, r, x, 1, n);
		} else {
			cout << solve(l, r, x) << "\n";
		}
	}
	
	return 0;
}