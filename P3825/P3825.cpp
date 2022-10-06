
// Problem: P3825 [NOI2017] 娓告垙
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3825?contestId=41164
// Memory Limit: 128 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)


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

const int N = 2e5 + 5;

int head[N], nxt[N<<1], to[N<<1], tot;
int dfn[N], low[N], scc[N], ins[N], scccnt, dfncnt;
int stk[N], top;
char S[N];
int n, d, m;

struct Query {
	int i, j;
	char hi, hj;
};

Query qry[N];
int pos[N], a[N];

void Add(int u, int v) {
	debug("add {} => {}\n", u, v);
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

inline void Tarjan(int u) {
	low[u] = dfn[u] = ++dfncnt;
	stk[++top] = u;
	ins[u] = 1;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if (!dfn[v])
			Tarjan(v), low[u] = min(low[u], low[v]);
		else if (ins[v])
			low[u] = min(low[u], low[v]);
	}
	if (dfn[u] == low[u]) {
		int x = 0;
		scccnt++;
		while ((x = stk[top--]) != u) {
			ins[x] = 0;
			scc[x] = scccnt;
		}
		ins[x] = 0;
		scc[x] = scccnt;
	}
}

//p 选p的第一个
//p+n 选p的第二个
//p+2n 不选p的第一个
//p+3n 不选p的第二个

void Connect(int x, int y) {
	if(x < 0) x = -x + 2 * n;
	if(y < 0) y = -y + 2 * n;
	Add(x, y);
}

int GetCnt(char x, char y) {
	if(x == 'A') return y == 'B' ? 1 : 2;
	if(x == 'B') return y == 'A' ? 1 : 2;
	if(x == 'C') return y == 'A' ? 1 : 2;
	return '*';
}

char GetCh(char x, int y) {
	if(x == 'A') return y == 1 ? 'B' : 'C';
	if(x == 'B') return y == 1 ? 'A' : 'C';
	if(x == 'C') return y == 1 ? 'A' : 'B';
	return '#';
}

int GetId(int x, char y) {
	assert(x > 0);
	if(GetCnt(S[x], y) == 1) return x;
	else return x + n;
}

void Solve() {
	memset(head, 0, sizeof head);
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	scccnt = dfncnt = 0;
	tot = 0;
	rep(i, 1, n) Connect(i, -(i+n)), Connect(-(i+n), i), Connect(-i, i+n), Connect(i+n, -i);
	rep(i, 1, m) {
		int x = qry[i].i, y = qry[i].j;
		char a = qry[i].hi, b = qry[i].hj;
		debug("op[{}] = {} {} {} {}\n", i, x, y, a, b);
		if(a == S[x]) continue;
		if(b == S[y]) Connect(GetId(x, a), -GetId(x, a));
		else Connect(GetId(x, a), GetId(y, b)), Connect(-GetId(y, b), -GetId(x, a));
	}
	rep(i, 1, n*4) if(!dfn[i]) Tarjan(i);
	rep(i, 1, n*4) debug("scc[{}]={}\n", i, scc[i]);
	rep(i, 1, n) if(scc[i] == scc[i+n] || scc[i] == scc[i+2*n] || scc[i+n] == scc[i+3*n]) return;
	rep(i, 1, n) {
		int x = scc[i] > scc[i+n] ? 2 : 1;
		printf("%c", GetCh(S[i], x));
	}
	exit(0);
}

int main() {
	scanf("%d%d", &n, &d);
	scanf("%s", S+1);
	rep(i, 1, n) S[i] = S[i] - 'a' + 'A';
	scanf("%d", &m);
	rep(i, 1, m) {
		char x, y;
		scanf("%d %c %d %c", &qry[i].i, &x, &qry[i].j, &y);
		qry[i].hi = x, qry[i].hj = y;
	}
	int p = 0;
	rep(i, 1, n) if(S[i] == 'X') pos[++p] = i;
	for(int base = 0; base < (1 << d); base++) {
		rep(i, 1, d) {
			int cur = (base >> (i-1)) & 1;
			S[pos[i]] = 'A' + cur;
		}
		Solve();
		rep(i, 1, d) S[pos[i]] = 'X';
	}
	puts("-1");
	return 0;
}