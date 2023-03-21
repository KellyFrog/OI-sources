
// Problem: P4130 [NOI2007] 项链工厂
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4130?contestId=43450
// Memory Limit: 125 MB
// Time Limit: 4000 ms
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

const int N = 5e5 + 5;

struct Node {
  int cl, cr, ans;
  int lazy;
  Node(int l = 0, int r = 0, int as = 0, int lz = -1) : cl(l), cr(r), ans(as), lazy(lz) {}
};

Node tree[N << 2];
int n, c, q;
int a[N];

inline void Merge(Node &tar, Node x, Node y) {
	tar.lazy = -1;
	if(x.cl == 0) {
		tar = y;
		return;
	}
	if(y.cl == 0) {
		tar = x;
		return;
	}
  if (x.cr == y.cl)
    tar.ans = x.ans + y.ans - 1;
  else
    tar.ans = x.ans + y.ans;
  tar.cl = x.cl;
  tar.cr = y.cr;
}

inline void Lazy(int cur, int x) {
	tree[cur] = Node(x, x, 1, x);
}

inline void PushDown(int cur) {
	if(tree[cur].lazy != -1) {
		Lazy(cur << 1, tree[cur].lazy);
		Lazy(cur << 1 | 1, tree[cur].lazy);
		tree[cur].lazy = -1;
	}
}

inline void PushUp(int cur) {
  Merge(tree[cur], tree[cur << 1], tree[cur << 1 | 1]);
}

inline void Build(int cur, int l, int r) {
  if (l == r) return tree[cur] = Node(a[l], a[l], 1), void();
  rg int mid = l + r >> 1;
  Build(cur << 1, l, mid);
  Build(cur << 1 | 1, mid + 1, r);
  PushUp(cur);
}

inline void Query(int cur, int ql, int qr, int l, int r, Node &res) {
  if (ql <= l && r <= qr) return Merge(res, res, tree[cur]), void();
  PushDown(cur);
  rg int mid = l + r >> 1;
  if (ql <= mid) Query(cur << 1, ql, qr, l, mid, res);
  if (mid < qr) Query(cur << 1 | 1, ql, qr, mid + 1, r, res);
}

inline void Modify(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Modify(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Modify(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

int delta = 0, rev = 0;

int getpos(int k) {
	if(rev) k = n - k + 2;
	k -= delta;
	while(k < 1) k += n;
	while(k > n) k -= n;
	return k;
}

int main() {
  scanf("%d%d", &n, &c);
  rep(i, 1, n) scanf("%d", &a[i]);
  Build(1, 1, n);
  scanf("%d", &q);
  while (q--) {
    char op[4] = {};
    scanf("%s", op);
    	int np = getpos(n);
    	int sp = getpos(1);
    if(op[0] == 'R') {
    	int x;
    	scanf("%d", &x);
    	delta += rev ? -x : x;
    	while(delta < 0) delta += n;
    	while(delta > n) delta -= n;
    } else if(op[0] == 'F') {
    	rev ^= 1;
    } else if(op[0] == 'S') {
    	int x, y;
    	scanf("%d%d", &x, &y);
    	x = getpos(x);
    	y = getpos(y);
    	Node x0, y0;
    	Query(1, x, x, 1, n, x0);
    	Query(1, y, y, 1, n, y0);
    	
    	Modify(1, x, x, y0.cl, 1, n);
    	Modify(1, y, y, x0.cl, 1, n);
    } else if(op[0] == 'P') {
    	int L, R, x;
    	scanf("%d%d%d", &L, &R, &x);
    	L = getpos(L);
    	R = getpos(R);
    	if(rev) swap(L, R);
    	debug("modify = {} -> {}\n", L, R);
    	if(L <= R) Modify(1, L, R, x, 1, n);
    	else Modify(1, L, n, x, 1, n), Modify(1, 1, R, x, 1, n);
    } else if(op[0] == 'C' && op[1] != 'S') {
    	printf("%d\n", max(tree[1].ans - (tree[1].cl == tree[1].cr), 1));
    } else if (op[0] == 'C' && op[1] == 'S') {

    	int L, R;
    	scanf("%d%d", &L, &R);
    	L = getpos(L);
    	R = getpos(R);
    	
    	if(rev) swap(L, R);
    	debug("query = {} -> {}\n", L, R);
    	if(L <= R) {
    		Node res;
    		Query(1, L, R, 1, n, res);
    		printf("%d\n", res.ans);
    	} else {
    		Node res1, res2;
    		Query(1, L, n, 1, n, res1);
    		Query(1, 1, R, 1, n, res2);
    		int c1 = res1.cr;
    		int c2 = res2.cl;
    		debug("c = {} {}\n", c1, c2);
    		printf("%d\n", max(1, res1.ans + res2.ans - (c1 == c2)));
    	}
    }
    debug("after op={} pos1={} pos2={}\n", op, getpos(1), getpos(2));
  }
  fastio::flush();
  return 0;
}