
// Problem: CF427D Match &amp; Catch
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF427D?contestId=41161
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

string S, T;
int n, m;
int a[N], b[N], c[N], d[N], e[N];

void KMP(string s, int len, int* nxt) {
	nxt[0] = nxt[1] = 0;
	rep(i, 2, len) {
		int j = nxt[i-1];
		while(j && s[i] != s[j+1]) j = nxt[j];
		nxt[i] = s[i] == s[j+1] ? j+1 : 0;
	}
	debug("KMPed str='{}'\n", s);
	rep(i, 1, len) debug("{} ", nxt[i]); debug("\n");
}

int main() {
	cin >> S >> T;
	S = '*' + S;
	T = '*' + T;
	n = S.length()-1;
	m = T.length()-1;
	int ans = 5005;
	rep(i, 1, n) {		
		string suf = S.substr(i, n);
		string s0 = '*' + suf + '$' + S.substr(1, n) + '#' + T.substr(1, m);
		KMP(s0, s0.length()-1, a);
		memset(d, 0, sizeof d);
		memset(e, 0, sizeof e);
		int p1 = 1, p2 = suf.size();
		int p3 = p2+2;
		int p4 = p3+S.size()-2;
		int p5 = p4+2;
		int p6 = s0.size()-1;
		rep(j, p3, p4) d[a[j]]++;
		per(j, p3, p4) d[a[a[j]]] += d[a[j]];
		rep(j, p5, p6) e[a[j]]++;
		per(j, p5, p6) e[a[a[j]]] += e[a[j]];
		rep(i, 1, n) if(d[i] == 1 && e[i] == 1) ans = min(ans, i);
		
	}
	cout << (ans == 5005 ? -1 : ans) << "\n";
  return 0;
}