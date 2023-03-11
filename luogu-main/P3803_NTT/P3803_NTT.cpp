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
#define rg register
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

const int N = 1e6 + 5;
const int mod = 998244353;
const int G = 3;
using Poly = vector<ll>;

Poly a, b;
int n, m;
ll g[N], invg[N];

void NTT(Poly& f, int h, int type) {
	int n = 1 << h;
	if(h == 0) {
		return;
	}
	Poly f0, f1;
	f0.resize(n>>1);
	f1.resize(n>>1);
	for(int i = 0; i < n; i += 2) f0[i>>1] = f[i];
	for(int i = 1; i < n; i += 2) f1[i>>1] = f[i];
	NTT(f0, h-1, type);
	NTT(f1, h-1, type);
	ll w = type == 1 ? g[h] : invg[h];
	ll x = 1;
	rep(i, 0, n/2-1) {
		f[i] = (f0[i] + x * f1[i]) % mod;
		f[i + n/2] = (f0[i] - x * f1[i]) % mod;
		x = (x * w) % mod;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int lim = 1, h = 0;
	while((lim = 1 << h) <= n + m) h++;
	a.resize(lim);
	b.resize(lim);
	rep(i, 0, n) scanf("%d", &a[i]);
	rep(i, 0, m) scanf("%d", &b[i]);
	g[23] = qpow(3, 119, mod);
	per(i, 0, 22) g[i] = (g[i+1] * g[i+1]) % mod;
	rep(i, 0, 23) invg[i] = qpow(g[i], mod-2, mod);
	NTT(a, h, 1);
	NTT(b, h, 1);
	rep(i, 0, lim-1) a[i] = (a[i] * b[i]) % mod;
	NTT(a, h, -1);
	int inv = qpow(lim, mod-2, mod);
	rep(i, 0, n+m) printf("%lld ", ((a[i]+mod)%mod)*inv%mod); puts("");
	return 0;
}
	