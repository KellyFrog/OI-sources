
// Problem: T169427 开锁
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T169427?contestId=41458
// Memory Limit: 500 MB
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
const int B = 1 << 5;
const int C = 30;

vector<int> adj[N];
pair<string, int> pat[N], mat[N];
int n, m, k;
int ind[N];

int main() {
	cin >> n >> m >> k;
	rep(i, 1, n) {
		cin >> pat[i].fi; pat[i].se = i;
	}
	sort(pat + 1, pat + 1 + n);
	rep(i, 1, m) {
		cin >> mat[i].fi;
	}
	rep(i, 1, m) cin >> mat[i].se;
	rep(i, 1, m) {
		string cur = "";
		rep(j, 1, k) cur += '_';
		rep(base, 0, (1 << k) - 1) {
			rep(j, 0, k-1) {
				if(((base >> j) & 1) == 0) cur[j] = mat[i].fi[j];
				else cur[j] = '_';
			}
			auto pt = lower_bound(pat + 1, pat + 1 + n, mp(cur, 0));
			if(cur == (*pt).fi && mat[i].se != (*pt).se) {
				adj[mat[i].se].pb((*pt).se);
				ind[(*pt).se]++;
			}
		}
	}
	priority_queue<int, vector<int>, greater<int> > q;
	rep(i, 1, n) if(!ind[i]) q.push(i);
	while(!q.empty()) {
		int u = q.top(); q.pop();
		cout << u << " ";
		for(int v : adj[u]) {
			if(--ind[v] == 0) q.push(v);
		}
	}
	return 0;
}