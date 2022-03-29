
// Problem: P4254 [JSOI2008]Blue Mary开公司
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P4254?contestId=43655
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

const int N = 2e5 + 5;

struct Line {
	double k, b; //y=kx+b
};

Line line[N];
int tree[N << 2];
int n;

inline double Calc(int id, int x) {
	return (x-1) * line[id].k + line[id].b;
}

inline void Modify(int cur, int l, int r, int x) {
	if(Calc(x, l) >= Calc(tree[cur], l) && Calc(x, r) >= Calc(tree[cur], r)) return tree[cur] = x, void();
	if(Calc(x, l) <= Calc(tree[cur], l) && Calc(x, r) <= Calc(tree[cur], r)) return;
	rg int mid = l + r >> 1;
	if(line[x].k > line[tree[cur]].k) {
		if(Calc(x, mid) >= Calc(tree[cur], mid)) Modify(cur << 1, l, mid, tree[cur]), tree[cur] = x;
		else Modify(cur << 1 | 1, mid + 1, r, x);
	} else {
		if(Calc(x, mid) >= Calc(tree[cur], mid)) Modify(cur << 1 | 1, mid + 1, r, tree[cur]), tree[cur] = x;
		else Modify(cur << 1, l, mid, x);
	}
}

inline double Query(int cur, int x, int l, int r) {
	if(l == r) return Calc(tree[cur], x);
	rg int mid = l + r >> 1;
	if(x <= mid) return max(Calc(tree[cur], x), Query(cur << 1, x, l, mid));
	else return max(Calc(tree[cur], x), Query(cur << 1 | 1, x, mid + 1, r));
}

int main() {
	scanf("%d", &n);
	int cnt = 0;
	int n0 = 5e4;
	while(n--) {
		static char op[15];
		scanf("%s", op);
		if(op[0] == 'P') {
			cnt++;
			scanf("%lf%lf", &line[cnt].b, &line[cnt].k);
			Modify(1, 1, n0, cnt);
		} else {
			int x;
			scanf("%d", &x);
			printf("%d\n", (int)(Query(1, x, 1, n0) / 100));
		}
	}
  fastio::flush();
  return 0;
}