
// Problem: CF1418G Three Occurrences
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1418G?contestId=43655
// Memory Limit: 500 MB
// Time Limit: 5000 ms
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

int lazy[N << 2], mx[N << 2], cnt[N << 2];
int n, a[N];
vector<int> pos[N];

inline void Lazy(int cur, int x) {
	lazy[cur] += x;
	mx[cur] += x;
}

inline void PushDown(int cur) {
	if(lazy[cur]) {
		Lazy(cur << 1, lazy[cur]);
		Lazy(cur << 1 | 1, lazy[cur]);
		lazy[cur] = 0;
	}
}

inline void PushUp(int cur) {
	if(mx[cur << 1] > mx[cur << 1 | 1]) mx[cur] = mx[cur << 1], cnt[cur] = cnt[cur << 1];
	else if(mx[cur << 1] < mx[cur << 1 | 1]) mx[cur] = mx[cur << 1 | 1], cnt[cur] = cnt[cur << 1 | 1];
	else mx[cur] = mx[cur << 1], cnt[cur] = cnt[cur << 1] + cnt[cur << 1 | 1];
}

inline void Add(int cur, int ql, int qr, int x, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Add(cur << 1, ql, qr, x, l, mid);
	if(mid < qr) Add(cur << 1 | 1, ql, qr, x, mid + 1, r);
	PushUp(cur);
}

inline int Max(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return mx[cur];
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res = max(res, Max(cur << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, Max(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

inline int Count(int cur, int ql, int qr, int val, int l, int r) {
	if(ql <= l && r <= qr) return mx[cur] == val ? cnt[cur] : 0;
	PushDown(cur);
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res += Count(cur << 1, ql, qr, val, l, mid);
	if(mid < qr) res += Count(cur << 1 | 1, ql, qr, val, mid + 1, r);
	return res;
}

inline void Build(int cur, int l, int r) {
	if(l == r) return mx[cur] = l, cnt[cur] = 1, void();
	rg int mid = l + r >> 1;
	Build(cur << 1, l, mid);
	Build(cur << 1 | 1, mid + 1, r);
	PushUp(cur);
}

int main() {
	fastio::qread(n);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n) pos[i].pb(0);
	Build(1, 1, n);
	ll ans = 0;
	rep(R, 1, n) {
		if(pos[a[R]].size() >= 2) {
			int last = pos[a[R]][(int)pos[R].size()-2] + 1;
			int blast = pos[a[R]][(int)pos[R].size()-1];
			debug("get {} {}\n", last, blast);
			if(pos[a[R]].size() >= 3) {
				int llast = pos[a[R]][(int)pos[R].size()-3];
				Add(1, llast, last-1, -3, 1, n);
				debug("[-3] = {} {}, i={}\n", llast, last-1, R);
			}
			Add(1, last, blast, 3, 1, n);
			debug("[-3] = {} {}, i={}\n", blast, last, R);
			int maxi = mx[1];
			if(maxi == R) {
				ans += cnt[1];
			}
		}
		pos[a[R]].pb(R);
		OK;
	}
	cout << ans << "\n";
  fastio::flush();
  return 0;
}