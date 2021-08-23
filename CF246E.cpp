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

int lson[N << 5], rson[N << 5], rt[N], cnt; set<int> val[N << 5];
int a[N], dep[N], ans[N];
bool hasfa[N];
int n, m, tot;
map<string, int> mpi;
vi adj[N];
vector<pii> qry[N];

void Insert(int& cur, int p, int x, int l, int r) {
	if(cur == 0) cur = ++cnt;
	if(l == r) return val[cur].insert(x), void();
	rg int mid = l + r >> 1;
	if(p <= mid) Insert(lson[cur], p, x, l, mid);
	else Insert(rson[cur], p, x, mid + 1, r);
}

void Merge(int& cur, int old, int l, int r) {
	if(cur == 0 || old == 0) return cur += old, void();
	if(l == r) {
		if(val[cur].size() < val[old].size()) {
			for(int x : val[cur]) val[old].insert(x);
			cur = old;
		} else {
			for(int x : val[old]) val[cur].insert(x);
		}
		return;
	}
	rg int mid = l + r >> 1;
	Merge(lson[cur], lson[old], l, mid);
	Merge(rson[cur], rson[old], mid + 1, r);
}

int Query(int cur, int p, int l, int r) {
	if(cur == 0) return 0;
	if(l == r) return val[cur].size();
	rg int mid = l + r >> 1;
	if(p <= mid) return Query(lson[cur], p, l, mid);
	else return Query(rson[cur], p, mid + 1, r);
}

void Dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	for(int v : adj[u]) Dfs(v, u), Merge(rt[u], rt[v], 1, n);
	Insert(rt[u], dep[u], a[u], 1, n);
	for(auto x : qry[u]) ans[x.se] = dep[u] + x.fi <= n ? Query(rt[u], dep[u] + x.fi, 1, n) : 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	rep(i, 1, n) {
		string cur = ""; int x;
		cin >> cur >> x;
		a[i] = mpi[cur] == 0 ? mpi[cur] = ++tot : mpi[cur];
		if(x != 0) hasfa[i] = 1, adj[x].pb(i);
	}
	cin >> m;
	rep(i, 1, m) {
		int x, k;
		cin >> x >> k;
		qry[x].pb(mp(k, i));
	}
	rep(i, 1, n) if(!hasfa[i]) Dfs(i, 0);
	rep(i, 1, m) qwrite(ans[i], '\n');
	return 0;
}
