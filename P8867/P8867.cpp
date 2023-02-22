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

const int N = 1e6 + 5;
const int P = 1e9 + 7;
const int inv2 = (P+1) / 2;

int n, m;
int head[N], nxt[N], to[N], tot = 1;
int dfn[N], low[N], dfncnt, stk[N], top, bel[N], bc;
vector<int> adj[N];
int c1[N], c2[N], f[N], g[N], sum[N];

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
	if(low[u] == dfn[v]) {
		++bc;
		while(1) {
			int x = stk[top--];
			bel[x] = bc;
			if(x == u) break;
		}
	}
}

inline void dfs(int u, int fa) {
	sum[u] = c2[u];
	f[u] = pw[c1[u]+c2[u]];
	for(int v : adj[u]) {
		if(v != fa) {
			dfs(v, u);
			f[u] = (1ll * f[u] * pw[sum[v]] + 1ll * f[u]
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
	rep(i, 1, n) ++c1[bel[i]];
	rep(u, 1, n) for(int e = head[u]; e; e = nxt[e]) {
		int v = to[e];
		if(bel[u] == bel[v]) ++c2[bel[u]];
		else adj[bel[u]].pb(bel[v]), adj[bel[v]].pb(bel[u]);
	}
	rep(i, 1, bc) c2[i] >>= 1;
	dfs(1, 0);
	int ans = 0;
	rep(i, 1, n) ans = (ans + f[i]) % P;
	cout << ans << "\n";
	
	return 0;
}
