
// Problem: T107877 电梯调度[2019海淀区智慧杯初中组复赛T4]
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T107877?contestId=39107
// Memory Limit: 500 MB
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

const int N = 5005;
const ll inf = 1e18;

int n, m;
ll dp[2][N];
int s[N], t[N];
//dp[i][j] -> 第i次，第1辆在t[i-1]，第二辆在j，状压掉一维
//dp[i][j] = min(dp[i-1][j] + | t[i-1] - s[i] |

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) fastio::qread(s[i], t[i]);
	rep(i, 1, m) dp[1][i] = abs(s[1] - t[1]);
	rep(i, 2, n) {
		rep(j, 1, m) dp[i & 1][j] = abs(t[i-1] - s[i]) + abs(s[i] - t[i]) + dp[(i & 1) ^ 1][j];
		rep(j, 1, m) dp[i & 1][t[i-1]] = min(dp[i & 1][t[i-1]], dp[(i & 1) ^ 1][j] + abs(j - s[i]) + abs(s[i] - t[i]));
		//rep(j, 1, m) cerr << dp[i & 1][j] << " \n"[j == m];
	}
	ll ans = inf;
	rep(i, 1, m) ans = min(ans, dp[n & 1][i]);
	fastio::qwrite(ans, '\n');
	fastio::flush();
	return 0;
}