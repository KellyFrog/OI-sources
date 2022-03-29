// Problem: P2831 [NOIP2016 提高组] 愤怒的小鸟
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2831
// Memory Limit: 500 MB
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

const int N = 18;
const int L = 1 << N | 5;
const double eps = 1e-6;

int dp[L];
double x[N+5], y[N+5];
int n, m;

void calc(double& a, double& b, int i, int j) {
	a = (y[i] / x[i] - y[j] / x[j]) / (x[i] - x[j]);
	b = (y[i] / x[i] - a * x[i]);
}

void solve() {
	cin >> n >> m;
	rep(i, 1, n) cin >> x[i] >> y[i];
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	int lim = (1 << n) - 1;
	rep(S, 1, lim) {
		int p = -1;
		rep(i, 0, n-1) if(S & (1 << i)) { p = i; break; }
		assert(p != -1);
		if(!(S ^ (1 << p))) {
			dp[S] = 1;
			continue;
		}
		rep(i, p+1, n-1) {
			if(fabs(x[p+1] - x[i+1]) < eps) continue;
			double a, b;
			calc(a, b, p+1, i+1);
			if(a > 0 || fabs(a) < eps) continue;
			debug("S = {} p = {} i = {}, a = {} b = {}\n", S, p+1, i+1, a, b);
			int S0 = S;
			rep(j, 0, n-1) {
				if(S0 & (1 << j)) {
					if(fabs(y[j+1] - (a * x[j+1] * x[j+1] + b * x[j+1])) < eps) {
						debug("ok get {} for S0\n", j+1);
						S0 ^= (1 << j);
					}
				}
			}
			chkmin(dp[S], dp[S0]+1);
		}
		chkmin(dp[S], dp[S^(1<<p)]+1);
		debug("dp[{}] = {}\n", S, dp[S]);
	}
	cout << dp[lim] << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	fastio::flush();
	return 0;
}
