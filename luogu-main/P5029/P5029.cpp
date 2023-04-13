// Problem: P5029 T'ill It's Over
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5029
// Memory Limit: 125 MB
// Time Limit: 500000 ms
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


template<const int N, const int M> 
class Flow {
	const ll inf = 1e18;
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

const int N = 1e5 + 5;
const ll inf = 1e18;

int idin[N << 2], idout[N << 2];

Flow<N<<3, N<<7> f;

int n, m, k;
int s, t;
int tot;

inline void build(int cur, int l, int r) {
	idin[cur] = ++tot;
	idout[cur] = ++tot;
	
	if(cur >> 1) {
		f.addedge(idin[cur >> 1], idin[cur], inf);
		f.addedge(idin[cur], idin[cur >> 1], 0);
		f.addedge(idout[cur], idout[cur >> 1], inf);
		f.addedge(idout[cur >> 1], idout[cur], 0);
	}
	
	if(l == r) {
		f.addedge(idin[cur], idout[cur], inf);
		f.addedge(idout[cur], idin[cur], 0);
		if(l == 1) f.addedge(s, idin[cur], n), f.addedge(idin[cur], s, 0);
		if(l == k) f.addedge(idin[cur], t, inf), f.addedge(t, idin[cur], 0);
		return;
	}
	int mid = l + r >> 1;
	
	build(cur << 1, l, mid);
	build(cur << 1 | 1, mid + 1, r);
}

inline void connect(int cur, int ql, int qr, int l, int r, bool in, int x) {
	if(ql <= l && r <= qr) {
		if(in) f.addedge(x, idin[cur], inf), f.addedge(idin[cur], x, 0);
		else f.addedge(idout[cur], x, inf), f.addedge(x, idout[cur], 0);
		return;
	}
	int mid = l + r >> 1;
	if(ql <= mid) connect(cur << 1, ql, qr, l, mid, in, x);
	if(mid < qr) connect(cur << 1 | 1, ql, qr, mid + 1, r, in, x);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	s = ++tot, t = ++tot;
	
	fastio::qread(n, m, k);
	build(1, 1, k);
	rep(i, 1, m) {
		int l1, l2, r1, r2, x, op;
		fastio::qread(op, x);
		if(op == 1) fastio::qread(l1, l2), r1 = l1, r2 = l2;
		else if(op == 2) fastio::qread(l1, r1, l2), r2 = r1;
		else if(op == 3) fastio::qread(l1, l2, r2), r1 = l1;
		else fastio::qread(l1, r1, l2, r2);
		int a = ++tot;
		int b = ++tot;
		f.addedge(a, b, x);
		f.addedge(b, a, 0);
		connect(1, l1, r1, 1, k, 0, a);
		connect(1, l2, r2, 1, k, 1, b);
	}
	
	cout << f.solve(s, t) << "\n";
	
	fastio::flush();
	return 0;
}
