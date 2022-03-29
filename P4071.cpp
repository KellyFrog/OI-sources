
// Problem: P1595 信封问题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P1595
// Memory Limit: 125 MB
// Time Limit: 1000 ms
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

ll qpow(ll x, ll p, ll mod) {
	rg ll base = x, res = 1;
	while(p) {
		if(p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

const int N = 1e6 + 5;
const ll mod = 1e9 + 7;

ll dp[N], fac[N], ifac[N];
int n, s = 1e6;

ll Cnm(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int main() {
	dp[1] = 0, dp[2] = 1;
	rep(i, 3, s) dp[i] = 1ll * (i - 1) * (dp[i-1] + dp[i-2]) % mod;
	fac[1] = 1;
	rep(i, 2, s) fac[i] = (fac[i-1] * i) % mod;
	ifac[s] = qpow(fac[s], mod - 2, mod);
	per(i, 1, s - 1) ifac[i] = ifac[i+1] * (i+1) % mod;
	int T, n, m; qread(T);
	while(T--) {
		qread(n, m);
		qwrite(m == 0 ? dp[n] : n - m == 1 ? 0 : n == m ? 1 : dp[n - m] * Cnm(n, m) % mod, '\n');
	}
	return 0;
}
