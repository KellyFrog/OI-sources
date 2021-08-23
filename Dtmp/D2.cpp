// Problem: Mocha and Diana (Hard Version)
// Contest: Codeforces
// URL: http://m2.codeforces.com/contest/1559/problem/D2
// Memory Limit: 256 MB
// Time Limit: 2000 ms

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

pair<int, int> eg1[N], eg2[N];
int n, m1, m2;
int uni1[N], uni2[N], uni3[N];
int uni[N<<1];
set<int> e1[N], e2[N], e[N<<1];
vector<pair<int, int> > ans;

int find(int x) {
	return x == uni[x] ? x : uni[x] = find(uni[x]);
}

int find1(int x) {
	return x == uni1[x] ? x : uni1[x] = find1(uni1[x]);
}

int find2(int x) {
	return x == uni2[x] ? x : uni2[x] = find2(uni2[x]);
}

int find3(int x) {
	return x == uni3[x] ? x : uni3[x] = find3(uni3[x]);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m1 >> m2;
	rep(i, 1, m1) cin >> eg1[i].fi >> eg1[i].se;
	rep(i, 1, m2) cin >> eg2[i].fi >> eg2[i].se;
	
	
	rep(i, 1, n) uni1[i] = uni2[i] = i;
	rep(i, 1, m1) {
		int x = eg1[i].fi, y = eg1[i].se;
		uni1[find1(x)] = find1(y);
	}
	
	rep(i, 1, m2) {
		int x = eg2[i].fi, y = eg2[i].se;
		uni2[find2(x)] = find2(y);
	}
	
	rep(i, 1, n) e1[find1(i)].insert(i);
	rep(i, 1, n) e2[find2(i)].insert(i);
	
	rep(i, 1, 2*n) uni3[i] = i;
	
	rep(i, 1, n) {
		int u1 = find1(i), u2 = find2(i);
		if(u1 == u2 || find3(u1) == find3(u2+n)) continue;
		
		/*
		e1[u1].erase(i);
		e2[u2].erase(i);
		while(!e1[u1].empty() && !e2[u2].empty()) {
			auto it1 = e1[u1].begin();
			auto it2 = e2[u2].begin();
			if(*it1 == *it2) {
				e1[u1].erase(it1);
				e2[u2].erase(it2);
			} else {
				ans.pb(mp(*it1, *it2));
				uni3[find3(u1)] = find3(u2+n);
				break;
			}
		}
		*/
		int x1 = -1, x2 = -1;
		for(int x : e1[u1]) {
			if(!e2[u2].count(x)) {
				x1 = x;
				break;
			}
		}
		for(int x : e2[u2]) {
			if(!e1[u1].count(x)) {
				x2 = x;
				break;
			}
		}
		if(min(x1, x2) != -1) {
			debug("merge = {} {}\n", u1, u2);
			ans.pb(mp(x1, x2));
			uni3[find3(u1)] = find3(u2+n);
		}
	}
	
	rep(i, 1, n) uni[i] = i;
	
	rep(i, 1, m1) {
		int x = find(eg1[i].fi), y = find(eg1[i].se);
		uni[x] = y;
	}
	
	rep(i, 1, m2) {
		int x = find(eg2[i].fi), y = find(eg2[i].se);
		uni[x] = y;
	}
	
	
	vector<int> last;
	rep(i, 1, n) if(find(i) == i) last.pb(i);
	rep(i, 0, (int)last.size()-2) ans.pb(mp(last[i], last[i+1]));
	
	cout << ans.size() << "\n";
	for(auto [x, y] : ans) cout << x << " " << y << "\n";
	
	fastio::flush();
	return 0;
}
