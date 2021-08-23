
// Problem: T173835 跳格子
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T173835?contestId=42819
// Memory Limit: 500 MB
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
const int M = 25;
const int inf = 0x3f3f3f3f;

int dist[N][M]; //在i，做传了j次
deque<pair<int, int> > q;
int n, m, k;
int a[N];

void Update(int x, int y, int w, int d) {
	if(x < 1 || x > n || y < 0 || y > k) return;
	
	if(w == 1) {
		dist[x][y] = d + 1;
		q.push_back(mp(x, y));
	} else {
		dist[x][y] = d;
		q.push_front(mp(x, y));
	}
}

int main() {
	fastio::qread(n, m, k);
	rep(i, 1, n) fastio::qread(a[i]);
	memset(dist, 0x3f, sizeof dist);
	dist[1][0] = 0;
	q.push_back(mp(1, 0));
	while(!q.empty()) {
		int x = q.front().fi, y = q.front().se;
		q.pop_front();
		rep(i, max(1, x-m), min(n, x+m)) {
			if(dist[x][y] + 1 < dist[i][y]) {
				Update(i, y, 1, dist[x][y]);
			}
		}
		if(a[x] && dist[a[x]][y+1] > dist[x][y]) Update(a[x], y+1, 0, dist[x][y]);
	}
	int ans = inf;
	rep(i, 0, k) ans = min(ans, dist[n][i]);
	cout << ans << "\n";
  fastio::flush();
  return 0;
}