// Problem: CF700C Break Up
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF700C?contestId=41164
// Memory Limit: 250 MB
// Time Limit: 3000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

#include <cstdio>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>

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

const int N = 1e5 + 5;
const int M = 1e5 + 5;
const ll inf = 1e18;

int head[N], to[M << 1], nxt[M << 1];
ll weight[N], tot;
int s, t;
vector<int> eg, tree[N];
int dfn[N], low[N], dfncnt;
int edcc[N], edcccnt;
int stk[N], top, ins[N];
int wei[M];
int n, m;
int from[N], frome[N];
ll fromw[N];

void AddEdge(int u, int v, ll w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
	weight[tot] = w;
}

inline bool Tarjan(int u, int fat, int e, int x) {
	dfn[u] = low[u] = ++dfncnt;
	ins[u] = 1;
	stk[++top] = u;
	bool ret = 0;
	//debug("Tarjan={} {} {} {}\n", u, fat, e, x);
	e = (e % 2 ? e + 1 : e - 1);
	for (int i = head[u]; i; i = nxt[i]) {
		if (((i+1) / 2 == (x+1)/2) || (i+1)/2 == (e+1)/2) continue;
		int v = to[i];
		if (!dfn[v]) {
			bool flag = Tarjan(v, u, i, x);
			low[u] = min(low[u], low[v]);
			if(flag) ret = 1;
			if (low[v] > dfn[u] && flag) {
				//debug("got {} => {}\n", u, v);
				eg.pb((i + 1) / 2);
				ret = 1;
			}
		} else if (ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	return ret || (u == t);
}

int ans0;

inline ll Solve(int x) {
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	dfncnt = 0;
	eg.clear();
	Tarjan(s, 0, 0, x);
	ll res0 = inf;
	
	for (int i = 0; i < (int)eg.size(); i++) {
		int e = eg[i];
	  if (weight[e << 1] < res0) {
	    ans0 = e;
	    res0 = weight[e << 1];
	  } 
	}
	

	return res0;
}

ll ans = inf;
vector<int> res;

int main() {
	scanf("%d%d", &n, &m);
	scanf("%d%d", &s, &t);
	rep(i, 1, m) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
		wei[i] = w;
	}
	rep(c, 0, 1000) ans = min(ans, Solve(-1));
	if (ans != inf) {
		res.pb(ans0);
	}
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = nxt[i]) {
			int v = to[i];
			ll w = weight[i];
			if (from[v] == 0 || ((from[v] == u) && fromw[v] > w)) {
				if (from[v] == 0) q.push(v);
				from[v] = u;
				frome[v] = i;
				fromw[v] = w;
			}
		}
	}
	/*
	if(!from[t]) {
		puts("0\n0");
		return 0;
	}
	int cur = t;
	while(cur != s) {
		int e = frome[cur];
		ll curres = fromw[cur] + Solve(e);
		if(curres < ans) {
			ans = curres;
			res.clear();
			res.pb(ans0), res.pb((e+1) / 2);
		}
		cur = from[cur];
	}
	*/
	if(ans == inf) return puts("-1"), 0;
	
	cout << ans << " " << res.size() << "\n";
	for(int x : res) cout << x << " ";
	
	return 0;
}
