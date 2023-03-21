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

struct Complex {
	double a, b;
	Complex() {a=0,b=0;}
	Complex(double a0) : a(a0), b(0) {}
	Complex(double a0, double b0) : a(a0), b(b0) {}
	inline Complex operator + (const Complex& x) const {
		return Complex(a + x.a, b + x.b);
	}
	inline Complex operator - (const Complex& x) const {
		return Complex(a - x.a, b - x.b);
	}
	inline Complex operator * (const Complex& x) const {
		return Complex(a * x.a - b * x.b, a * x.b + b * x.a);
	}
};

using Poly = vector<Complex>;
const double pi = acos(-1);
const int N = 2e6 + 5;

char S1[N], S2[N];

Poly a, b, c;
int n, m;
int ans[N];

void FFT(Poly& f, int h, int type) {
	
	if(h == 0) {
		return;
	}
	Poly f0, f1;
	f0.resize(1 << h-1);
	f1.resize(1 << h-1);
	rg int n = 1 << h;
	for(rg int i = 0; i < n; i += 2) f0[i / 2] = f[i];
	FFT(f0, h-1, type);
	for(rg int i = 1; i < n; i += 2) f1[i / 2] = f[i];
	FFT(f1, h-1, type);
	Complex w(cos(2 * pi / n), type * sin(2 * pi / n));
	Complex x = 1;
	rep(i, 0, n/2-1) {
		f[i] = f0[i] + x * f1[i];
		f[i + n/2] = f0[i] - x * f1[i];
		x = x * w;
	}
}

int main() {
	scanf("%s%s", S1, S2);
	n = strlen(S1), m = strlen(S2);
	n--,m--;
	reverse(S1, S1+1+n);
	reverse(S2, S2+1+m);
	int lim = 1;
	while((1 << lim) <= (n + m)) lim++;
	a.resize(1 << lim);
	b.resize(1 << lim);
	rep(i, 0, (1<<lim)-1) a[i] = Complex(0, 0), b[i] = Complex(0, 0);
	rep(i, 0, n) a[i].a = S1[i] - '0';
	rep(i, 0, m) b[i].a = S2[i] - '0';
	FFT(a, lim, 1);
	FFT(b, lim, 1);
	rep(i, 0, (1 << lim) - 1) a[i] = a[i] * b[i];
	FFT(a, lim, -1);
	rep(i, 0, n+m) {
		ans[i] = (ll)(a[i].a / (1<<lim) + 0.5);
	}
	rep(i, 0, n+m) {
		ans[i+1] += ans[i] / 10;
		ans[i] %= 10;
	}
	if(ans[n+m+1]) fastio::qwrite(ans[n+m+1]);
	per(i, 0, n+m) fastio::qwrite(ans[i]);
	fastio::flush();
	return 0;
}

