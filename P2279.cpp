
// Problem: P2279 [HNOI2003]消防局的设立
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2279
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

template<typename T>
inline void chkmin(T& x, T y) {
	x = x > y ? y : x;
}

const int N = 1e3 + 5;

int dp[N][4];
vector<int> adj[N];
int n, dep[N], fat[N], a[N];
int vis[N];
bool has[N];

inline void Dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for(int v : adj[u]) {
		if(v != fa) {
			Dfs(v, u);
		}
	}
}

void Solve(int x, int d, int id) {
	debug("solve = {} {} {}\n", x, d, id);
	vis[x] = id;
	if(abs(dep[x] - d) == 2) return;
	for(int v : adj[x]) {
		if(vis[v] != id) {
			//vis[v] = id;
			Solve(v, d, id);
		}
	}
}

int main() {
  fastio::qread(n);
  rep(i, 2, n) {
  	fastio::qread(fat[i]);
  	adj[i].pb(fat[i]);
  	adj[fat[i]].pb(i);
  }
  Dfs(1, 0);
  rep(i, 1, n) a[i] = i;
  sort(a + 1, a + 1 + n, [](const int& x, const int& y) {
  	return dep[x] < dep[y];
  });
  fat[1] = 1;
  int ans = 0;
  per(i, 1, n) {
  	if(vis[a[i]]) continue;
  	ans++;
  	Solve(fat[fat[a[i]]], dep[fat[fat[a[i]]]], fat[fat[a[i]]]);
  }
  cout << ans << "\n";
  fastio::flush();
  return 0;
}