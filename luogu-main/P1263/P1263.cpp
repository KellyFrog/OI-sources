
// Problem: P1263 宫廷守卫
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1263
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

//点->左边第一个墙，上边第一个墙连边
//O(n^2m^2)

const int N = 5e2 + 5;
const int NN = N * N;

int a[N][N];
int n, m;
int id[N][N], idx[NN], idy[NN], tot;
vector<int> adj[NN];
int vis[NN], match[NN];

bool Dfs(int u) {
	if(vis[u]) return 0;
	vis[u] = 1;
	for(int v : adj[u]) {
		if(!match[v]) {
			match[v] = u;
			return 1;
		} else if(Dfs(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int main() {
	cin >> n >> m;
	rep(i, 0, n) rep(j, 0, m) {
		tot++;
		id[i][j] = tot;
		idx[tot] = i;
		idy[tot] = j;
	}
	rep(i, 1, n) a[i][0] = 2;
	rep(i, 1, m) a[0][i] = 2;
	rep(i, 1, n) rep(j, 1, m) {
		cin >> a[i][j];
		if(a[i][j]) continue;
		int x1, y1, x2, y2;
		per(k, 0, i-1) {
			if(a[k][j] == 2) {
				x1 = k, y1 = j;
				break;
			}
		}
		per(k, 0, j-1) {
			if(a[i][k] == 2) {
				x2 = i, y2 = k;
				break;
			}
		}
		adj[id[x1][y1]].pb(id[x2][y2]);
		debug("{},{} -> {},{}\n", x1, y1, x2, y2);
	}
	vector<pair<int, int> > ans;
	rep(i, 0, n) rep(j, 0, m) {
		if(a[i][j] == 2) {
			memset(vis, 0, sizeof vis);
			Dfs(id[i][j]);
		}
	}
	rep(i, 0, n) rep(j, 0, m) {
		if(match[id[i][j]]) {
			ans.pb(mp(i, idy[match[id[i][j]]]));
		}
	}
	cout << ans.size() << "\n";
	for(auto x : ans) cout << x.fi << " " << x.se << "\n";
	return 0;
}