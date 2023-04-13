// Problem: U181406 从思念伊始
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U181406?contestId=53984
// Memory Limit: 500 MB
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
#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)

namespace nqio{const unsigned R=4e5,W=4e5;char*a,*b,i[R],o[W],*c=o,*d=o+W,h[40],*p=h,y;bool s;struct q{void r(char&x){x=a==b&&(b=(a=i)+fread(i,1,R,stdin),a==b)?-1:*a++;}void f(){fwrite(o,1,c-o,stdout);c=o;}~q(){f();}void w(char x){*c=x;if(++c==d)f();}q&operator>>(char&x){do r(x);while(x<=32);return*this;}q&operator>>(char*x){do r(*x);while(*x<=32);while(*x>32)r(*++x);*x=0;return*this;}template<typename t>q&operator>>(t&x){for(r(y),s=0;!isdigit(y);r(y))s|=y==45;if(s)for(x=0;isdigit(y);r(y))x=x*10-(y^48);else for(x=0;isdigit(y);r(y))x=x*10+(y^48);return*this;}q&operator<<(char x){w(x);return*this;}q&operator<<(char*x){while(*x)w(*x++);return*this;}q&operator<<(const char*x){while(*x)w(*x++);return*this;}template<typename t>q&operator<<(t x){if(!x)w(48);else if(x<0)for(w(45);x;x/=10)*p++=48|-(x%10);else for(;x;x/=10)*p++=48|x%10;while(p!=h)w(*--p);return*this;}}qio;}using nqio::qio;

#define OK debug("OK!\n");
#ifndef ONLINE_JUDGE
namespace debuger{void debug(const char *s) {cerr << s;}template<typename T1,typename... T2>void debug(const char*s, const T1 x, T2...ls) { int p=0; while(*(s + p)!='\0') {if(*(s+p)=='{'&&*(s+p+1)=='}'){cerr << x;debug(s + p + 2, ls...);return;}cerr << *(s + p++);}}}using debuger::debug;
#else
#define debug(...) void(0)
#endif

// const ll mod = 1e9 + 7;
const ll mod = 998244353;
template <typename T> inline void chkadd(T& x, T y) { x = x + y >= mod ? x + y - mod : x + y; }
template <typename T> inline void chkadd(T& x, T y, T z) { x = y + z >= mod ? y + z - mod : y + z; }
template <typename T> inline void chkmns(T& x, T y) { x = x - y < 0 ? x - y + mod : x - y; }
template <typename T> inline void chkmns(T& x, T y, T z) { x = y - z < 0 ? y - z + mod : y - z;}
template <typename T> inline void chkmax(T& x, T y) { x = x < y ? y : x; }
template <typename T> inline void chkmax(T& x, T y, T z) { x = y > z ? y : z; }
template <typename T> inline void chkmin(T& x, T y) { x = x < y ? x : y;}
template <typename T> inline void chkmin(T& x, T y, T z) { x = y < z ? y : z;}
ll qpow(ll x, ll p) { ll base = x, res = 1;	while (p) { if (p & 1) res = (res * base) % mod; base = (base * base) % mod; p >>= 1;} return res;}

mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

/* template ends here */

const int N = 1e5 + 5;
const int M = N * 200;

struct Node {
	int ans, sum, cnt;
	int lans, rans;
	Node() : cnt(0), ans(0), sum(0), lans(0), rans(0) {}
};

Node tree[M];
int lson[M], rson[M];
int tcnt;

inline Node mergenode(const Node& x, const Node& y, int lenl, int lenr) {
	Node ret;
	ret.sum = x.sum + y.sum;
	chkmax(ret.ans, x.ans);
	chkmax(ret.ans, y.ans);
	chkmax(ret.ans, x.rans + y.lans);
	ret.lans = x.lans; if(x.sum == lenl) ret.lans = x.sum + y.lans;
	ret.rans = y.rans; if(y.sum == lenr) ret.rans = y.sum + x.rans;
	
	debug("merge node, ans = {}, {} {}\n", ret.ans, x.ans, y.ans);
	
	return ret;
}

inline void pushup(int cur, int l, int r) {
	int mid = l + r >> 1;
	tree[cur] = mergenode(tree[lson[cur]], tree[rson[cur]], mid - l + 1, r - mid);
}

inline void merge(int& rt1, int rt2, int l, int r) {
	if(rt1 == 0 || rt2 == 0) {
		rt1 += rt2;
		return;
	}
	if(l == r) {
		debug("merge leave at {} {}, pos = {}\n", rt1, rt2, l, r);
		tree[rt1].cnt += tree[rt2].cnt;
		if(tree[rt1].cnt) {
			tree[rt1].sum = 1;
			tree[rt1].lans = tree[rt1].rans = tree[rt1].ans = 1;
		} else {
			tree[rt1] = Node();
		}
		return;
	}
	int mid = l + r >> 1;
	merge(lson[rt1], lson[rt2], l, mid);
	merge(rson[rt1], rson[rt2], mid+1, r);
	pushup(rt1, l, r);
}

bool isfirst;
Node res;
int len;

inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		debug("get {} [{}, {}], q = [{}, {}], ans = {}\n", cur, l, r, ql, qr, tree[cur].ans);
		if(isfirst) res = tree[cur], len = r - l + 1, isfirst = 0;
		else res = mergenode(res, tree[cur], len, r - l + 1), len += r - l + 1;
		debug("res.ans = {}\n", res.ans);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) query(lson[cur], ql, qr, l, mid);
	if(mid < qr) query(rson[cur], ql, qr, mid + 1, r);
}

inline void add(int& cur, int p, int val, int l, int r) {
	if(!cur) cur = ++tcnt;
	if(l == r) {
		tree[cur].cnt += val;
		if(tree[cur].cnt) {
			tree[cur].sum = 1;
			tree[cur].lans = tree[cur].rans = tree[cur].ans = 1;
		} else {
			tree[cur] = Node();
		}
		return;
	}
	int mid = l + r >> 1;
	if(p <= mid) add(lson[cur], p, val, l, mid);
	else add(rson[cur], p, val, mid+1, r);
	pushup(cur, l, r);
}

int uni[N], rt[N], n, q;
int a[N];

inline int find(int x) { return x == uni[x] ? x : uni[x] = find(uni[x]); }

int main() {
	ios::sync_with_stdio(false); cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(15); cerr << fixed << setprecision(15);
	
	cin >> n >> q;
	rep(i, 1, n) {
		cin >> a[i];
		uni[i] = i;
		add(rt[i], a[i], 1, 1, (int)1e9);
	}
	while(q--) {
		int op, x, y, z;
		cin >> op >> x >> y;
		debug("op = {}\n", op);
		if(op == 1) {
			int fx = find(x);
			int fy = find(y);
			if(fx == fy) continue;
			debug("merge get {} {}\n", fx, fy);
			merge(rt[fx], rt[fy], 1, (int)1e9);
			uni[fy] = fx;
		} else if(op == 2) {
			int fx = find(x);
			cin >> z;
			isfirst = 1;
			debug("fx = {}\n", fx);
			query(rt[fx], y, z, 1, (int)1e9);
			cout << res.ans << "\n";
		} else {
			int fx = find(x);
			add(rt[fx], a[x], -1, 1, (int)1e9);
			a[x] = y;
			add(rt[fx], a[x], 1, 1, (int)1e9);
		}
	}
	
	return 0;
}
