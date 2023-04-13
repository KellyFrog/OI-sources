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

const int N = 1e5 + 5;

vi adj[N]; 
int a[N], b[N], ans[N];
int sum[N << 5], lson[N << 5], rson[N << 5], rt[N], cnt;
int n, m;

void Add(int& cur, int p, int l, int r) {
	if(cur == 0) cur = ++cnt;
	sum[cur]++;
	if(l == r) return;
	rg int mid = l + r >> 1;
	if(p <= mid) Add(lson[cur], p, l, mid);
	else Add(rson[cur], p, mid + 1, r);
}

int Sum(int cur, int ql, int qr, int l, int r) {
	if(cur == 0) return 0;
	if(ql <= l && r <= qr) return sum[cur];
	rg int mid = l + r >> 1;
	rg int res = 0;
	if(ql <= mid) res += Sum(lson[cur], ql, qr, l, mid);
	if(mid < qr) res += Sum(rson[cur], ql, qr, mid + 1, r);
	return res;
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	sum[cur] += sum[old];
	if(l == r) return;
	rg int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
}

void Dfs(int u) {
	for(int v : adj[u]) Dfs(v), Merge(rt[u], rt[v], 1, m);
	ans[u] = Sum(rt[u], a[u] + 1, m, 1, m);
	Add(rt[u], a[u] + 1, 1, m);
}

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i]), b[i] = a[i];
	sort(b + 1, b + 1 + n);
	m = unique(b + 1, b + 1 + n) - (b + 1);
	rep(i, 1, n) a[i] = lower_bound(b + 1, b + 1 + m, a[i]) - b;
	rep(i, 2, n) {
		int x; qread(x);
		adj[x].pb(i);
	}
	Dfs(1);
	rep(i, 1, n) qwrite(ans[i], '\n');
	return 0;
}
