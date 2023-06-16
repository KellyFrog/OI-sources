//#include "roads.h"

#include <vector>

std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W);
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

inline void dfs(int u, int fa, int lw) {
	ll s = sum[u];
	vector<ll> val;
	vis[u] = 1;
	for(auto [v, w] : bdj[u]) {
		if(adj[v].size() <= k) break;
		if(v == fa) continue;
		dfs(v, u, w);
		s -= w;
		s += f[v][1];
		val.pb(f[v][0] - f[v][1]);
	}
	int cc = 0;
	for(auto [v, w] : adj[u]) {
		if(cc > k) break;
		if(v == fa || adj[v].size() > k) continue;
		val.pb(-w);
		++cc;
	}
	assert(val.size() >= k);
	//pick lw
	f[u][0] = f[u][1] = s;
	sort(val.begin(), val.end());
	for(int i = 0; i < k; ++i) f[u][1] += min(0ll, val[i]);
	val.pb(-lw);
	sort(val.begin(), val.end());
	for(int i = 0; i < k; ++i) f[u][0] += min(0ll, val[i]);
}

std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
	n = N;
	for(int i = 0; i < N-1; ++i) {
		++U[i], ++V[i];
		adj[U[i]].emplace_back(V[i], W[i]);
		adj[V[i]].emplace_back(U[i], W[i]);
		sum[U[i]] += W[i];
		sum[V[i]] += W[i];
	}
	rep(i, 1, n) {
		bdj[i] = adj[i];
		sort(adj[i].begin(), adj[i].end(), [&](const pair<int, int>& x, const pair<int, int>& y) { return x.se > y.se; });
		sort(bdj[i].begin(), bdj[i].end(), [&](const pair<int, int>& x, const pair<int, int>& y) { return adj[x.fi].size() > adj[y.fi].size(); });
	}
	rep(i, 1, n) rep(j, 0, (int)adj[i].size()-1) cdj[j].pb(i);
	rep(i, 0, n) {
		k = i;
		for(int u : cdj[i]) if(!vis[u]) {
			dfs(u, 0, 0);
			ans[i] += f[u][1];
		}
		for(int u : cdj[i]) vis[u] = 0;
	}

	return vector<ll>(ans, ans + n);
}
