// Problem: P2774 方格取数问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2774
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

const ll inf = 1e18;
	
template<const int N, const int M> 
class Flow {
	int head[N], nxt[M<<1], to[M<<1];
	int cur[N];
	ll wgt[M<<1];
	int tot = 0;
	int dis[N];
	int s, t;
	
	
	
	
	inline bool bfs() {
		memset(dis, 0, sizeof dis);
		memcpy(cur, head, sizeof cur);
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
		for(int e = cur[u]; e; e = nxt[e]) {
			cur[u] = e;
			int v = to[e];
			ll w = wgt[e];
			if(w && dis[v] == dis[u] + 1) {
				ll cur = dfs(v, min(in, w));
				in -= cur;
				res += cur;
				wgt[e] -= cur;
				wgt[e^1] += cur;
				if(!in) break;
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

const int N = 105;

Flow<2*N*N, 5*N*N> f;
int cnt = 0;
int s, t;
int n, m;
int a[N][N], id[N][N];

inline void add(int i, int j, int ii, int jj) {
	if(1 <= ii && ii <= n && 1 <= jj && jj <= m) {
		f.addedge(id[i][j], id[ii][jj], inf);
		f.addedge(id[ii][jj], id[i][j], 0);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m;
	rep(i, 1, n) rep(j, 1, m) cin >> a[i][j];
	rep(i, 1, n) rep(j, 1, m) id[i][j] = ++cnt;
	int s = ++cnt, t = ++cnt;
	rep(i, 1, n) rep(j, 1, m) {
		if((i + j) & 1) {
			f.addedge(s, id[i][j], a[i][j]);
			f.addedge(id[i][j], s, 0);
			add(i, j, i+1, j);
			add(i, j, i-1, j);
			add(i, j, i, j-1);
			add(i, j, i, j+1);
		} else {
			f.addedge(id[i][j], t, a[i][j]);
			f.addedge(t, id[i][j], 0);
		}
	}
	ll sum = 0;
	rep(i, 1, n) rep(j, 1, m) sum += a[i][j];
	cout << sum - f.solve(s, t) << "\n";
	fastio::flush();
	return 0;
}
