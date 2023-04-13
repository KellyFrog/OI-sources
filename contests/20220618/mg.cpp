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

const int N = 4e5 + 5;
const int M = 1e6 + 5;

int n, m;
int head[N], nxt[M<<1], to[M<<1], tot = 1;
int ans[N], d[N];

inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

namespace bf {
int dfn[N], low[N], dfncnt;
bool ins[N], ans[N], vis[N];
int ban;

inline void tarjan(int u, bool rt = 1) {
	int cnt = 0;
	ins[u] = 1;
	dfn[u] = low[u] = ++dfncnt;
	for(int e = head[u]; e; e = nxt[e]) {
		if(e == ban || e == (ban ^ 1)) continue;
		int v = to[e];
		if(!dfn[v]) {
			tarjan(v, 0);
			++cnt;
			low[u] = min(low[u], low[v]);
			if(low[v] == dfn[u] && !rt) ans[u] = 1;
		} else if(ins[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(rt) ans[u] = cnt > 1;
	ins[u] = 0;
}

void clear() {
	rep(u, 1, n) dfn[u] = low[u] = 0, vis[u] = ans[u] = 0;
	dfncnt = 0;
}

inline void dfs(int u) {
	vis[u] = 1;
	for(int e = head[u]; e; e = nxt[e]) {
		if(e == ban || e == (ban ^ 1)) continue;
		int v = to[e];
		if(!vis[v]) dfs(v);
	}
}

void solve() {
	rep(i, 1, m) {
		ban = i*2;
		clear();

		--d[to[ban]];
		--d[to[ban^1]];

		// cerr << to[ban] << " " << to[ban^1] << "\n";

		dfs(1);
		bool ok = 1;
		rep(i, 1, n) if(!vis[i]) ok = 0;
		if(!ok) {
			int cnt = 0;
			rep(j, 1, n) cnt += d[j] == 0;
			if(cnt == 1) {
				cout << n-1 << "\n";
			} else {
				cout << n << "\n";
			}
			++d[to[ban]];
			++d[to[ban^1]];
			continue;
		}

		tarjan(1);
		int res = 0;
		rep(j, 1, n) res += ans[j];
		rep(j, 1, n) if(!dfn[j]) res = n;

		++d[to[ban]];
		++d[to[ban^1]];

		cout << res << "\n";
	}
}
}

namespace tree {

void solve() {
	rep(i, 1, m) {
		int o = i*2;
		cout << (min(d[to[o]], d[to[o^1]]) == 1 ? n-1 : n) << "\n";
	}
}
}

bool vis[N];

inline void dfs(int u) {
	vis[u] = 1;
	for(int e = head[u]; e; e = nxt[e]) {
		int v = to[e];
		if(!vis[v]) dfs(v);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	freopen("mg.in", "r", stdin);
	freopen("mg.out", "w", stdout);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		addedge(u, v);
		addedge(v, u);
		++d[u], ++d[v];
	}

	if(n == 2) {
		rep(i, 1, m) cout << 0 << "\n";
		return 0;
	}

	dfs(1);
	bool ok = 1;
	rep(i, 1, n) if(!vis[i]) ok = 0;
	if(!ok) {
		int cnt = 0;
		rep(j, 1, n) cnt += d[j] == 0;
		if(cnt == 1) {
			rep(i, 1, m) cout << n-1 << "\n";
		} else {
			rep(i, 1, m) cout << n << "\n";
		}
		return 0;
	}

	if(n <= 5000) bf::solve();
	else tree::solve();
	
	return 0;
}