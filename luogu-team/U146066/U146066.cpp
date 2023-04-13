// Author: Chenkaifeng

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
//#define debug(x) cerr << (#x) << " = " << (x) << "\n"
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
  while (p) {
    if (p & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    p >>= 1;
  }
  return res;
}

const int N = 3e5 + 5;
const ll mod = 998244353;

struct Matrix {
  ll a[4][4];
  bool unit;
  void clear() {
    memset(a, 0, sizeof a);
  }
};

/*
  1 1 0
  0 1 0
  0 0 1

  1 0 0
  0 1 1
  0 0 1

  1 0 0
  0 1 0
  1 0 1

  +[v 0 0]

  1 0 0
  0 v 0
  0 0 1

  1 0 0
  0 1 0
  0 0 0

  +[0 0 v]
*/

template<typename T>
void chkadd(T& x, T y) {
  x = x + y > 2 * mod ? (x + y) % mod : x + y >= mod ? x + y - mod : x + y;
}

template<typename T>
void chkadd(T& x, T y, T z) {
  x = y + z >= mod ? y + z - mod : y + z;
}

Matrix unt, op1[10];
Matrix tmp1, tmp2, tmp3, tmp4;

int n, m;
Matrix sum[N << 2], lazy[N << 2], add[N << 2];
int a[N], b[N], c[N];
ll resa, resb, resc;

void PushUp(int cur) {
  chkadd(sum[cur].a[1][1], sum[cur << 1].a[1][1], sum[cur << 1 | 1].a[1][1]);
  chkadd(sum[cur].a[1][2], sum[cur << 1].a[1][2], sum[cur << 1 | 1].a[1][2]);
  chkadd(sum[cur].a[1][3], sum[cur << 1].a[1][3], sum[cur << 1 | 1].a[1][3]);
}

void LazyMul(int cur, const Matrix& x) {
  lazy[cur].unit = 0;
  tmp2 = sum[cur];
  tmp3 = lazy[cur];
  tmp4 = add[cur];
  
  sum[cur].a[1][1] = (tmp2.a[1][1] * x.a[1][1] + tmp2.a[1][2] * x.a[2][1] + tmp2.a[1][3] * x.a[3][1]) % mod;
  sum[cur].a[1][2] = (tmp2.a[1][1] * x.a[1][2] + tmp2.a[1][2] * x.a[2][2] + tmp2.a[1][3] * x.a[3][2]) % mod;
  sum[cur].a[1][3] = (tmp2.a[1][1] * x.a[1][3] + tmp2.a[1][2] * x.a[2][3] + tmp2.a[1][3] * x.a[3][3]) % mod;
  
  lazy[cur].a[1][1] = (tmp3.a[1][1] * x.a[1][1] + tmp3.a[1][2] * x.a[2][1] + tmp3.a[1][3] * x.a[3][1]) % mod;
  lazy[cur].a[1][2] = (tmp3.a[1][1] * x.a[1][2] + tmp3.a[1][2] * x.a[2][2] + tmp3.a[1][3] * x.a[3][2]) % mod;
  lazy[cur].a[1][3] = (tmp3.a[1][1] * x.a[1][3] + tmp3.a[1][2] * x.a[2][3] + tmp3.a[1][3] * x.a[3][3]) % mod;
  lazy[cur].a[2][1] = (tmp3.a[2][1] * x.a[1][1] + tmp3.a[2][2] * x.a[2][1] + tmp3.a[2][3] * x.a[3][1]) % mod;
  lazy[cur].a[2][2] = (tmp3.a[2][1] * x.a[1][2] + tmp3.a[2][2] * x.a[2][2] + tmp3.a[2][3] * x.a[3][2]) % mod;
  lazy[cur].a[2][3] = (tmp3.a[2][1] * x.a[1][3] + tmp3.a[2][2] * x.a[2][3] + tmp3.a[2][3] * x.a[3][3]) % mod;
  lazy[cur].a[3][1] = (tmp3.a[3][1] * x.a[1][1] + tmp3.a[3][2] * x.a[2][1] + tmp3.a[3][3] * x.a[3][1]) % mod;
  lazy[cur].a[3][2] = (tmp3.a[3][1] * x.a[1][2] + tmp3.a[3][2] * x.a[2][2] + tmp3.a[3][3] * x.a[3][2]) % mod;
  lazy[cur].a[3][3] = (tmp3.a[3][1] * x.a[1][3] + tmp3.a[3][2] * x.a[2][3] + tmp3.a[3][3] * x.a[3][3]) % mod;
  
  add[cur].a[1][1] = (tmp4.a[1][1] * x.a[1][1] + tmp4.a[1][2] * x.a[2][1] + tmp4.a[1][3] * x.a[3][1]) % mod;
  add[cur].a[1][2] = (tmp4.a[1][1] * x.a[1][2] + tmp4.a[1][2] * x.a[2][2] + tmp4.a[1][3] * x.a[3][2]) % mod;
  add[cur].a[1][3] = (tmp4.a[1][1] * x.a[1][3] + tmp4.a[1][2] * x.a[2][3] + tmp4.a[1][3] * x.a[3][3]) % mod;
}

void LazyAdd(int cur, const Matrix& x, int l, int r) {
  chkadd(sum[cur].a[1][1], x.a[1][1] * (r - l + 1));
  chkadd(sum[cur].a[1][2], x.a[1][2] * (r - l + 1));
  chkadd(sum[cur].a[1][3], x.a[1][3] * (r - l + 1));
  chkadd(add[cur].a[1][1], x.a[1][1]);
  chkadd(add[cur].a[1][2], x.a[1][2]);
  chkadd(add[cur].a[1][3], x.a[1][3]);
}

void PushDown(int cur, int l, int r) {
  rg int mid = l + r >> 1;

  if(!lazy[cur].unit) {
    LazyMul(cur << 1, lazy[cur]);
    LazyMul(cur << 1 | 1, lazy[cur]);
  
    memset(lazy[cur].a, 0, sizeof lazy[cur].a);
  
    lazy[cur].a[1][1] = 1;
    lazy[cur].a[2][2] = 1;
    lazy[cur].a[3][3] = 1;

    lazy[cur].unit = 1;
  }
  
  chkadd(sum[cur << 1].a[1][1], add[cur].a[1][1] * (mid - l + 1));
  chkadd(sum[cur << 1].a[1][2], add[cur].a[1][2] * (mid - l + 1));
  chkadd(sum[cur << 1].a[1][3], add[cur].a[1][3] * (mid - l + 1));
  chkadd(add[cur << 1].a[1][1], add[cur].a[1][1]);
  chkadd(add[cur << 1].a[1][2], add[cur].a[1][2]);
  chkadd(add[cur << 1].a[1][3], add[cur].a[1][3]);
  
  chkadd(sum[cur << 1 | 1].a[1][1], add[cur].a[1][1] * (r - mid));
  chkadd(sum[cur << 1 | 1].a[1][2], add[cur].a[1][2] * (r - mid));
  chkadd(sum[cur << 1 | 1].a[1][3], add[cur].a[1][3] * (r - mid));
  chkadd(add[cur << 1 | 1].a[1][1], add[cur].a[1][1]);
  chkadd(add[cur << 1 | 1].a[1][2], add[cur].a[1][2]);
  chkadd(add[cur << 1 | 1].a[1][3], add[cur].a[1][3]);
  
  add[cur].a[1][1] = 0;
  add[cur].a[1][2] = 0;
  add[cur].a[1][3] = 0;
}

void Build(int cur, int l, int r) {
  lazy[cur].a[1][1] = 1;
  lazy[cur].a[2][2] = 1;
  lazy[cur].a[3][3] = 1;
  lazy[cur].unit = 1;
  if(l == r) {
    sum[cur].a[1][1] = a[l];
    sum[cur].a[1][2] = b[l];
    sum[cur].a[1][3] = c[l];
    return;
  }
  rg int mid = l + r >> 1;
  Build(cur << 1, l, mid);
  Build(cur << 1 | 1, mid + 1, r);
  PushUp(cur);
}

void Sum(int cur, int ql, int qr, int l, int r) {
  if(ql <= l && r <= qr) return chkadd(resa, sum[cur].a[1][1]), chkadd(resb, sum[cur].a[1][2]), chkadd(resc, sum[cur].a[1][3]), void();
  PushDown(cur, l, r);
  rg int mid = l + r >> 1;
  if(ql <= mid) Sum(cur << 1, ql, qr, l, mid);
  if(mid < qr) Sum(cur << 1 | 1, ql, qr, mid + 1, r);
}

void Mul(int cur, int ql, int qr, int l, int r, const Matrix& x) {
  if(ql <= l && r <= qr) return LazyMul(cur, x), void();
  PushDown(cur, l, r);
  rg int mid = l + r >> 1;
  if(ql <= mid) Mul(cur << 1, ql, qr, l, mid, x);
  if(mid < qr) Mul(cur << 1 | 1, ql, qr, mid + 1, r, x);
  PushUp(cur);
}

void Add(int cur, int ql, int qr, int l, int r, const Matrix& x) {
  if(ql <= l && r <= qr) return LazyAdd(cur, x, l, r), void();
  PushDown(cur, l, r);
  rg int mid = l + r >> 1;
  if(ql <= mid) Add(cur << 1, ql, qr, l, mid, x);
  if(mid < qr) Add(cur << 1 | 1, ql, qr, mid + 1, r, x);
  PushUp(cur);
}
int main() {
  clock_t s = clock();
  unt.a[1][1] = unt.a[2][2] = unt.a[3][3] = 1;
  op1[1].a[1][1] = op1[1].a[2][1] = op1[1].a[2][2] = op1[1].a[3][3] = 1;
  op1[2].a[1][1] = op1[2].a[2][2] = op1[2].a[3][2] = op1[2].a[3][3] = 1;
  op1[3].a[1][1] = op1[3].a[2][2] = op1[3].a[1][3] = op1[3].a[3][3] = 1;
  fastio::qread(n, m);
  rep(i, 1, n) fastio::qread(a[i]);
  rep(i, 1, n) fastio::qread(b[i]);
  rep(i, 1, n) fastio::qread(c[i]);
  Build(1, 1, n);
  rep(i, 1, m) {
    rg int op, l, r, x;
    fastio::qread(op, l, r);
    if(op <= 3) Mul(1, l, r, 1, n, op1[op]);
    else if(op == 4) {
      fastio::qread(x);
      tmp1.a[1][1] = x;
      Add(1, l, r, 1, n, tmp1);
      tmp1.a[1][1] = 0;
    }
    else if(op == 5) {
      fastio::qread(x);
      tmp1.a[1][1] = 1;
      tmp1.a[3][3] = 1;
      tmp1.a[2][2] = x;
      Mul(1, l, r, 1, n, tmp1);
      tmp1.a[1][1] = 0;
      tmp1.a[2][2] = 0;
      tmp1.a[3][3] = 0;
    }
    else if(op == 6) {
      fastio::qread(x);
      tmp1.a[1][1] = 1;
      tmp1.a[2][2] = 1;
      Mul(1, l, r, 1, n, tmp1);
      tmp1.a[1][1] = 0;
      tmp1.a[2][2] = 0;
      tmp1.a[1][3] = x;
      Add(1, l, r, 1, n, tmp1);
      tmp1.a[1][3] = 0;
    }
    else {
      resa = 0, resb = 0, resc = 0;
      Sum(1, l, r, 1, n);
      fastio::qwrite((resa + resb + resc) % mod, '\n');
    }
    //debug(1, 1, n);
  }
  fastio::flush();
  cerr << "runtime=" << (float)(clock() - s) / CLOCKS_PER_SEC << endl;
  return 0;
}