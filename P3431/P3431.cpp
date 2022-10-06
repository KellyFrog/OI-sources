
// Problem: P3431 [POI2005]AUT-The Bus
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3431
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

//Author: Chenkaifeng

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

#define rep(i, s, t) for(rg int i = s; i <= t; i++)
#define per(i, s, t) for(rg int i = t; i >= s; i--)
#define debug(x) cerr << (#x) << " = " << (x) << "\n"
#define OK cerr << "OK!\n"


namespace fastio {
  const int SIZE = (1 << 20) + 1;
  char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
  char _st[55];
  int _qr = 0;

  inline char getchar() {
    return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
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
    return ;
  }
  inline void putchar(char _x) {
    *oS++ = _x;
    if(oS == oT) flush();
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
}; //namespace fastio

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e5 + 5;

int tree[N << 1];
int a[N << 1];
int n, m;
pair<pair<int, int>, int> pos[N];

int lowbit(int x) {
	return x & (-x);
}

int query(int x) {
	int res = 0;
	for(rg int x0 = x; x0 > 0; x0 -= lowbit(x0)) res = max(res, tree[x0]);
	return res;
}

void modify(int x, int p) {
	for(rg int x0 = x; x0 <= 2 * n + 2; x0 += lowbit(x0)) tree[x0] = max(tree[x0], p);
}

int main() {
	int tmp;
	fastio::qread(tmp);
	fastio::qread(tmp);
	fastio::qread(n);
	rep(i, 1, n) {
		fastio::qread(pos[i].fi.fi, pos[i].fi.se, pos[i].se);
		a[i * 2 - 1] = pos[i].fi.fi;
		a[i * 2] = pos[i].fi.se;
	}
	sort(a + 1, a + 1 + 2 * n);
	m = unique(a + 1, a + 1 + 2 * n) - (a + 1);
	rep(i, 1, n) {
		pos[i].fi.fi = lower_bound(a + 1, a + 1 + m, pos[i].fi.fi) - a;
		pos[i].fi.se = lower_bound(a + 1, a + 1 + m, pos[i].fi.se) - a;
//		cerr << pos[i].fi.fi << " " << pos[i].fi.se << endl;
	}
	sort(pos + 1, pos + 1 + n);
	int ans = 0;
	rep(i, 1, n) {
		int x = query(pos[i].fi.se) + pos[i].se;
		ans = max(ans, x);
		modify(pos[i].fi.se, x);
	}
	fastio::qwrite(ans, '\n');
	fastio::flush();
	return 0;
}