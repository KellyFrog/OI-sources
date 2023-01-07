// Problem: U114436 【模板】割边
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/U114436?contestId=96511
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// Create Time: 2022-12-30 15:06:12
// Input/Output: stdin/stdout
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

const int N = 2e5 + 5;

int n, m;
int head[N], nxt[N], to[N], tot = 1;
int dfn[N], low[N], dfncnt;
bool vis[N];
int cnt;
vector<pair<int, ll>> ans;

inline void addedge(int u, int v) {
	nxt[++tot] = head[u];
	to[tot] = v;
	head[u] = tot;
}

inline void dfs(int u) {
	vis[u] = 1, ++cnt;
	for(int e = head[u]; e; e = nxt[e]) if(!vis[to[e]]) dfs(to[e]);
}

inline void tarjan(int u, int lst) {
	dfn[u] = low[u] = ++dfncnt;
	for(int e = head[u]; e; e = nxt[e]) {
		if((e ^ lst) == 1) continue;
		int v = to[e];
		if(!dfn[v]) {
			tarjan(v, e);
			low[u] = min(low[u], low[v]);
			if(low[v] == dfn[v]) {
				ans.emplace_back(e >> 1, 1ll * (dfncnt - dfn[v] + 1) * (cnt - (dfncnt - dfn[v] + 1)));
			}
		} else {
			low[u] = min(low[u], dfn[v]);
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
	rep(i, 1, n) if(!dfn[i]) {
		cnt = 0;
		dfs(i);
		tarjan(i, 0);
	}
	sort(ans.begin(), ans.end());
	for(auto [e, val] : ans) cout << e << " " << val << "\n";

	return 0;
}
