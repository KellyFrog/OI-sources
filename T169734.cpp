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
#define rg register
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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e6 + 5;
const int inf = 1e9 + 5;

int head[N], nxt[N << 1], to[N << 1], weight[N << 1], tot;
int dis[N], dp[N];
int n, m, k;
bool ban[N], vis[N];;

void AddEdge(int u, int v, int w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	weight[tot] = w;
	head[u] = tot;
}

void Dij() {
	dp[1] = inf;
	rep(i, 2, n) dis[i] = inf;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	q.push(mp(dis[1], 1));
	while(!q.empty()) {
		int u = q.top().se; q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		if(ban[u]) dp[u] = 0;
		for(int i = head[u]; i; i = nxt[i]) {
			rg int v = to[i];
			rg int w = weight[i];
			if(dis[u] + w == dis[v] && (!ban[v])) {
				dp[v] = max(dp[v], min(dp[u], w));
			} else if(dis[u] + w < dis[v]) {
				dp[v] = min(dp[u], w);
				dis[v] = dis[u] + w;
				q.push(mp(dis[v], v));
			}
		}
	}
}

int main() {
	fastio::qread(n, m, k);
	rep(i, 1, k) {
		int x; fastio::qread(x);
		ban[x] = 1;
	}
	rep(i, 1, m) {
		int u, v, w;
		fastio::qread(u, v, w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	Dij();
	cout << dp[n] << "\n";
	return 0;
}