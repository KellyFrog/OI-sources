
// Problem: P4246 [SHOI2008]堵塞的交通
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4246?contestId=43450
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

#ifndef ONLINE_JUDGE

void debug(const char *s) { cerr << s; }
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

const int N = 4e5 + 5;

struct Node {
	vector<pair<int, int> > chg;
	int qs, qt;
};

Node tree[N << 2];

int C, R = 2, q, Q = 2e5 + 5;
map<pair<int, int>, int> opt;
int stk[N << 3], top;
int fa[N], siz[N];

inline int id(int x, int y) {
	return (x - 1) * C + y;
}

inline int find(int x) {
	return x == fa[x] ? x : find(fa[x]);
}

inline bool merge(int x, int y) {
	x = find(x);
	y = find(y);
	if(x == y) return 0;
	if(siz[x] < siz[y]) swap(x, y);
	stk[++top] = y;
	fa[y] = x;
	siz[x] += siz[y];
	return 1;
}

inline bool insame(int x, int y) {
	return find(x) == find(y);
}

inline void undo() {
	int x = stk[top--];
	int fx = fa[x];
	fa[x] = x;
	siz[fx] -= siz[x];
}

inline void AddC(int cur, int ql, int qr, int s, int t, int l, int r) {
	//debug("AddC = [{}, {}] {} -> {}\n", ql, qr, s, t);
	if(ql <= l && r <= qr) return tree[cur].chg.pb(mp(s, t)), void();
	rg int mid = l + r >> 1;
	if(ql <= mid) AddC(cur << 1, ql, qr, s, t, l, mid);
	if(mid < qr) AddC(cur << 1 | 1, ql, qr, s, t, mid + 1, r); 
}

inline void AddQ(int cur, int p, int s, int t, int l, int r) {
	//debug("AddQ = [{}] {} -> {}\n", p, s, t);
	if(l == r) {
		tree[cur].qs = s;
		tree[cur].qt = t;
		return;
	}
	rg int mid = l + r >> 1;
	if(p <= mid) AddQ(cur << 1, p, s, t, l, mid);
	else AddQ(cur << 1 | 1, p, s, t, mid + 1, r);
}

inline void dfs(int cur, int l, int r) {
	int p = top;
	for(auto e : tree[cur].chg) {
		merge(e.fi, e.se);
	}
	if(l == r) {
		if(tree[cur].qs) puts(insame(tree[cur].qs, tree[cur].qt) ? "Y" : "N");
		return;
	}
	rg int mid = l + r >> 1;
	int p1 = top; dfs(cur << 1, l, mid); while(top > p1) undo();
	int p2 = top; dfs(cur << 1 | 1, mid + 1, r); while(top > p2) undo();
}

int main() {
	scanf("%d", &C);
	char op[6];
	rep(i, 1, 2*C) fa[i] = i, siz[i] = 1;
	while(1) {
		q++;
		scanf("%s", op);
		if(op[0] == 'E') break;
		else if(op[0] == 'O') {
			rg int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			opt[mp(id(x1, y1), id(x2, y2))] = q;
		} else if(op[0] == 'C') {
			rg int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			int lastpos = opt[mp(id(x1, y1), id(x2, y2))];
			opt[mp(id(x1, y1), id(x2, y2))] = 0;
			assert(lastpos != 0);
			AddC(1, lastpos, q, id(x1, y1), id(x2, y2), 1, Q);
		} else {
			rg int x1, x2, y1, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			AddQ(1, q, id(x1, y1), id(x2, y2), 1, Q);
		}
	}
	for(auto e : opt) {
		if(e.se) {
			AddC(1, e.se, q, e.fi.fi, e.fi.se, 1, Q);
		}
	}
	dfs(1, 1, Q);
  fastio::flush();
  return 0;
}