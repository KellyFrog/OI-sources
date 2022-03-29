
// Problem: CF703D Mishka and Interesting sum
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF703D?contestId=42241
// Memory Limit: 250 MB
// Time Limit: 3500 ms
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

int a[N], n, m;

struct BIT {
	int tree[N];
	
	inline int lowbit(int x) {
		return x & (-x);
	}
	
	int Sum(int p) {
		int res = 0;
		while(p) {
			res ^= tree[p];
			p -= lowbit(p);
		}
		return res;
	}
	
	void Add(int p, int x) {
		while(p <= n) {
			tree[p] ^= x;
			p += lowbit(p);
		}
	}
};

BIT b1, b2;
map<int, vector<int> > c;
vector<pair<int, int> > qry[N];
int pos[N], ans[N];
int pre[N];

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]), pre[i] = pre[i-1] ^ a[i], c[a[i]].pb(i), pos[i] = c[a[i]].size();
	fastio::qread(m);
	rep(i, 1, m) {
		int L, R; fastio::qread(L, R);
		qry[R].pb(mp(L, i));
	}
	rep(i, 1, n) for(auto x : qry[i]) debug("{} {}\n", x.fi, i);
	rep(R, 1, n) {
		if(pos[R] == 1) {
			b1.Add(1, a[R]);
			b1.Add(R+1, a[R]);
			debug("b1 add= {} {}\n", 1, a[R]);
			debug("b1 add= {} {}\n", R+1, a[R]);
		} else {
			b1.Add(c[a[R]][pos[R]-2]+1, a[R]);
			b1.Add(R+1, a[R]);
			debug("b1 add= {} {}\n", c[a[R]][pos[R]-2]+1, a[R]);
			debug("b1 add= {} {}\n", R+1, a[R]);
		}
		b2.Add(1, a[R]);
		b2.Add(R+1, a[R]);
		for(auto x : qry[R]) {
			debug("{} {} got {} {}\n", x.fi, R, b1.Sum(x.fi), b2.Sum(x.fi));
			ans[x.se] = b1.Sum(x.fi) ^ b2.Sum(x.fi);
		}
	}
	rep(i, 1, m) fastio::qwrite(ans[i], '\n');
  fastio::flush();
  return 0;
}