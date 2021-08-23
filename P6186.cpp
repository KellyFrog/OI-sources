
// Problem: P6186 [NOI Online #1 提高组] 冒泡排序
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6186?contestId=42578
// Memory Limit: 250 MB
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

//维护prefix a

int n, m;
int a[N], b[N];

struct BIT {
	ll tree[N];
	
	int lowbit(int x) {
		return x & (-x);
	}
	
	void Add(int x, int p) {
		if(x == 0) return;
		for(rg int x0 = x; x0 <= n; x0 += lowbit(x0)) {
			tree[x0] += p;
		}
	}
	
	ll Sum(int x) {
		ll res = 0;
		for(rg int x0 = x; x0; x0 -= lowbit(x0)) res += tree[x0];
		return res;
	}
	
	ll Sum(int L, int R) {
		return Sum(R) - Sum(L-1);
	}
};

BIT t1, t2;
//- t1 -> *x
//t2 bubian

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(a[i]);
	rep(i, 1, n) {
		b[i] = t1.Sum(a[i], n);
		t1.Add(a[i], 1);
	}
	OK;
	memset(t1.tree, 0, sizeof t1.tree);
	rep(i, 1, n) {
		t1.Add(b[i], 1);
		t2.Add(b[i], b[i]);
	}
	rep(i, 1, m) {
		int op, x;
		fastio::qread(op, x);
		if(op == 1) {
			/*
			debug("-sss-\n");
			rep(i, 1, n) cerr << a[i] << " \n"[i == n];
			rep(i, 1, n) cerr << b[i] << " \n"[i == n];
			rep(i, 1, n) cerr << t1.Sum(i, i) << " \n"[i == n];
			rep(i, 1, n) cerr << t2.Sum(i, i) << " \n"[i == n];
			debug("--\n");
			*/
			
			t1.Add(b[x], -1);
			t2.Add(b[x], -b[x]);
			t1.Add(b[x+1], -1);
			t2.Add(b[x+1], -b[x+1]);
			
			if(a[x] < a[x+1]) b[x]++;
			else b[x+1]--;
			swap(a[x], a[x+1]);
			swap(b[x], b[x+1]);
			
			t1.Add(b[x], 1);
			t2.Add(b[x], b[x]);
			t1.Add(b[x+1], 1);
			t2.Add(b[x+1], b[x+1]);
			/*
			debug("-s-\n");
			rep(i, 1, n) cerr << a[i] << " \n"[i == n];
			rep(i, 1, n) cerr << b[i] << " \n"[i == n];
			rep(i, 1, n) cerr << t1.Sum(i, i) << " \n"[i == n];
			rep(i, 1, n) cerr << t2.Sum(i, i) << " \n"[i == n];
			debug("--\n");
			*/
		} else {
			if(x >= n) {
				fastio::qwrite(0, '\n');
				continue;
			}
			debug("{} {}\n", t2.Sum(x+1, n), t1.Sum(x+1, n));
			fastio::qwrite(t2.Sum(x+1, n) - 1ll * t1.Sum(x+1, n) * x, '\n');
		}
	}
  fastio::flush();
  return 0;
}