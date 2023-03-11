
// Problem: T169735 树上距离
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T169735?contestId=41524
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

const int N = 1e5 + 5;

ll dp1[N], dp2[N];
int siz1[N], siz2[N];
ll ans1[N], ans2[N];
vector<pair<int, int> > adj[N];
int n;
int mark[N];

void Dfs1(int u, int fa) {
	siz2[u] = 1;
	for(auto e : adj[u]) {
		int v = e.fi, w = e.se;
		if(v == fa) continue;
		Dfs1(v, u);
		if(w % 2 == 0) {
			siz1[u] += siz1[v];
			siz2[u] += siz2[v];
			dp1[u] += dp1[v] + siz1[v] * w;
			dp2[u] += dp2[v] + siz2[v] * w;
		} else {
			siz1[u] += siz2[v];
			siz2[u] += siz1[v];
			dp1[u] += dp2[v] + siz2[v] * w;
			dp2[u] += dp1[v] + siz1[v] * w;
		}
	}
}

void Dfs2(int u, int fa, int we) {
	if(u != 1) {
		int x1 = ans1[fa], x2 = siz1[fa];
		int y1 = ans2[fa], y2 = siz2[fa];
		int a = siz1[u], b = siz2[u];
		if(we % 2 == 0) {
			ans1[u] = x1 + (x2 - 2 * a) * we;
			ans2[u] = y1 + (y2 - 2 * b) * we;
			siz1[u] = siz1[fa];
			siz2[u] = siz2[fa];
		} else {
			ans1[u] = y1 + (y2 - 2 * a) * we;
			ans2[u] = x1 + (x2 - 2 * b) * we;
			siz1[u] = siz2[fa];
			siz2[u] = siz1[fa];
		}
	}
	for(auto e : adj[u]) {
		int v = e.fi, w = e.se;
		if(v != fa) Dfs2(v, u, w);
	}
}

int main() {
	cin >> n;
	rep(i, 1, n) cin >> mark[i];
	rep(i, 1, n-1) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].pb(mp(v, w));
		adj[v].pb(mp(u, w));
	}
	Dfs1(1, 0);
	ans1[1] = dp1[1];
	ans2[1] = dp2[1];
	Dfs2(1, 0, 0);
	ll res1 = (ll)1e18, res2;
	rep(i, 1, n) {
		if(mark[i] == 0) {
			if(ans1[i] < res1) {
				res1 = ans1[i];
				res2 = i;
			}
		} else {
			if(ans2[i] < res1) {
				res1 = ans2[i];
				res2 = i;
			}
		}
	}
	cout << res2 << " " << res1 << "\n";
  fastio::flush();
  return 0;
}