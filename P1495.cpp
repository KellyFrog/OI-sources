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

inline void qread() {}
template<typename T1, typename ...T2>
inline void qread(T1 &x, T2&... ls) {
	x = 0;
	rg char ch = ' '; rg int ps = 1;
	while(!isdigit(ch) && ch != '-') ch = getchar();
	if(ch == '-') ps = -1, ch = getchar();
	while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
	x *= ps;
	qread(ls...);
}

template<typename T>
inline void qwrite(T x) {
	if(x < 0) putchar('-'), x = -x;
	if(x < 10) return putchar('0' + x), void();
	qwrite(x / 10), putchar('0' + (x % 10));
}

template<typename T>
inline void qwrite(T x, char ch) {
	qwrite(x), putchar(ch);
}

template<typename T>
inline void chkmax(T& x, T y) {
	if(x < y) x = y;
}

template<typename T>
inline void chkmin(T& x, T y) {
	if(x > y) x = y;
}

template<typename T>
inline void chkmod(T& x, ll mod) {
	x = x > mod ? x - mod : x;
}

template<typename T>
inline void chkadd(T& x, T y, ll mod) {
	x = x + y > mod ? x + y - mod : x + y;
}

template<typename T>
inline void chkmns(T& x, T y, ll mod) {
	x = x - y < 0 ? x - y + mod : x - y;
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

//ax+by=gcd(x,y)=1
void exgcd(ll a, ll b, ll& x, ll& y) {
	if(b == 0) return y = 0, x = 1, void();
	ll x1, y1;
	exgcd(b, a % b, x1, y1);
	x = y1, y = x1 - a / b * y1;
}

//k * mul + x === bi mod ai
//k * mul1 + x = bi + p * ai
//k * mul - p * ai = bi - x

const int N = 15;

int n;
ll a[N], b[N], mul = 1, x;

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i], b[i]);
	rep(i, 1, n) {
		ll x0, y0;
		exgcd(mul, a[i], x0, y0);
		y0 *= (b[i] - x) % a[i];
		x0 *= (b[i] - x) % a[i];
		x += x0 * mul;
		mul *= a[i];
		x %= mul;
		if(x < 0) x += mul;
	}
	qwrite(x, '\n');
	return 0;
}
