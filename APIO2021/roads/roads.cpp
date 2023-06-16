#include "roads.h"
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

const int N = 1e5 + 5;

int n, k;
vector<pair<int, int>> adj[N], bdj[N];
vector<int> cdj[N];
ll ans[N], f[N][2], sum[N];
bool vis[N];
set<pair<ll, int>> st[N];

inline void dfs(int u, int fa, ll lw) {
	ll s = 0;
	vector<ll> val;
	vis[u] = 1;
	for(auto [v, w] : bdj[u]) {
		if(adj[v].size() < k) break;
		if(v == fa) continue;
		if(adj[v].size() == k) {
			st[u].emplace(w, v);
			sum[u] += w;
		}
	}
	int d = adj[u].size() - k;
	while(st[u].size() > d) {
		auto it = prev(st[u].end());
		sum[u] -= it->fi;
		st[u].erase(it);
	}
	for(auto [v, w] : bdj[u]) {
		if(adj[v].size() <= k) break;
		if(v == fa) continue;
		dfs(v, u, w);
		s += f[v][0];
		st[u].emplace(f[v][1] - f[v][0], v);
		sum[u] += f[v][1] - f[v][0];
	}
	vector<pair<ll, int>> v;
	while(st[u].size() > d) {
		auto it = prev(st[u].end());
		sum[u] -= it->fi;
		v.pb(*it);
		st[u].erase(it);
	}


	auto it = prev(st[u].end());
	f[u][0] = s + sum[u] - it->fi + min(it->fi, lw);
	f[u][1] = s + sum[u] - it->fi + lw;

	for(auto e : v) st[u].insert(e), sum[u] += e.fi;
	for(auto [v, w] : bdj[u]) {
		if(adj[v].size() <= k) break;
		if(v == fa) continue;
		st[u].erase(mp(f[v][1] - f[v][0], v));
		sum[u] -= f[v][1] - f[v][0];
	}
}

std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
	n = N;
	for(int i = 0; i < N-1; ++i) {
		++U[i], ++V[i];
		adj[U[i]].emplace_back(V[i], W[i]);
		adj[V[i]].emplace_back(U[i], W[i]);
		ans[0] += W[i];
	}
	rep(i, 1, n) {
		bdj[i] = adj[i];
		sort(adj[i].begin(), adj[i].end(), [&](const pair<int, int>& x, const pair<int, int>& y) { return x.se > y.se; });
		sort(bdj[i].begin(), bdj[i].end(), [&](const pair<int, int>& x, const pair<int, int>& y) { return adj[x.fi].size() > adj[y.fi].size(); });
	}
	rep(i, 1, n) rep(j, 0, (int)adj[i].size()-1) cdj[j].pb(i);
	rep(i, 1, n) {
		k = i;
		for(int u : cdj[i]) if(!vis[u]) {
			dfs(u, 0, 1e18);
			ans[i] += f[u][0];
		}
		for(int u : cdj[i]) vis[u] = 0;
	}

	return vector<ll>(ans, ans + n);
}
