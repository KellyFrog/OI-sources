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
const ll inf = 1e18;

int fa[N][20], dep[N];;
int n;
ll dis[N], a[N];
int delta[N], ans[N];
vector<pair<int, int> > adj[N];

void Dfs1(int u, int f, int w) {
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	dis[u] = dis[f] + w;
	rep(i, 1, 19) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(auto x : adj[u]) Dfs1(x.fi, u, x.se);
}

void Dfs2(int u, int f) {
	for(auto x : adj[u]) Dfs2(x.fi, u), delta[u] += delta[x.fi];
}

int main() {
	qread(n);
	rep(i, 1, n) qread(a[i]);
	rep(i, 2, n) {
		int fat, w;
		qread(fat, w);
		adj[fat].pb(mp(i, w));
	}
	Dfs1(1, 0, 0);
	rep(x, 1, n) {
		int u = x;
		per(i, 0, 19) if(fa[u][i] && dis[x] - dis[fa[u][i]] <= a[x]) u = fa[u][i];
		delta[x]++;
		delta[fa[u][0]]--;
	}
	Dfs2(1, 0);
	rep(i, 1, n) qwrite(delta[i]-1, " \n"[i == n]);
	return 0;
}
