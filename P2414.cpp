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

char S[N];
int son0[N][27], son[N][27], fa[N], fail[N], endpos[N], wordcnt, dfncnt, rt, tot;
int dfn[N], siz[N];
int sum[N], ans[N];
int n, q;
vector<int> adj[N];
vector<pair<int, int> > qry[N];

inline int lowbit(int x) {
	return x & (-x);
}

inline void add(int p, int x) {
	while(p <= tot) {
		sum[p] += x;
		p += lowbit(p);
	}
}

inline int query(int p) {
	int res = 0;
	while(p) {
		res += sum[p];
		p -= lowbit(p);
	}
	return res;
}

inline int query(int L, int R) {
	return query(R) - query(L-1);
}

inline void buildtrie() {
	int cur = rt = ++tot;
	rep(i, 1, n) {
		if(S[i] == 'P') endpos[++wordcnt] = cur;
		else if(S[i] == 'B') cur = fa[cur];
		else {
			if(!son[cur][S[i]-'a']) fa[son[cur][S[i]-'a']=++tot] = cur;
			cur = son[cur][S[i]-'a'];
		}
	}
}

inline void buildfail() {
	static int que[N], head = 1, tail = 0;
	head = 1, tail = 0;
	fail[rt] = rt;
	rep(i, 0, 25) if(son[rt][i]) fail[son[rt][i]] = rt, que[++tail] = son[rt][i]; else son[rt][i] = rt;
	while(head <= tail) {
		int cur = que[head++]; rep(i, 0, 25) if(son[cur][i]) fail[son[cur][i]] = son[fail[cur]][i], que[++tail] = son[cur][i]; else son[cur][i] = son[fail[cur]][i];
	}
	rep(i, 2, tot) adj[fail[i]].pb(i);
}

inline void dfs1(int u) {
	dfn[u] = ++dfncnt;
	siz[u] = 1;
	for(int v : adj[u]) dfs1(v), siz[u] += siz[v];
}

inline void dfs2(int u) {
	add(dfn[u], 1);
	for(auto e : qry[u]) ans[e.se] = query(dfn[endpos[e.fi]], dfn[endpos[e.fi]] + siz[endpos[e.fi]] - 1);
	rep(i, 0, 25) if(son0[u][i]) dfs2(son[u][i]);
	add(dfn[u], -1);
}

int main() {
	scanf("%s", S+1);
	n = strlen(S+1);
	scanf("%d", &q);
	buildtrie();
	memcpy(son0, son, sizeof son0);
	buildfail();
	dfs1(1);
	rep(i, 1, q) {
		int x, y;
		scanf("%d%d", &x, &y);
		qry[endpos[y]].pb(mp(x, i));
	}
	dfs2(1);
	rep(i, 1, q) fastio::qwrite(ans[i], '\n');
  fastio::flush();
  return 0;
}
