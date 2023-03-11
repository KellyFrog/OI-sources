// Problem: P4178 Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4178
// Memory Limit: 500 MB
// Time Limit: 1000 ms
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

vector<pair<int, int> > adj[N], curtree;
vector<ll> dist;
int n, vis[N], siz[N], val[N];
ll dis[N], ans, k;

inline void dfsinit(int u, int fa) {
	curtree.pb(mp(u, fa));
	siz[u] = 1;
	for(auto [v, w] : adj[u]) {
		if(vis[v] || v == fa) continue;
		dfsinit(v, u);
		siz[u] += siz[v];
	}
}

inline int getcentroid(int rt) {
	int p = rt;
	for(auto [u, fa] : curtree) {
		val[u] = siz[rt]-val[u];
		chkmax(val[fa], val[u]);
	}
	for(auto [u, fa] : curtree) if(val[u] < val[p]) p = u;
	return p;
}

inline void dfsdis(int u, int fa, ll dis0) {
	dist.pb(dis0);
	for(auto [v, w] : adj[u]) if(v != fa && !vis[v]) dfsdis(v, u, dis0 + w);
}

inline ll getans(int rt, ll k) {
	ll res = 0;
	dist.clear();
	dfsdis(rt, 0, 0);
	sort(dist.begin(), dist.end());
	// for(auto x : dist) cerr << x << " "; cerr << "\n";
	for(int p1 = 0, p2 = (int)dist.size() - 1; p1 < dist.size(); p1++) {
		for(; dist[p1] + dist[p2] > k && p1 <= p2; p2--);
		if(p1 > p2) break;
		res += p2 - p1;
	}
	// debug("res = {}\n", res);
	return res;
}


inline void dfswork(int rt) {
	// debug("dfswork = {}\n", rt);
	curtree.clear();
	dist.clear();
	dfsinit(rt, 0);
	int ce = getcentroid(rt);
	// debug("get ce = {}\n", ce);
	vis[ce] = 1;
	ans += getans(ce, k);
	for(auto [v, w] : adj[ce]) if(!vis[v]) ans -= getans(v, k-2*w);
	for(auto [v, w] : adj[ce]) if(!vis[v]) dfswork(v);
}

int main() {
	fastio::qread(n);
	rep(i, 1, n-1) {
		int u, v, w;
		fastio::qread(u, v, w);
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	fastio::qread(k);
	dfswork(1);
	cout << ans << "\n";
	fastio::flush();
}
