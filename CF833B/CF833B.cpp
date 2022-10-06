
// Problem: CF833B The Bakery
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF833B
// Memory Limit: 250 MB
// Time Limit: 2500 ms
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

const int N = 3.5e5 + 5;
const int K = 55;

int maxi[N << 2], lazy[N << 2];
int dp[N][K];
int a[N], pre[N];
int pos[N];
int n, k;

void Lazy(int cur, int x) {
	maxi[cur] += x;
	lazy[cur] += x;
}

void PushDown(int cur) {
	Lazy(cur << 1, lazy[cur]);
	Lazy(cur << 1 | 1, lazy[cur]);
	lazy[cur] = 0;
}

void PushUp(int cur) {
	maxi[cur] = max(maxi[cur << 1], maxi[cur << 1 | 1]);
}

void Build(int cur, int l, int r, int tim) {
	lazy[cur] = 0;
	maxi[cur] = 0;
	if(l == r) return maxi[cur] = dp[l][tim], void();
	rg int mid = l + r >> 1;
	Build(cur << 1, l, mid, tim);
	Build(cur << 1 | 1, mid + 1, r, tim);
	PushUp(cur);
}

int Query(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return maxi[cur];
	PushDown(cur);
	rg int mid = l + r >> 1, res = 0;
	if(ql <= mid) res = max(res, Query(cur << 1, ql, qr, l, mid));
	if(mid < qr) res = max(res, Query(cur << 1 | 1, ql, qr, mid + 1, r));
	return res;
}

void Modify(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return Lazy(cur, 1), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Modify(cur << 1, ql, qr, l, mid);
	if(mid < qr) Modify(cur << 1 | 1, ql, qr, mid + 1, r);
	PushUp(cur);
}

int main() {
	fastio::qread(n, k);
	rep(i, 1, n) fastio::qread(a[i]), pre[i] = pos[a[i]], pos[a[i]] = i;
	rep(i, 1, k) {
		Build(1, 0, n, i-1);
		//cerr << "round " << i << " =";
		rep(j, i, n) {
			Modify(1, pre[j], j-1, 0, n);
			dp[j][i] = Query(1, 0, j-1, 0, n);
		}
	}
	fastio::qwrite(dp[n][k], '\n');
	fastio::flush();
	return 0;
}