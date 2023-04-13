
// Problem: U144364 deadline是第一生产力
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U144364?contestId=39360
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
#define OK cerr << "OK!\n"


namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
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
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
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
		if(oS == oT) flush();
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
}; //namespace fastio

namespace debug {
	void format(const char* s) {
		cerr << s << endl;
	}
	template<typename T1, typename ...T2>
	void format(const char* s, const T1 x, T2 ...ls) {
		
	}
};

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int T = 1005;
const int N = 10005;
const int I = N << 5;

ll cost[I], weight[I], p;
ll dp[T];
int t, n;

int main() {
	int ts, ms, te, me;
	fastio::qread(ts, ms, te, me, n);
	t = (te - ts) * 60 + (me - ms);
	rep(i, 1, n) {
		int ti, ci, pi;
		fastio::qread(ti, ci, pi);
		if(pi == 0) pi = t;
		for(rg int j = 0; pi - (1ll << j) > 0; j++) {
			pi -= 1ll << j;
			p++;
			cost[p] = (1ll << j) * ti;
			weight[p] = (1ll << j) * ci;
		}
		p++;
		cost[p] = 1ll * pi * ti;
		weight[p] = 1ll * pi * ci;
	}
	rep(i, 1, p) {
		//cerr << cost[i] << " " << weight[i] << endl;
		per(j, 1, t) {
			if(j >= cost[i]) dp[j] = max(dp[j], dp[j - cost[i]] + weight[i]);
		}
	}
	ll ans = 0;
	rep(i, 1, t) ans = max(ans, dp[i]);
	fastio::qwrite(ans, '\n');
	fastio::flush();
	return 0;
}