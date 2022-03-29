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

ll qpow(ll x, ll p, ll mod = 10007) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const ll mod = 10007;
const int N = 1005;

ll fac[N], ifac[N];

ll a, b, k, n, m;

ll cnm(ll x, ll y) {
	return (ifac[x] * ifac[y - x] % mod) * fac[y] % mod;
}

int main() {
	qread(a, b, k, n, m);
	fac[1] = 1;
	rep(i, 2, k) fac[i] = fac[i-1] * i % mod;
	ifac[k] = qpow(fac[k], mod - 2, mod);
	per(i, 1, k-1) ifac[i] = ifac[i+1] * (i+1) % mod;
	qwrite(cnm(n, k) * qpow(a, n) % mod * qpow(b, m) % mod, '\n');
	return 0;
}
