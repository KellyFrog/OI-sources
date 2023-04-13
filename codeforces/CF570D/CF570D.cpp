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

#define popcount __builtin_popcount

const int N = 5e5 + 5;

int val[N << 5], lson[N << 5], rson[N << 5], rt[N], cnt;
int fa[N], dep[N]; 
bool ans[N];
int ch[N]; char str[N];
vector<pii> qry[N];
int n, m;

void Modify(int& cur, int p, int x, int l, int r) {
	if(cur == 0) cur = ++cnt;
	if(l == r) return val[cur] ^= x, void();
	rg int mid = l + r >> 1;
	if(p <= mid) Modify(lson[cur], p, x, l, mid);
	else Modify(rson[cur], p, x, mid + 1, r);
}

int Query(int cur, int p, int l, int r) {
	if(cur == 0) return 0;
	if(l == r) return val[cur];
	rg int mid = l + r >> 1;
	if(p <= mid) return Query(lson[cur], p, l, mid);
	else return Query(rson[cur], p, mid + 1, r);
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	if(l == r) return val[cur] ^= val[old], void();
	rg int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
}

void Thru(int cur, int l, int r) {
	if(cur == 0) return;
	if(l == r) return fprintf(stderr, "[%d,%d]=%d\n", l, r, val[cur]), void();
	rg int mid = l + r >> 1;
	Thru(lson[cur], l, mid);
	Thru(rson[cur], mid + 1, r);
}

int main() {
	qread(n, m);
	rep(i, 2, n) qread(fa[i]);
	scanf("%s", str + 1);
	rep(i, 1, n) ch[i] = str[i] - 'a' + 1;
	rep(i, 1, n) dep[i] = dep[fa[i]] + 1;
	rep(i, 1, m) {
		int x, k; qread(x, k);
		qry[x].pb(mp(k, i));
	}
	per(i, 1, n) {
		Modify(rt[i], dep[i], 1 << ch[i], 1, n);
		for(auto x : qry[i]) ans[x.se] = popcount(Query(rt[i], x.fi, 1, n)) < 2;
		Merge(rt[fa[i]], rt[i], 1, n);
	}
	rep(i, 1, m) puts(ans[i] ? "Yes" : "No");
	return 0;
}
