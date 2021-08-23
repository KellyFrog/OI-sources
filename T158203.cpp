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

const int N = 1e3 + 5;

struct bigint {
	const ll base = 1e18;
	const int len = 2005 / 18;
	ll num[2005];
	bigint() {
		memset(num, 0, sizeof num);
	}
	ll& operator [](const int& p) {
		return num[p];
	}
	ll& size() {
		return num[0];
	}
	bigint operator = (const ll& x) {
		return num[num[0] = 1] = x, *this;
	}
	bigint operator = (const bigint& x) {
		memcpy(num, x.num, sizeof x.num);
	}
	bigint operator + (bigint& x) {
		bigint res;
		res.size() = max(size(), x.size());
		rep(i, 1, res.num[0]) res[i] = num[i] + x[i];
		rep(i, 1, res.num[0]) res[i+1] += res[i] / base, res[i] %= base;
		if(res[res.size() + 1]) ++res.size();
		return res;
	}
	void write() {
		printf("%lld", num[num[0]]);
		per(i, 1, num[0] - 1) printf("%018lld", num[i]);
		puts("");
	}
};

bigint fib[N];

int main() {
	bigint fn1, fn2, fn;
	int x, y;
	qread(x, y);
	fib[1] = 1, fib[2] = 1;
	rep(i, 3, y - x + 1) fib[i] = fib[i-1] + fib[i-2];
	fib[y - x + 1].write();
	return 0;
}
