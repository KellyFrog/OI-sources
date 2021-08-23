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

unordered_map<int, int> id[N];
bool vis[N], sel[N];
int n, type;
int x[N], y[N];

inline bool find(int i, int j, int type) {
	int id1 = -1, id2 = -1, id3 = -1, id4 = -1;
	if(type == 1) {
		id1 = id[i][j];
		id2 = id[i+1][j];
		id3 = id[i][j+1];
		id4 = id[i+1][j+1];
	} else if(type == 2) {
		id1 = id[i][j];
		id2 = id[i+1][j];
		id3 = id[i][j-1];
		id4 = id[i+1][j-1];
	} else if(type == 3) {
		id1 = id[i][j];
		id2 = id[i-1][j];
		id3 = id[i][j-1];
		id4 = id[i-1][j-1];
	} else if(type == 4) {
		id1 = id[i][j];
		id2 = id[i-1][j];
		id3 = id[i][j+1];
		id4 = id[i-1][j+1];
	} else assert(0);
	return id1 && id2 && id3 && id4 && !(vis[id1] && vis[id2] && vis[id3] && vis[id4]);
}

inline void color(int i, int j, int type) {
	int id1 = -1, id2 = -1, id3 = -1, id4 = -1;
	if(type == 1) {
		id1 = id[i][j];
		id2 = id[i+1][j];
		id3 = id[i][j+1];
		id4 = id[i+1][j+1];
	} else if(type == 2) {
		id1 = id[i][j];
		id2 = id[i+1][j];
		id3 = id[i][j-1];
		id4 = id[i+1][j-1];
	} else if(type == 3) {
		id1 = id[i][j];
		id2 = id[i-1][j];
		id3 = id[i][j-1];
		id4 = id[i-1][j-1];
	} else if(type == 4) {
		id1 = id[i][j];
		id2 = id[i-1][j];
		id3 = id[i][j+1];
		id4 = id[i-1][j+1];
	} else assert(0);
	int k = -1;
	if(!vis[id1]) k = id1, vis[id1] = sel[id1] = 1;
	if(!vis[id2]) k = id2, vis[id2] = sel[id2] = 1;
	if(!vis[id3]) k = id3, vis[id3] = sel[id3] = 1;
	if(!vis[id4]) k = id4, vis[id4] = sel[id4] = 1;
	if(k != -1) sel[k] = 0;
}

void update(int x, int y) {
	bool ok1 = find(x, y, 1);
	bool ok2 = find(x, y, 2);
	bool ok3 = find(x, y, 3);
	bool ok4 = find(x, y, 4);
	if(ok1) {
		color(x, y, 1);
	}
	if(ok2) {
		color(x, y, 2);
	}
	if(ok3) {
		color(x, y, 3);
	}
	if(ok4) {
		color(x, y, 4);
	}
	if(ok1) {
		update(x+1, y);
		update(x, y+1);
		update(x+1, y+1);
	}
	
	if(ok2) {
		update(x+1, y);
		update(x, y-1);
		update(x+1, y-1);
	}
	if(ok3) {
		update(x-1, y);
		update(x, y-1);
		update(x-1, y-1);
	}
	
	if(ok4) {
		update(x-1, y);
		update(x, y+1);
		update(x-1, y+1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> type;
	int mix = 1e9, miy = 1e9;
	rep(i, 1, n) {
		cin >> x[i] >> y[i];
		chkmin(mix, x[i]);
		chkmin(miy, y[i]);
	}
	mix--, miy--;
	rep(i, 1, n) {
		x[i] -= mix;
		y[i] -= miy;
		id[x[i]][y[i]] = i;
	}
	rep(i, 1, n) {
		if(find(x[i], y[i], 1)) color(x[i], y[i], 1);
	}
	/*
	rep(i, 1, n) {
		update(x[i], y[i]);
	}
	int ans = 0;
	rep(i, 1, n) {
		if(!vis[i]) sel[i] = 1;
		if(sel[i]) ans++;
	}
	*/
	int ans = 0;
	rep(i, 1, n) {
		if(!vis[i]) sel[i] = 1;
		if(sel[i]) ans++;
	}
	cout << ans << "\n";
	if(type == 1) rep(i, 1, n) if(sel[i]) cout << i << " "; cout << "\n";
	fastio::flush();
	return 0;
}
