
// Problem: P6146 [USACO20FEB]Help Yourself G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P6146
// Memory Limit: 250 MB
// Time Limit: 2000 ms
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

const int N = 2e5 + 5;
const ll mod = 1e9 + 7;

pair<int, int> seg[N];
int n;
int pre[N], pw2[N];
ll dp[N];

int main() {
	qread(n);
	rep(i, 1, n) qread(seg[i].fi, seg[i].se);
	pw2[0] = 1; rep(i, 1, n << 1) pw2[i] = pw2[i-1] * 2 % mod;
	sort(seg + 1, seg + 1 + n);
	rep(i, 1, n) pre[seg[i].se]++;
	rep(i, 1, n << 1) pre[i] += pre[i-1];
	ll ans = 0;
	rep(i, 1, n) ans = (ans + ans + pw2[pre[seg[i].fi-1]]) % mod;
	qwrite(ans, '\n');
	return 0;
}
