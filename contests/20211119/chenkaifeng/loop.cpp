/*
 * Author: chenkaifeng @BDFZ
 */
 
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

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;
const int inf = 0x3f3f3f3f;

vector<pair<int, int>> adj[N];
int dis[N];
bool vis[N], s1[N], s2[N];
int n, m;

int solve(int p, int b) {
    memset(dis, 0x3f, sizeof dis);
    memset(vis, 0, sizeof vis);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(mp(dis[1] = 0, 1));
    while(!pq.empty()) {
	int u = pq.top().se; pq.pop();
	if(vis[u]) continue;
	vis[u] = 1;
	for(auto e : adj[u]) {
	    int v = e.fi, w = e.se;
	    if(u == 1) {
		if((v >> p-1 & 1) == b) {
		    if(dis[u] + w < dis[v]) {
			pq.push(mp(dis[v] = dis[u] + w, v));
		    }
		}
	    } else {
		if(dis[u] + w < dis[v]) {
		    pq.push(mp(dis[v] = dis[u] + w, v));
		}
	    }
	}
    }

    int ans = inf;


    rep(u, 2, n) {
	if(((u >> p-1 & 1) ^ 1) == b) {
	    for(auto e : adj[u]) {
		int v = e.fi, w = e.se;
		if(v == 1) ans = min(ans, dis[u] + w);
	    }
	}
    }

    return ans;
}

int main() {
    freopen("loop.in", "r", stdin);
    freopen("loop.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n >> m;
    rep(i, 1, m) {
	int u, v, w1, w2;
	cin >> u >> v >> w1 >> w2;
	adj[u].pb(mp(v, w1));
	adj[v].pb(mp(u, w2));
    }
    int ans = inf;
    rep(i, 0, 20) {
	ans = min(ans, solve(i, 0));
	ans = min(ans, solve(i, 1));
    }
    cout << (ans == inf ? -1 : ans) << endl;
    
    return 0;
}
    
