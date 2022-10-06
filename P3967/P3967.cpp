
// Problem: P3967 [TJOI2014]匹配
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3967?contestId=41722
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

//枚举每个边

const int N = 85;
const int inf = 1e9;

int a[N][N];
//vector<int> adj[N];
int lx[N], ly[N], match[N];
bool visl[N], visr[N];
int delta;
int n;

bool Dfs(int u) {
	if(u == 0) return 0;
	if(visl[u]) return 0;
	visl[u] = 1;
	rep(v, 1, n) {
		if(lx[u] + ly[v] == a[u][v]) {
			visr[v] = 1;
			if(!match[v] || Dfs(match[v])) {
				match[v] = u;
				return 1;
			}
		} else {
			delta = min(delta, lx[u] + ly[v] - a[u][v]);
		}
	}
	return 0;
}

int KM() {
	debug("KM\n");
	memset(match, 0, sizeof match);
	rep(i, 1, n) {
		lx[i] = -inf;
		rep(v, 1, n) {
			lx[i] = max(lx[i], a[i][v]);
		}
		ly[i] = 0;
	}
	rep(i, 1, n) {
		while(1) {
			memset(visl, 0, sizeof visl);
			memset(visr, 0, sizeof visr);
			delta = inf;
			if(Dfs(i)) break;
			rep(j, 1, n) {
				if(visl[j]) lx[j] -= delta;
				if(visr[j]) ly[j] += delta;
			}
		}
	}
	int res = 0;
	rep(i, 1, n) res += lx[i] + ly[i];
	return res;
}

int res[N];

int main() {
	cin >> n;
	rep(i, 1, n) rep(j, 1, n) cin >> a[i][j];
	int mx = KM();
	cout << mx << "\n";
	rep(i, 1, n) res[i] = match[i], cerr << res[i] << " \n"[i == n];
	vector<pair<int, int> > ans;
	rep(i, 1, n) {
		int x = res[i], y = i;
		int z = a[x][y];
		debug("chaned={} {}\n", x, y);
		a[x][y] = -inf;
		if(KM() != mx) ans.pb(mp(x, y));
		a[x][y] = z;
	}
	sort(ans.begin(), ans.end());
	for(auto x : ans) cout << x.fi << " " << x.se << "\n";
  fastio::flush();
  return 0;
}