#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pf push_front
#define rep(i, s, t) for (int i = s; i <= t; ++i)
#define per(i, s, t) for (int i = t; i >= s; --i)

const int P = 1e9 + 7;

int qpow(int x, ll p) {
	int res = 1, base = x;
	while(p) {
		if(p & 1) res = 1ll * res * base % P;
		base = 1ll * base * base % P;
		p >>= 1;
	}
	return res;
}

const int N = 10;
const int M = 1e6 + 5;

int n, s, t;
int p[N][N];
int cur[N], head[N], nxt[M<<1], to[M<<1], tot = 1, fl[M<<1];
int que[N], ph, pt, dis[N];

inline void addedge(int u, int v, int w) {
	nxt[++tot] = head[u];
	to[tot] = v;
	fl[tot] = w;
	head[u] = tot;
}

inline bool bfs() {
	ph = 1, pt = 0;
	memset(dis, 0, sizeof dis);
	memcpy(cur, head, sizeof cur);
	que[++pt] = s;
	dis[s] = 1;
	while(ph <= pt) {
		int u = que[ph++];
		for(int e = head[u]; e; e = nxt[e]) {
			int v = to[e], f = fl[e];
			if(f && dis[v] == 0) {
				dis[v] = dis[u] + 1;
				que[++pt] = v;
			}
		}
	}
	return dis[t];
}

inline int dfs(int u, int lim) {
	if(u == t) return lim;
	ll res = 0;
	for(int& e = cur[u]; e; e = nxt[e]) {
		int v = to[e], f = fl[e];
		if(f && dis[v] == dis[u] + 1) {
			ll x = dfs(v, min(lim, f));
			lim -= x;
			res += x;
			fl[e] -= x;
			fl[e^1] += x;
		}
		if(!lim) break;
	}
	if(lim) dis[u] = -1;
	return res;
}

int dinic() {
	int res = 0;
	while(bfs()) res += dfs(s, INT_MAX);
	return res;
}

void clear() {
	memset(head, 0, sizeof head);
	tot = 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("ne.in", "r", stdin);
	freopen("ne.out", "w", stdout);

	int inv100 = qpow(100, P - 2);

	cin >> n;
	rep(i, 1, n) rep(j, 1, n) cin >> p[i][j], p[i][j] = 1ll * p[i][j] * inv100 % P;
	vector<pair<int, int>> v;
	rep(i, 1, n) rep(j, 1, n) if(p[i][j] != 0 && p[i][j] != 1) v.emplace_back(i, j);

	int u = (1 << v.size()) - 1;
	int ans = 0;

	rep(ss, 0, u) {
		clear();
		s = 2*n + 1, t = 2*n + 2;
		rep(i, 1, n) {
			addedge(s, i, 1);
			addedge(i, s, 0);
			addedge(i+n, t, 1);
			addedge(t, i+n, 0);
		}
		int pt = 0, t = 1;
		rep(i, 1, n) rep(j, 1, n) {
			if(p[i][j] == 1) {
				addedge(i, j+n, 1);
				addedge(j+n, i, 0);
			} else if(p[i][j] != 0) {
				if(ss >> pt & 1) {
					t = 1ll * t * p[i][j] % P;
					addedge(i, j+n, 1);
					addedge(j+n, i, 0);
				} else {
					t = 1ll * t * (1 - p[i][j]) % P;
				}
				++pt;
			}
		}
		ans = (ans + 1ll * t * (dinic() == n)) % P;
	}
	cout << (ans + P) % P << "\n";

	return 0;
}