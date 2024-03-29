
// Problem: F2. Guess the K-th Zero (Hard version)
// Contest: Codeforces - Codeforces Round #719 (Div. 3)
// URL: https://codeforces.com/problemset/problem/1520/F2
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
const int mod =2017;

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

const int N = 2e5 + 5;
const int SIZ = 8;

int n, q;

int sum[N];
inline int lowbit(int x) {
	return x & (-x);
}
inline void add(int x, int val) {
	for(int x0 = x; x0 <= n; x0 += lowbit(x0)) sum[x0] += val;
}
inline int getsum(int x) {
	int res = 0;
	for(int x0 = x; x0 > 0; x0 -= lowbit(x0)) res += sum[x0];
	return res;
}

inline int ask(int L, int R) {
	L = max(L, 1);
	R = min(R, n);
	printf("? %d %d\n", L, R);
	fflush(stdout);
	int ret = 0;
	scanf("%d", &ret);
	return R - L + 1 - ret;
}

inline void answer(int p) {
	printf("! %d\n", p);
	fflush(stdout);
}

inline void solve(int k) {
	int L = 1, R = n / SIZ + 1;
	int res = -1;
	while(L <= R) {
		int mid = L + R >> 1;
		if(getsum(mid) >= k) {
			res = mid;
			R = mid - 1;
		} else {
			L = mid + 1;
		}
	}
	int p = (res - 1) * SIZ + 1;
	L = 1, R = SIZ;
	res = -1;
	while(L < R) {
		int mid = L + R >> 1;
		if(ask(1, p + mid - 1) >= k) {
			R = mid;
		} else {
			L = mid + 1;
		}
	}
	res = p + R - 1;
	answer(res);
	add((res - 1) / SIZ + 1, -1);
}

int main() {
	scanf("%d%d", &n, &q);
	int x;
	scanf("%d", &x);
	for(int i = 1; i <= n; i += SIZ) add(i / SIZ + 1, ask(i, i + SIZ - 1));
	solve(x);
	rep(i, 2, q) {
		scanf("%d", &x);
		solve(x);
	}
	return 0;
}
