
// Problem: P6008 [USACO20JAN]Cave Paintings P
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6008
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

const int N = 1005;
const ll mod = 1e9 + 7;

int fa[N][N];
ll dp[N][N];

int main() {
	return 0;
}