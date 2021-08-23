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

const int N = 2e5 + 5;

int n, a[N];


namespace sub1 {
	int cnt1[N], cnt2[N];
	
	void solve() {
		ll ans = 0;
		rep(i, 1, n) {
			int R = i;
			int t = 0;
			per(p, 1, i) {
				if(!cnt1[a[p]]) {
					t++;
					cnt1[a[p]] = 1;
					while(cnt1[a[R+1]] && R+1 <= n && t) {
						if(!cnt2[a[R+1]]) {
							cnt2[a[R+1]] = 1;
							t--;
						}
						R++;
					}
					if(t == 0) {
						int p1 = p, p2 = R;
						while(p1 - 1 > 0 && cnt1[a[p1-1]]) p1--;
						while(p2 + 1 <= n && cnt2[a[p2+1]]) p2++;
						ans += 1ll * (p - p1 + 1) * (p2 - R + 1);
					}
				}
			}
			rep(j, 0, n) cnt1[j] = cnt2[j] = 0;
		}
		cout << ans << "\n";
	}
}

namespace sub2 {
	int pos1[N][12], pos2[N][12];
	int cnt1[11], cnt2[11];
	ll ans =0 ;
	void solve() {
		rep(i, 1, n) {
			rep(j, 1, 10) pos1[i][j] = pos1[i-1][j];
			pos1[i][a[i]] = i;
		}
		per(i, 1, n) {
			rep(j, 1, 10) pos2[i][j] = pos2[i+1][j];
			pos2[i][a[i]] = i;
		}
		rep(i, 1, n) sort(pos1[i] + 1, pos1[i] + 10 + 1);
		rep(i, 1, n) sort(pos2[i] + 1, pos2[i] + 10 + 1);
		rep(i, 1, n) {
			int R = 0, t = 0;
			while(pos2[i+1][R] == 0 && R <= 10) R++;
			R--;
			per(p, 1, 10) {
				if(pos1[i][p] == 0) break;
				cnt1[a[pos1[i][p]]]++;
				t++;
				while(R+1 <= 10 && cnt1[a[pos2[i+1][R+1]]] && t) {
					cnt2[a[pos2[i+1][R+1]]] = 1;
					t--;
					R++;
				}
				if(t == 0) {
					ans += 1ll * (pos1[i][p] - pos1[i][p-1]) * ((pos2[i+1][R+1] == 0 ? (n+1) : pos2[i+1][R+1]) - pos2[i+1][R]);
				}
			}
			memset(cnt1, 0, sizeof cnt1);
			memset(cnt2, 0, sizeof cnt2);
		}
		cout << ans << "\n";
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	if(n <= 2000) sub1::solve();
	else sub2::solve();
	
	fastio::flush();
	return 0;
}
