//Author: Chenkaifeng

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
#define fi first
#define se second
#define rg register
#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"

inline void qread() {}
template<typename T1, typename ...T2>
inline void qread(T1 &x, T2&... ls) {
	rg char ch = ' '; rg int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
	qread(ls...);
}

template<typename T>
inline void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) return putchar('0' + x), void();
	qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
inline void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
}

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

//x+y2=x^2+2xy

typedef pair<ll, ll> pll;

const int N = 1e6 + 5;

int n;
ll sum[N<<2], lazy[N<<2], sqr[N<<2];

void Lazy(int cur, ll x, int l, int r) {
	lazy[cur] += x;
	sqr[cur] += x * x + 2 * x * sum[cur];
	sum[cur] += (r - l + 1) * x;
}

void PushDown(int cur, int l, int r) {
	if(lazy[cur] == 0) return;
	rg int mid = l + r >> 1;
	Lazy(cur << 1, lazy[cur], l, mid);
	Lazy(cur << 1 | 1, lazy[cur], mid + 1, r);
	lazy[cur] = 0;
}

void PushUp(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
	sqr[cur] = sqr[cur << 1] + sqr[cur << 1 | 1];
}

void Add(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, 1, l, r);
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, mid + 1, r);
	PushUp(cur);
}

pll Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mp(sum[cur], sqr[cur]);
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg pll res = mp(0, 0), x;
	if(ql <= mid) x = Sum(cur << 1, ql, qr, l, mid), res = x;
	if(mid < qr) x = Sum(cur << 1 | 1, ql, qr, mid + 1, r), res.fi += x.fi, res.se += x.se;
	return res;
}

int main() {
	qread(n);
	rep(i, 1, n) {
		
	}
	return 0;
}
