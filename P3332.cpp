
// Problem: P3332 [ZJOI2013]K大数查询
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3332
// Memory Limit: 500 MB
// Time Limit: 1500 ms
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


void debug(const char* s) {
	cerr << s;
}
template<typename T1, typename ...T2>
void debug(const char * s, const T1 x, T2 ...ls) {
	int p = 0;
	while(*(s + p) != '\0') {
		if(*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
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

const int N = 5e4 + 5;

#define int long long

struct Oper {
	ll op, l, r, c, p, ans;
};

ll a[N], sz, pt;
int n, m;
Oper op[N], cpy[N], tmp[N];
ll ans[N];
ll sum[N << 2], lazy[N << 2];

void Lazy(int cur, int x, int l, int r) {
	sum[cur] += (r - l + 1) * x;
	lazy[cur] += x;
}

void PushDown(int cur, int l, int r) {
	if(lazy[cur]) {
		rg int mid = l + r >> 1;
		Lazy(cur << 1, lazy[cur], l, mid);
		Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
		lazy[cur] = 0;
	}
}

void PushUp(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}

void Add(int cur, int x, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x, l, r), void();
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, x, ql, qr, l, mid);
	if(mid < qr) Add(cur << 1 | 1, x, ql, qr, mid + 1, r);
	PushUp(cur);
}

int Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res += Sum(cur << 1, ql, qr, l, mid);
	if(mid < qr) res += Sum(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

void Solve(ll ql, ll qr, ll l, ll r) {
	if(ql > qr || l > r) return;
	if(op[ql].p > op[qr].p) reverse(op + ql, op + qr + 1);
	//debug("Solving=[{}, {}]  [{}, {}] mid={}\n", ql, qr, l, r, l + r >> 1);
	//rep(i, ql, qr) debug("opt[{}] op={}, [{}, {}], {}\n", op[i].p, op[i].op, op[i].l, op[i].r, op[i].c);
	if(l == r) {
		rep(i, ql, qr) if(op[i].op == 2) ans[op[i].p] = l;
		return;
	}
	rg ll mid = l + r >> 1; //域值中间值
	ll pl = ql, pr = qr;
	rep(i, ql, qr) {
		if(op[i].op == 1) {
			if(op[i].c > mid) {
				Add(1, 1, op[i].l, op[i].r, 1, n);
				//debug("added [{}, {}]\n", op[i].l, op[i].r);
				tmp[pr--] = op[i];
			} else {
				tmp[pl++] = op[i];
			}
		} else {
			ll res = Sum(1, op[i].l, op[i].r, 1, n);
			//debug("queried [{}, {}]={} expect={}\n", op[i].l, op[i].r, res, op[i].c);
			if(res >= op[i].c) {
				tmp[pr--] = op[i];
			} else {
				op[i].c -= res;
				tmp[pl++] = op[i];
			}
		}
	}
	rep(i, ql, qr) if(op[i].op == 1 && op[i].c > mid) Add(1, -1, op[i].l, op[i].r, 1, n);
	assert(pl == pr + 1);
	rep(i, ql, qr) op[i] = tmp[i];
	Solve(ql, pl - 1, l, mid);
	Solve(pl, qr, mid + 1, r);
}

signed main() {
	fastio::qread(n, m);
	rep(i, 1, m) {
		fastio::qread(op[i].op, op[i].l, op[i].r, op[i].c); op[i].p = i;
		if(op[i].op == 1) a[++sz] = op[i].c;
	}
	sort(a + 1, a + 1 + sz);
	pt = unique(a + 1, a + 1 + sz) - (a + 1);
	rep(i, 1, m) if(op[i].op == 1) op[i].c = lower_bound(a + 1, a + 1 + pt, op[i].c) - a;
	rep(i, 1, m) cpy[i] = op[i];
	Solve(1, m, 1, pt);
	rep(i, 1, m) if(cpy[i].op == 2) fastio::qwrite(a[ans[i]], '\n');
	fastio::flush();
	return 0;
}