
// Problem: P6007 [USACO20JAN]Springboards G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6007?contestId=42241
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

//dp[i][j] = min(dp[i'][j'] + (i-i') + (j-j')
//维护dp[i][j] - i - j

//对所有关键点的i排序

#define int long long

const int N = 1e6 + 5;
const int inf = 0x3f3f3f3f3f3f3f3f;

pair<pair<int, int>, int> pos[N<<1];
pair<pair<int, int>, pair<int, int> > node[N];
int a[N<<2], tot, siz;
int dp[N<<1], tree[N<<1];
int n, m;

template<typename T>
inline void chkmax(T& x, T y) {
	x = x > y ? x : y;
}

int lowbit(int x) {
	return x & (-x);
}

void Modify(int p, int x) {
	while(p <= siz + 5) {
		chkmax(tree[p], x);
		p += lowbit(p);
	}
}

int Query(int p) {
	int res = 0;
	while(p) {
		chkmax(res, tree[p]);
		p -= lowbit(p);
	}
	return res;
}

int link[N<<1];

struct Node {
	int sx, sy, tx, ty, pos, dis;
};

Node nd[N];
int last[N];

signed main() {
	fastio::qread(n, m);
	rep(i, 1, m) {
		fastio::qread(nd[i].sx, nd[i].sy, nd[i].tx, nd[i].ty);
		if(max({nd[i].sx, nd[i].sy, nd[i].tx, nd[i].ty}) > n) nd[i].sx = nd[i].sy = nd[i].tx = nd[i].ty = 0;
		nd[i].dis = nd[i].tx - nd[i].sx + nd[i].ty - nd[i].sy;
		a[++siz] = nd[i].sx;
		a[++siz] = nd[i].sy;
		a[++siz] = nd[i].tx;
		a[++siz] = nd[i].ty;
	}
	sort(a + 1, a + 1 + siz);
	int q = unique(a + 1, a + 1 + siz) - (a + 1);
	rep(i, 1, m) {
		#define uni(x) x = lower_bound(a + 1, a + 1 + q, x) - a;
		uni(nd[i].sx);
		uni(nd[i].sy);
		uni(nd[i].tx);
		uni(nd[i].ty);
		nd[i].pos = i;
		pos[++tot] = mp(mp(nd[i].sx, nd[i].sy), i);
		pos[++tot] = mp(mp(nd[i].tx, nd[i].ty), i);
	}
	sort(pos + 1, pos + 1 + tot);
	int ans = 0;
	rep(i, 1, tot) {
		dp[i] = Query(pos[i].fi.se);
		if(last[pos[i].se] == 0) last[pos[i].se] = i;
		else{
			dp[i] = max(dp[i], dp[last[pos[i].se]] + nd[pos[i].se].dis);
		}
		Modify(pos[i].fi.se, dp[i]);
		debug("{} : {} {} {} {}\n", i, pos[i].fi.fi, pos[i].fi.se, pos[i].se, dp[i]);
		ans = max(ans, dp[i]);
	}
	cout << 2 * n - ans << "\n";
  fastio::flush();
  return 0;
}