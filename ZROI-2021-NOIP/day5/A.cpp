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

struct HashFunc {
	template<typename T, typename U>
	size_t operator()(const std::pair<T, U>& p) const {
		return std::hash<T>()(p.first) ^ std::hash<U>()(p.second);
	}
};

int n, t;

namespace sub1 {
	const int N = 5e5 + 5;
	
	int uni[N];
	bool bad[N];
	unordered_map<pair<ll, ll>, ll, HashFunc> id;
	int idcnt, tcnt, bcnt;
	int find(int x) {
		if(x == -1) return -1;
		return x == uni[x] ? x : uni[x] = find(uni[x]);
	}
	int check(ll x, ll y) {
		int cid = id[mp(x, y)], ids[5] = {-1, -1, -1, -1};
		if(id.count(mp(x+1, y))) ids[0] = find(id[mp(x+1, y)]);
		if(id.count(mp(x-1, y))) ids[1] = find(id[mp(x-1, y)]);
		if(id.count(mp(x, y+1))) ids[2] = find(id[mp(x, y+1)]);
		if(id.count(mp(x, y-1))) ids[3] = find(id[mp(x, y-1)]);
		
		tcnt++;
		
		if(ids[0] == -1 && ids[1] == -1 && ids[2] == -1 && ids[3] == -1) {
			return tcnt == 1;
		}
		
		sort(ids, ids + 4);
		rep(i, 0, 3) {
			if(ids[i] != -1 && ids[i] != ids[i+1]) {
				tcnt--;
				uni[ids[i]] = find(cid);
			}
		}
		
		return tcnt <= 1; 
	}
	void solve() {
		srand(time(0));
		rep(i, 1, n) uni[i] = i;
		ll lastans = 0;
		rep(i, 1, n) {
			ll x, y;
			cin >> x >> y;
			x ^= (lastans * t);
			y ^= (lastans * t);
			id[mp(x, y)] = ++idcnt;
			int res = check(x, y);
			cout << res << " \n"[i == n];
			lastans = (2 * lastans + res) % n;
		}
	}
}

namespace sub2 {
	const int N = 5e5 + 5;
	unordered_map<pair<ll, ll>, ll, HashFunc> id;
	pair<ll, ll> pos[N];
	int idcnt, tcnt, bcnt;
	bool ans[N];
	int uni[N];
	int find(int x) {
		if(x == -1) return -1;
		return x == uni[x] ? x : uni[x] = find(uni[x]);
	}
	int check(ll x, ll y) {
		int cid = id[mp(x, y)], ids[5] = {-1, -1, -1, -1};
		if(id.count(mp(x+1, y))) ids[0] = find(id[mp(x+1, y)]);
		if(id.count(mp(x-1, y))) ids[1] = find(id[mp(x-1, y)]);
		if(id.count(mp(x, y+1))) ids[2] = find(id[mp(x, y+1)]);
		if(id.count(mp(x, y-1))) ids[3] = find(id[mp(x, y-1)]);
		
		tcnt++;
		
		if(ids[0] == -1 && ids[1] == -1 && ids[2] == -1 && ids[3] == -1) {
			return tcnt == 1;
		}
		
		sort(ids, ids + 4);
		rep(i, 0, 3) {
			if(ids[i] != -1 && ids[i] != ids[i+1]) {
				tcnt--;
				uni[ids[i]] = find(cid);
			}
		}
		
		return tcnt <= 1; 
	}
	void solve() {
		rep(i, 1, n) uni[i] = i;
		rep(i, 1, n) cin >> pos[i].fi >> pos[i].se, id[pos[i]] = ++idcnt, ans[i] = check(pos[i].fi, pos[i].se);
		rep(i, 1, n) ;
		reverse(pos + 1, pos + 1 + n);
		rep(i, 1, n) ans[n-i+1] &= check(pos[i].fi, pos[i].se);
		rep(i, 1, n) cout << ans[i] << " \n"[i == n];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> t;
	if(t == 0) sub2::solve();
	else sub1::solve();
	
	fastio::flush();
	return 0;
}
