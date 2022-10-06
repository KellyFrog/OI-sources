
// Problem: CF1252K Addition Robot
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1252K
// Memory Limit: 250 MB
// Time Limit: 3000 ms
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


void debug(const char* s) {
	cerr << s;
}
template<typename T1, typename ...T2>
void debug(const char * s, const T1 x, T2 ...ls) {
	int p = 0;
	while(*(s + p) != '\0') {
		if(*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

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
	void mata() {
		clear();
		a[0][0] = a[1][1] = a[1][0] = 1;
	}
	void matb() {
		clear();
		a[0][0] = a[1][1] = a[0][1] = 1;
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

int n, q;



int main() {
	
	fastio::flush();
	return 0;
}