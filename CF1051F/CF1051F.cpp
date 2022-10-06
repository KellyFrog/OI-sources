
// Problem: CF1051F The Shortest Statement
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1051F
// Memory Limit: 250 MB
// Time Limit: 4000 ms
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
#define OK cerr << "OK!\n"


namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE],*oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		rg char ch = ' ';
		rg int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return ;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if(oS == oT) flush();
	}
	template <typename T>
	inline void qwrite(T x) {
		if (x < 0) putchar('-'), x = -x;
		if (x < 10) return putchar('0' + x), void();
		qwrite(x / 10), putchar('0' + (x % 10));
	}

	template <typename T>
	inline void qwrite(T x, char ch) {
		qwrite(x), putchar(ch);
	}
}; //namespace fastio


void debug(const char* s) {
	cerr << s;
}
template<typename T1, typename ...T2>
void debug(const char * s, const T1 x, T2 ...ls) {
	int p = 0;
	while(*(s + p) != '\0') {
		if(*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
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
const ll inf = 0x3f3f3f3f3f3f3f3f;

vector<pair<int, int> > tree[N], adj[N];
vector<ll> dis0[N], dis1[N];
vector<int> sp;
bool vis[N];
int uni[N];
int fa[N][21], dep[N];
ll dis[N];
bool inq[N];
int n, m, q;

int Find(int x) {
	return x == uni[x] ? x : uni[x] = Find(uni[x]);
}

void Dfs(int u, int f, int w) {
	//debug("dfs={} {} {}\n", u, f, w);
	dis[u] = dis[f] + w;
	fa[u][0] = f;
	dep[u] = dep[f] + 1;
	rep(i, 1, 20) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(auto x : tree[u]) if(x.fi != f) Dfs(x.fi, u, x.se);
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 20) if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
	if(x == y) return x;
	per(i, 0, 20) if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}

ll getdis(int x, int y) {
	return dis[x] + dis[y] - 2 * dis[LCA(x, y)];
}

void Dij(int s, vector<ll>& dis) {
	rep(i, 1, n) dis[i] = inf, inq[i] = 0;
	priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > q;
	q.push(mp(dis[s] = 0, s));
	while(!q.empty()) {
		int u = q.top().se;
		q.pop();
		if(inq[u]) continue;
		inq[u] = 1;
		for(auto x : adj[u]) {
			rg int v = x.fi, w = x.se;
			//debug("{} => {} ({})\n", u, v, w);
			if(dis[u] + w < dis[v]) {
				q.push(mp(dis[v] = dis[u] + w, v));
			}
		}
		for(auto x : tree[u]) {
			rg int v = x.fi, w = x.se;
			//debug("{} => {} ({})\n", u, v, w);
			if(dis[u] + w < dis[v]) {
				q.push(mp(dis[v] = dis[u] + w, v));
			}
		}
	}
}

int main() {
	fastio::qread(n, m);
	rep(i, 1, n) uni[i] = i;
	rep(i, 1, m) {
		int u, v, w;
		fastio::qread(u, v, w);
		int fu = Find(u);
		int fv = Find(v);
		if(fu == fv) {
			adj[u].pb(mp(v, w));
			adj[v].pb(mp(u, w));
			//debug("added edge {} <=> {} ({})\n", u, v, w);
			if(!vis[u]) vis[u] = 1, dis0[u].resize(n + 1);
			if(!vis[v]) vis[v] = 1, dis0[v].resize(n + 1);
		} else {
			tree[u].pb(mp(v, w));
			tree[v].pb(mp(u, w));
			uni[fu] = fv;
		}
	}
	Dfs(1, 0, 0);
	rep(i, 1, n) if(vis[i]) sp.pb(i), Dij(i, dis0[i]);
	/*
		debug("dis of {}=\n", i);
		for(ll x : dis0[i]) cerr << x << " ";
		cerr << endl;
	}
	*/
	fastio::qread(q);
	while(q--) {
		int s, t;
		fastio::qread(s, t);
		ll ans = getdis(s, t);
		//debug("==========query={} {}==============\n", s, t);
		for(int u : sp) {
			ans = min(ans, dis0[u][s] + dis0[u][t]);
		}
		fastio::qwrite(ans, '\n');
	}
	fastio::flush();
	return 0;
}