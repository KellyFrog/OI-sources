// Problem: P2766 最长不下降子序列问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2766
// Memory Limit: 125 MB
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

template<const int N, const int M> 
class Flow {
	const ll inf = 1e18;
	int head[N], nxt[M<<1], to[M<<1];
	ll wgt[M<<1];
	int tot = 0;
	int dis[N];
	int s, t;
	
	
	
	
	inline bool bfs() {
		memset(dis, 0, sizeof dis);
		static int que[N]; int hea = 1, tail = 0;
		dis[s] = 1;
		que[++tail] = s;
		while(hea <= tail) {
			int u = que[hea++];
			for(int e = head[u]; e; e = nxt[e]) {
				int v = to[e];
				ll w = wgt[e];
				if(w != 0 && dis[v] == 0) {
					dis[v] = dis[u] + 1;
					que[++tail] = v;
				}
			}
		}
		return dis[t];
	}
	
	inline ll dfs(int u, ll in) {
		if(u == t) return in;
		ll res = 0;
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e];
			ll w = wgt[e];
			if(w && dis[v] == dis[u] + 1) {
				ll cur = dfs(v, min(in, w));
				in -= cur;
				res += cur;
				wgt[e] -= cur;
				wgt[e^1] += cur;
			}
		}
		return res ? res : dis[u] = 0, res;
	}
	
	public:
	
	Flow() : tot(1), s(-1), t(-1) {}
	
	inline void addedge(int u, int v, ll w) {
		nxt[++tot] = head[u];
		to[tot] = v;
		wgt[tot] = w;
		head[u] = tot;
	}
	
	inline ll solve(int s0, int t0) {
		s = s0;
		t = t0;
		assert(s != t);
		ll ans = 0;
		while(bfs()) ans += dfs(s, inf);
		return ans;
	}
};


const int N = 1e3 + 5;
const int M = N << 1;
const ll inf = 1e18;

Flow<N, M> f1, f2;
int n, a[N];
int dp[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	int mx = 0;
	
	cin >> n;
	rep(i, 1, n) cin >> a[i];
	
	if(n == 1) {
		cout << 1 << "\n" << 1 << "\n" << 1 << "\n";
		return 0;
	} else if(n == 2) {
		cout << 2 << "\n" << 2 << "\n" << 2 << "\n";
		return 0;
	}
	
	rep(i, 1, n) rep(j, 0, i-1) if(a[j] <= a[i]) chkmax(dp[i], dp[j]+1);
	rep(i, 1, n) chkmax(mx, dp[i]);
	
	if(mx == 1) {
		cout << 1 << "\n" << n << "\n" << n << "\n";
		return 0;
	}
	
	int s = 2*n+1, t = 2*n+2;
	
	rep(i, 1, n) {
		if(i == 1 || i == n) {
			f1.addedge(i, i+n, 1);
			f1.addedge(i+n, i, 0);
			f2.addedge(i, i+n, inf);
			f2.addedge(i+n, i, 0);
			debug("f2 add = {} {} {}\n", i, i+n, inf);
		} else {
			f1.addedge(i, i+n, 1);
			f1.addedge(i+n, i, 0);
			f2.addedge(i, i+n, 1);
			f2.addedge(i+n, i, 0);
			debug("f2 add = {} {} {}\n", i, i+n, 1);
		}
	}
	
	rep(i, 1, n) {
		if(dp[i] == 1) {
			f1.addedge(s, i, inf);
			f1.addedge(i, s, 0);
			f2.addedge(s, i, inf);
			f2.addedge(i, s, 0);
			debug("f2 add = {} {} {}\n", s, i, inf);
		}
		if(dp[i] == mx) {
			f1.addedge(i+n, t, 1);
			f1.addedge(t, i+n, 0);
			if(i != n) {
				f2.addedge(i+n, t, 1);
				f2.addedge(t, i+n, 0);
				debug("f2 add = {} {} {}\n", i+n, t, 1);
			} else {
				f2.addedge(i+n, t, inf);
				f2.addedge(t, i+n, 0);
			debug("f2 add = {} {} {}\n", i+n, t, inf);
			}
		}
	}
	
	rep(i, 1, n) rep(j, i+1, n) {
		if(a[i] <= a[j] && dp[i] + 1 == dp[j]) {
			f1.addedge(i+n, j, inf);
			f1.addedge(j, i+n, 0);
			if(i == 1 && j == n) {
				f2.addedge(i+n, j, 1);
				f2.addedge(j, i+n, 0);
			} else {
				f2.addedge(i+n, j, inf);
				f2.addedge(j, i+n, 0);
			}
			debug("f2 add = {} {} {}\n", i+n, j, inf);
		}
	}
	
	cout << mx << "\n";
	cout << f1.solve(s, t) << "\n";
	cout << f2.solve(s, t) << "\n";
	
	fastio::flush();
	return 0;
}
