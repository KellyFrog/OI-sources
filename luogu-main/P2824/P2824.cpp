// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
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
#define rg register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
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
		rg char ch = ' ';
		rg int ps = 1;
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
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 2e5 + 5;

int sum[N << 2], lazy[N << 2];
int n, q, p, a[N], b[N];
pair<int, pair<int, int> > qry[N];

void Lazy(int cur, int x, int l, int r) {
	lazy[cur] = x;
	sum[cur] = x * (r - l + 1);
}

void pushdown(int cur, int l, int r) {
	int mid = l + r >> 1;
	if(lazy[cur] != -1) {
		Lazy(cur << 1, lazy[cur], l, mid);
		Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
		lazy[cur] = -1;
	}
}

void pushup(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}

int querysum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res = res + querysum(cur << 1, ql, qr, l, mid);
	if(mid < qr) res = res + querysum(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

void modify(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x, l, r), void();
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) modify(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

void build(int cur, int l, int r) {
	lazy[cur] = -1;
	if(l == r) return sum[cur] = b[l], void();
	int mid = l + r >> 1;
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
	pushup(cur);
}

bool check(int x) {
	rep(i, 1, n) b[i] = (a[i] <= x);
	build(1, 1, n);
	rep(i, 1, q) {
		int op = qry[i].fi, L = qry[i].se.fi, R = qry[i].se.se;
		if(L > R) continue;
		if(op == 0) {
			int sm = querysum(1, L, R, 1, n);
			if(sm > 0) modify(1, L, L + sm - 1, 1, 1, n);
			if(sm < R - L + 1) modify(1, L + sm, R, 0, 1, n);
		} else {
			int sm = querysum(1, L, R, 1, n);
			if(sm > 0) modify(1, R - sm + 1, R, 1, 1, n);
			if(sm < R - L + 1) modify(1, L, R - sm, 0, 1, n);
		}
	}
	return querysum(1, p, p, 1, n);
}

int main() {
	fastio::qread(n, q);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, q) fastio::qread(qry[i].fi, qry[i].se.fi, qry[i].se.se);
	fastio::qread(p);
	int L = 1, R = n;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		if(check(mid)) res = mid, R = mid - 1;
		else L = mid + 1;
	}
	// assert(res != -1);
	cout << res << "\n";
	fastio::flush();
	return 0;
}
