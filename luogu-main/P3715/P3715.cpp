
// Problem: P3715 [BJOI2017]魔法咒语
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3715
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
inline void qread(T1& x, T2&... ls) {
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

void debug(const char* s) { cerr << s; }
template <typename T1, typename... T2>
void debug(const char* s, const T1 x, T2... ls) {
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

const int L = 1e2 + 5;
const int N = 50;
const int mod = 1e9 + 7;

template <typename T>
inline void chkadd(T& x, T y) {
  x = x + y > mod ? x + y - mod : x + y;
}

template <typename T>
inline void chkadd(T& x, T y, T z) {
  x = y + z > mod ? y + z - mod : y + z;
}

template <typename T>
inline void chkmax(T& x, T y) {
  x = x > y ? x : y;
}

int son[L][27], fail[L], tot = 1;
int hasg[L], hasb[L];
int que[L], head = 1, tail = 0;

void Insert(const char* C, int len, int op) {
  int cur = 1;
  rep(i, 1, len) {
    if (!son[cur][C[i] - 'a' + 1]) son[cur][C[i] - 'a' + 1] = ++tot;
    debug("trie {} -> {}\n", cur, son[cur][C[i] - 'a' + 1]);
    cur = son[cur][C[i] - 'a' + 1];
  }
  if (op == 1)
    hasg[cur] = len;
  else
    debug("bad ends in {}\n", cur), hasb[cur] = 1;
}

void BuildAC() {
  fail[1] = 1;
  rep(i, 1, 26) {
    if (son[1][i]) {
      fail[son[1][i]] = 1;
      debug("fail {} = {}\n", son[1][i], 1);
      que[++tail] = son[1][i];
    } else {
    	son[1][i] = 1;
    }
  }
  while (head <= tail) {
    int cur = que[head++];
    rep(i, 1, 26) {
      if (son[cur][i]) {
        que[++tail] = son[cur][i];
        fail[son[cur][i]] = son[fail[cur]][i];
      } else {
        son[cur][i] = son[fail[cur]][i];
      }
    }
  }
  rep(i, 1, tot) {
    chkmax(hasg[i], hasg[fail[i]]);
    chkmax(hasb[i], hasb[fail[i]]);
  }
  rep(i, 1, tot) {
  	debug("AC node = {} fail={} bad={} good={} son: ", i, fail[i], hasb[i], hasg[i]);
  	rep(j, 1, 26) debug("{} ", son[i][j]);
  	debug("\n");
  }
}

int dp[L][L];
char S[L][L], tmp[L];
int len[L];
int n, m, l;

int Solve(const char* C, int st, int len) {
	int cur = st;
	bool ret = 1;
	rep(i, 1, len) {
		if(hasb[son[cur][C[i]-'a'+1]]) ret = 0;
		cur = son[cur][C[i] - 'a' + 1];
	}
	return ret == 0  ? -1 : cur;
}

void Solve1() {
	
  int ans = 0;
  dp[0][1] = 1;
  rep(i, 1, l) {
  	rep(j, 1, n) {
  		if(len[j] <= i) {
  			rep(k, 1, tot) {
  				int ed = Solve(S[j], k, len[j]);
  				if(ed != -1) chkadd(dp[i][ed], dp[i-len[j]][k]);
  			}
  		}
  	}
  }
  rep(i, 1, tot) chkadd(ans, dp[l][i]);
  cout << ans << "\n";
}

/*
 [dp[1]~dp[tot]]
 a[st][ed] = 1 | st可以到ed并且st在单词库里
*/

/*
 * [dp[1][1]~dp[1][tot] dp[2][1]~dp[2][tot]]
 *
*/

void Solve2() {
	
}

int main() {
  scanf("%d%d%d", &n, &m, &l);
  rep(i, 1, n) {
    scanf("%s", S[i] + 1);
    len[i] = strlen(S[i]+1);
  }
  rep(i, 1, m) {
    scanf("%s", tmp + 1);
    int len = strlen(tmp + 1);
    Insert(tmp, len, 0);
  }
  BuildAC();
  if(l <= 100) Solve1();
  else Solve2();
  return 0;
}