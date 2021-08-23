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

const int N = 1e3 + 5;

int n, m, k;
bool block[N][N];
int limup[N][N], limdown[N][N];
ll res1[N][N], res2[N][N];
vector<int> bad[N];

ll sum[N << 2], lazy[N << 2];

inline void setlazy(int cur, int l, int r, ll x) {
	sum[cur] += 1ll * (r - l + 1 ) * x;
	lazy[cur] += x;
}

inline void pushdown(int cur, int l, int r) {
	if(lazy[cur]) {
		int mid =l  + r >> 1;
		setlazy(cur << 1, l, mid, lazy[cur]);
		setlazy(cur << 1 | 1, mid + 1, r, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void pushup(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}

inline void add(int cur, int ql, int qr, ll x, int l, int r) {
	if(ql > qr) return;
	if(ql <= l && r <= qr) return setlazy(cur, l, r, x);
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	if(ql <= mid) add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	pushup(cur);
}

inline void modify(int cur, int p, ll x, int l, int r) {
	if(l == r) {
		lazy[cur] = 0, sum[cur] = x;
		return;
	}
	pushdown(cur, l, r);
	int mid = l + r >> 1;
	if(p <= mid) modify(cur << 1, p, x, l, mid);
	else modify(cur << 1 | 1, p, x, mid + 1, r);
	pushup(cur);
}

inline ll query(int cur, int ql, int qr, int l, int r) {
	if(ql > qr) return 0;
	if(ql <= l && r <= qr) return sum[cur];
	pushdown(cur, l, r);
	ll res = 0;
	int mid = l + r >> 1;
	if(ql <= mid ) res += query(cur << 1, ql, qr, l, mid);
	if(mid < qr) res += query(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m >> k;
	rep(i, 1, k) {
		int x, y;
		cin >> x >> y;
		block[x][y] = 1;
		bad[y].pb(x);
	}
	rep(i, 1, n) limup[1][i] = block[1][i] ? -1 : 0;
	rep(i, 2, n) rep(j, 1, m) limup[i][j] = block[i][j] ? -1 : limup[i-1][j] + 1;
	
	rep(i, 1, m) limdown[n][i] = block[n][i] ? -1 : 0;
	per(i, 1, n-1) rep(j, 1, m) limdown[i][j] = block[i][j] ? -1 : limdown[i+1][j] + 1;
	/*
	rep(i, 1, n) rep(j, 1, m) cerr << block[i][j] << " \n"[j == m];
	cerr << "limdown\n";
	rep(i, 1, n) rep(j, 1, m) cerr << limdown[i][j] << " \n"[j == m];
	*/
	rep(i, 2, n-1) {
		memset(sum, 0, sizeof sum);
		memset(lazy, 0, sizeof lazy);
		rep(j, 2, m-1) {
			add(1, i-limup[i][j-1], i-1, 1, 1, n);
			for(int x : bad[j]) {
				modify(1, x, 0, 1, n);
			}
			if(block[i][j]) {
				memset(sum, 0, sizeof sum);
				memset(lazy, 0, sizeof lazy);
			}
			res1[i][j] = query(1, i-limup[i][j], i-1, 1, n);
		}
	}
	
	rep(i, 2, n-1) {
		memset(sum, 0, sizeof sum);
		memset(lazy, 0, sizeof lazy);
		per(j, 2, m-1) {
			add(1, i+1, i+limdown[i][j+1], 1, 1, n);
			for(int x : bad[j]) {
				modify(1, x, 0, 1, n);
			}
			if(block[i][j]) {
				memset(sum, 0, sizeof sum);
				memset(lazy, 0, sizeof lazy);
			}
			// rep(i0, 1, n) cerr << curans[i0] << " \n"[i0 == n];
			res2[i][j] = query(1, i+1, i+limdown[i][j], 1, n);
			//rep(i0, i+1, i+limdown[i][j]) res2[i][j] += curans[i0];
		}
	}
	/*
	cerr << "res1\n";
	rep(i, 1, n) rep(j, 1, m) cerr << res1[i][j] << " \n"[j == m];
	cerr << "res2\n";
	rep(i, 1, n) rep(j, 1, m) cerr << res2[i][j] << " \n"[j == m];
	*/
	
	ll ans = 0;
	rep(i, 1, n) rep(j, 1, m) ans += 1ll * res1[i][j] * res2[i][j];
	cout << ans << "\n";
	
	fastio::flush();
	return 0;
}
