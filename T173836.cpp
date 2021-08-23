
// Problem: T173836 摘桃子
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T173836?contestId=42819
// Memory Limit: 500 MB
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

const int N = 1e5 + 5;
const int S = 500;

vector<int> adj[N];
int a[N], n, m;
int siz[N], tmp[S], dp[N][S]; //i子树，选了j个的最小花费
int s = 450;

ll qpow(ll x, ll p, ll mod) {
  rg ll base = x, res = 1;
  while (p) {
    if (p & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    p >>= 1;
  }
  return res;
}

void Dfs(int u, int f) {
	dp[u][1] = a[u];
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v == f) continue;
		Dfs(v, u);
		memset(tmp, 0x3f, sizeof tmp);
		rep(j, 1, min(s, siz[v])) {
			rep(k, 1, min(s, siz[u])) {
				if(j+k>s) continue;
				tmp[j+k] = min(tmp[j+k], dp[u][k] + dp[v][j]);
			}
		}
		rep(j, 1, s) dp[u][j] = min(dp[u][j], tmp[j]);
		siz[u] += siz[v];
	}
}

signed main() {
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n-1) {
		int u, v;
		fastio::qread(u, v);
		adj[u].pb(v);
		adj[v].pb(u);
	}
	memset(dp, 0x3f, sizeof dp);
	Dfs(1, 0);
	int ans = 0;
	rep(i, 1, n) rep(j, 1, s) if(dp[i][j] <= m) ans = max(ans, j);
	cout << ans << "\n";
  fastio::flush();
  return 0;
}