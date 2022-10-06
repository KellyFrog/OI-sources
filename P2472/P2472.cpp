// Problem: P2472 [SCOI2007]蜥蜴
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2472
// Memory Limit: 128 MB
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

const int N = 45;
const int M = 1005;
const ll inf = 1e18;

Flow<N*N, N*M> f;
int n, m, d;
char S[N][N], T[N][N];
int id[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	cin >> n >> m >> d;
	rep(i, 1, n) cin >> S[i] + 1;
	rep(i, 1, n) cin >> T[i] + 1;
	
	rep(i, 1, n) rep(j, 1, m) id[i][j] = (i-1) * m + j;
	
	int nm = n * m;
	
	int s = 2 * nm + 1;
	int t = 2 * nm + 2;
	
	rep(i, 1, n) rep(j, 1, m) {
		if(S[i][j]-'0' == 0) continue;
		f.addedge(id[i][j], id[i][j] + nm, S[i][j]-'0');
		f.addedge(id[i][j] + nm, id[i][j], 0);
		
		bool out = 0;
		
		rep(i0, 0, n+1) rep(j0, 0, m+1) {
			if(i0 == i && j0 == j) continue;
			if((i0 - i) * (i0 - i) + (j0 - j) * (j0 - j) <= d * d) {
				if(i0 == 0 || j0 == 0 || i0 == n+1 || j0 == m+1) out = 1;
				else if(S[i0][j0] != '0') {
					f.addedge(id[i][j] + nm, id[i0][j0], inf);
					f.addedge(id[i0][j0], id[i][j] + nm, 0);
				}
			}
		}
		
		if(out) {
			f.addedge(id[i][j] + nm, t, inf);
			f.addedge(t, id[i][j] + nm, 0);
		}
	}
	
	int cnt = 0;
	
	rep(i, 1, n) rep(j, 1, m) if(T[i][j] == 'L') {
		cnt++;
		f.addedge(s, id[i][j], 1);
		f.addedge(id[i][j], s, 0);
	}
	
	cout << cnt - f.solve(s, t) << "\n";
	
	fastio::flush();
	return 0;
}
