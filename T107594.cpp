// Problem: T107594 保护堡垒[2019海淀区智慧杯初中组复赛T2]
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/T107594?contestId=38917
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

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

int n, m, s, t;
int delta[N];

void Add(int l, int r, int x = 1) {
	if(l > r) swap(l, r);
	//cerr << "added=" << l << " " << r << endl;
	delta[l] += x;
	delta[r+1] -= x;
}

int main() {
	qread(n, m, s, t);
	if(s > t) swap(s, t);
	rep(i, 1, m) {
		int x, y;
		qread(x, y);
		if(x > y) swap(x, y);
		if(x >= s) Add(x, s);
		if(y <= t) Add(y, t);
	}
	int ans =0 ;
	rep(i, 1, n) if((delta[i] += delta[i-1]) == m || i == s || i == t) ans++;
	qwrite(ans - 2, '\n');
	return 0;
}
