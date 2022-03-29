
// Problem: T107876 力量增强[2019海淀区智慧杯初中组复赛T3]
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T107876?contestId=38917
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

const int N = 1e5 + 5;
const ll inf = 1e18;

int sum[N];
int n, x;
pair<int, int> a[N];

int lowbit(int x) {
	return x & (-x);
}

void Add(int p, int k) {
	while(p <= n) {
		sum[p] += k;
		p += lowbit(p);
	}
}

int Sum(int p) {
	int res = 0;
	while(p) {
		res += sum[p];
		p -= lowbit(p);
	}
	return res;
}

int main() {
	qread(n, x);
	rep(i, 1, n) qread(a[i].fi), a[i].se = i;
	sort(a + 1, a + 1 + n);
	ll ans = inf, cost = 0;
	rep(i, 1, n) Add(i, 1);
	per(i, 1, n) {
		cost += Sum(n) - Sum(a[i].se);
		Add(a[i].se, -1);
	}
	ans = min(ans, cost);
	memset(sum, 0, sizeof sum);
	rep(i, 1, n) {
		//cerr << i << " " << cost << endl;
		cost = cost - (a[i].se - 1 - Sum(a[i].se - 1)) + x;
		Add(a[i].se, 1);
		ans = min(ans, cost);
	} 
	qwrite(ans, '\n');
	return 0;
}
