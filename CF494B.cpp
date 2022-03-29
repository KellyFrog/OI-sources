
// Problem: CF494B Obsessive String
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF494B?contestId=41161
// Memory Limit: 250 MB
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

const int N = 1e5 + 5;
const ll mod = 1e9 + 7;

char S[N], T[N];
int n, m;
ll dp[N];
int pos[N], nxt[N];
ll sum1[N], sum2[N];

void KMP() {
	rep(i, 2, m) {
		int j = nxt[i-1];
		while(j && T[j+1] != T[i]) j = nxt[j];
		nxt[i] = T[j+1] == T[i] ? j+1 : 0;
	}
	int mj = 0;
	rep(i, 1, n) {
		while(mj && S[i] != T[mj+1]) mj = nxt[mj];
		mj = S[i] == T[mj+1] ? mj+1 : 0;
		if(mj == m) {
			pos[i] = i-m+1;
			mj = nxt[mj];
		} else {
			pos[i] = pos[i-1];
		}
	}
}

int main() {
	scanf("%s%s", S + 1, T + 1);
	n = strlen(S + 1);
	m = strlen(T + 1);
	KMP();
	sum1[0] = sum2[0] = dp[0] = 1;
	rep(i, 1, n) {
		rep(j, pos[i-1]+1, pos[i]-1) sum2[j] = (sum2[j-1] + sum1[j]) % mod;
		dp[i] = (pos[i]-1 == -1 ? 0 : sum2[pos[i]-1]) % mod;
		sum1[i] = (sum1[i-1] + dp[i]) % mod;
		if(pos[i] > 0) sum2[pos[i]] = (sum2[pos[i]-1] + sum1[pos[i]]) % mod;
		debug("dp[{}]={} {}\n", i, dp[i], pos[i]);
		rep(i, 1, n) debug("sum[{}]={},{}\n", i, sum1[i], sum2[i]);
	}
	ll ans = 0;
	rep(i, 1, n) ans = (ans + dp[i]) % mod;
	cout << ans << "\n";
  return 0;
}