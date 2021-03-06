#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define rep(i, s, t) for(int i = (s); i <= (t); ++i)
#define per(i, s, t) for(int i = (t); i >= (s); --i)
#define fi first
#define se second
#define pb push_back
#define mp make_pair

const int N = 1e6 + 5;

int n, a[N];
int p[N], q[N];
bool vis[N], ins[N], has[N];
int ans;
vector<int> res;

inline void dfs1(int u) {
    vis[u] = 1;
    ins[u] = 1;
    if(!vis[a[u]]) {
	dfs1(a[u]);
	p[u] = a[u];
	q[a[u]] = u;
	++ans;
    } else if(!ins[a[u]] && !q[a[u]]) {
	p[u] = a[u];
	q[a[u]] = u;
	++ans;
    }
}

inline void dfsclear(int u) {
    ins[u] = 0;
    if(ins[a[u]]) dfsclear(a[u]);
}

inline void dfs2(int u) {
    if(q[u]) {
	dfs2(q[u]);
    }
    cout << u << " ";
    res.pb(u);
}

int main() {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    cin >> n;
    rep(i, 1, n) cin >> a[i], has[a[i]] = 1;
    //rep(i, 1, n) cerr << i << " -> " << a[i] << "\n";

    rep(i, 1, n) {
	if(!vis[i] && !has[i]) dfs1(i), dfsclear(i);
    }

    rep(i, 1, n) if(!vis[i]) dfs1(i), dfsclear(i);
    
    cout << ans << "\n";
    rep(i, 1, n) {
	if(!p[i]) dfs2(i);
    }
    cout << endl;

    int ans0 = 0;
    for(int i = 0; i < n - 1; ++i) if(res[i+1] == a[res[i]]) ++ans0;
    assert(ans == ans0);
    
    return 0;
}
