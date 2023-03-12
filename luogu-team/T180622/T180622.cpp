// Problem: T180622 开方平方
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T180622?contestId=45228
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e5 + 5;

int n, q;
int a[N];
int cnt1[N<<2], cnt2[N<<2];

inline void setsqrt(int cur, int x) {
	if(x >= cnt2[cur]) {
		x -= cnt2[cur];
		cnt2[cur] = 0;
		cnt1[cur] += x;
	} else {
		cnt2[cur] -= x;
	}
}

inline void setsq(int cur, int x) {
	cnt2[cur] += x;
}

inline void pushdown(int cur) {
	if(cnt1[cur]) {
		setsqrt(cur << 1, cnt1[cur]);
		setsqrt(cur << 1 | 1, cnt1[cur]);
		cnt1[cur] = 0;
	}
	if(cnt2[cur]) {
		setsq(cur << 1, cnt2[cur]);
		setsq(cur << 1 | 1, cnt2[cur]);
		cnt2[cur] = 0;
	}
}

inline pair<int, int> query(int cur, int p, int l, int r) {
	if(l == r) return mp(cnt1[cur], cnt2[cur]);
	pushdown(cur);
	int mid = l + r >> 1;
	if(p <= mid) return query(cur << 1, p, l, mid);
	else return query(cur << 1 | 1, p, mid + 1, r);
}


inline void modifysq(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return setsq(cur, 1), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) modifysq(cur << 1, ql, qr, l, mid);
	if(mid < qr) modifysq(cur << 1 | 1, ql, qr, mid + 1, r);
}

inline void modifysqrt(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return setsqrt(cur, 1), void();
	pushdown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) modifysqrt(cur << 1, ql, qr, l, mid);
	if(mid < qr) modifysqrt(cur << 1 | 1, ql, qr, mid + 1, r);
}

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]);
	fastio::qread(q);
	while(q--) {
		int op, L, R;
		fastio::qread(op, L, R);
		if(op == 1) modifysqrt(1, L, R, 1, n);
		else modifysq(1, L, R, 1, n);
	}
	ll ans = 0;
	rep(i, 1, n) {
		auto res = query(1, i, 1, n);
		int x = res.fi, y = res.se;
		for(int j = 1; j <= x && a[i] != 1; j++) a[i] = sqrt(a[i]);
		ll p = qpow(2, y, mod-1);
		chkadd(ans, qpow(a[i], p, mod));
	}
	cout << ans << "\n";
  fastio::flush();
  return 0;
}
