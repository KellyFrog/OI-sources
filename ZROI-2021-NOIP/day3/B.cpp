/*
 * Author: chenkaifeng @BDFZ
 */

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

#if __cplusplus < 201703L
#define register
#else
#define rg
#endif

#define mp make_pair
#define pb push_back
#define pf push_front

#define rep(i, s, t) for (int i = s; i <= t; i++)
#define per(i, s, t) for (int i = t; i >= s; i--)
#define OK cerr << "OK!\n"

namespace fastio {
	const int SIZE = (1 << 20) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = obuf + SIZE - 1;
	char _st[55];
	int _qr = 0;

	inline char getchar() {
		return (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, SIZE, stdin),
		        (iS == iT ? EOF : *iS++) : *iS++);
	}
	inline void qread() {}
	template <typename T1, typename... T2>
	inline void qread(T1 &x, T2 &...ls) {
		x = 0;
		char ch = ' ';
		int ps = 1;
		while (!isdigit(ch) && ch != '-') ch = getchar();
		if (ch == '-') ps = -1, ch = getchar();
		while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
		x *= ps;
		qread(ls...);
	}

	inline void flush() {
		fwrite(obuf, 1, oS - obuf, stdout);
		oS = obuf;
		return;
	}
	inline void putchar(char _x) {
		*oS++ = _x;
		if (oS == oT) flush();
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
};  // namespace fastio

#ifndef ONLINE_JUDGE

void debug(const char *s) {
	cerr << s;
}
template <typename T1, typename... T2>
void debug(const char *s, const T1 x, T2... ls) {
	int p = 0;
	while (*(s + p) != '\0') {
		if (*(s + p) == '{' && *(s + p + 1) == '}') {
			cerr << x;
			debug(s + p + 2, ls...);
			return;
		}
		cerr << *(s + p++);
	}
}

#else
#define debug(...) void(0)
#endif

const ll mod = 1e9 + 7;
// const ll mod = 1e9 + 9;
// const ll mod = 19260817;
// const ll mod = 998244353;
// const int mod =2017;

template <typename T>
inline void chkadd(T& x, T y) {
	x = x + y >= mod ? x + y - mod : x + y;
}
template <typename T>
inline void chkadd(T& x, T y, T z) {
	x = y + z >= mod ? y + z - mod : y + z;
}
template <typename T>
inline void chkmns(T& x, T y) {
	x = x - y < 0 ? x - y + mod : x - y;
}
template <typename T>
inline void chkmns(T& x, T y, T z) {
	x = y - z < 0 ? y - z + mod : y - z;
}
template <typename T>
inline void chkmax(T& x, T y) {
	x = x < y ? y : x;
}
template <typename T>
inline void chkmax(T& x, T y, T z) {
	x = y > z ? y : z;
}
template <typename T>
inline void chkmin(T& x, T y) {
	x = x < y ? x : y;
}
template <typename T>
inline void chkmin(T& x, T y, T z) {
	x = y < z ? y : z;
}

ll qpow(ll x, ll p) {
	ll base = x, res = 1;
	while (p) {
		if (p & 1) res = (res * base) % mod;
		base = (base * base) % mod;
		p >>= 1;
	}
	return res;
}

/* template ends here */

const int N = 505;
const int M = 1e6 + 5;
const int inf = 0x3f3f3f3f;

const int nxt[4][2] = {
	{-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

int ans[M];
int n, m, k1, k2;
int id[N][N], idcnt;
int sx, sy, Q;
vector<int> adj[N*N], dag[M], tree[M];
set<int> adj0[M];
int ind[M], dist[M], dep[M], anc[M][21];

bool check(int x, int y) {
	return !(x < 1 || x > n || y < 1 || y > n);
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	per(i, 0, 20) if(dep[anc[x][i]] >= dep[y]) x = anc[x][i];
	if(x == y) return x;
	per(i, 0, 20) if(anc[x][i] != anc[y][i]) x = anc[x][i], y = anc[y][i];
	return anc[x][0];
}

inline void dfs(int u) {
	if(u > n*m) {
		ans[u] = 1;
	}
	for(int v : tree[u]) {
		ans[v] |= ans[u];
		dfs(v);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	memset(dist, 0x3f, sizeof dist);
	
	cin >> n >> m;
	
	rep(i, 1, n) rep(j, 1, m) id[i][j] = (i-1) * m + j;
	rep(i, 1, n) rep(j, 1, m) {
		rep(k, 0, 3) {
			int ni = i + nxt[k][0];
			int nj = j + nxt[k][1];
			if(id[ni][nj]) adj0[id[i][j]].insert(id[ni][nj]);
		}
	}
	
	cin >> k1 >> k2;
	rep(i, 1, k1) {
		int x, y;
		cin >> x >> y;
		adj0[id[x][y]].erase(id[x][y+1]);
		adj0[id[x][y+1]].erase(id[x][y]);
	}
	rep(i, 1, k2) {
		int x, y;
		cin >> x >> y;
		adj0[id[x][y]].erase(id[x+1][y]);
		adj0[id[x+1][y]].erase(id[x][y]);
	}
	
	rep(i, 1, n*m) for(int x : adj0[i]) adj[i].pb(x);
	idcnt = n*m;
	
	cin >> sx >> sy >> Q;
	
	queue<int> q;
	q.push((dist[id[sx][sy]] = 0, id[sx][sy]));
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : adj[u]) {
			if(dist[v] == inf) {
				dist[v] = dist[u] + 1;
				int t = ++idcnt;
				dag[u].pb(t);
				dag[t].pb(v);
				ind[t]++, ind[v]++;
				q.push(v);
			} else if(dist[v] == dist[u] + 1) {
				int t = ++idcnt;
				dag[u].pb(t);
				dag[t].pb(v);
				ind[t]++, ind[v]++;
			}
		}
	}
	
	
	assert(ind[id[sx][sy]] == 0);
	q.push(id[sx][sy]);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		tree[anc[u][0]].pb(u);
		dep[u] = dep[anc[u][0]] + 1;
		rep(i, 1, 20) anc[u][i] = anc[anc[u][i-1]][i-1];
		for(int v : dag[u]) {
			if(!anc[v][0]) anc[v][0] = u;
			else anc[v][0] = LCA(anc[v][0], u);
			
			if(--ind[v] == 0) q.push(v);
		}
	}
	
	dfs(id[sx][sy]);
	
	while(Q--) {
		int x, y;
		cin >> x >> y;
		int p = id[x][y];
		if(dist[p] == inf) cout << 0 << "\n";
		else cout << ans[p] << "\n";
	}
	
	fastio::flush();
	return 0;
}
