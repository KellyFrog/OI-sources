
// Problem: P2178 [NOI2015] 品酒大会
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2178?contestId=41163
// Memory Limit: 500 MB
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

const int N = 3e5 + 5;
const ll inf = 1e18;

int n, m = 3e5;
int cnt[N], sa[N], rk[N], h[N];
pair<pair<int, int>, int> cur[N], tmp[N];
char S[N];
ll a[N];

void RSort() {
	memset(cnt, 0, sizeof cnt);
	per(i, 1, n) cnt[cur[i].fi.se]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.se]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	memset(cnt, 0, sizeof cnt);
	per(i, 1, n) cnt[cur[i].fi.fi]++;
	rep(i, 1, m) cnt[i] += cnt[i-1];
	per(i, 1, n) tmp[cnt[cur[i].fi.fi]--] = cur[i];
	rep(i, 1, n) cur[i] = tmp[i];
	
	int p = 1;
	rk[cur[1].se] = 1;
	rep(i, 2, n) {
		if(cur[i].fi != cur[i-1].fi) p++;
		rk[cur[i].se] = p;
	}
}

void SA() {
	rep(i, 1, n) rk[i] = S[i];
	for(int len = 1; len / 2 <= n; len <<= 1) {
		rep(i, 1, n) cur[i] = mp(mp(rk[i], rk[i+len]), i);
		RSort();
	}
	rep(i, 1, n) sa[rk[i]] = i;
}

void GetH() {
	int siz = 0;
	rep(i, 1, n) {
		if(siz >= 1) siz--;
		while(S[i+siz] == S[sa[rk[i]-1]+siz] && i+siz <= n && sa[rk[i]-1]+siz <= n) siz++;
		h[rk[i]] = siz;
	}
}

ll fa[N], siz[N], maxi[N], mini[N];
ll ans1, ans2 = -inf;

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

void Merge(int x, int y) {
	x = Find(x);
	y = Find(y);
	if(x == y) return;
	ans1 += siz[x] * siz[y];
	ans2 = max(ans2, mini[x] * mini[y]);
	ans2 = max(ans2, maxi[x] * maxi[y]);
	mini[x] = min(mini[x], mini[y]);
	maxi[x] = max(maxi[x], maxi[y]);
	siz[x] += siz[y];
	fa[y] = x;
}

pair<ll, ll> nd[N], res0[N];

int main() {
	scanf("%d%s", &n, S+1);
	rep(i, 1, n) scanf("%lld", &a[i]);
	SA();
	GetH();
	rep(i, 1, n) nd[i] = mp(h[i], i);
	rep(i, 1, n) mini[rk[i]] = maxi[rk[i]] = a[i];
	rep(i, 1, n) fa[i] = i, siz[i] = 1;
	sort(nd + 1, nd + 1 + n);
	int pt = n;
	per(p, 0, n-1) {
		//debug("solveing p={}\n", p);
		while(p <= nd[pt].fi && pt > 0) {
			int x = nd[pt--].se;
			//debug("merge {} {}\n", x, x-1);
			if(x == 1) continue;
			Merge(x, x-1);
		}
		debug("got ans= {} {}\n", ans1, ans2);
		res0[p] = mp(ans1, ans2 == -inf ? 0 : ans2);
	}
	rep(i, 0, n-1) printf("%lld %lld\n", res0[i].fi, res0[i].se);
	return 0;
}