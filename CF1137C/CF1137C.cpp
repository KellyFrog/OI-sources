
// Problem: CF1137C Museums Tour
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1137C?contestId=41163
// Memory Limit: 500 MB
// Time Limit: 4000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)


// Happy Chinese new year! (Feb. 12th, 2021)

/*
 * Codeforces @Chenkaifeng
 * Luogu @longer_name
 */

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>

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
const int D = 52;
const int ND = N * D;

//5e6

int n, m, t, d;
int dfn[ND], low[ND], scc[ND], cnt[ND], scccnt, dfncnt;
int ins[ND], stk[ND], top;
int tmp[ND], p, head = 1, tail;
bool vis[N];
char S[N][D];

int head1[ND], nxt1[ND], to1[ND], tot1;
int nxt2[ND];

#define head2 stk
#define to2 ins
#define dp dfn
#define ind low
int tot2;

inline void AddEdge1(int u, int v) {
	nxt1[++tot1] = head1[u];
	to1[tot1] = v;
	head1[u] = tot1;
}


inline void AddEdge2(int u, int v) {
	nxt2[++tot2] = head2[u];
	to2[tot2] = v;
	head2[u] = tot2;
}

inline void Tarjan(int u) {
	low[u] = dfn[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	for(int i = head1[u]; i; i = nxt1[i]) {
		int v = to1[i];
		if(!dfn[v]) Tarjan(v), low[u] = min(low[u], low[v]);
		else if(ins[v]) low[u] = min(low[u], low[v]);
	}
	if(dfn[u] == low[u]) {
		int x = 0;
		scccnt++;
		while((x = stk[top--]) != u) {
			ins[x] = 0;
			scc[x] = scccnt;
			tmp[++p] = x;
		}
		ins[x] = 0;
		scc[x] = scccnt;
		tmp[++p] = x;

		rep(i, 1, p) {
			if(S[(tmp[i]-1)/d+1][(tmp[i]-1)%d+1] == '0') continue;
			if(!vis[(tmp[i]-1)/d]) cnt[scccnt]++, vis[(tmp[i]-1)/d] = 1;
		}
		rep(i, 1, p) vis[(tmp[i]-1)/d] = 0;

		p = 0;
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &d);
	rep(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		rep(j, 1, d) {
			AddEdge1((u-1) * d + j,((v-1) * d + j % d + 1));
		}
	}
	rep(i, 1, n) scanf("%s", S[i] + 1);
	t = n * d;
	rep(i, 1, t) if(!dfn[i]) Tarjan(i);


	memset(dfn, 0, sizeof dfn);
	memset(ind, 0, sizeof ind);

	memset(head2, 0, sizeof head2);
	memset(to2, 0, sizeof to2);
	memset(nxt2, 0, sizeof nxt2);

	OK;

	rep(u, 1, t) {
		for(int i = head1[u]; i; i = nxt1[i]) {
			int v = to1[i];
			if(scc[u] != scc[v]) {
				AddEdge2(scc[v], scc[u]);
				ind[scc[u]]++;
			}
		}
	}
	rep(i, 1, scccnt) {
		if(!ind[i]) tmp[++tail] = i;
	}
	
	int ans = 0;
	while(head <= tail) {
		int u = tmp[head++];
		dp[u] += cnt[u];
		for(int i = head2[u]; i; i = nxt2[i]) {
			int v = to2[i];
			dp[v] = max(dp[v], dp[u]);
			if(--ind[v] == 0) tmp[++tail] = v;
		}
	}
	printf("%d\n", dp[scc[1]]);
	return 0;
}