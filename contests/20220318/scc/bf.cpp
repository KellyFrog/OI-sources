#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 25;

int a, b, m;
int dfn[N], low[N], dfncnt, ins[N], stk[N], top, ans;
vector<int> adj[N];
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
	++ans;
	while(1) {
	    int x = stk[top--];
	    ins[x] = 0;
	    if(x == u) break;
	}
    }
}

inline int getans(int s) {
    dfncnt = top = 0;
    ans = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(ins, 0, sizeof ins);
    rep(i, 1, a+b) adj[i].clear();
    rep(i, 2, a) adj[i-1].pb(i);
    rep(i, 2, b) adj[i-1+a].pb(i+a);
    rep(i, 1, m) {
	cerr << (s>>i-1&1);
	if(!(s >> i-1 & 1)) {
	    adj[eu[i]].pb(ev[i]+a);
	} else {
	    adj[ev[i]+a].pb(eu[i]);
	}
    }
    cerr << "\n";
    rep(i, 1, a+b) if(!dfn[i]) tarjan(i);
    cerr << ans << "\n";
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> a >> b;
    cin >> m;
    rep(i, 1, m) cin >> eu[i] >> ev[i];
    int u = (1 << m) - 1;
    int res = 1e9;
    rep(s, 0, u) {
	res = min(res, getans(s));
    }
    cout << res << "\n";

    return 0;
}
