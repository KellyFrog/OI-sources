// Problem: E. Trees of Tranquillity
// Contest: Codeforces - Codeforces Round #722 (Div. 2)
// URL: https://codeforces.com/contest/1529/problem/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms

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

const int N = 3e5 + 5;

int dfn[N], siz[N], dfncnt;
int n, curans, ans;
vector<int> t1[N], t2[N];

struct BIT {
ll tree[N];
inline int lowbit(int x) {
	return x & (-x);
}

inline void add(int x, ll val) {
	for(int x0 = x; x0 <= n; x0 += lowbit(x0)) {
		tree[x0] += val;
	}
}

inline void add(int l, int r, ll val) {
	add(l, val);
	add(r+1, -val);
}

inline ll query(int x) {
	if(x > n) x = n;
	ll res = 0;
	for(int x0 = x; x0; x0 -= lowbit(x0)) res += tree[x0];
	return res;
}

inline ll query(int l, int r) {
	return query(r) - query(l-1);
}
};

BIT b1, b2;

inline void dfst2(int u, int fa) {
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	for(int v : t2[u]) {
		dfst2(v, u);
		siz[u] += siz[v];
	}
}

inline void dfst1(int u, int fa) {
	int last = -1;
	if(!b1.query(dfn[u], dfn[u] + siz[u] - 1)) {
		last = b2.query(dfn[u]);
		if(last) {
			b1.add(dfn[last], -1);
			b1.add(dfn[u], 1);
			b2.add(dfn[last], dfn[last] + siz[last] - 1, -last);
			b2.add(dfn[u], dfn[u] + siz[u] - 1, u);
		} else {
			b1.add(dfn[u], 1);
			b2.add(dfn[u], dfn[u] + siz[u] - 1, u);
			curans++;
		}
	}
	chkmax(ans, curans);
	
	for(int v : t1[u]) dfst1(v, u);
	
	if(last != -1) {
		if(last) {
			b1.add(dfn[last], 1);
			b1.add(dfn[u], -1);
			b2.add(dfn[last], dfn[last] + siz[last] - 1, last);
			b2.add(dfn[u], dfn[u] + siz[u] - 1, -u);
		} else {
			b1.add(dfn[u], -1);
			b2.add(dfn[u], dfn[u] + siz[u] - 1, -u);
			curans--;
		}
	}
}

inline void solve() {
	cin >> n;
	rep(i, 1, n) t1[i].clear(), t2[i].clear(), b1.tree[i] = b2.tree[i] = 0;
	curans = ans = dfncnt = 0;
	rep(i, 2 ,n) {
		int f;
		cin >> f;
		t1[f].pb(i);
	}
	rep(i, 2, n) {
		int f;
		cin >> f; 
		t2[f].pb(i);
	}
	dfst2(1, 0);
	dfst1(1, 0);
	cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	int t;
	cin >> t;
	while(t--) solve();
	
	fastio::flush();
	return 0;
}
