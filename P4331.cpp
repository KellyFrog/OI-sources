
// Problem: P4331 [BalticOI 2004]Sequence 数字序列
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4331?contestId=41933
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

const int N = 1e6 + 5;

struct Node {
	int l, r, ans, rt;
	Node() {}
	Node(int l0, int r0, int ans0, int rt0) : l(l0), r(r0), ans(ans0), rt(rt0) {}
};

int dist[N], val[N], lson[N], rson[N], siz[N];
int n;
stack<Node> s;
int ans[N];

void Merge(int& rt, int x, int y) {
	if(x == 0 || y == 0) return rt = x + y, void();
	if(val[x] < val[y]) swap(x, y);
	rt = x;
	Merge(rson[x], rson[x], y);
	if(dist[rson[x]] > dist[lson[x]]) swap(lson[x], rson[x]);
	dist[x] = dist[rson[x]] + 1;
	siz[x] = siz[lson[x]] + siz[rson[x]] + 1;
	debug("merged {} {}, siz={},{}\n", x, y, siz[x], siz[y]);
}

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(val[i]), val[i] -= i, siz[i] = 1;
	rep(i, 1, n) {
		Node cur(i, i, i, i);
		if(!s.empty()) debug("Solve={} {} {}\n", i, val[s.top().ans], val[cur.ans]);
		while(!s.empty() && val[s.top().ans] > val[cur.ans]) {
			debug("OK in loop\n");
			cur.l = s.top().l;
			int cursiz = cur.r - cur.l + 1;
			Merge(cur.ans, cur.ans, s.top().ans);
			debug("after merge, top={} siz={} [{},{}]\n", val[cur.ans], siz[cur.ans], cur.l, cur.r);
			s.pop();
			while(siz[cur.ans] > (cursiz + 1) / 2) {
				Merge(cur.ans, lson[cur.ans], rson[cur.ans]);
				debug("merged, siz={}\n", siz[cur.ans]);
			}
		}
		debug("OK2\n");
		s.push(cur);
	}
	ll ans0 = 0;
	while(!s.empty()) {
		auto x = s.top();
		s.pop();
		rep(i, x.l, x.r) {
			ans[i] = val[x.ans];
		}
	}
	rep(i, 1, n) {
		val[i] += i;
		ans[i] += i;
		ans0 += abs(val[i] - ans[i]);
	}
	fastio::qwrite(ans0, '\n');
	rep(i, 1, n) fastio::qwrite(ans[i], " \n"[i == n]);
  fastio::flush();
  return 0;
}