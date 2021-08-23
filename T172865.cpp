
// Problem: T172865 子串问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T172865?contestId=42491
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

const ll mod = 1234567891;
const int N = 2e5 + 5;
const int base = 131;

int cnt1[27], cnt2[27];
bool match[N];
ll hs[N], po[N];
map<ll, ll> vis;
int n, m;

template <typename T>
inline void chkadd(T& x, T y) {
  x = x + y > mod ? x + y - mod : x + y;
}

template <typename T>
inline void chkadd(T& x, T y, T z) {
  x = y + z > mod ? y + z - mod : y + z;
}

template <typename T>
inline void chkmins(T& x, T y) {
  x = x - y < 0 ? x - y + mod : x - y;
}

template <typename T>
inline void chkmins(T& x, T y, T z) {
  x = y - z < 0 ? y - z + mod : y - z;
}

template <typename T>
inline T getmins(T x, T y) {
  return x - y < 0 ? x - y + mod : x - y;
}

char S[N], T[N];

inline ll gethash(int L, int R) {
  return getmins(hs[R], hs[L - 1] * po[R - L + 1] % mod);
}

int main() {
  scanf("%s%s", S + 1, T + 1);
  n = strlen(S + 1);
  m = strlen(T + 1);
  po[0] = 1;
  rep(i, 1, m) po[i] = po[i - 1] * base % mod;
  rep(i, 1, m) hs[i] = (hs[i - 1] * base + T[i] - 'a') % mod;
  int need = 0;
  rep(i, 1, n) {
  	if(cnt1[S[i] - 'a' + 1] == 0)	need++;
  	cnt1[S[i] - 'a' + 1]++;
  }
  rep(i, 1, m) {
    cnt2[T[i] - 'a' + 1]++;
    if (cnt2[T[i] - 'a' + 1] - 1 == cnt1[T[i] - 'a' + 1])
      need++;
    else if (cnt2[T[i] - 'a' + 1] == cnt1[T[i] - 'a' + 1])
      need--;
    if (i > n) {
      cnt2[T[i - n] - 'a' + 1]--;
      if (cnt2[T[i - n] - 'a' + 1] + 1 == cnt1[T[i - n] - 'a' + 1])
        need++;
      else if (cnt2[T[i - n] - 'a' + 1] == cnt1[T[i - n] - 'a' + 1])
        need--;
    }
    if(need == 0) {
    	vis[gethash(i-n+1, i)] = 1;
    	debug("matched {} {}\n", i-n+1, i);
    }
  }
  int ans = 0;
  for(auto x : vis) if(x.se) ans++;
  cout << ans << "\n";
  fastio::flush();
  return 0;
}