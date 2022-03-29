
// Problem: P5479 [BJOI2015]隐身��?
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P5479?contestId=41163
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

#define OK debug("OK!\n")

const int N = 1e5 + 5;

char S[N];
int sa[N], rk[N], h[N], cnt[N];
int n, m = 1e5;
pair<pair<int, int>, int> cur[N], tmp[N];
int st[20][N];

void RSort() {
  memset(cnt, 0, sizeof cnt);
  rep(i, 1, n) cnt[cur[i].fi.se]++;
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  per(i, 1, n) tmp[cnt[cur[i].fi.se]--] = cur[i];
  rep(i, 1, n) cur[i] = tmp[i];

  memset(cnt, 0, sizeof cnt);
  rep(i, 1, n) cnt[cur[i].fi.fi]++;
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  per(i, 1, n) tmp[cnt[cur[i].fi.fi]--] = cur[i];
  rep(i, 1, n) cur[i] = tmp[i];

  int p = 1;
  rk[cur[1].se] = 1;
  rep(i, 2, n) {
    if (cur[i].fi != cur[i - 1].fi) p++;
    rk[cur[i].se] = p;
  }
}

void SA() {
  rep(i, 1, n) rk[i] = S[i];
  for (int len = 1; len / 2 <= n; len <<= 1) {
    rep(i, 1, n) { cur[i] = mp(mp(rk[i], rk[i + len]), i); }
    RSort();
  }
  rep(i, 1, n) sa[rk[i]] = i;
}

void GetH() {
  int p = 0;
  rep(i, 1, n) {
    if (p > 0) p--;
    while (S[i + p] == S[sa[rk[i] - 1] + p] && i + p <= n &&
           sa[rk[i] - 1] + p <= n)
      p++;
    h[rk[i]] = p;
  }

  rep(i, 1, n) st[0][i] = h[i];
  rep(j, 1, 19) {
    for (rg int i = 1; i + (1 << j - 1) <= n; i++) {
      st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << j - 1)]);
    }
  }
}

int Query(int l, int r) {
  int lg = log2(r - l + 1);
  return min(st[lg][l], st[lg][r - (1 << lg) + 1]);
}

int LCP(int l, int r) {
	l = rk[l], r = rk[r];
	if(l > r) swap(l, r);
	return Query(l+1, r);
}

int k, n1, n2;
char S1[N], S2[N];
int ans;
bool vis[N];
int L, R;

//i S1   j S2
void Dfs(int i, int j, int x) {
	debug("dfs={} {} {}\n", i, j, x);
	int lcp = LCP(i+1, j+1);
	debug("{} {} got lcp={}\n", i+1, j+1, lcp);
	i += lcp;
	j += lcp;
	if(j == n1) {
		rep(k, i-x, i+x) vis[k] = 1;
		L = min(L, i-x);
		R = max(R, i+x);
		return;
	}
	if(x == 0) return;
	Dfs(i+1, j, x-1);
	Dfs(i, j+1, x-1);
	Dfs(i+1, j+1, x-1);
}

int main() {
  scanf("%d", &k);
  scanf("%s%s", S1 + 1, S2 + 1);
  n1 = strlen(S1 + 1);
  n2 = strlen(S2 + 1);
  rep(i, 1, n1) S[i] = S1[i];
  rep(i, 1, n2) S[i + n1 + 1] = S2[i];
  S[n1 + 1] = '$';
  n = n1 + n2 + 1;
  SA();
  GetH();
  rep(i, 1, n) {
		debug("[{}]  rk={} h={} sa={} : {}\n", i, rk[i], h[i], sa[i], S+sa[i]);
	}
  rep(i, n1 + 2, n1 + n2 + 1) {
  	debug("solve={}\n", i);
  	L = n+1;
  	R = -1;
  	Dfs(i-1, 0, k);
  	rep(j, L, R) {
  		if(vis[j]) ans++;
  		vis[j] = 0;
  	}
  }
  cout << ans << "\n";
  return 0;
}