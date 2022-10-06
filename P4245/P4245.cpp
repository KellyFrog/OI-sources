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
const ll mod1 = 998244535;
const ll mod2 = 167772161;
const ll mod3 = 754974721;
const ll M = 1ll * mod1 * mod2;
using Poly = vector<ll>;

int lim, h;
int n, m;
ll p;
Poly a, b;

namespace NTT1 {
	const int mod = 998244353;
	const int G = 3;
	Poly a, b;
	ll g[N], invg[N];
	int n, m, lim, h;

	void Init(int n0, int m0) {
		n = n0, m = m0;
		while((lim = 1 << h) <= (n + m)) h++;
		a.resize(lim);
		b.resize(lim);
	}

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

	void Solve() {
		g[23] = qpow(3, 119, mod);
		per(i, 0, 22) g[i] = (g[i+1] * g[i+1]) % mod;
		rep(i, 0, 23) invg[i] = qpow(g[i], mod-2, mod);
		NTT(a, h, 1);
		NTT(b, h, 1);
		rep(i, 0, lim-1) a[i] = (a[i] * b[i]) % mod;
		NTT(a, h, -1);
		int inv = qpow(lim, mod-2, mod);
		rep(i, 0, n+m) a[i] = ((a[i]+mod)%mod)*inv%mod;
	}
};

namespace NTT2 {
	const int mod = 167772161;
	const int P = 25;
	const int G = 5;
	Poly a, b;
	ll g[N], invg[N];
	int n, m, lim, h;

	void Init(int n0, int m0) {
		n = n0, m = m0;
		while((lim = 1 << h) <= (n + m)) h++;
		a.resize(lim);
		b.resize(lim);
	}

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

	void Solve() {
		g[25] = qpow(3, 5, mod);
		per(i, 0, 24) g[i] = (g[i+1] * g[i+1]) % mod;
		rep(i, 0, 25) invg[i] = qpow(g[i], mod-2, mod);
		NTT(a, h, 1);
		NTT(b, h, 1);
		rep(i, 0, lim-1) a[i] = (a[i] * b[i]) % mod;
		NTT(a, h, -1);
		int inv = qpow(lim, mod-2, mod);
		rep(i, 0, n+m) a[i] = ((a[i]+mod)%mod)*inv%mod;
	}
};

namespace NTT3 {
	const int mod = 754974721;
	const int P = 24;
	const int G = 45;
	Poly a, b;
	ll g[N], invg[N];
	int n, m, lim, h;

	void Init(int n0, int m0) {
		n = n0, m = m0;
		while((lim = 1 << h) <= (n + m)) h++;
		a.resize(lim);
		b.resize(lim);
	}

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

	void Solve() {
		g[24] = qpow(11, 45, mod);
		per(i, 0, 23) g[i] = (g[i+1] * g[i+1]) % mod;
		rep(i, 0, 24) invg[i] = qpow(g[i], mod-2, mod);
		NTT(a, h, 1);
		NTT(b, h, 1);
		rep(i, 0, lim-1) a[i] = (a[i] * b[i]) % mod;
		NTT(a, h, -1);
		int inv = qpow(lim, mod-2, mod);
		rep(i, 0, n+m) a[i] = ((a[i]+mod)%mod)*inv%mod;
	}
};

void exgcd(ll& x, ll& y, ll a, ll b) {
	if(b == 0) return y = 0, x = 1, void();
	ll x1, y1;
	exgcd(x1, y1, b, a % b);
	x = y1, y1 = x1 - a / b * y1;
}

ll CRT(ll x1, ll x2, ll x3) {
	ll a1, a2;
	exgcd(a1, a2, mod1, mod2);
	a1 *= (x2 - x1);
	a2 *= (x2 - x1);
}

ll qmul(ll x, ll p, ll mod) {
	ll res = 0, base = x;
	while(p) {
		if(p & 1) res = (res + base) % mod;
		base = base + base % mod;
		p >>= 1;
	}
	return res;
}

ll Solve(int x1, int x2, int x3) {
	ll k1 = qpow(mod2 * mod3 % mod1, mod1 - 2, mod1);
	ll k2 = qpow(mod1 * mod3 % mod2, mod2 - 2, mod2);
	ll k3 = qpow(mod1 * mod2 % mod3, mod3 - 2, mod2);
	ll a1 = qmul(x1, qmul(k1, mod2 * mod3 % p, p), p);
	ll a2 = qmul(x2, qmul(k2, mod1 * mod3 % p, p), p);
	ll a3 = qmul(x3, qmul(k3, mod1 * mod2 % p, p), p);
	return (a1 + a2 + a3) % p;
}

int main() {
	scanf("%d%d%d", &n, &m, &p);
	lim = 1, h = 0;
	while((lim = 1 << h) <= n + m) h++;
	NTT1::Init(n, m);
	NTT2::Init(n, m);
	NTT3::Init(n, m);
	a.resize(n+m);
	b.resize(n+m);

	rep(i, 0, n) {
		scanf("%d", &a[i]);
		NTT1::a[i] = a[i], NTT2::a[i] = a[i], NTT3::a[i] = a[i];
	}
	rep(i, 0, m) scanf("%d", &b[i]), NTT1::b[i] = b[i], NTT2::b[i] = b[i], NTT3::b[i] = b[i];

	NTT1::Solve();
	NTT2::Solve();
	NTT3::Solve();
	
	rep(i, 0, n+m) cerr << NTT1::a[i] << " " << NTT2::a[i] << " " << NTT3::a[i] << "\n";

	rep(i, 0, n+m) {
		printf("%lld ", Solve(NTT1::a[i], NTT2::a[i], NTT3::a[i]));
	}
	puts("");

	return 0;
}