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

const int N = 2e5 + 5;

struct Op {
	int tp, x, k;
};

Op opt[N];

int n, m = 1e9;
int sum[N << 5], lson[N << 5], rson[N << 5], cnt;
int rt = 0;

void PushUp(int cur) {
	sum[cur] = sum[lson[cur]] + sum[rson[cur]];
}

void Modify(int& cur, int p, int tp, int l, int r) {
	if(cur == 0) cur = ++cnt;
	if(l == r) {
		if(tp == 1) sum[cur]++;
		else if(tp == 2) sum[cur] = 0;
		else sum[cur] = sum[cur] > 0 ? sum[cur] - 1 : sum[cur];
		return;
	}
	rg int mid = l + r >> 1;
	if(p <= mid) Modify(lson[cur], p, tp, l, mid);
	else Modify(rson[cur], p, tp, mid + 1, r);
	PushUp(cur);
}

int Sum(int cur, int ql, int qr, int l, int r) {
	if(cur == 0) return 0;
	if(ql <= l && r <= qr) return sum[cur];
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res += Sum(lson[cur], ql, qr, l, mid);
	if(mid < qr) res += Sum(rson[cur], ql, qr, mid + 1, r);
	return res;
}

int main() {
	qread(n);
	rep(i, 1, n) {
		qread(opt[i].tp, opt[i].x);
		if(opt[i].tp == 4) qread(opt[i].k);
	}
	rep(i, 1, n) {
		if(opt[i].tp == 4) {
			rg int left = 1, right = m; //[x - dis + 1, x + dis - 1]
			rg int res = -1, ressm = -1;
			while(left <= right) {
				rg int mid = left + right >> 1;
				rg int sm = Sum(rt, max(rt, opt[i].x - mid + 1), min(opt[i].x + mid - 1, m), 1, m);
//				fprintf(stderr, "[%d,%d]=%d, mid=%d\n", max(rt, opt[i].x - mid + 1), min(opt[i].x + mid - 1, m), sm, mid);
				if(sm >= opt[i].k) res = mid, ressm = sm, right = mid - 1;
				else left = mid + 1;
			}
			qwrite(res == -1 ? -1 : opt[i].x - res + 1 < 1 ? opt[i].x + res - 1 : opt[i].x + res - 1 > m ? opt[i].x - res + 1 : opt[i].k > (opt[i].x - res + 1 <= opt[i].x + res - 2 ? Sum(rt, opt[i].x - res + 1, opt[i].x + res - 2, 1, m) : 0) ? opt[i].x + res - 1 : opt[i].x - res + 1, '\n');
		} else {
//			fprintf(stderr, "modified: %d %d\n", opt[i].x, opt[i].tp);
			Modify(rt, opt[i].x, opt[i].tp, 1, m);
		}
	}
	return 0;
}
