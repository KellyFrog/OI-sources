// Problem: T143791 七彩路径(colorful)
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T143791
// Memory Limit: 500 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

/* template ends here */

const int N = 5e5 + 5;

vector<int> adj[N];
int n, a[N];
int siz[N], dfn[N], dfncnt;
ll ans;
bool vis[N];
stack<int> stk[N];

inline bool intree(int u, int v) {
	return dfn[u] <= dfn[v] && dfn[v] < dfn[u] + siz[u];
}

inline void dfs1(int u, int fa) {
	siz[u] = 1;
	dfn[u] = ++dfncnt;
	for(int v : adj[u]) if(v != fa) dfs1(v, u), siz[u] += siz[v];
}

inline void dfs2(int u, int fa) {
	stk[a[u]].push(u);
	for(int v : adj[u]) {
		if(v != fa) {
			dfs2(v, u);
			ll curcnt = siz[v];
			while(intree(v, stk[a[u]].top())) {
				curcnt -= siz[stk[a[u]].top()];
				stk[a[u]].pop();
			}
			ans += 1ll * curcnt * (curcnt - 1) / 2;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int tot = 0;
	
	fastio::qread(n);
	rep(i, 1, n) {
		fastio::qread(a[i]);
		if(!vis[a[i]]) tot++;
		vis[a[i]] = 1;
	}
	rep(i, 1, n-1) {
		int u, v;
		fastio::qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	
	dfs1(1, 0);
	siz[0] = n;
	rep(i, 1, (int)5e5) if(vis[i]) stk[i].push(0);
	dfs2(1, 0);
	
	
	
	rep(i, 1, (int)5e5) {
		if(!vis[i]) continue;
		ll curcnt = n;
		while(stk[i].top() != 0) {
			curcnt -= siz[stk[i].top()];
			stk[i].pop();
		}
		ans += 1ll * curcnt * (curcnt - 1 ) / 2;
	}
	
	
	cout << 1ll * tot * n * (n-1) / 2 - ans << "\n";
	
	fastio::flush();
	return 0;
}
