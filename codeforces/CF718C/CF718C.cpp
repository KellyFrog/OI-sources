
// Problem: CF718C Sasha and Array
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF718C
// Memory Limit: 250 MB
// Time Limit: 5000 ms
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

const int N = 1e5 + 5;
const ll mod = 1e9 + 7;

struct Matrix {
	ll a[2][2];
	void clear() {
		memset(a, 0, sizeof a);
	}
	void unit() {
		clear();
		a[0][0] = a[1][1] = 1;
	}
	void mat() {
		clear();
		a[0][0] = a[0][1] = a[1][0] = 1;
	}
};

Matrix operator * (const Matrix& a, const Matrix& b) {
	Matrix res; res.clear();
	res.a[0][0] = (a.a[0][0] * b.a[0][0] + a.a[0][1] * b.a[1][0]) % mod;
	res.a[0][1] = (a.a[0][0] * b.a[0][1] + a.a[0][1] * b.a[1][1]) % mod;
	res.a[1][0] = (a.a[1][0] * b.a[0][0] + a.a[1][1] * b.a[1][0]) % mod;
	res.a[1][1] = (a.a[1][0] * b.a[0][1] + a.a[1][1] * b.a[1][1]) % mod;
	return res;
}

Matrix vec[N], lazy[N];
ll resa, resb;
int n, m;

Matrix qpow(int p) {
	Matrix res; res.unit();
	Matrix base; base.mat();
	while(p) {
		if(p & 1) res = res * base;
		base = base * base;
		p >>= 1;
	}
	return res;
}

void Lazy(int cur, const Matrix& x) {
	lazy[cur] = lazy[cur] * x;
	vec[cur] = vec[cur] * x;
}

void PushDown(int cur) {
	Lazy(cur << 1, lazy[cur]);
	Lazy(cur << 1 | 1, lazy[cur]);
	lazy[cur].unit();
}

void PushUp(int cur) {
	vec[cur].a[0][0] = (vec[cur << 1].a[0][0] + vec[cur << 1 | 1].a[0][0]) % mod;
	vec[cur].a[0][1] = (vec[cur << 1].a[0][1] + vec[cur << 1 | 1].a[0][1]) % mod;
}

void Build(int cur, int l, int r) {
	vec[cur].clear(), vec[cur].a[0][0] = vec[cur].a[0][1] = 1;
	lazy[cur].unit();
	if(l == r) return;
	rg int mid = l + r >> 1;
	Build(cur << 1, l, mid);
	Build(cur << 1 | 1, mid + 1, r);
	PushUp(cur);
}

void Modify(int cur, int ql, int qr, int l, int r, const Matrix& x) {
	if(ql <= l && r <= qr) return Lazy(cur, x), void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Modify(cur << 1, ql, qr, l, mid, x);
	if(mid < qr) Modify(cur << 1 | 1, ql, qr, mid + 1, r, x);
	PushUp(cur);
}

void Sum(int cur, int ql, int qr, int l, int r) {
	if(ql <= l && r <= qr) return (resa += vec[cur].a[0][0]) %= mod, (resb += vec[cur].a[0][1]) %= mod, void();
	PushDown(cur);
	rg int mid = l + r >> 1;
	if(ql <= mid) Sum(cur << 1, ql, qr, l, mid);
	if(mid < qr) Sum(cur << 1 | 1, ql, qr, mid + 1, r);
}

void Debug(int cur, int l, int r) {
	cerr << cur << " [" << l << "," << r << "]\n";
	cerr << "vec=" << " ";
	rep(i, 0, 0) rep(j, 0, 1) cerr << vec[cur].a[i][j] << " \n"[j == 1];
	cerr << "lazy=\n";
	rep(i, 0, 1) rep(j, 0, 1) cerr << lazy[cur].a[i][j] << " \n"[j == 1];
	if(l == r) return;
	rg int mid = l + r >> 1;
	Debug(cur << 1, l, mid);
	Debug(cur << 1 | 1, mid + 1, r);
}

int main() {
	fastio::qread(n, m);
	Build(1, 1, n);
	rep(i, 1, n) {
		int x; fastio::qread(x);
		if(x > 1) {
			Matrix tmp = qpow(x - 1);
			Modify(1, i, i, 1, n, tmp);
		}
	}
	rep(i, 1, m) {
		int op, l, r, x;
		fastio::qread(op, l, r);
		if(op == 2) {
			resa = 0, resb = 0;
			Sum(1, l, r, 1, n);
			fastio::qwrite(resb, '\n');
		} else {
			fastio::qread(x);
			Matrix tmp = qpow(x);
			Modify(1, l, r, 1, n, tmp);
		}
		//cerr << "------------------------- " << op << " " << l << " " << r << " " << x << endl;
		//Debug(1, 1, n);
	}
	fastio::flush();
	return 0;
}