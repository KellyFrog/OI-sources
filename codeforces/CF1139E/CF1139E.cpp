
// Problem: CF1139E Maximize Mex
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1139E
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

const int N = 5e3 + 5;

vector<int> adj[N];
int match[N], vis[N], del[N];
int n, m, d;
int a[N], b[N], c[N], ans[N];

bool Dfs(int u) {
	if(u == 0) return 0;
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : adj[u]) {
		if(!match[v] || Dfs(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(a[i]), a[i]++;
	rep(i, 1, n) fastio::qread(b[i]);
	fastio::qread(d);
	rep(i, 1, d) {
		fastio::qread(c[i]);
		del[c[i]] = 1;
	}
	rep(i, 1, n) if(!del[i]) adj[a[i]].pb(b[i]);
	int p = 0;
	per(i, 1, d) {
		rep(j, p+1, n) {
			memset(vis, 0, sizeof vis);
			if(Dfs(j)) p++;
			else break;
		}
		ans[i] = p;
		adj[a[c[i]]].pb(b[c[i]]);
	}
	rep(i, 1, d) fastio::qwrite(ans[i], '\n');
	
  fastio::flush();
  return 0;
}