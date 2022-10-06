
// Problem: P3486 [POI2009]KON-Ticket Inspector
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3486
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

#define rep(i, sum, t) for(rg int i = sum; i <= t; i++)
#define per(i, sum, t) for(rg int i = t; i >= sum; i--)
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

const int N = 1005 + 5;

ll a[N][N], sum[N][N];
ll dp[N][N];
int last[N][N];
int n, k;

ll get(int x1, int y1, int x2, int y2) {
	return sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
}

int main(){
	fastio::qread(n, k);
	rep(i, 1, n) rep(j, i+1, n) fastio::qread(a[i][j]);
	rep(i, 1, n) rep(j, 1, n) sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i][j];
	rep(i, 1, n) rep(j, 1, k) rep(p, j-1, i-1) {
		if(get(p + 1, i + 1, i, n) + dp[p][j-1] > dp[i][j]) {
			last[i][j] = p;
			dp[i][j] = get(p + 1, i + 1, i, n) + dp[p][j-1];
		}
	}
	int p = 0;
	rep(i, 1, n) if(dp[i][k] > dp[p][k]) p = i;
	vector<int> ans;
	int x = p, y = k;
	while(x && y) {
		ans.pb(x);
		x = last[x][y--];
	}
	per(i, 0, ans.size() - 1) fastio::qwrite(ans[i], " \n"[i == 0]);
	fastio::flush();
	return 0;
}