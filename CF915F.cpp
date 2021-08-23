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

struct Edge {
	int u, v, w;
};

const int N = 1e6 + 5;

int fa[N], siz[N], n;
Edge eg[N];
ll ans, a[N];

void Init() {
	rep(i, 1, n) siz[i] = 1, fa[i] = i;
}

int Find(int x) {
	return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

ll Solve() {
	ll res = 0;
	rep(i, 1, n-1) {
		int u = eg[i].u, v = eg[i].v;
		u = Find(u), v = Find(v);
		if(u == v) continue;
		ll w = eg[i].w;
		res += w * siz[u] * siz[v];
		//cerr << eg[i].u << " " << eg[i].v << " " << w << " " << u << " " << v << " " << siz[u] << " " << siz[v] << " " << w * siz[u] * siz[v] << endl;
		fa[u] = v;
		siz[v] += siz[u];
	}
	return res;
}

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i]);
	rep(i, 1, n-1) qread(eg[i].u, eg[i].v);
	rep(i, 1, n-1) eg[i].w = max(a[eg[i].u], a[eg[i].v]);
	sort(eg + 1, eg + n, [](const Edge& x, const Edge& y) { return x.w < y.w; });
	Init(); ans += Solve();
	rep(i, 1, n-1) eg[i].w = min(a[eg[i].u], a[eg[i].v]);
	sort(eg + 1, eg + n, [](const Edge& x, const Edge& y) { return x.w > y.w; });
	Init(); ans -= Solve();
	qwrite(ans, '\n');
	return 0;
}
