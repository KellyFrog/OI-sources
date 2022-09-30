#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 4e5 + 5;

int a, b;
set<pair<int, int>> v1[N], v2[N];
int m;
int ans[N];
vector<int> adj[N];
int dfncnt, dfn[N], low[N], stk[N], ins[N], top, res;
int eu[N], ev[N];

inline void tarjan(int u) {
    dfn[u] = low[u] = ++dfncnt;
    stk[++top] = u, ins[u] = 1;
    for(int v : adj[u]) {
	if(!dfn[v]) {
	    tarjan(v);
	    low[u] = min(low[u], low[v]);
	} else if(ins[v]) {
	    low[u] = min(low[u], dfn[v]);
	}
    }
    if(dfn[u] == low[u]) {
	++res;
	while(1) {
	    int x = stk[top--];
	    ins[x] = 0;
	    if(x == u) break;
	}
    }
}

int main() {
    freopen("scc.in", "r", stdin);
    freopen("scc.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> a >> b;
    cin >> m;
    rep(i, 1, m) {
	int u, v;
	cin >> u >> v;
	eu[i] = u, ev[i] = v;
	v1[u].insert(mp(v, i));
	v2[v].insert(mp(u, i));
    }


    int lastp = 0;

    rep(i, 1, a) {
	for(auto e : v1[i]) {
	    int v = e.fi, p = e.se;
	    v2[v].erase(mp(i, p));
	    cerr << "get " << i << " -> " << v << "\n";
	    ans[p] = 1;
	    rep(j, lastp+1, v) {
		for(auto it = v2[j].begin(); it != v2[j].end(); ) {
		    auto ee = *it;
		    int vv = ee.fi, pp = ee.se;
		    if(vv < i) {
			ans[pp] = 0;
			v1[vv].erase(mp(j, pp));
		    } else {
			++it;
		    }
		}
	    }
	    lastp = v;
	}
    }

    rep(i, 2, a) adj[i-1].pb(i);
    rep(i, 2, b) adj[i-1+a].pb(i+a);

    rep(i, 1, m) {
	if(ans[i] == 0) {
	    adj[eu[i]].pb(ev[i]+a);
	} else {
	    adj[ev[i]+a].pb(eu[i]);
	}
    }

    rep(i, 1, a+b) if(!dfn[i]) tarjan(i);
    cout << res << "\n";

    rep(i, 1, m) cout << ans[i] << " \n"[i == m];
    cout.flush();

    return 0;
}
