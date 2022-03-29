// Problem: P3810 【模板】三维偏序（陌上花开）
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3810
// Memory Limit: 500 MB
// Time Limit: 1000 ms

/*
 * Author: chenkaifeng @BDFZ
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

#if __cplusplus < 201703L
#define register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
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
		char ch = ' ';
		int ps = 1;
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

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

const int N = 1e5 + 5;
const int M = 2e5 + 5;

struct Node { int a, b, c; } a[N];
int id[N], tmp[N], res[N], ans[N];
int n, k;
int tree[M];
inline int lowbit(int x) { return x & (-x); }
inline void add(int x, int val) { for(int x0 = x; x0 <= k; x0 += lowbit(x0)) tree[x0] += val; }
inline int query(int x) { int res = 0; for(int x0 = x; x0; x0 -= lowbit(x0)) res += tree[x0]; return res; }

void cdq(int l, int r) {
	if(l >= r) return;
	int mid = l + r >> 1; cdq(l, mid), cdq(mid+1, r);
	int p1 = l, p2 = mid + 1, p = l;
	while(p1 <= mid || p2 <= r) {
		if(p1 <= mid && (a[id[p1]].b <= a[id[p2]].b || p2 > r)) {
			add(a[id[p1]].c, 1), tmp[p++] = id[p1++];
		} else {
			res[id[p2]] += query(a[id[p2]].c), tmp[p++] = id[p2++];
		}
	}
	// assert(p1 == mid+1 && p2 == r+1);
	rep(i, l, mid) add(a[id[i]].c, -1);
	rep(i, l, r) id[i] = tmp[i];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> k;
	rep(i, 1, n) cin >> a[i].a >> a[i].b >> a[i].c;
	rep(i, 1, n) id[i] = i;
	sort(id + 1, id + n + 1, [&](const int& i, const int& j) { return a[i].a == a[j].a ? a[i].b == a[j].b ? a[i].c < a[j].c : a[i].b < a[j].b : a[i].a < a[j].a; });
	cdq(1, n);
	sort(id + 1, id + n + 1, [&](const int& i, const int& j) { return a[i].a == a[j].a ? a[i].b == a[j].b ? a[i].c < a[j].c : a[i].b < a[j].b : a[i].a < a[j].a; });
	rep(i, 1, n) {
		int i0 = i;
		while(i0 + 1 <= n && a[id[i0+1]].a == a[id[i]].a && a[id[i0+1]].b == a[id[i]].b && a[id[i0+1]].c == a[id[i]].c) i0++;
		int curres = 0;
		rep(j, i, i0) chkmax(curres, res[id[j]]);
		rep(j, i, i0) res[id[j]] = curres;
	}
	rep(i, 1, n) ans[res[i]]++;
	rep(i, 0, n-1) cout << ans[i] << "\n";
	
	fastio::flush();
	return 0;
}
