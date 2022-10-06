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

const int N = 1e5 + 5;

struct Opt {
	char tp[6];
	int x;
};

int sum[N << 4];
int a[N], b[N << 1], p;
Opt op[N];
int n, m, q;

void Add(int cur, int p, int l, int r) {
	sum[cur]++;
	if(l == r) return;
	rg int mid = l + r >> 1;
	if(p <= mid) Add(cur << 1, p, l, mid);
	else Add(cur << 1 | 1, p, mid + 1, r);
}

int Kth(int cur, int k, int l, int r) {
	if(l == r) return l;
	rg int mid = l + r >> 1;
	if(k <= sum[cur << 1]) return Kth(cur << 1, k, l, mid);
	else return Kth(cur << 1 | 1, k - sum[cur << 1], mid + 1, r);
}

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i]), b[++p] = a[i];
	qread(q);
	rep(i, 1, q) {
		scanf("%s", op[i].tp);
		if(op[i].tp[0] == 'a') scanf("%d", &op[i].x), b[++p] = op[i].x;
	}
	int sz = n;
	sort(b + 1, b + 1 + p);
	int m = unique(b + 1, b + 1 + p) - (b + 1);
	rep(i, 1, n) Add(1, a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b, 1, m);
	rep(i, 1, q) {
		if(op[i].tp[0] == 'a') Add(1, op[i].x = lower_bound(b + 1, b + 1 + m, op[i].x) - b, 1, m), sz++;
		else qwrite(b[Kth(1, (sz + 1) / 2, 1, m)], '\n');
	}
	return 0;
}
