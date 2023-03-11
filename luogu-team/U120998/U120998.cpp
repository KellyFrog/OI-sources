// Problem: U120998 最大连续子段和（带修）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U120998
// Memory Limit: 256 MB
// Time Limit: 2000 ms

/*
 * Author: chenkaifeng @BDFZ
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second

#if __cplusplus < 201703L
#define register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		char ch = ' ';
		int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

const int N = 5e5 + 5;

struct Node {
	ll maxi, pre, suf, lazy, sum;
};

Node tree[N<<2];
Node res; bool isfirst;
int a[N], n, q;

inline void merge(Node& x, const Node y, const Node z) {
	x.maxi = max(max(y.maxi, z.maxi), y.suf + z.pre);
	x.pre = max(y.pre, y.sum + z.pre);
	x.suf = max(z.suf, z.sum + y.suf);
	x.sum = y.sum + z.sum;
}

inline void pushup(int cur) {
	merge(tree[cur], tree[cur << 1], tree[cur << 1 | 1]);
}

inline void setlazy(int cur, ll x, int l, int r) {
	tree[cur].lazy = x;
	tree[cur].sum = 1ll * (r - l + 1) * x;
	if(x > 0) tree[cur].pre = tree[cur].suf = tree[cur].maxi = tree[cur].sum;
	else tree[cur].pre = tree[cur].suf = tree[cur].maxi = x;
}

inline void pushdown(int cur, int l, int r) {
	if(tree[cur].lazy) {
		int mid = l + r >> 1;
		setlazy(cur << 1, tree[cur].lazy, l, mid);
		setlazy(cur << 1 | 1, tree[cur].lazy, mid + 1, r);
		tree[cur].lazy = 0;
	}
}

inline void modify(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql <= l && r <= qr) return setlazy(cur, x, l, r), void();
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) modify(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

inline void query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) {
		if(isfirst) res = tree[cur], isfirst = 0;
		else merge(res, res, tree[cur]);
		return;
	}
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) query(cur << 1, ql, qr, l, mid);
	if(mid < qr) query(cur << 1 | 1, ql, qr, mid + 1, r);
}

inline void build(int cur, int l, int r) {
	if(l == r) return setlazy(cur, a[l], l, l), void();
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> q;
	rep(i, 1, n) cin >> a[i];
	build(1, 1, n);
	while(q--) {
		int op, l, r;
		cin >> op >> l >> r;
		if(op == 1) {
			int x; cin >> x;
			modify(1, l, r, x, 1, n);
		} else {
			isfirst = 1;
			query(1, l, r, 1, n);
			cout << res.maxi << "\n";
		}
	}
	
	fastio::flush();
	return 0;
}
