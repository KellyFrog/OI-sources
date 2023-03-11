//Author: Chenkaifeng

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef long double ldb;
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
	int tp, l, r, x;
};

Opt op[N];
int a[N<<5], b[N<<5], p;
int sum[N<<5], tag[N<<5];
int n, m;

void Lazy(int cur) {
	sum[cur] = 0, tag[cur] = 1;
}

void PushDown(int cur) {
	if(tag[cur]) {
		Lazy(cur << 1), Lazy(cur << 1 | 1);
		tag[cur] = 0;
	}
}

void PushUp(int cur) {
	sum[cur] = sum[cur<<1] + sum[cur<<1|1];
}
	
void Modify(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur), void();
	PushDown(cur);
	int mid = l + r >> 1;
	if(ql <= mid) Modify(cur<<1, ql, qr, l, mid);
	if(mid < qr) Modify(cur<<1|1, ql, qr, mid+1, r);
	PushUp(cur);
}

void Add(int cur, int p, int l, int r) {
	sum[cur]++;
	if(l == r) return;
	PushDown(cur);
	int mid = l + r >> 1;
	if(p <= mid) Add(cur<<1, p, l, mid);
	else Add(cur<<1|1, p, mid+1, r);
}

int Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	if(tag[cur]) return PushDown(cur), 0;
	int mid = l + r >> 1;
	int res = 0;
	if(ql <= mid) res += Sum(cur<<1, ql, qr, l, mid);
	if(mid < qr) res += Sum(cur<<1|1, ql, qr, mid+1, r);
	return res;
}

int main() {
	qread(n);
	rep(i, 1, n) {
		qread(op[i].tp);
		if(op[i].tp == 1) qread(op[i].x), a[++p] = op[i].x;
		if(op[i].tp == 2) qread(op[i].l, op[i].r), a[++p] = op[i].l, a[++p] = op[i].r;
		if(op[i].tp == 3) qread(op[i].l, op[i].r, op[i].x), a[++p] = op[i].l, a[++p] = op[i].r;
	}
	sort(a+1, a+1+p);
	int m = unique(a+1, a+1+p) - (a+1);
	#define find(x) lower_bound(a+1, a+1+m, x) - a
	rep(i, 1, n) {
		if(op[i].tp == 1) op[i].x = find(op[i].x);
		else op[i].l = find(op[i].l), op[i].r = find(op[i].r);
	}
	#undef find
	rep(i, 1, n) {
//		cerr << op[i].tp << " " << op[i].l << " " << op[i].r << " " << op[i].x << "\n";
		if(op[i].tp == 1) Add(1, op[i].x, 1, m);
		else if(op[i].tp == 2) Modify(1, op[i].l, op[i].r, 1, m);
		else {
			rg int left = op[i].l, right = op[i].r, res = m+1;
			while(left <= right) {
				rg int mid = left + right >> 1;
//				fprintf(stderr, "[%d,%d]=%d\n", mid, op[i].r, Sum(1, mid, op[i].r, 1, m));
				if(Sum(1, mid, op[i].r, 1, m) >= op[i].x) res = mid, left = mid + 1;
				else right = mid - 1;
			}
			qwrite((res == m+1 ? -1 : a[res]), '\n');
		}
	}
	return 0;
}
