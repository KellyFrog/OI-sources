// Problem: P4168 [Violet]蒲公英
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4168
// Memory Limit: 500 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

#if __cplusplus < 201703L
#define rg register
#else
#define rg
#endif

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
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e5 + 5;
const int SZ = 400 + 5;

pair<int, int> val[SZ][SZ];
int cnt[SZ][N];
int n, q;
int a[N], b[N];
int siz, tot;
int blockid[N], blockleft[N], blockright[N];


int main() {
	fastio::qread(n);
	siz = sqrt(n), tot = (n+siz-1)/siz;
	rep(i, 1, n) blockid[i] = (i-1)/siz + 1;
	rep(i, 1, tot) blockleft[i] = (i-1)*siz + 1, blockright[i] = min(n, i*siz);
	rep(i, 1, n) fastio::qread(a[i]), b[i] = a[i];
	sort(b + 1, b + 1 + n);
	int p = unique(b + 1, b + 1 + n) - (b + 1);
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + 1 + p, a[i]) - b;
	rep(i, 1, tot) {
		memcpy(cnt[i], cnt[i-1], sizeof cnt[i]);
		rep(j, blockleft[i], blockright[i]) cnt[i][a[j]]++;
	}
	rep(i, 1, tot) {
		int mx = -1, mxval = 0;
		rep(j, i, tot) {
			rep(k, blockleft[j], blockright[j]) {
				if(cnt[j][a[k]] - cnt[i-1][a[k]] == mx) {
					if(a[k] < mxval) mxval = a[k];
				} else if(cnt[j][a[k]] - cnt[i-1][a[k]] > mx) {
					mx = cnt[j][a[k]] - cnt[i-1][a[k]];
					mxval = a[k];
				}
			}
			val[i][j] = mp(mx, mxval);
		}
	}
	int lastans = 0;
	rep(test, 1, n) {
		int L, R;
		fastio::qread(L, R);
		int id1 = blockid[L], id2 = blockid[R];
		if(id1 == id2) {
			int mx = -1, mxval = 0;
			static int cnt0[N];
			rep(i, L, R) {
				cnt0[a[i]]++;
				if(cnt0[a[i]] == mx) {
					if(a[i] < mxval) mxval = a[i];
				} else if(cnt0[a[i]] > mx) {
					mx = cnt0[a[i]];
					mxval = a[i];
				}
			}
			rep(i, L, R) cnt0[a[i]] = 0;
			fastio::qwrite(lastans = b[mxval], '\n');
		} else {
			int mx = val[id1+1][id2-1].fi, mxval = val[id1+1][id2-1].se;
			static int cnt0[N];
			rep(i, L, blockright[id1]) {
				cnt0[a[i]]++;
				if(cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]] == mx) {
					if(a[i] < mxval) mxval = a[i];
				} else if(cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]] > mx) {
					mx = cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]];
					mxval = a[i];
				}
			}
			rep(i, blockleft[id2], R) {
				cnt0[a[i]]++;
				if(cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]] == mx) {
					if(a[i] < mxval) mxval = a[i];
				} else if(cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]] > mx) {
					mx = cnt0[a[i]] + cnt[id2-1][a[i]] - cnt[id1][a[i]];
					mxval = a[i];
				}
			}
			rep(i, L, blockright[id1]) cnt0[a[i]] = 0;
			rep(i, blockleft[id2], R) cnt0[a[i]] = 0;
			fastio::qwrite(lastans = b[mxval], '\n');
		}
	}
	fastio::flush();
	return 0;
}
