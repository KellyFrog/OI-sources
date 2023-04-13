// Problem: P8867 [NOIP2022] 建造军营
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P8867
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

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

const int N = 2e6 + 5;
const int P = 1e9 + 7;
const int inv2 = (P+1) / 2;

int n, m;
int head[N], nxt[N], to[N], tot = 1;
int dfn[N], low[N], dfncnt, stk[N], top, bel[N], bc;
vector<int> adj[N];
int c[N], f[N], pw[N], siz[N];

inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

inline void tarjan(int u, int lst) {
	dfn[u] = low[u] = ++dfncnt;
	stk[++top] = u;
	for(int e = head[u]; e; e = nxt[e]) {
		if(e == (lst ^ 1)) continue;
		int v = to[e];
		if(!dfn[v]) {
			tarjan(v, e);
			low[u] = min(low[u], low[v]);
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(low[u] == dfn[u]) {
		++bc;
		while(1) {
			int x = stk[top--];
			bel[x] = bc;
			if(x == u) break;
		}
	}
}

inline void dfs(int u, int fa) {
	f[u] = pw[c[u]];
	siz[u] = 1;
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			f[u] = (1ll * f[u] * pw[siz[v]-1] + 1ll * f[u] * f[v]) % P;
			siz[u] += siz[v];
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	cout << fixed << setprecision(15); 
	cerr << fixed << setprecision(15);

	cin >> n >> m;
	rep(i, 1, m) {
		int u, v; cin >> u >> v;
		addedge(u, v), addedge(v, u);
	}
	tarjan(1, 0);
	rep(i, 1, n) ++c[bel[i]];
	rep(u, 1, n) for(int e = head[u]; e; e = nxt[e]) {
		int v = to[e];
		if(bel[u] != bel[v]) adj[bel[u]].pb(bel[v]);
	}
	pw[0] = 1;
	rep(i, 1, max(n, m)) pw[i] = 2 * pw[i-1] % P;
	dfs(1, 0);
	int ans = 0;
	rep(i, 1, bc) {
		ans = (ans + 1ll * (f[i] - pw[siz[i]-1]) * pw[max(0,bc-siz[i]-1)] % P * pw[m-(bc-1)]) % P;
	}
	cout << (ans + P) % P << "\n";
	
	return 0;
}
