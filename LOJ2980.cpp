
// Problem: #2980. 「THUSCH 2017」大魔法师
// Contest: LibreOJ
// URL: https://loj.ac/p/2980
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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

ll qpow(ll x, ll p, ll mod) {
  rg ll base = x, res = 1;
  while (p) {
    if (p & 1) res = (res * base) % mod;
    base = (base * base) % mod;
    p >>= 1;
  }
  return res;
}

const int N = 2.5e5 + 5;
const ll mod = 998244353;

struct Node {
	int x, y, z;
	Node() {}
	Node(int x0, int y0, int z0) : x(x0), y(y0), z(z0) {};
};

struct Matrix {
  ll a[4][4];
  int n, m;
  Matrix() { memset(a, 0, sizeof a); }
  Matrix(int n0, int m0, const initializer_list<Node> & t) {
  	memset(a, 0, sizeof a);
  	for(auto& i : t) a[i.x][i.y] = i.z;
  }
};

Matrix operator * (const Matrix& x, const Matrix& y) {
	Matrix res;
	rep(i, 1, 3) rep(k, 1, 3) rep(j, 1, 3) res.a[i][j] += x.a[i][k] * y.a[k][j];
	rep(i, 1, 3) rep(j, 1, 3) res.a[i][j] %= mod;
	return res;
}

Matrix operator * (const Matrix& x, const ll& y) {
	Matrix res = x;
	rep(i, 1, 3) rep(j, 1, 3) res.a[i][j] = (res.a[i][j] * y) % mod;
	return res;
}

Matrix operator + (const Matrix& x, const Matrix& y) {
	Matrix res;
	rep(i, 1, 3) rep(j, 1, 3) res.a[i][j] = (x.a[i][j] + y.a[i][j]) % mod;
	return res;
}

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

const Matrix 
unt(3, 3, {Node(1, 1, 1), Node(2, 2, 1), Node(3, 3, 1)}),
op1[8] = {
	Matrix(), 
	Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1), Node(3, 3, 1), Node(2, 1, 1)}),
	Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1), Node(3, 3, 1), Node(3, 2, 1)}),
	Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1), Node(3, 3, 1), Node(1, 3, 1)}),
	Matrix(),
	Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1), Node(3, 3, 1)}),
	Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1)})
};


int n, m;
Matrix sum[N << 2], lazy[N << 2], add[N << 2];
int a[N], b[N], c[N];

void PushUp(int cur) {
	sum[cur] = sum[cur << 1] + sum[cur << 1 | 1];
}

void LazyMul(int cur, const Matrix& x) {
	sum[cur] = sum[cur] * x;
	lazy[cur] = lazy[cur] * x;
	add[cur] = add[cur] * x;
}

void LazyAdd(int cur, const Matrix& x, int l, int r) {
	sum[cur] = sum[cur] + x * (r - l + 1);
	add[cur] = add[cur] + x;
}

void PushDown(int cur, int l, int r) {
	rg int mid = l + r >> 1;
	LazyMul(cur << 1, lazy[cur]);
	LazyMul(cur << 1 | 1, lazy[cur]);
	lazy[cur] = unt;
	LazyAdd(cur << 1, add[cur], l, mid);
	LazyAdd(cur << 1 | 1, add[cur], mid + 1, r);
	add[cur] = Matrix();
}

void Build(int cur, int l, int r) {
	lazy[cur] = unt;
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

Matrix Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return sum[cur];
	PushDown(cur, l, r);
	rg int mid = l + r >> 1;
	Matrix res;
	if(ql <= mid) res = res + Sum(cur << 1, ql, qr, l, mid);
	if(mid < qr) res = res + Sum(cur << 1 | 1, ql, qr, mid + 1, r);
	return res;
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
  qread(n);
  rep(i, 1, n) qread(a[i], b[i], c[i]);
  Build(1, 1, n);
  qread(m);
  rep(i, 1, m) {
  	int op, l, r, x;
  	qread(op, l, r);
  	//cerr << "op=" << op << " " << l << " " << r << endl;
  	if(op <= 3) Mul(1, l, r, 1, n, op1[op]);
  	else if(op == 4) qread(x), Add(1, l, r, 1, n, Matrix(3, 3, {Node(1, 1, x)}));
  	else if(op == 5) qread(x), Mul(1, l, r, 1, n, Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, x), Node(3, 3, 1)}));
  	else if(op == 6) qread(x), Mul(1, l, r, 1, n, Matrix(3, 3, {Node(1, 1, 1), Node(2, 2, 1)})), Add(1, l, r, 1, n, Matrix(3, 3, {Node(1, 3, x)}));
  	else {
  		Matrix res = Sum(1, l, r, 1, n);
  		rep(i, 1, 3) qwrite(res.a[1][i], " \n"[i == 3]);
  	}
  }
  return 0;
}
