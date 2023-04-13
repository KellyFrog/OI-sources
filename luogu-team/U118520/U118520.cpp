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
const int M = 2e5 + 5;
const int LOG = 50;
#define double long double
#define int long long
ll sum1[N << 2];
int lson[N << 2], rson[N << 2];
double sum2[N << 2];
int a[N], b[N];
int n;

double c[N];
int d[N];
int p;

void add(int cur, int p, int x, int l, int r) {
	// debug("add = {} {} {} {} {}\n", cur, p, x, l, r);
	sum1[cur] += x;
	sum2[cur] += c[p] * x;
	if(l == r) return;
	int mid = (l + r) / 2;
	if(p <= mid) add(cur << 1, p, x, l, mid);
	else add(cur << 1 | 1, p, x, mid + 1, r);
}

int kth(int cur, ll k, int l, int r) {
	if(l == r) return l;
	int mid = (l + r) / 2;
	if(sum1[cur << 1] >= k) return kth(cur << 1, k, l, mid);
	else return kth(cur << 1 | 1, k - sum1[cur << 1], mid + 1, r);
}

pair<double, ll> querysum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mp(sum2[cur], sum1[cur]);
	int mid = (l + r) / 2;
	pair<double, ll> res = mp(0, 0);
	if(ql <= mid) {
		auto curres = querysum(cur << 1, ql, qr, l, mid);
		res.fi += curres.fi;
		res.se += curres.se;
	}
	if(mid < qr) {
		auto curres = querysum(cur << 1 | 1, ql, qr, mid + 1, r);
		res.fi += curres.fi;
		res.se += curres.se;
	}
	return res;
}

double calcans(int val) {
	if(val > p) return 1e18;
	debug("calcans={}\n", c[val]);
	auto ans1 = querysum(1, 1, val, 1, p);
	auto ans2 = querysum(1, val, p, 1, p);
	return c[val] * ans1.se - ans1.fi + ans2.fi - c[val] * ans2.se;
}

signed main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n) fastio::qread(b[i]);
	ll sum = 0;
	ll ans0 = 0;
	rep(i, 1, n) {
		if(a[i] < 0) a[i] *= -1, b[i] *= -1;
		if(a[i] == 0) c[i] = 1e18;
		else c[i] = (double) -b[i] / a[i];
		
	}
	sort(c + 1, c + 1 + n);
	p = unique(c + 1, c + 1 + n) - (c + 1);
	rep(i, 1, n) d[i] = lower_bound(c + 1, c + 1 + p, (double) -b[i] / a[i]) - c;
	double lastans = 0;
	rep(i, 1, n) {
		// debug("add to seg = {} {}\n", (double) d[i], a[i]);
		if(a[i] == 0) {
			ans0 += abs(b[i]);
			lastans += abs(b[i]);
			printf("%.11Lf\n", lastans);
			continue;
		}
		add(1, d[i], a[i], 1, p);
		sum += a[i];
		int ansval = 0;
		if(sum % 2 == 1) {
			ansval = kth(1, sum / 2 + 1, 1, p);
		} else {
			ansval = kth(1, sum / 2, 1, p);
		}
		printf("%.16Lf\n", lastans = min(calcans(ansval), calcans(ansval + 1)) + ans0);
	}
}