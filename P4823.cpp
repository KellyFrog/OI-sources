//Author: Chenkaifeng

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
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (rg int i = s; i <= t; i++)
#define per(i, s, t) for (rg int i = t; i >= s; i--)
//#define debug(x) cerr << (#x) << " = " << (x) << "\n"
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;

		while (!isdigit(ch) && ch != '-')
			ch = getchar();

		if (ch == '-')
			ps = -1, ch = getchar();

		while (isdigit(ch))
			x = x * 10 + ch - '0', ch = getchar();

		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return ;
	}
	inline void putchar(char _x) {
		*oS++ = _x;

		if (oS == oT)
			flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0)
			putchar('-'), x = -x;

		if (x < 10)
			return putchar('0' + x), void();

		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
}; //namespace fastio


template<typename T>
inline void chkmax(T& x, T y) {
	if(x < y) x = y;
}

template<typename T>
inline void chkmin(T& x, T y) {
	if(x > y) x = y;
}

template<typename T>
inline void chkmod(T& x, ll mod) {
	x = x > mod ? x - mod : x;
}

template<typename T>
inline void chkadd(T& x, T y, ll mod) {
	x = x + y > mod ? x + y - mod : x + y;
}

template<typename T>
inline void chkmns(T& x, T y, ll mod) {
	x = x - y < 0 ? x - y + mod : x - y;
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 2005;
const int inf = 1e9;

int n, h;
int dp[N];  //算上所有小矮人，跑掉i个人最多的高度
pair<int, int> a[N];

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i].fi, a[i].se);
	fastio::qread(h);
	rep(i, 1, n) dp[i] = -inf;
	sort(a + 1, a + 1 + n, [](const pair<int, int> a, const pair<int, int> b) {
		return a.fi + a.se < b.fi + b.se;
	});
	dp[0] = 0;
	rep(i, 1, n) dp[0] += a[i].fi;
	rep(i, 1, n) {
		per(j, 1, i) {
			if(dp[j-1] + a[i].se >= h) dp[j] = max(dp[j], dp[j-1] - a[i].fi);
		}
	}
	per(i, 0, n) if(dp[i] >= 0) return cout << i << "\n", 0;
	return 0;
}