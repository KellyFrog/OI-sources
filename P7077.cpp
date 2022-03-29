// Problem: P7077 [CSP-S2020] 函数调用
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P7077
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

// const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
const ll mod = 998244353;
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

struct Opt {
	ll tp, x, y;
} op[N];

vector<int> adj[N];
ll f[N], g[N], a[N], b[N];
int n, m, q;
int ind[N];

void dfs(int u) {
	if(f[u] != -1) return;
	f[u] = op[u].tp == 2 ? op[u].x : 1;
	for(int v : adj[u]) {
		dfs(v);
		f[u] = f[u] * f[v] % mod;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	memset(f, -1, sizeof f);
	
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]);
	fastio::qread(m);
	rep(i, 1, m) {
		fastio::qread(op[i].tp);
		if(op[i].tp == 1) {
			fastio::qread(op[i].x, op[i].y);
			if(op[i].y > mod) op[i].y -= mod;
		} else if(op[i].tp == 2) {
			fastio::qread(op[i].x);
			if(op[i].x > mod) op[i].x -= mod;
		} else {
			int k; fastio::qread(k);
			adj[i].resize(k);
			per(j, 0, k-1) fastio::qread(adj[i][j]), ind[adj[i][j]]++;
		}
	}
	fastio::qread(q);
	adj[m+1].resize(q);
	per(i, 0, q-1) fastio::qread(adj[m+1][i]), ind[adj[m+1][i]]++;
	dfs(m+1);
	g[m+1] = 1;
	queue<int> q;
	rep(i, 1, m+1) if(!ind[i]) q.push(i);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		ll t = g[u];
		for(int v : adj[u]) {
			g[v] = (g[v] + t) % mod;
			t = t * f[v] % mod;
			if(--ind[v] == 0) q.push(v);
		}
	}
	rep(i, 1, m) {
		if(op[i].tp == 1) {
			b[op[i].x] = (b[op[i].x] + g[i] * op[i].y) % mod;
		}
	}
	
	rep(i, 1, n) fastio::qwrite((f[m+1] * a[i] + b[i]) % mod, " \n"[i == n]);
	
	fastio::flush();
	return 0;
}
