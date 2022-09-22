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

/* template ends here */

std::mt19937 mtrnd(std::chrono::system_clock::now().time_since_epoch().count());

const int N = 2e5 + 5;

int n, m;
vector<int> adj[N];
int eu[N], ev[N];
int uni[N], mipos[N];
pair<int, int> egs[N]; int egp;

inline int find(int x) {
    return x == uni[x] ? x : uni[x] = find(uni[x]);
}

void solve() {
    cin >> n >> m;
    rep(i, 1, n) adj[i].clear(), uni[i] = i, mipos[i] = n+1;
    egp = 0;
    rep(i, 1, m) {
	int u, v;
	cin >> u >> v;
	eu[i] = u, ev[i] = v;
	adj[min(u,v)].pb(max(u,v));
    }
    if(m < n - 1) {
	cout << -1 << "\n";
	return;
    }
    rep(i, 1, n) sort(adj[i].begin(), adj[i].end(), greater<int>());
    per(u, 1, n) {
	for(int v : adj[u]) {
	    int fx = find(u);
	    int fy = find(v);
	    if(fx != fy) {
		uni[fx] = fy;
	    } else {
		egs[++egp] = mp(min(u, v), max(u, v));
	    }
	}
    }
    sort(egs + 1, egs + egp + 1);
    rep(i, 1, n) mipos[find(i)] = min(mipos[find(i)], i);
    vector<int> v;
    rep(i, 1, n) if(mipos[i] != n+1) v.pb(mipos[i]);
    sort(v.begin(), v.end());
    cout << v.size() - 1 << "\n";
    assert(egp >= v.size() - 1);
    for(int i = 1; i < v.size(); i++) {
	cout << egs[i].fi << " " << egs[i].se << " " << v[0] << " " << v[i] << "\n";
    }
}

int main() {
    freopen("rebuild.in", "r", stdin);
    freopen("rebuild.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int t;
    cin >> t;
    while(t--) solve();
    cout.flush();
    
    return 0;
}
    
