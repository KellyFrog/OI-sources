
// Problem: P3273 [SCOI2011]棘手的操作
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3273
// Memory Limit: 125 MB
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

const int N = 3e5 + 5;
const int inf = 1e9;

struct Opt {
	int op, x, y;
};

Opt qry[N];

int mx[N << 2], lazy[N << 2];
int fa[N << 1][21], weight[N<<1], uni[N], rt[N];
int dfn[N], dfncnt;
int a[N], tot;
int L[N<<1], R[N<<1];
int n, m;
int adj[N<<1][2];

inline int Find(int x) {
	return x == uni[x] ? x : uni[x] = Find(uni[x]);
}

inline void Lazy(int cur, int x) {
	mx[cur] += x;
	lazy[cur] += x;
}

inline void PushDown(int cur) {
	if(lazy[cur]) {
		Lazy(cur << 1, lazy[cur]);
		Lazy(cur << 1 | 1, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void PushUp(int cur) {
	mx[cur] = max(mx[cur << 1], mx[cur << 1 | 1]);
}

inline void Modify(int cur, int p, int x, int l, int r) {
	if(l == r) return mx[cur] = x, void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(p <= mid) Modify(cur << 1, p, x, l, mid);
	else Modify(cur << 1 | 1, p, x, mid + 1, r);
	PushUp(cur);
}

inline void Add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid+1, r);
	PushUp(cur);
}

inline int Max(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mx[cur];
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg int res = -inf;
	if(ql <= mid) res = max(res, Max(cur << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, Max(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

inline void Dfs(int u, int f) {
	//debug("Dfs={} {}\n", u, f);
	L[u] = n+1;
	R[u] = -1;
	fa[u][0] = f;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i-1]][i-1];
	if(1 <= u && u <= n) {
		L[u] = R[u] = dfn[u] = ++dfncnt;
		return;
	}
	rep(i, 0, 1) {
		int v = adj[u][i];
		//if(v == 0) continue;
		Dfs(v, u);
		L[u] = min(L[u], L[v]);
		R[u] = max(R[u], R[v]);
	}
}

inline int GetT(int x, int t) {
	per(i, 0, 20) {
		if(fa[x][i] && weight[fa[x][i]] <= t) x = fa[x][i];
	}
	return x;
}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n) uni[i] = rt[i] = i;
	scanf("%d", &m);
	tot = n;
	int p = 0;
	rep(i, 1, m) {
		char ch; int op;
		cin >> ch;
		if(ch == 'U') {
			p++;
			qry[i].op = 1;
			scanf("%d%d", &qry[i].x, &qry[i].y);
			int x = qry[i].x, y = qry[i].y;
			x = Find(x);
			y = Find(y);
			if(x == y) continue;
			tot++;
			weight[tot] = p;
			adj[tot][0] = rt[x];
			adj[tot][1] = rt[y];
			rt[y] = tot;
			uni[x] = y;
		} else if(ch == 'A') {
			scanf("%d%d%d", &op, &qry[i].x, &qry[i].y);
			qry[i].op = 1 + op;
		} else {
			scanf("%d", &op);
			if(op < 3) scanf("%d", &qry[i].x);
			qry[i].op = 4 + op;
		}
	}
	int tm = 0;
	per(i, 1, tot) if(!L[i]) Dfs(i, 0);
	rep(i, 1, n) Modify(1, dfn[i], a[i], 1, n);
	rep(i, 1, m) {
		if(qry[i].op == 1) {
			tm++;
		} else if(qry[i].op == 2) {
			Add(1, dfn[qry[i].x], dfn[qry[i].x], qry[i].y, 1, n);
		} else if(qry[i].op == 3) {
			int x = GetT(qry[i].x, tm);
			Add(1, L[x], R[x], qry[i].y, 1, n);
		} else if(qry[i].op == 4) {
			Add(1, 1, n, qry[i].x, 1, n);
		} else if(qry[i].op == 5) {
			fastio::qwrite(Max(1, dfn[qry[i].x], dfn[qry[i].x], 1, n), '\n');
		} else if(qry[i].op == 6) {
			int x = GetT(qry[i].x, tm);
			fastio::qwrite(Max(1, L[x], R[x], 1, n), '\n');
		} else if(qry[i].op == 7) {
			fastio::qwrite(mx[1], '\n');
		}
	}
  fastio::flush();
  return 0;
}